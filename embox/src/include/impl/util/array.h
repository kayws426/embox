/**
 * @file
 * @brief Implements distributed arrays backed by linker section SORT facility.
 *
 * @date 13.06.2010
 * @author Eldar Abusalimov
 */

#ifndef UTIL_ARRAY_H_
# error "Do not include this file directly, use <util/array.h> instead!"
#endif /* UTIL_ARRAY_H_ */

#include <stddef.h>

#include <util/macro.h>

/*
 * For each diffuse array four sections are created. These sections are then
 * placed together strictly successively each after each.
 */

/* The symbol for the array name is placed in head section. */
#define __ARRAY_DIFFUSE_SECTION_HEAD(s_array) \
		__ARRAY_DIFFUSE_SECTION(s_array, 0, head)

/* Body hosts the array elements (excepting terminator, if any). */
#define __ARRAY_DIFFUSE_SECTION_BODY(s_array) \
		__ARRAY_DIFFUSE_SECTION(s_array, 1, body)

/* Contains terminator element (if any). */
#define __ARRAY_DIFFUSE_SECTION_TERM(s_array) \
		__ARRAY_DIFFUSE_SECTION(s_array, 8, term)

/* Contains the array end marker. */
#define __ARRAY_DIFFUSE_SECTION_TAIL(s_array) \
		__ARRAY_DIFFUSE_SECTION(s_array, 9, tail)

/*
 * All array_diffuse-related sections are linked using something
 * like *(SORT(.array_diffuse.*.rodata)). SORT guarantees that the wildcard is
 * expanded in the lexicographical order.
 */

/* Order argument is used to control the relative placement of sections within
 * a particular array.
 * Tag is just appended to the name of section (in debugging purposes). */
#define __ARRAY_DIFFUSE_SECTION(s_array, order, tag) \
	".array_diffuse." MACRO_STRING(s_array##_##order##_##tag) ".rodata"

/* Every array entry, group of entries or marker symbols are backed by an
 * individual array (empty for markers) defined as follows. */
#define __ARRAY_DIFFUSE_ENTRY_DEF(type, s_entry, sect) \
	/* __extension__ bypasses compiler warnings about empty arrays. */ \
	__extension__ const type s_entry[] __attribute__ ((used, section(sect)))

/* Diffuse arrays implementation-private entries are named as follows
 * to prevent namespace pollution. */
#define __ARRAY_DIFFUSE_PRIVATE(s_array, s_tag) \
	__array_diffuse__##s_array##__##s_tag

#define __ARRAY_DIFFUSE_PRIVATE_DEF(type, s_array, s_tag, section) \
	__ARRAY_DIFFUSE_ENTRY_DEF(type, \
		__ARRAY_DIFFUSE_PRIVATE(s_array, s_tag), section)

/* Here goes API implementation. */

/* Diffuse definition. */

#define __ARRAY_DIFFUSE_DEF(element_type, array_name) \
	__ARRAY_DIFFUSE_DEF_TERMINATED(element_type, array_name, /* empty */)

#define __ARRAY_DIFFUSE_DEF_TERMINATED(element_type, array_name, terminator) \
	__ARRAY_DIFFUSE_ENTRY_DEF(element_type, array_name, \
		__ARRAY_DIFFUSE_SECTION_HEAD(array_name)) = { /* empty */ }; \
	__ARRAY_DIFFUSE_PRIVATE_DEF(element_type, array_name, term, \
		__ARRAY_DIFFUSE_SECTION_TERM(array_name)) = { terminator }; \
	__ARRAY_DIFFUSE_PRIVATE_DEF(element_type, array_name, tail, \
		__ARRAY_DIFFUSE_SECTION_TAIL(array_name)) = { /* empty */ }

/* Diffuse element addition. */

#define __ARRAY_DIFFUSE_ADD(array_name, ...) \
	__ARRAY_DIFFUSE_ADD_NAMED(array_name, \
		MACRO_GUARD(__ARRAY_DIFFUSE_PRIVATE(array_name, entry)), \
		__VA_ARGS__)

#define __ARRAY_DIFFUSE_ADD_NAMED(array_name, ptr_name, ...) \
	__ARRAY_DIFFUSE_ENTRY_DEF(static typeof(*(array_name)), ptr_name, \
		__ARRAY_DIFFUSE_SECTION_BODY(array_name)) = { __VA_ARGS__ }

/* Diffuse size calculations. */

#define __ARRAY_DIFFUSE_SIZE(array_name) \
		__ARRAY_DIFFUSE_SIZE_MARKER(array_name, tail)

#define __ARRAY_DIFFUSE_SIZE_IGNORE_TERMINATING(array_name) \
		__ARRAY_DIFFUSE_SIZE_MARKER(array_name, term)

#define __ARRAY_DIFFUSE_SIZE_MARKER(array_name, marker) __extension__ ({ \
		extern typeof(array_name) __ARRAY_DIFFUSE_PRIVATE(array_name,marker); \
		(size_t) (__ARRAY_DIFFUSE_PRIVATE(array_name, marker) - array_name);  \
	})

/* Static array size. */

#define __ARRAY_SIZE(array) \
	(sizeof(array) / sizeof(*(array)))

#define __array_static_foreach_ptr(element_ptr, array) \
		__array_foreach_ptr(element_ptr, array, ARRAY_SIZE(array))

#define __array_nullterm_foreach_ptr(element_ptr, array) \
		__array_cond_foreach_ptr(element_ptr, array, (element_ptr) != NULL)

#define __array_foreach_ptr(element_ptr, array, size) \
		__array_cond_foreach_ptr(element_ptr, array,  \
				(element_ptr) < (array) + (size))

#define __array_cond_foreach_ptr(element_ptr, array, condition) \
	for ((element_ptr) = (array); (condition); ++(element_ptr))

#define __array_foreach(element, array) \
		__array_foreach_element(element, array, \
				MACRO_GUARD(__array_foreach_element_ptr))

#define __array_foreach_element(element, array, element_ptr) \
	for(typeof(element) *element_ptr = __extension__ ({ \
				(element) = *(array); (array); \
			}); \
		(element) != NULL; (element) = *(++element_ptr))
