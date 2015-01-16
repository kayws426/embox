/**
 * @file
 *
 * @brief An implementation of 'hashtable' interface
 *
 * @date 30.09.11
 *
 * @author Dmitry Zubarevich
 * @author Avdyukhin Dmitry
 * @author Anton Bondarev
 */

#include <errno.h>
#include <string.h>

#include <util/hashtable.h>
#include <util/dlist.h>


#include <mem/objalloc.h>


#include <framework/mod/options.h>

#if 0
#define CONFIG_HASHTABLE_ELEM_QUNTITY  OPTION_GET(NUMBER,item_quntity)

OBJALLOC_DEF(ht_elem_pool, struct hashtable_item,
		CONFIG_HASHTABLE_ELEM_QUNTITY * 16);

#endif

struct hashtable *hashtable_create(struct hashtable *ht, size_t table_size,
		ht_hash_ft get_hash, ht_cmp_ft cmp) {

	ht->table = (struct hashtable_entry *)(ht + 1);

	memset(ht->table, 0, table_size * sizeof(struct hashtable_entry));

	ht->get_hash_key = get_hash;
	ht->table_size = table_size;
	ht->cmp = cmp;
	dlist_init(&ht->all);

	return ht;
}
struct hashtable_item *hashtable_item_init(struct hashtable_item *ht_item,
		void *key, void *value) {

	assert(ht_item);

	ht_item->key = key;
	ht_item->value = value;

	dlist_head_init(&ht_item->lnk);

	return ht_item;
}
#if 0
int hashtable_put(struct hashtable *ht, void *key, void *value) {
	size_t idx;
	struct hashtable_item *htel;

	assert(ht);

	if (NULL == (htel = objalloc(&ht_elem_pool))) {
		return -ENOMEM;
	}
	htel->key = key;
	htel->value = value;

	idx = ht->get_hash_key(key) % ht->table_size;
	if (0 == ht->table[idx].cnt) {
		dlist_init(&ht->table[idx].list);
	}

	ht->table[idx].cnt ++;
	dlist_add_next(dlist_head_init(&htel->lnk), &ht->table[idx].list);

	dlist_add_prev(dlist_head_init(&htel->general_lnk), &ht->all);

	return ENOERR;
}
#endif

int hashtable_put(struct hashtable *ht, struct hashtable_item *ht_item) {
	size_t idx;

	assert(ht);
	assert(ht_item);

	idx = ht->get_hash_key(ht_item->key) % ht->table_size;
	if (0 == ht->table[idx].cnt) {
		dlist_init(&ht->table[idx].list);
	}

	ht->table[idx].cnt ++;
	dlist_add_next(&ht_item->lnk, &ht->table[idx].list);

	dlist_add_prev(dlist_head_init(&ht_item->general_lnk), &ht->all);

	return ENOERR;
}

void *hashtable_get(struct hashtable *ht, void* key) {
	size_t idx;
	struct hashtable_item *htel;

	assert(ht);

	idx = ht->get_hash_key(key) % ht->table_size;
	if (!ht->table[idx].cnt) {
		return NULL;
	}
	dlist_foreach_entry(htel, &ht->table[idx].list, lnk) {
		if(0 == ht->cmp(key, htel->key)) {
			return htel->value;
		}
	}

	return NULL;
}

struct hashtable_item *hashtable_del(struct hashtable *ht, void *key) {
	size_t idx;
	struct hashtable_item *htel;

	assert(ht);

	idx = ht->get_hash_key(key) % ht->table_size;
	dlist_foreach_entry(htel, &ht->table[idx].list, lnk) {
		if(0 == ht->cmp(key, htel->key)) {
			dlist_del_init(&htel->lnk);
			dlist_del_init(&htel->general_lnk);
#if 0
			objfree(&ht_elem_pool, htel);
#endif
			ht->table[idx].cnt--;

			return htel;
		}
	}

	return NULL;
}

void hashtable_destroy(struct hashtable *ht) {
	int i;
	struct hashtable_item *htel;

	assert(ht);

	for(i = 0; i < ht->table_size; i ++) {
		if (0 == ht->table[i].cnt) {
			continue;
		}
		dlist_foreach_entry(htel, &ht->table[i].list, lnk) {
#if 0
			objfree(&ht_elem_pool, htel);
#endif
		}

	}
}

void *hashtable_get_key_first(struct hashtable *ht) {
	struct hashtable_item *htel;

	assert(ht);

	if (dlist_empty(&ht->all)) {
		return NULL;
	}

	htel = dlist_first_entry(&ht->all, struct hashtable_item, general_lnk);
	return &htel->key;
}

void *hashtable_get_key_next(struct hashtable *ht, void *prev_key) {
	struct hashtable_item *htel;

	assert(ht);

	if (dlist_empty(&ht->all)) {
		return NULL;
	}

	htel = member_cast_out(prev_key, struct hashtable_item, key);
	if (dlist_last(&ht->all) == &htel->general_lnk) {
		return NULL;
	}

	htel = dlist_first_entry(&htel->general_lnk, struct hashtable_item, general_lnk);
	return &htel->key;
}


