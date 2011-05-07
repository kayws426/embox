/**
 * @file
 * @brief EMBuild-side binding interface.
 *
 * @date 12.06.10
 * @author Eldar Abusalimov
 */

#ifndef FRAMEWORK_MOD_EMBUILD_H_
#define FRAMEWORK_MOD_EMBUILD_H_

#include __impl_x(framework/mod/embuild_impl.h)

/**
 * Defines a new mod. For the new mod the @link #mod corresponding @endlink
 * structure is allocated. Also two section-driven arrays are defined for the
 * mod#provides and mod#requires lists.
 *
 * @param mod_nm
 *   The variable name used later to access the mod structure with #MOD_PTR(),
 *   to define dependencies with #MOD_DEP_DEF(), or to bind mod-specific
 *   @link #__mod_info information @endlink using #MOD_INFO_DEF() macro and its
 *   derivatives. For the code generated by EMBuild this argument must be the
 *   same as provided by the __EMBUILD_MOD__ macro for each mod at compilation
 *   time.
 * @param mod_package_nm
 *   The package variable name used in #MOD_PACKAGE_DEF().
 * @param mod_name
 *   A string containing the mod name. The name of the current mod (referenced
 *   by __EMBUILD_MOD__) is available at compilation time using #MOD_SELF_NAME
 *   macro.
 * @param brief
 *   A one-line string containing brief description of the mod.
 * @param details
 *   A string with detailed description.
 */
#define MOD_DEF(mod_nm, mod_package_nm, mod_name, brief, details) \
		__MOD_DEF(mod_nm, mod_package_nm, mod_name, brief, details)

/**
 * Defines a new dependency between two specified modules.
 *
 * @param mod_nm
 *   Symbol name of the module which depends on @a dep_nm.
 * @param dep_nm
 *   Symbol name of the module on which @a mod_nm depends.
 */
#define MOD_DEP_DEF(mod_nm, dep_nm) \
		__MOD_DEP_DEF(mod_nm, dep_nm)

/**
 * Defines a new package.
 *
 * @param package_nm
 *   Variable name to use.
 * @param package_name
 *   A string containing the package name.
 */
#define MOD_PACKAGE_DEF(package_nm, package_name) \
		__MOD_PACKAGE_DEF(package_nm, package_name)

#endif /* FRAMEWORK_MOD_EMBUILD_H_ */
