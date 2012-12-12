
import sys
import os
import re

sys.path.append(os.getcwd())

import mybuild_prot
from mybuild_prot import one_or_many
#from mybuild_prot import Integer, Boolean, String, List
from mybuild_prot import *

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
    global __package_tree, __package
    __package = name

    __package_tree.built_subpack(name)


def _build_obj(cls, name, args, kargs):
    global __package
    global __dirname
    global __modlist
    __modlist.append('.'.join ((__package, name)))
    mybuild_prot.obj_package(cls, __package_tree[__package], name, *args, **kargs)

def module(name, *args, **kargs):
    if kargs.has_key('sources'):
	kargs['sources'] = map (lambda s: Source(__dirname, s), kargs['sources'])
    _build_obj(mybuild_prot.Module, name, args, kargs)

def interface(name, *args, **kargs):
    _build_obj(mybuild_prot.Interface, name, args, kargs)

def include(name, opts={}):
    global __modconstr
    __modconstr.append((name, mybuild_prot.Domain([True])))
    for opt_name, value in opts.items():
	__modconstr.append(("%s.%s" % (name, opt_name), mybuild_prot.Domain([value])))

def exclude(name):
    pass

def lds_region(name, base, size):
    global __ld_defs
    __ld_defs.append('LDS_REGION_BASE_%s=%s' % (name, base))
    __ld_defs.append('LDS_REGION_SIZE_%s=%s' % (name, size))

def lds_section_load(name, vma, lma):
    global __ld_defs
    __ld_defs.append('LDS_SECTION_VMA_%s=%s' % (name, vma))
    __ld_defs.append('LDS_SECTION_LMA_%s=%s' % (name, lma))

def lds_section(name, reg):
    lds_section_load(name, reg, reg)


def mybuild_main(argv):
    import os
    rootpkg = mybuild_prot.Package('root', None)
    allmodlist = []
    scope = mybuild_prot.Scope()

    glob = globals()

    glob['__package_tree'] = rootpkg
    glob['__modlist'] = allmodlist

    for arg in argv:
	for dirpath, dirnames, filenames in os.walk(arg):
	    for file in filenames:
		if file.endswith('.py') or file == 'Pybuild':
		    glob['__dirname'] = dirpath
		    execfile(os.path.join(dirpath, file), glob)

    #print rootpkg
    #print
    #print glob['__modlist']

    conf = 'pyconf/conf.py'

    glob['__scope'] = scope

    modlst = map(lambda name: glob['__package_tree'][name], glob['__modlist'])
    #print 
    #print modlst
    mybuild_prot.add_many(scope, modlst)

    glob['__modconstr'] = []

    execfile(conf, glob)

    modconstr = map(lambda (name, dom): (rootpkg[name], dom), glob['__modconstr'])

    #print 
    #print modconstr

    cut_scope = mybuild_prot.cut_many(scope, modconstr)
    final = mybuild_prot.fixate(cut_scope)
    #print
    #print final

    return final

from waflib.TaskGen import feature, after
from waflib import TaskGen, Task
from waflib import Utils

@TaskGen.extension('.lds.S')
def lds_s_hook(self, node):
    tgtnode = node.change_ext('.lds', '.lds.S')
    self.env['DEFINES'] = self.defines
    return self.create_task('lds_s', node, tgtnode)

class lds_s(Task.Task):
    run_str = '${CC} ${ARCH_ST:ARCH} ${CFLAGS} ${CPPFLAGS} ${FRAMEWORKPATH_ST:FRAMEWORKPATH} ${CPPPATH_ST:INCPATHS} ${DEFINES_ST:DEFINES} ${CC_SRC_F}${SRC} -E -P -o ${TGT}'
    ext_out = ['.lds'] # set the build order easily by using ext_out=['.h']

@feature('module_header')
def header_gen(self):
    header = '''
#ifndef {GUARD}
#define {GUARD}

{INCLUDES}

{OPTIONS}

#endif /* {GUARD} */
'''
    options = []
    for name, opt in self.mod.items():
	repr = ''
	if isinstance(opt, mybuild_prot.Integer):
	    repr = 'NUMBER'
	elif isinstance(opt, mybuild_prot.Boolean):
	    repr = 'BOOLEAN'
	elif isinstance(opt, mybuild_prot.String):
	    repr = 'STRING'
	else:
	   continue

	options.append('OPTION_%s_%s %s' % (repr, opt.qualified_name().replace('.', '__'),
	    self.scope[opt].value()))

    includes = []
    
    if isinstance(self.mod, mybuild_prot.Interface):
	for impl in self.scope[self.mod]:
	    for src in impl.sources:
		if re.match('.*\.h', src.filename):
		    includes.append(src.fullpath())

    hdr = header.format(GUARD=self.mod.qualified_name().replace('.', '_').upper(),
	OPTIONS=''.join(map(lambda str: '#define %s\n\n' %(str,), options)),
	INCLUDES=''.join(map(lambda str: '#include __impl_x(%s)\n\n' % (str,), includes)))

    self.rule = lambda self: self.outputs[0].write(hdr)

def waf_layer(bld):

    final = mybuild_main(['src'])   

    lds_conf = 'pyconf/lds.py'

    glob = globals()

    glob['__ld_defs'] = []

    execfile(lds_conf, glob)

    bld.env._ld_defs = glob['__ld_defs']

    for opt, dom in final.items():
	need_header = isinstance(opt, mybuild_prot.Interface)

	if (isinstance(opt, mybuild_prot.Module) and dom == mybuild_prot.Domain([True])):
	    need_header |= True

	    for src in opt.sources:
		src.build(bld, opt, final) 

	if need_header:
	    bld(features = 'module_header',
		target = 'include/module/%s.h' % (opt.qualified_name().replace('.','/'),),
		mod = opt,
		scope = final)


    bld(
	features = 'c cprogram',
	target = bld.env.target,
	includes = bld.env.includes,
	linkflags = bld.env.LDFLAGS,
	use = 'generated objects ldscripts',
    )

if __name__ == '__main__':
    import sys
    mybuild_main(sys.argv[1:])
