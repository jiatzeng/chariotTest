/****************************************************************
 *
 *  IxChariot API SDK              File: ChrVideoMGroupsTest.c
 *
 *  This module contains code made available by Ixia on an AS IS
 *  basis.  Any one receiving the module is considered to be 
 *  licensed under Ixia copyrights to use the Ixia-provided 
 *  source code in any way he or she deems fit, including copying
 *  it, compiling it, modifying it, and redistributing it, with 
 *  or without modifications. No license under any Ixia patents
 *  or patent applications is to be implied from this copyright
 *  license.
 *
 *  A user of the module should understand that Ixia cannot 
 *  provide technical support for the module and will not be
 *  responsible for any consequences of use of the program.
 *
 *  Any notices, including this one, are not to be removed from
 *  the module without the prior written consent of Ixia.
 *
 *  For more information, contact:
 *
 *  Ixia
 *  26601 W. Agoura Rd. 
 *  Calabasas, CA 91302 USA
 *  Web:   http://www.ixiacom.com
 *  Phone: 818-871-1800
 *  Fax:   818-871-1805
 *
 *  General Information:
 *    e-mail: info@ixiacom.com
 *
 *  Technical Support:
 *    e-mail: support@ixiacom.com
 *
 *
 *  EXAMPLE: Video Multicast Groups Test
 *  This script creates and runs a test with video multicast
 *  groups, displays the DF and MLR and saves the test to a file.
 *
 *  All attributes of this test are defined by this program.
 *
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * The header file which defines everything in the Chariot API:
 * functions, constants, etc
 */
#include "chrapi.h"

/*
 * Data for test:
 * Change these values for your local network if desired.
 */
static
CHR_STRING testFile =
    "chrvideomgroupstest.tst";

static
CHR_COUNT mgroupCount = 1;

/*
 * For IPv6 multicast test change e1Addrs to IPv6 style addresses.
 */
static
CHR_STRING e1Addrs[] = {
    "10.10.44.48"
};

/*
 * For IPv6 multicast test change mcAddrs to IPv6 style addresses.
 */
static
CHR_STRING mcAddrs[] = {
    "226.1.1.1"
};

static
CHR_PORT mcPorts[] = {
    5500
};

/*
 * For IPv6 multicast test change protocols to UDP6 or RTP6.
 */
static
CHR_PROTOCOL protocols[] = {
    CHR_PROTOCOL_UDP
};

static
CHR_VIDEO_CODEC codecs[] = {
    CHR_VIDEO_CODEC_MPEG2
};

static
CHR_COUNT trDuration = 1;

static
CHR_FLOAT bitrate = 2.5;

static
CHR_THROUGHPUT_UNITS bitrateUM = CHR_THROUGHPUT_UNITS_Mb;

static
CHR_COUNT mpairCount = 1;

/*
 * For IPv6 multicast test change e2Addrs to IPv6 style addresses.
 */
static
CHR_STRING e2Addrs[] = {
    "10.10.44.48"
};

static
CHR_COUNT timeout = 5;    /* 5 seconds */
static
CHR_COUNT maxWait = 300;

static
CHR_STRING logFile = "videomgroupstest.log";

/*
 * Local function to log & print information about errors
 */
static void
show_error(
    CHR_HANDLE handle,
    CHR_API_RC code,
    CHR_STRING where);


/**************************************************************
 *
 * Program main
 *
 * If the return code from any Chariot API function call
 * is not CHR_OK, the show_error() function is called to
 * display information about what happened then exit.
 *
 **************************************************************/

