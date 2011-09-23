/**
 * @file
 *
 * @date 01.07.10
 * @author Anton Kozlov
 */

#ifndef HAL_IPL_H_
# error "Do not include this file directly!"
#endif /* HAL_IPL_H_ */

#include <types.h>
#include <hal/interrupt.h>

#include <asm/modes.h>
#include <asm/hal/reg.h>

typedef uint32_t __ipl_t;


static inline void ipl_init(void) {
	set_cpsr(get_cpsr() & ~(I_BIT | F_BIT));		
}

static inline __ipl_t ipl_save(void) {
	uint32_t r = get_cpsr();
	set_cpsr(r | I_BIT | F_BIT);		
	return r;
}

static inline void ipl_restore(__ipl_t ipl) {
	set_cpsr(ipl);
}
