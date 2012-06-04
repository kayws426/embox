/**
 * @file
 *
 * @brief
 *
 * @date 14.05.2012
 * @author Anton Bondarev
 */

#ifndef KERNEL_TIME_H_
#define KERNEL_TIME_H_

/* Parameters used to convert the time specific values */
#define MSEC_PER_SEC    1000L
#define USEC_PER_MSEC   1000L
#define NSEC_PER_USEC   1000L
#define USEC_PER_SEC    1000000L
#define NSEC_PER_SEC    1000000000L

struct ktimespec {
	long tv_sec;    /* seconds */
	long tv_nsec;   /* nanoseconds */
};


struct ktimeval {
	long tv_sec;    /* seconds */
	long tv_usec;   /* microseconds */
};

/* time in struct timeval from start of system */
extern struct ktimeval * get_timeval(struct ktimeval *);

#endif /* KERNEL_TIME_H_ */