void main() {

    CHR_TEST_HANDLE    test;
    CHR_VIDEO_MGROUP_HANDLE  videoMGroup;
    CHR_MPAIR_HANDLE   mpair;

    char       errorInfo[CHR_MAX_ERROR_INFO];
    CHR_LENGTH errorLen;

    CHR_COUNT mgrpIndex, mprIndex, index;

    CHR_BOOLEAN isStopped;
    CHR_COUNT   timer = 0;

    CHR_API_RC rc;

    CHR_FLOAT  df;
    CHR_FLOAT  mlr;

    /*
     * Initialize the Chariot API
     */
    rc = CHR_api_initialize(CHR_DETAIL_LEVEL_ALL, errorInfo,
                            CHR_MAX_ERROR_INFO, &errorLen);
    if (rc != CHR_OK) {

        /*
         * Because initialization failed, we can't
         * ask the API for the message for this
         * return code so we can't call our
         * show_error() function. Instead, we'll
         * print what we do know before exiting.
         */
        printf("Initialization failed: rc = %d\n", rc);
        printf("Extended error info:\n%s\n", errorInfo);
        exit(EXIT_FAILURE);
    }

    /* Create a new test */
    printf("Create the test...\n");
    rc = CHR_test_new(&test);
    if (rc != CHR_OK) {
        show_error((CHR_HANDLE) NULL, rc, "test_new");
    }

    /* Set the test filename for saving later */
    rc = CHR_test_set_filename(test, testFile, strlen(testFile));
    if (rc != CHR_OK) {
        show_error(test, rc, "test_set_filename");
    }

    /* Define some multicast groups for the test */
    for( mgrpIndex = 0; mgrpIndex < mgroupCount; mgrpIndex++) {

        char groupName[CHR_MAX_GROUP_NAME];

        /* Create a video mgroup */
        printf("Create a video mgroup...\n");

        rc = CHR_video_mgroup_new(&videoMGroup);
        if (rc != CHR_OK) {
            show_error((CHR_HANDLE)NULL, rc, "video_mgroup_new");
        }

        /* Set the video mgroup attributes from our lists */
        printf("Set video mgroup attributes...\n");

        sprintf(groupName, "Video Multicast Group %d", mgrpIndex + 1);
        rc = CHR_mgroup_set_name(videoMGroup,
                                 groupName,
                                 strlen(groupName));
        if (rc != CHR_OK) {
            show_error(videoMGroup, rc, "mgroup_set_name");
        }

        rc = CHR_mgroup_set_e1_addr(videoMGroup,
                                    e1Addrs[mgrpIndex],
                                    strlen(e1Addrs[mgrpIndex]));
        if (rc != CHR_OK) {
            show_error(videoMGroup, rc, "mgroup_set_e1_addr");
        }

        rc = CHR_mgroup_set_multicast_addr(videoMGroup,
                                           mcAddrs[mgrpIndex],
                                           strlen(mcAddrs[mgrpIndex]));
        if (rc != CHR_OK) {
            show_error(videoMGroup, rc, "mgroup_set_multicast_addr");
        }

        rc = CHR_mgroup_set_multicast_port(videoMGroup, mcPorts[mgrpIndex]);
        if (rc != CHR_OK) {
            show_error(videoMGroup, rc, "mgroup_set_multicast_port");
        }

        rc = CHR_mgroup_set_protocol(videoMGroup, protocols[mgrpIndex]);
        if (rc != CHR_OK) {
            show_error(videoMGroup, rc, "mgroup_set_protocol");
        }

        /* Set video mgroup specific attributes */
        /* Note: the codec must always be set */
        rc = CHR_video_mgroup_set_codec(videoMGroup, codecs[mgrpIndex]);
        if (rc != CHR_OK) {
            show_error(videoMGroup, rc, "video_mgroup_set_codec");
        }

        rc = CHR_video_mgroup_set_tr_duration(videoMGroup, trDuration);
        if (rc != CHR_OK) {
            show_error(videoMGroup, rc, "video_mgroup_set_tr_duration");
        }

        rc = CHR_video_mgroup_set_bitrate(videoMGroup, bitrate, bitrateUM);
        if (rc != CHR_OK) {
            show_error(videoMGroup, rc, "video_mgroup_set_bitrate");
        }

        /* Define mpairs for the group */
        for (mprIndex = 0; mprIndex < mpairCount; mprIndex++) {

            /* Create an mpair */
            printf("Create an mpair...\n");
            rc = CHR_mpair_new(&mpair);
            if ( rc != CHR_OK ) {
                show_error((CHR_HANDLE) NULL, rc, "mpair_new");
            }

            /* Set mpair attribues */
            printf( "Set mpair attributes...\n");
            index = (mgrpIndex * mpairCount) + mprIndex;
            rc = CHR_mpair_set_e2_addr(mpair,
                                       e2Addrs[index],
                                       strlen(e2Addrs[index]));
            if ( rc != CHR_OK ) {
                show_error( mpair, rc, "mpair_set_e2_addr");
            }

            /* Add the mpair to the video_mgroup */
            rc = CHR_mgroup_add_mpair(videoMGroup, mpair);
            if (rc != CHR_OK) {
                show_error(videoMGroup, rc, "mgroup_add_mpair");
            }
        }

        /* Add the video_mgroup to the test */
        rc = CHR_test_add_mgroup(test, videoMGroup);
        if (rc != CHR_OK) {
            show_error(test, rc, "test_add_mgroup");
        }
    }

    /* The test is defined, so now run it */
    printf("Run the test...\n");
    rc = CHR_test_start(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "tes_start");
    }

    /*
     * Wait for the test to stop
     * We'll check in a loop here every 5 seconds
     * then call it an error after two minutes if
     * the test is still not stopped.
     */
    printf("Wait for the test to stop...\n");
    isStopped = CHR_FALSE;
    timer = 0;
    while(!isStopped && timer < maxWait) {
        rc = CHR_test_query_stop(test, timeout);
        if (rc == CHR_OK) {
            isStopped = CHR_TRUE;
        }
        else if (rc == CHR_TIMED_OUT) {
            timer += timeout;
            printf("Waiting for test to stop... (%d)\n",
                    timer );
        }
        else {
            show_error(test, rc, "test_query_stop");
        }
    }
    if (!isStopped) {
        show_error(test, CHR_TIMED_OUT, "test_query_stop");
    }

    /* Print the average, min and max values of DF and MLR */
    if (CHR_OK == rc) {
        rc = CHR_pair_results_get_average(mpair, CHR_RESULTS_DF, &df);
        if (CHR_OK == rc) {
            printf("Average DF:  %d ms\n", (int)df);
        }
        else {
            show_error(mpair, rc, "pair_results_get_average DF");
        }
    }

    if (CHR_OK == rc) {
        rc = CHR_pair_results_get_minimum(mpair, CHR_RESULTS_DF, &df);
        if (CHR_OK == rc) {
            printf("Min DF:      %d ms\n", (int)df);
        }
        else {
            show_error(mpair, rc, "pair_results_get_minimum DF");
        }
    }

    if (CHR_OK == rc) {
        rc = CHR_pair_results_get_maximum(mpair, CHR_RESULTS_DF, &df);
        if (CHR_OK == rc) {
            printf("Max DF:      %d ms\n", (int)df);
        }
        else {
            show_error(mpair, rc, "pair_results_get_maximum DF");
        }
    }

    if (CHR_OK == rc) {
        rc = CHR_pair_results_get_average(mpair, CHR_RESULTS_MLR, &mlr);
        if (CHR_OK == rc) {
            printf("Average MLR: %.3f media packets/second\n", mlr);
        }
        else {
            show_error(mpair, rc, "pair_results_get_average MLR");
        }
    }

    if (CHR_OK == rc) {
        rc = CHR_pair_results_get_minimum(mpair, CHR_RESULTS_MLR, &mlr);
        if (CHR_OK == rc) {
            printf("Min MLR:     %.3f media packets/second\n", mlr);
        }
        else {
            show_error(mpair, rc, "pair_results_get_minimum MLR");
        }
    }

    if (CHR_OK == rc) {
        rc = CHR_pair_results_get_maximum(mpair, CHR_RESULTS_MLR, &mlr);
        if (CHR_OK == rc) {
            printf("Max MLR:     %.3f media packets/second\n", mlr);
        }
        else {
            show_error(mpair, rc, "pair_results_get_maximum MLR");
        }
    }

    /* Finally, save the test */
    printf("Save the test..\n");
    rc = CHR_test_save(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "test_save");
    }

    /*
     * The test was successfully saved, so we're done!
     */
    exit(EXIT_SUCCESS);
}


