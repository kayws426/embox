/**
 * @file
 * @brief Implementation private types used by mods infrastructure.
 *
 * @date 12.06.10
 * @author Eldar Abusalimov
 */

#ifndef FRAMEWORK_MOD_TYPES_H_
#define FRAMEWORK_MOD_TYPES_H_

#include <stddef.h>

struct mod;
struct mod_package;
struct __mod_private;

struct mod_info;
struct mod_extra;
struct mod_member;

struct mod {
	/** Null-terminated array with dependency information. */
	const struct mod **requires, **provides; /**< Modules, that this module depends on;
                                                  which are dependent on this. */
	const struct mod **after_deps; /**< Should be loaded right after this. */
	const struct mod **contents;  /**< Contained in this module. */

	/* Descriptive information about the module provided by Embuild. */

	const struct mod_package *package; /**< Definition package. */
	const char *name;                  /**< Name assigned by EMBuild. */

	/* Data used to properly enable/disable the module itself. */

	const struct mod_info    *info;    /**< (optional) Application specific. */
	const struct mod_extra   *extra;   /**< (optional) Application specific. */
	const struct mod_member **members; /**< Members to setup/finalize. */
	struct __mod_private     *priv; /**< Used by dependency resolver. */

};

struct mod_extra {
	char  *data;
	size_t data_sz;
	char  *bss;
	size_t bss_sz;
	const char *brief;
	const char *details;
};

struct mod_package {
	const char *name; /**< Package name assigned by EMBuild. */
};

struct __mod_private {
	unsigned int flags;
};

#endif /* FRAMEWORK_MOD_TYPES_H_ */
