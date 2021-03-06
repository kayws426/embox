/**
 * @file
 *
 * @date Feb 28, 2013
 * @author: Anton Bondarev
 */

#include <termios.h>
#include <stropts.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <drivers/tty.h>

int tcgetattr(int fd, struct termios *termios) {
	return ioctl(fd, TIOCGETA, termios);
}

int tcsetattr(int fd, int opt, const struct termios *termios) {
	switch (opt) {
	case TCSANOW:
		return (ioctl(fd, TIOCSETA, termios));
	case TCSADRAIN:
		return (ioctl(fd, TIOCSETAW, termios));
	case TCSAFLUSH:
		return (ioctl(fd, TIOCSETAF, termios));
	default:
		errno = EINVAL;
		return (-1);
	}
}

pid_t tcgetpgrp(int fd) {
	pid_t pid;

	if (-1 == ioctl(fd, TIOCGPGRP, &pid)) {
		return -1;
	}

	return pid;
}

int tcsetpgrp(int fd, pid_t pgrp) {
	return ioctl(fd, TIOCSPGRP, &pgrp);
}

int tcflush(int fd, int queue_selector) {
	int arg = 0;
	switch (queue_selector) {
		case TCIFLUSH:
			arg = FLUSHR; 
			break;
		case TCOFLUSH:
			arg = FLUSHW;
			break;
		case TCIOFLUSH:
			arg = FLUSHRW;
			break;
		default:
			SET_ERRNO(EINVAL);
			return -1;
	}
	return ioctl(fd, I_FLUSH, (void *) &arg);
}