/***************************************************************
 *
 * Print information about an error and exit. If there is
 * extended error information, log that before exiting.
 *
 * Parameters: handle - what object had the error
 *             code   - the Chariot API return code
 *             where  - what function call failed
 ***************************************************************/

static void
show_error(
    CHR_HANDLE handle,
    CHR_API_RC code,
    CHR_STRING where)
{
    char       msg[CHR_MAX_RETURN_MSG];
    CHR_LENGTH msgLen;

    char       errorInfo[CHR_MAX_ERROR_INFO];
    CHR_LENGTH errorLen;

    FILE  *fd;
    time_t currentTime;
    char  *timestamp;

    CHR_API_RC rc;


    /*
     * Get the API message for this return code.
     */
    rc = CHR_api_get_return_msg(code, msg,
                                CHR_MAX_RETURN_MSG, &msgLen);
    if (rc != CHR_OK) {

        /* Could not get the message: show why */
        printf("%s failed\n", where);
        printf(
          "Unable to get message for return code %d, rc = %d\n",
           code, rc);
    }
    else {

        /* Tell the user about the error */
        printf("%s failed: rc = %d (%s)\n", where, code, msg);
    }

    /*
     * See if there is extended error information available.
     * It's meaningful only after some error returns. After 
     * failed "new" function calls, we don't have a handle so 
     * we cannot check for extended error information.
     */
    if ((code == CHR_OPERATION_FAILED || 
         code == CHR_OBJECT_INVALID ||
         code == CHR_APP_GROUP_INVALID) &&
         handle != (CHR_HANDLE)NULL) {

        /* Open the log file */
        fd = fopen(logFile, "a+");

        /* Get the timestamp */
        currentTime = time(NULL);
        timestamp = ctime(&currentTime);

        /* Get the extended error info */
        rc = CHR_common_error_get_info(handle,
                                       CHR_DETAIL_LEVEL_ALL,
                                       errorInfo,
                                       CHR_MAX_ERROR_INFO,
                                      &errorLen);
        if (rc == CHR_OK) {

            /*
             * We can ignore all non-success return codes here
             * because most should not occur (the api's been
             * initialized, the handle is good, the buffer
             * pointer is valid, and the detail level is okay),
             * and the NO_SUCH_VALUE return code here means
             * there is no info available.
             */
            if (fd != NULL) {

                /* Log it if the file was opened successfully */
                fprintf(fd, "%s %s failed\n",
                        timestamp, where );
                fprintf(fd, "%s %s\n",
                        timestamp, errorInfo);
                fclose(fd);

                printf("%s\n", errorInfo);
            }
        }
    }

    /*
     * We've told everything we know, so now just exit.
     */
    exit(EXIT_FAILURE);
}

