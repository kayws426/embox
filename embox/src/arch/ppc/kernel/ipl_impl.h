/**
 * @file
 *
 * @date 08.11.12
 * @author Ilia Vaprol
 */

#ifndef PPC_IPL_IMPL_H_
#define PPC_IPL_IMPL_H_

#ifndef __ASSEMBLER__

#include <types.h>

#include <asm/psr.h>
#include <asm/regs.h>

typedef uint32_t __ipl_t;

static inline void ipl_init(void) {
	__set_msr(__get_msr() | MSR_EE);
}

static inline __ipl_t ipl_save(void) {
	__ipl_t ipl;
	ipl = __get_msr();
	__set_msr(ipl & ~MSR_EE);
	return ipl;
}

static inline void ipl_restore(__ipl_t ipl) {
	__set_msr(ipl);
}

#endif /* __ASSEMBLER__ */

#endif /* PPC_IPL_IMPL_H_ */
