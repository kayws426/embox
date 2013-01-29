/**
 * @file
 * @brief Single-thread sleep
 *
 * @date 09.02.09
 * @author Andrey Baboshin
 * @author Ilia Vaprol
 */

#include <types.h>
#include <kernel/time/ktime.h>
#include <kernel/time/timer.h>
#include <hal/arch.h>

static void wake_up(sys_timer_t *timer, void *param) {
	*(int *)param = 0;
}

int n_ksleep(useconds_t nsec) {
	volatile int wait_flag; // for sleep func
	sys_timer_t timer;

	if(0 == nsec) {
		return 0;
	}

	wait_flag = 1;
	/* FIXME timer_set argument is tick (not usec) */
	if (timer_init_ns(&timer, TIMER_ONESHOT, nsec, &wake_up, (void *) &wait_flag)) {
		return 1;
	}
	while (wait_flag) {
		arch_idle();
	}
	timer_close(&timer);
	return 0;
}

int u_ksleep(useconds_t usec) {
	volatile int wait_flag; // for sleep func
	sys_timer_t timer;

	if(0 == usec) {
		return 0;
	}

	wait_flag = 1;
	/* FIXME timer_set argument is tick (not usec) */
	if (timer_init_us(&timer, TIMER_ONESHOT, usec, &wake_up, (void *) &wait_flag)) {
		return 1;
	}
	while (wait_flag) {
		arch_idle();
	}
	timer_close(&timer);
	return 0;
}

int m_ksleep(useconds_t msec) {
	volatile int wait_flag; // for sleep func
	sys_timer_t timer;

	if(0 == msec) {
		return 0;
	}

	wait_flag = 1;
	/* FIXME timer_set argument is tick (not usec) */
	if (timer_init_ms(&timer, TIMER_ONESHOT, msec, &wake_up, (void *) &wait_flag)) {
		return 1;
	}
	while (wait_flag) {
		arch_idle();
	}
	timer_close(&timer);
	return 0;
}
