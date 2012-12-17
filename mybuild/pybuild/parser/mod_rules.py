
from .. package import Package, obj_in_pkg
from .. module  import Module
from .. interface import Interface
from .. option import *

class Annotation():
    def __init__(self):
	pass

def annotated(obj, annot):
    try:
	obj.annots.append(annot)
	return obj
    except Exception, ex:
	class AnnotHolder(obj.__class__):
	    pass
	new_obj = AnnotHolder(obj)
	new_obj.annots = [annot]
	return new_obj

class NoRuntimeAnnotation(Annotation):
    pass

class SourceAnnotation(Annotation):
    pass

class LDScriptAnnotation(SourceAnnotation):
    def build(self, bld, source, mod, scope):
	tgt = source.replace('.lds.S', '.lds')
	bld.env.append_value('LINKFLAGS', '-Wl,-T,%s' % (tgt,))
	bld(
	    name = 'ldscripts',
	    features = 'includes',
	    source = source,
	    includes = bld.env.includes,
	    defines = bld.env._ld_defs,
	)
	return tgt

class GeneratedAnnotation(SourceAnnotation):
    def __init__(self, rule):
	self.rule = rule
    def build(self, bld, source, mod, scope):
	print 'generate %s' % (source, )
	tgt = source
	bld(
	    rule = lambda f: f.outputs[0].write(self.rule(mod, scope)),
	    target = tgt
	)
	return tgt

def NoRuntime(obj):
    return annotated(obj, NoRuntimeAnnotation())

def LDScript(obj):
    return annotated(obj, LDScriptAnnotation())

def Generated(obj, rule):
    return annotated(obj, GeneratedAnnotation(rule))

class Source(object):
    def __init__(self, dirname, filename):
	self.dirname = dirname
	self.filename = filename

    def __repr__(self):
	return "Source('%s/%s')" % (self.dirname, self.filename)

    def fullpath(self):
	return os.path.join(self.dirname, self.filename)

    def annotations(self):
	anns = getattr(self.filename, 'annots', [])
	print 'annotations of %s is %s' % (self, anns)
	return anns

    def build(self, bld, opt, scope):
	f = self.fullpath()
	cnt = 0
	for ann in self.annotations():
	    f = ann.build(bld, f, opt, scope)

	if re.match('.*\.c', f):	
	    bld.objects(
		source = f,
		target = 'objects',
		defines = ['__EMBUILD_MOD__'],
		includes = bld.env.includes,
	    )
	    f = f.replace('.c', '.o')
    
	return f


def package(name):
    global package_name
    package_name = name

    import build_ctx
    ctx = build_ctx

    ctx.root.built_subpack(name)


def _build_obj(cls, name, args, kargs):
    global package_name
    
    import build_ctx
    ctx = build_ctx
    ctx.modlist.append('.'.join ((package_name, name)))
    obj_in_pkg(cls, ctx.root[package_name], name, *args, **kargs)

def module(name, *args, **kargs):
    import build_ctx
    ctx = build_ctx
    if kargs.has_key('sources'):
	kargs['sources'] = map (lambda s: Source(ctx.dirname, s), kargs['sources'])
    _build_obj(Module, name, args, kargs)

def interface(name, *args, **kargs):
    _build_obj(Interface, name, args, kargs)

