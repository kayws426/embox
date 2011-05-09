/**
 * @file
 * @brief Describes tty devices interface and structures
 *
 * @date 13.11.10
 * @author Anton Bondarev
 */

#ifndef TTY_H_
#define TTY_H_

#include <types.h>

#define TTY_RXBUFF_SIZE 0x80
#define TTY_TXBUFF_SIZE 0x80

#include <fs/file.h>
#include <drivers/vtbuild.h>
#include <drivers/vtparse.h>
#include <drivers/vconsole.h>

struct vconsole;

#define CONFIG_TTY_QUEUE 32

#ifndef CONFIG_TTY_CONSOLE_COUNT
#define	CONFIG_TTY_CONSOLE_COUNT 1
#endif

typedef struct tty_device {
	volatile bool out_busy; /*TODO move to vconsole */
	volatile char out_buff[TTY_RXBUFF_SIZE + 1];
	volatile bool has_events;
	volatile uint32_t rx_cur;
	char  rx_buff[TTY_RXBUFF_SIZE + 1];
	char  tx_buff[TTY_TXBUFF_SIZE + 1];
	volatile uint32_t rx_cnt;
	volatile bool     ins_mod;
	struct 	 vtbuild vtb[1];
	struct 	 vtparse vtp[1];
	struct vconsole *consoles[CONFIG_TTY_CONSOLE_COUNT];
	uint32_t console_cur;
	file_operations_t *file_op;
} tty_device_t;

extern tty_device_t *cur_tty;

extern int tty_register(tty_device_t *tty);

extern int tty_unregister(tty_device_t *tty);

extern int tty_get_uniq_number(void);

/**
 * add parsed char to receive buffer
 */
extern int tty_add_char(tty_device_t *tty, int ch);

extern uint8_t* tty_readline(tty_device_t *tty);

extern void tty_freeline(tty_device_t *tty, uint8_t *line);

#endif /* TTY_H_ */
