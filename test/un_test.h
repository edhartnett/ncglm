/* Header file for test code as part of Using NetCDF.
 *
 * Ed Hartnett
 * 10/15/19
 * Amsterdam
 */
#ifndef _UN_TEST_H
#define _UN_TEST_H

#define MILLION 1000000

/* This macro prints an error message with line number and name of
 * test program. */
#define ERR do {							\
        fflush(stdout); /* Make sure our stdout is synced with stderr. */ \
        fprintf(stderr, "Sorry! Unexpected result, %s, line: %d\n",	\
                __FILE__, __LINE__);					\
        fflush(stderr);							\
        return 2;							\
    } while (0)

/* Prototype from tst_utils.c. */
int un_timeval_subtract(struct timeval *result, struct timeval *x,
			struct timeval *y);

#endif /* _UN_TEST_H */
