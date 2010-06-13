/**
 * @file
 * @brief TODO
 *
 * @date 13.06.2010
 * @author Eldar Abusalimov
 */

#ifndef UTIL_ARRAY_H_
# error "Do not include this file directly, use <util/array.h> instead!"
#endif /* UTIL_ARRAY_H_ */

#include <util/macro.h>
#include <util/guard.h>

/*
 * For each diffuse array three sections are created. These sections are then
 * placed together successively each after each.
 */

/* The array symbol is placed in HEAD section. */
#define __ARRAY_DIFFUSE_SECTION_HEAD(s_array) \
		__ARRAY_DIFFUSE_SECTION(s_array, 0, head)

/* BODY hosts the array elements. */
#define __ARRAY_DIFFUSE_SECTION_BODY(s_array) \
		__ARRAY_DIFFUSE_SECTION(s_array, 1, body)

/* Contains the array end marker and terminator element (if any). */
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

/* Each array entry is placed in a variable with following name. */
#define __ARRAY_DIFFUSE_ENTRY(s_array, s_guard) \
	GUARD_SUFFIX(__array_diffuse_entry__##s_array##__##s_guard)

#define __ARRAY_DIFFUSE_ENTRY_DEF(s_array, s_guard, _section) \
	static typeof(s_array[0]) __ARRAY_DIFFUSE_ENTRY(s_array, s_guard) \
		__attribute__ ((used, section(_section)))

/* Marker is just zero-size variable. Prefix prevents namespace pollution. */
#define __ARRAY_DIFFUSE_MARKER(s_array, s_guard) \
	GUARD_SUFFIX(__array_diffuse_entry__##s_array##__##s_guard)

#define __ARRAY_DIFFUSE_MARKER_DEF(type, s_array, s_guard, _section) \
		__ARRAY_DIFFUSE_MARKER_RAW_DEF(type, \
			__ARRAY_DIFFUSE_MARKER(s_array, s_guard), _section)

#define __ARRAY_DIFFUSE_MARKER_RAW_DEF(type, s_marker, _section) \
	__extension__ type s_marker[0] __attribute__ ((used, section(_section)))

/* Common part included in each array definition. */
#define __ARRAY_DIFFUSE_COMMON_DEF(element_type, array_name) \
		__ARRAY_DIFFUSE_MARKER_RAW_DEF(element_type, array_name, \
				__ARRAY_DIFFUSE_SECTION_HEAD(array_name))

/* Here goes API implementation. */

#define __ARRAY_DIFFUSE_DEF(element_type, array_name) \
		__ARRAY_DIFFUSE_COMMON_DEF(element_type, array_name); \
		__ARRAY_DIFFUSE_MARKER_DEF(element_type, array_name, tail, \
				__ARRAY_DIFFUSE_SECTION_TAIL(array_name))

#define __ARRAY_DIFFUSE_DEF_TERMINATED(element_type, array_name, terminator) \
		__ARRAY_DIFFUSE_COMMON_DEF(element_type, array_name); \
		__ARRAY_DIFFUSE_ENTRY_DEF(array_name, tail, \
				__ARRAY_DIFFUSE_SECTION_TAIL(array_name)) = terminator

#define __ARRAY_DIFFUSE_DEF_STATIC(element_type, array_name) \
		__ARRAY_DIFFUSE_DEF(static element_type, array_name)

#define __ARRAY_DIFFUSE_DEF_TERMINATED_STATIC(element_type, name, terminator) \
		__ARRAY_DIFFUSE_DEF_TERMINATED(static element_type, name, terminator)

#define __ARRAY_DIFFUSE_ADD(array_name, element) \
	__ARRAY_DIFFUSE_ENTRY_DEF(array_name, TODO, \
			__ARRAY_DIFFUSE_SECTION_BODY(array_name)) = element

