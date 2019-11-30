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

void print_time(float time_offset)
{
    static const unsigned long ticks_per_sec = 100000000L;
    static const time_t epoch_delta = 16071L*24*60*60;
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

        /* Find the time of the first event. */
        printf("time_offset %g\n", event[0].time_offset);
        printf("lat %g lon %g\n", event[0].lat, event[0].lon);
        printf("energy %g parent_group_id %d\n", event[0].energy, event[0].parent_group_id);
        print_time(event[0].time_offset);
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
