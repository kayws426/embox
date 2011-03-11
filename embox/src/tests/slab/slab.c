/**
 * @file
 * @brief Test slab_dm allocator
 *
 * @date 22.12.10
 * @author Kirill Tyushev
 * @author Alexandr Kalmuk
 */

#include <stdio.h>
#include <embox/test.h>
#include <lib/list.h>
#include <kernel/mm/slab.h>

EMBOX_TEST(run);

#define ADDR_OF_MAIN_CACHE 0x40000574

/**
 * function to free cache list
 * @return 0 on success
 */
static int destroy_all_caches() {
	cache_t *kmalloc_cache = ADDR_OF_MAIN_CACHE;
	cache_t *cachep;

	while (1) {
		cachep = (cache_t*) kmalloc_cache->next.next;
		if (&cachep->next == &kmalloc_cache->next)
			break;
		cache_destroy(cachep);
	}

	return 0;
}

/**
 * testing smalloc() and sfree()
 * @return 0 on success
 */
static int test_s_functions(void) {
	cache_t *kmalloc_cache = ADDR_OF_MAIN_CACHE;
	void* objp[30];
	struct list_head *tmp;
	size_t i;

	for (i = 0; i < 10; i++) {
		objp[i] = kmalloc(8);
	}
	for (i = 10; i < 20; i++) {
		objp[i] = kmalloc(16);
	}
	for (i = 20; i < 30; i++) {
		objp[i] = kmalloc(32);
	}
	/*how many caches are in cache list*/
	i = 0;
	list_for_each(tmp,&(kmalloc_cache->next)) {
		i++;
	}
	TRACE("\n%d caches were created for 3 types\n", i);

	for (i = 0; i < 30; i++) {
		kfree(objp[i]);
	}
	destroy_all_caches();
	i = 0;
	list_for_each(tmp,&(kmalloc_cache->next)) {
		i++;
	}
	TRACE("%d caches now\n", i);

	return 0;
}

static void test1(void) {
	void* objp[10];
	size_t i;
	cache_t *cachep = cache_create("cache1", 50);

	for (i = 0; i < 10; i++) {
		objp[i] = cache_alloc(cachep);
	}

	for (i = 0; i < 10; i++) {
		cache_free(cachep, objp[i]);
	}

	cache_destroy(cachep);

	cache_shrink(cachep);
}

static void test2(void) {
	cache_t *cachep;

	for (int i = 0; i < 14; i++) {
		cachep = cache_create("cache1", 1 << i);
		cache_destroy(cachep);
	}
}

static int run(void) {
	if (0 != test_s_functions()) {
		TRACE("smalloc test FAILED\n");
		return -1;
	}
	test1();
	test2();

	return 0;
}
