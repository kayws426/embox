
import unittest
import operator
import itertools

def get_all_options(obj):
    option_set = set()
    for mod in [obj] + obj.supers():
	option_set |= set(mod.options.keys())
    return option_set

def isiter(obj):
    if isinstance(obj, BaseScope):
	return False

    try:
	t = [e for e in obj]
	return True
    except TypeError:
	return False

def one_or_many(obj):
    return obj if isiter(obj) else [obj]

class Option:
    def __init__(self, name='', mod=None, value=None):
	self.name = name
	self.value = value
	self.mod = mod

    def trigger(self, scope, domain):
	pass

class Domain(frozenset):
    def value(self):
	if len(self) == 1:
	    for v in self:
		return v
	return None
    
    def force_value(self):
	for v in sorted(self):
	    return v

class Inherit():
    def __init__(self, super=None):
	self.super = super

    def supers(self):
	if self.super:
	    return [self.super] + self.super.supers()
	return []

class BaseScope(dict):
    def __init__(self, parent=None):
	self.parent = parent
	
    def __getitem__(self, x):
	if dict.has_key(self, x):
	    return dict.__getitem__(self, x)
	elif self.parent:
	    return self.parent[x]
	else:
	    raise AttributeError

    def __len__(self):
	par = 0
	if self.parent:
	    par = len(self.parent)
	return dict.__len__(self) + par

    def keys(self):
	par_keys = ()
	if self.parent: 
	    par_keys = self.parent.keys()

	return itertools.chain(dict.keys(self), par_keys)

    def items(self):
	par_items = ()
	if self.parent: 
	    par_keys = self.parent.items()

	return itertools.chain(dict.items(self), par_items)

    def has_key(self, k):
	return k in self.keys()

class Scope(BaseScope):
    def __repr__(self):
	return 'Scope {' + \
	    reduce (operator.add, map(lambda x: "\t%s: %s" % x, self.items()), "")

class Module(Option, Inherit, BaseScope):
    def __init__(self, name, options={}, super=None, implements=(), depends=(), tunings=()):
	self.parent = super
	self.name = name
	self.id = name + ".__include_mod" # actually, this is option
	self.tunings = tunings

	if not isiter(depends):
	    self.depends = ((depends, {}),)
	else:
	    self.depends = []
	    for d in depends:
		if not isiter(d):
		    self.depends.append((d, {}))
		else:
		    self.depends.append(d)

	self.implements = one_or_many(implements)

	dict.__setitem__(self, self, Domain([True, False]))

	for o, d in options.items():
	    dict.__setitem__(self, o, d)

    def trigger(self, scope, domain):
	for dep, opts in self.depends:
	    cut(scope, dep, Domain([True]))
	    for opt, d in opts.items():
		cut(scope, opt, d)

    def implements(self):
	def get_impl(obj):
	    return [obj] + [get_impl(impl) for impl in obj.implements]

	return get_impl(self)[1:]	

    def option_val(self, scope, option_name):
	try:
	    return scope[self[option_name]]
	except:
	    return self[option_name].value
	    
    def is_list(self):
	return self.implements

    def __repr__(self):
	return "<Module %s, depends %s>" % (self.name, self.depends)

    def subeval(self, scope):
	new_scope = scope

	res = True
	for tuning in self.tunings:
	    ret = tuning.tuning(new_scope)
	    if isinstance(ret, Scope):
		new_scope = ret
	    elif not ret:
		return False

	res = True
	for dep, opts in self.depends:
	    res &= new_scope.eval(dep, opts)

	return res

    def __hash__(self):
	return self.id.__hash__()

class Interface(Inherit):
    def __init__(self, name, super=()):
	self.name = name
	self.id = name + ".__include_mod" 
	self.super = one_or_many(super)

    def is_list(self):
	return oneself.supers()

    def inst(self):
	return Instanse(self)

    def subeval(self, scope):
	return True

    def __repr__(self):
	return "Interface '" + self.name + "'"

class CutConflictException(BaseException):
    pass

def add_many(scope, ents):
    for ent in ents:
	add_step(scope, ent)

def add_step(scope, ent, options = {}):

    for o, d in ent.items():
	if scope.has_key(o):
	    raise Exception
	scope[o] = d 

    for o, d in options.items():
	cut(scope, o, d)

    return scope

def try_add_step(scope, ent, options = {}):

    new_scope = Scope(scope)

    try:
	add_step(new_scope, ent, options)
    except CutConflictException:
	return False

    return new_scope

def cut(scope, opt, domain):
    strict_domain = scope[opt] & domain
    if strict_domain:
	scope[opt] = strict_domain
	opt.trigger(scope, strict_domain)
    else:
	raise CutConflictException("%s option with %s domain cutting down with %s" % (opt, scope[opt], domain))
    
