/* Header file for test code as part of Using NetCDF.
 *
 * Ed Hartnett
 * 10/15/19
 * Amsterdam
 */
#ifndef _UN_TEST_H
#define _UN_TEST_H

#include <assert.h>

#define MILLION 1000000

/* This is the name of the data file we use for testing. */
#define GLM_DATA_FILE "OR_GLM-L2-LCFA_G17_s20192692359400_e20192700000000_c20192700000028.nc"

/* This macro prints an error message with line number and name of
 * test program. */
#define ERR do {							\
        fflush(stdout); /* Make sure our stdout is synced with stderr. */ \
        err++;                                                          \
        fprintf(stderr, "Sorry! Unexpected result, %s, line: %d\n",	\
                __FILE__, __LINE__);					\
        fflush(stderr);							\
        return 2;							\
    } while (0)

/* This macro prints an error message with line number and name of
 * test program. */
#define ERR2 do {							\
        fflush(stdout); /* Make sure our stdout is synced with stderr. */ \
        fprintf(stderr, "Sorry! Unexpected result, %s, line: %d\n",	\
                __FILE__, __LINE__);					\
        fflush(stderr);							\
        return 2;							\
    } while (0)

/* After a set of tests, report the number of errors, and increment
 * total_err. */
#define SUMMARIZE_ERR do { \
   if (err) \
   { \
      printf("%d failures\n", err); \
      total_err += err; \
      err = 0; \
   } \
   else \
      printf("ok.\n"); \
} while (0)

/* This macro prints out our total number of errors, if any, and exits
 * with a 0 if there are not, or a 2 if there were errors. Make will
 * stop if a non-zero value is returned from a test program. */
#define FINAL_RESULTS do { \
   if (total_err) \
   { \
      printf("%d errors detected! Sorry!\n", total_err); \
      return 2; \
   } \
   printf("*** Tests successful!\n"); \
   return 0; \
} while (0)

/* Prototype from tst_utils.c. */
int un_timeval_subtract(struct timeval *result, struct timeval *x,
			struct timeval *y);

#endif /* _UN_TEST_H */
