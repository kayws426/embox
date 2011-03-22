/**
 * @file
 * @brief Software interrupts subsystem.
 *
 * @date 24.12.2009
 * @author Anton Bondarev
 *         - Initial implementation
 * @author Eldar Abusalimov
 *         - Rewriting from scratch:
 *          - Implementing new interface
 *          - Introducing interrupt safety
 */

#include <stddef.h>
#include <stdint.h>
#include <errno.h>

#include <kernel/softirq.h>
#include <hal/ipl.h>
#include <kernel/evdispatch.h>

struct softirq_action {
	softirq_handler_t handler;
	void *data;
};

volatile static struct softirq_action softirq_actions[SOFTIRQ_NRS_TOTAL];
volatile static uint32_t softirq_pending;

void softirq_init(void) {
	// TODO install common softirqs. -- Eldar
}

int softirq_install(softirq_nr_t nr, softirq_handler_t handler, void *data) {
	ipl_t ipl;

	if (!softirq_nr_valid(nr)) {
		return -EINVAL;
	}

	ipl = ipl_save();
	softirq_actions[nr].handler = handler;
	softirq_actions[nr].data = data;
	ipl_restore(ipl);

	return 0;
}

int softirq_raise(softirq_nr_t nr) {
	ipl_t ipl;

	if (!softirq_nr_valid(nr)) {
		return -EINVAL;
	}

	ipl = ipl_save();
	softirq_pending |= (1 << nr);
	ipl_restore(ipl);

	return 0;
}

void softirq_dispatch(void) {
	uint32_t pending;
	softirq_nr_t nr;
	softirq_handler_t handler;
	void *data;

	while (0x0 != (pending = softirq_pending)) {
		softirq_pending = 0;
		for (nr = 0; pending; pending >>= 1, ++nr) {
			if (0x0 == (pending & 0x1)) {
				continue;
			}

			if (NULL != (handler = softirq_actions[nr].handler)) {
				data = softirq_actions[nr].data;
				ipl_enable();
				handler(nr, data);
				ipl_disable();
			}
		}
	}

	event_dispatch();
}
