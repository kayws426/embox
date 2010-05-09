/**
 * @file
 * @brief Tests thread with infinite recursion.
 *
 * @date 09.05.2010
 * @author Dmitry Avdyukhin
 */

#include <embox/test.h>
#include <kernel/thread.h>
#include <kernel/scheduler.h>
#include <errno.h>
#include <assert.h>

#define THREAD_STACK_SIZE 0x1000
#define MAX_DEPTH 2
static char recursion_stack[THREAD_STACK_SIZE];
static struct thread *recursion_thread;

EMBOX_TEST(run_test)
;

/**
 * Shows natural number on the screen and maybe calls itself.
 * @param i shown number. if i < MAX_DEPTH f calls itself.
 */
void f(int i) {
	TRACE("%d ", i);
	if (i < MAX_DEPTH) {
		f(i+1);
	}
	TRACE("-%d ", i);
}

/**
 * Starts recursion.
 * Shows natural numbers.
 */
static void recursion_run(void) {
	while (true) {
		f(1);
	}
}


/**
 * Test, which writes natural numbers using recursion.
 *
 * If MAX_DEPTH > 2, then error occurs.
 *
 * @retval 0 if test is passed
 * @retval -EINVAL if an error occurs.
 */
static int run_test() {
	TRACE("\n");
	scheduler_init();

	recursion_thread =
		thread_create(recursion_run, recursion_stack + THREAD_STACK_SIZE);

	assert(recursion_thread != NULL);

	thread_start(recursion_thread);

	TRACE("\nBefore start\n");
	scheduler_start();

	/* NOTREACHED */
	assert(false);
	return 0;
}
