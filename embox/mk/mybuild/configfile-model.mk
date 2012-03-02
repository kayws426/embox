# Generated by Xpand using M2Make template.

# Model of 'configFile' package.

ifndef __mybuild_configfile_model_mk
__mybuild_configfile_model_mk := 1

include mk/model/model_impl.mk

#
# Model object 'FileContent'.
#
# The following features are defined:
#   - reference 'configurations'
#   - attribute 'imports'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-CfgFileContent
	# Extends 'ENamedObject' class.
	$(eobject ConfigFile_FileContent,
		CfgFileContent,ENamedObject,)

	# Property 'configurations... : CfgConfiguration'.
	$(eobject-reference ConfigFile_FileContent_configurations,
		configurations,CfgConfiguration,fileContent,changeable many containment)

	# Property 'imports...'.
	$(eobject-attribute ConfigFile_FileContent_imports,
		imports,changeable many)

	# PROTECTED REGION ID(FileContent) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'Configuration'.
#
# The following features are defined:
#   - reference 'fileContent'
#   - reference 'includes'
#
# The following features and operations are inherited from 'ENamedObject':
#   - attribute 'name'
#   - attribute 'qualifiedName'
#   - attribute 'origin'
#   - operation 'eInverseResolvedLinks'
#
define class-CfgConfiguration # abstract
	# Extends 'ENamedObject' class.
	$(eobject ConfigFile_Configuration,
		CfgConfiguration,ENamedObject,abstract)

	# Property 'fileContent : CfgFileContent'.
	$(eobject-reference ConfigFile_Configuration_fileContent,
		fileContent,CfgFileContent,configurations,changeable container)

	# Property 'includes : CfgInclude'.
	$(eobject-reference ConfigFile_Configuration_includes,
		includes,CfgInclude,,changeable containment)

	# PROTECTED REGION ID(Configuration) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'Include'.
#
# The following features are defined:
#   - reference 'module'
#   - reference 'optionBindings'
#
define class-CfgInclude
	$(eobject ConfigFile_Include,
		CfgInclude,,)

	# Property 'module : MyModule'.
	# Property 'module_link : ELink'.
	$(eobject-reference ConfigFile_Include_module,
		module,MyModule,,changeable linkable)

	# Property 'optionBindings... : CfgOptionBinding'.
	$(eobject-reference ConfigFile_Include_optionBindings,
		optionBindings,CfgOptionBinding,,changeable many containment)

	# PROTECTED REGION ID(Include) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

#
# Model object 'OptionBinding'.
#
# The following features are defined:
#   - attribute 'value'
#
define class-CfgOptionBinding
	$(eobject ConfigFile_OptionBinding,
		CfgOptionBinding,,)

	# Property 'value'.
	$(eobject-attribute ConfigFile_OptionBinding_value,
		value,changeable)

	# PROTECTED REGION ID(OptionBinding) ENABLED START
#	# TODO Add custom implementation here and remove this comment.
	# PROTECTED REGION END
endef

$(def_all)

endif # __mybuild_configfile_model_mk