def fixate(scope):
    new_scope = Scope(scope)

    for k, v in scope.items():
	new_scope[k] = v.force_value()

    return new_scope

class TestCase(unittest.TestCase):
    def test_recursive_feature_add(self):
	blck = Module('module block')
	stdio = Module('module stdio')
	fs = Module('module FS', depends=(blck, stdio))
	test = Module('test')
	test2 = Module('test2', depends=test)
	test3 = Module('test3')

	scope = Scope()
	add_many(scope, [blck, stdio, fs, test2, test, test3])

	cut(scope, fs, Domain([True]))
	cut(scope, test2, Domain([True]))

	final = fixate(scope)

	self.assertTrue(final[blck])
	self.assertTrue(final[stdio])
	self.assertTrue(final[fs])
	self.assertTrue(final[test])
	self.assertTrue(final[test2])
	self.assertFalse(final[test3])

    def test_depends_with_options(self):
	stack_sz_opt = Option('stack_sz')
	stack_lds = Module("stack", options = {stack_sz_opt : Domain(range(8192,1000000))})
	thread_core = Module("thread_core", depends = (
	    (stack_lds, {stack_sz_opt : Domain([16000])}),))

	scope = Scope()
	add_many(scope, [stack_lds, thread_core])

	cut(scope, thread_core, Domain([True]))

	final = fixate(scope)

	self.assertTrue(final[thread_core])
	self.assertTrue(final[stack_lds])
	self.assertEqual(final[stack_sz_opt], 16000)

    def test_depends_with_options(self):
	stack_sz_opt = Option('stack_sz')
	stack_lds = Module("stack", options = {stack_sz_opt : Domain(range(8192,12000))})
	thread_core = Module("thread_core", depends = (
	    (stack_lds, {stack_sz_opt : Domain([16000])}),))

	scope = Scope()
	add_many(scope, [stack_lds, thread_core])

	self.assertRaises(CutConflictException, cut, scope, thread_core, Domain([True]))

    @unittest.expectedFailure 
    def test_interface(self):
	timer_api = Interface("Timer api")
	head_timer = Module("Head timer", implements=timer_api)

	scope = try_add_step(Scope(), head_timer)
	self.assertEqual(scope[timer_api], scope[head_timer])

    @unittest.expectedFailure 
    def test_options(self):
	timer_api = Interface("Timer api")
	head_timer = Module("Head timer", implements=timer_api, options = {'timer_nr' : 32, 'impl_name' : None})
	rt = Module("Hard realtime head timer", implements=timer_api, super=head_timer, options={'impl_name' : "rt timer"})

	scope = try_add_step(Scope(), rt)
	scope = try_add_step(scope, head_timer, options = {'timer_nr' : 64})

	self.assertEqual(rt.option_val(scope, 'timer_nr'),	    64)
	self.assertEqual(rt.option_val(scope, 'impl_name'),	    "rt timer")
	self.assertEqual(head_timer.option_val(scope, 'impl_name'), None)

    @unittest.expectedFailure 
    def test_options_error(self):
	timer = Module("Head timer", options = {'timer_nr' : 32})
	self.assertRaises(AttributeError, try_add_step, Scope(), timer, options = {'inobviously incorrect name' : 32 })

    @unittest.expectedFailure 
    def test_constraints(self):
	stack_lds = Module("stack", options = {'stack_sz' : 1024})
	tunings = [Tuning(stack_lds, None, lambda scope: ent.option_val(scope, 'stack_sz') > 4096)]

	thread_core = Module("thread_core", tunings=tunings)

	scope = try_add_step(Scope(), stack_lds)
	self.assertTrue(False != scope[stack_lds])
	scope = try_add_step(scope, thread_core)
	self.assertRaises(AttributeError, scope.__getitem__, thread_core)

    @unittest.expectedFailure 
    def test_constraints_unordered(self):
	stack_lds = Module("stack", options = {'stack_sz' : 8192})
	tunings = [Tuning(stack_lds, None, lambda scope: ent.option_val(scope, 'stack_sz') > 4096)]

	thread_core = Module("thread_core", tunings=tunings)

	scope = try_add_step(Scope(), thread_core)
	scope = try_add_step(scope, stack_lds)
	self.assertTrue(False != scope[thread_core])
	self.assertTrue(False != scope[stack_lds])

    def test_interfer_options(self):
	pass

    def test_cond_depends(self):
	pass

    def test_scope_pred(self):
	scope = Scope()
	self.assertTrue(scope != False)
	scope = Scope(scope)
	self.assertTrue(scope != False)


if __name__ == '__main__':
    unittest.main()
