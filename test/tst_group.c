/*
  Program to read group data from the GOES-17 Global Lightning Mapper.

  Ed Hartnett, 11/19/19

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "un_test.h"
#include "ncglm.h"

/* Err is used to keep track of errors within each set of tests,
 * total_err is the number of errors in the entire test program, which
 * generally cosists of several sets of tests. */
int total_err = 0, err = 0;

int
main()
{
    printf("Testing GLM group reads.\n");
    printf("testing GLM group reads...");
    {
        int ncid;
        size_t nevent, ngroup, nflash;
        GLM_GROUP_T *group;
        int ret;

        /* Open the data file as read-only. */
        if ((ret = nc_open(GLM_DATA_FILE, NC_NOWRITE, &ncid)))
            NC_ERR(ret);

        /* Check number of events, groups, and flashes. */
        if ((ret = glm_read_dims(ncid, &nevent, &ngroup, &nflash))) ERR;
        if (nevent != 4578 || ngroup != 1609 || nflash != 123) ERR;

        /* Allocat array of struct to hold data. */
        if (!(group = malloc(ngroup * sizeof(GLM_GROUP_T)))) ERR;

        /* Read data. */
        if (glm_read_group_structs(ncid, ngroup, group)) ERR;

        /* Free resources. */
        free(group);

        /* Close the data file. */
        if ((ret = nc_close(ncid)))
            NC_ERR(ret);
    }
   SUMMARIZE_ERR;
   FINAL_RESULTS;
}
