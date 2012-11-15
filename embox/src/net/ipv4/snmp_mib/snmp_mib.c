/**
 * @file
 * @brief SNMP MIB operations
 *
 * @date 9.11.2012
 * @author Alexander Kalmuk
 */

#include <mem/objalloc.h>
#include <errno.h>
#include <string.h>
#include <framework/mod/options.h>
#include <net/mib.h>
#include <embox/unit.h>
#include <util/array.h>
#include <embox/cmd.h>

EMBOX_CMD(mib_init);

ARRAY_SPREAD_DEF(const struct mib_obj_register *, __mib_register);
OBJALLOC_DEF(mib_obj_pool, struct mib_obj, OPTION_GET(NUMBER, max_obj_count));

struct mib_obj mib_root;

static mib_obj_t getchild_by_id(mib_obj_t obj, unsigned char id);

int mib_obj_link(mib_obj_t obj, mib_obj_t parent) {
	assert(obj != NULL);
	assert(parent != NULL);

	dlist_head_init(&obj->parent_link);
	dlist_add_prev(&obj->parent_link, &parent->children);

	return ENOERR;
}

mib_obj_t mib_obj_alloc(void) {
	mib_obj_t obj = objalloc(&mib_obj_pool);

	if (!obj) {
		return NULL;
	}

	dlist_init(&obj->children);

	return obj;
}

#if 0
void mib_obj_unlink(mib_obj_t obj) {
	assert(obj != NULL);
	dlist_del(&obj->parent_link);
}
#endif

mib_obj_t mib_obj_getbyoid(const char *oid, unsigned char len) {
	mib_obj_t cur = &mib_root;

	while ((len--) > 0) {
		unsigned char id = *oid;

		cur = getchild_by_id(cur, id);
		if (!cur) {
			break;
		}
		oid++;
	}

	return cur;
}

mib_obj_t mib_obj_addbyoid(const char *oid, unsigned char len) {
	mib_obj_t cur = &mib_root;
	mib_obj_t prev = cur;

	while ((len--) > 0) {
		unsigned char id = *oid;

		cur = getchild_by_id(cur, id);
		if (!cur) {
			cur = mib_obj_alloc();
			cur->id = id;
			mib_obj_link(cur, prev);
		}
		prev = cur;
		oid++;
	}

	return cur;
}

static mib_obj_t getchild_by_id(mib_obj_t obj, unsigned char id) {
	mib_obj_t cur, nxt;

	dlist_foreach_entry(cur, nxt, &obj->children, parent_link) {
		if (cur->id == id) {
			break;
		}
	}

	return (&cur->parent_link == &obj->children ? NULL : cur);
}

static int mib_init(int argc, char **argv) {
	const struct mib_obj_register *reg;

	dlist_init(&mib_root.children);
	mib_root.name = "root";

	array_foreach(reg, __mib_register, ARRAY_SPREAD_SIZE(__mib_register)) {
		reg->init();
	}

	return 0;
}
