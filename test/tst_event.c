/*
  Program to read data from the GOES-17 Global Lightning Mapper.

  Ed Hartnett, 11/16/19

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "un_test.h"
#include "ncglm.h"

/* Err is used to keep track of errors within each set of tests,
 * total_err is the number of errors in the entire test program, which
 * generally cosists of several sets of tests. */
int total_err = 0, err = 0;

#define EPSILON .001
#define NUM_VAL 5

int are_same(double a, double b)
{
    /* printf("%g %g %g\n", a, b, fabs(a - b)); */
    return fabs(a - b) < EPSILON ? 1 : 0;
}

void print_time(float time_offset)
{
    static const unsigned long ticks_per_sec = 100000000L;
    static const time_t epoch_delta = 18165*24*60*60;
    time_t seconds = time_offset + epoch_delta;
    int int_part = (int)time_offset;
    float fractional = round(time_offset * 100) / 100 - int_part;

    unsigned long fraction = fractional * ticks_per_sec;
    struct tm tm = *gmtime(&seconds);
    printf("%4d-%02d-%02d %02d:%02d:%02d.%03lu\n",
           tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
           tm.tm_hour, tm.tm_min, tm.tm_sec,
           fraction/10000);
}

int
main()
{
    printf("Testing GLM event reads.\n");
    printf("testing GLM event reads...");
    {
        int ncid;
        size_t nevent, ngroup, nflash;
        size_t my_nevent;
        GLM_EVENT_T *event;
        float expected_time[NUM_VAL] = {-0.475699, -0.475699, -0.444037,
                                        -0.332646, -0.330739};
        int i;
        int ret;

        /* Open the data file as read-only. */
        if ((ret = nc_open(GLM_DATA_FILE, NC_NOWRITE, &ncid)))
            NC_ERR(ret);

        /* Check number of events, groups, and flashes. */
        if ((ret = glm_read_dims(ncid, &nevent, &ngroup, &nflash))) ERR;
        if (nevent != 4578 || ngroup != 1609 || nflash != 123) ERR;

        /* Allocat array of struct to hold data. */
        if (!(event = malloc(nevent * sizeof(GLM_EVENT_T)))) ERR;

        /* Read data. */
        if (glm_read_event_structs(ncid, &my_nevent, event)) ERR;
        if (my_nevent != nevent) ERR;

        /* Check some timestamps. */
        for (i = 0; i < NUM_VAL; i++)
            if (!are_same(event[i].time_offset, expected_time[i])) ERR;

        /* Print the values of the first 10 events. */
        for (i = 0; i < 10; i++)
        {
        /*     printf("time_offset[%d] %g\n", i, event[i].time_offset); */
            printf("lat %g lon %g\n", event[i].lat, event[i].lon);
            printf("energy %g parent_group_id %d\n", event[i].energy, event[i].parent_group_id);
        }
        /* for (int e = 0; e < nevent; e++) */
        /*     print_time(event[e].time_offset); */

        /* Free resources. */
        free(event);

        /* Close the data file. */
        if ((ret = nc_close(ncid)))
            NC_ERR(ret);
    }
   SUMMARIZE_ERR;
   FINAL_RESULTS;
}
