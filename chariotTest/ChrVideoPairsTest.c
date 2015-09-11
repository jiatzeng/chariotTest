/****************************************************************
 *
 *  IxChariot API SDK              File: ChrVideoPairsTest.c
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
 *  EXAMPLE: Endpoint Video Pairs Test
 *  This script creates and runs a test with video endpoint pairs,
 *  displays the DF and MLR and then saves the test to a file.
 *
 *  All attributes of this test are defined by this program.
 *
 **************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * The header file which defines everything in the Chariot API:
 * functions, constants, etc.
 */
#include "chrapi.h"

/*
 * Data for test:
 * Change these values for your local network if desired.
 */
static
CHR_STRING testFile =
    "chrvideopairstest.tst";

static
CHR_COUNT pairCount = 1;

static
CHR_STRING e1Addrs[] = {
    "localhost"
};

static
CHR_STRING e2Addrs[] = {
    "localhost"
};

static
CHR_VIDEO_CODEC codecs[] = {
    CHR_VIDEO_CODEC_MPEG2
};

static
CHR_PROTOCOL protocols[] = {
    CHR_PROTOCOL_UDP
};

static
CHR_COUNT trDuration = 1;

static
CHR_FLOAT bitrate = 2.5;

static
CHR_THROUGHPUT_UNITS bitrateUM = CHR_THROUGHPUT_UNITS_Mb;

static
CHR_COUNT timeout = 15;    /* 15 seconds */

static
CHR_COUNT maxWait = 300;

static
CHR_STRING logFile = "videoPairsTest.log";


/*
 * Local function to log & print information about errors.
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

    CHR_TEST_HANDLE test;
    CHR_VIDEO_PAIR_HANDLE videoPair;

    char       errorInfo[CHR_MAX_ERROR_INFO];
    CHR_LENGTH errorLen;

    CHR_COUNT  index;

    CHR_BOOLEAN isStopped;
    CHR_COUNT   timer = 0;

    CHR_API_RC rc;

    CHR_FLOAT  df;
    CHR_FLOAT  mlr;

    /* Initialize the Chariot API */
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
        exit(255);
    }

    /* Create a new test */
    printf("Create the test...\n");
    rc = CHR_test_new(&test);
    if (rc != CHR_OK) {
        show_error((CHR_HANDLE)NULL, rc, "test_new");
    }

    /* Set the test filename for saving later */
    rc = CHR_test_set_filename(test, testFile, strlen(testFile));
    if (rc != CHR_OK) {
        show_error(test, rc, "test_set_filename");
    }

    /* Define some pairs for the test */
    for (index = 0; index < pairCount; index++) {

        char comment[CHR_MAX_PAIR_COMMENT];

        /* Create a video pair */
        printf("Create a video pair...\n");
        rc = CHR_video_pair_new(&videoPair);
        if (rc != CHR_OK) {
            show_error((CHR_HANDLE)NULL, rc, "video_pair_new");
        }

        /* Set the video pair attributes from our lists */
        /* Most pair calls accept video pairs */
        printf("Set video pair attributes...\n");
        sprintf(comment, "Video Pair %d", index + 1);
        rc = CHR_pair_set_comment(videoPair,
                                  comment,
                                  strlen(comment));
        if (rc != CHR_OK) {
            show_error(videoPair, rc, "pair_set_comment");
        }

        rc = CHR_pair_set_e1_addr(videoPair,
                                  e1Addrs[index],
                                  strlen(e1Addrs[index]));
        if (rc != CHR_OK) {
            show_error(videoPair, rc, "pair_set_e1_addr");
        }

        rc = CHR_pair_set_e2_addr(videoPair,
                                  e2Addrs[index],
                                  strlen(e2Addrs[index]));
        if (rc != CHR_OK) {
            show_error(videoPair, rc, "pair_set_e2_addr");
        }

        rc = CHR_pair_set_protocol(videoPair, protocols[index]);
        if (rc != CHR_OK) {
            show_error(videoPair, rc, "pair_set_protocol");
        }

        /* Set video pair specific attributes */
        /* Note: the codec must always be set */
        rc = CHR_video_pair_set_codec(videoPair, codecs[index]);
        if (rc != CHR_OK) {
            show_error(videoPair, rc, "video_pair_set_codec");
        }

        rc = CHR_video_pair_set_tr_duration(videoPair, trDuration);
        if (rc != CHR_OK) {
            show_error(videoPair, rc, "video_pair_set_tr_duration");
        }

        rc = CHR_video_pair_set_bitrate(videoPair, bitrate, bitrateUM);
        if (rc != CHR_OK) {
            show_error(videoPair, rc, "video_pair_set_bitrate");
        }

        /* Add the pair to the test */
        rc = CHR_test_add_pair(test, videoPair);
        if (rc != CHR_OK) {
            show_error(test, rc, "test_add_pair");
        }
    }

    /* The test is defined, so now run it */
    printf("Run the test...\n");
    rc = CHR_test_start(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "test_start");
    }

    /*
     * Wait for the test to stop
     * We'll check in a loop here every 15 seconds
     * then call it an error after 3 minutes if
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
        rc = CHR_pair_results_get_average(videoPair, CHR_RESULTS_DF, &df);
        if (CHR_OK == rc) {
            printf("Average DF:  %d ms\n", (int)df);
        }
        else {
            show_error(videoPair, rc, "pair_results_get_average DF");
        }
    }

    if (CHR_OK == rc) {
        rc = CHR_pair_results_get_minimum(videoPair, CHR_RESULTS_DF, &df);
        if (CHR_OK == rc) {
            printf("Min DF:      %d ms\n", (int)df);
        }
        else {
            show_error(videoPair, rc, "pair_results_get_minimum DF");
        }
    }

    if (CHR_OK == rc) {
        rc = CHR_pair_results_get_maximum(videoPair, CHR_RESULTS_DF, &df);
        if (CHR_OK == rc) {
            printf("Max DF:      %d ms\n", (int)df);
        }
        else {
            show_error(videoPair, rc, "pair_results_get_maximum DF");
        }
    }

    if (CHR_OK == rc) {
        rc = CHR_pair_results_get_average(videoPair, CHR_RESULTS_MLR, &mlr);
        if (CHR_OK == rc) {
            printf("Average MLR: %.3f media packets/second\n", mlr);
        }
        else {
            show_error(videoPair, rc, "pair_results_get_average MLR");
        }
    }

    if (CHR_OK == rc) {
        rc = CHR_pair_results_get_minimum(videoPair, CHR_RESULTS_MLR, &mlr);
        if (CHR_OK == rc) {
            printf("Min MLR:     %.3f media packets/second\n", mlr);
        }
        else {
            show_error(videoPair, rc, "pair_results_get_minimum MLR");
        }
    }

    if (CHR_OK == rc) {
        rc = CHR_pair_results_get_maximum(videoPair, CHR_RESULTS_MLR, &mlr);
        if (CHR_OK == rc) {
            printf("Max MLR:     %.3f media packets/second\n", mlr);
        }
        else {
            show_error(videoPair, rc, "pair_results_get_maximum MLR");
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
            }
        }
    }

    /*
     * We've told everything we know, so now just exit.
     */
    exit(EXIT_FAILURE);
}

