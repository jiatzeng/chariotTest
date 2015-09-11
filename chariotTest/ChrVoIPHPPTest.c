/****************************************************************
 *
 *  IxChariot API SDK              File: ChrVoIPHPPTest.c
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
 *  EXAMPLE: VoIP HPP Pairs Test
 *  This program creates and runs a test with just voice over ip
 *  hardware performance pairs, then saves the test to a file.
 *
 *  VoIP HPP tests rely on Ixia hardware.
 *  This test requires that the Ixia network configuration file
 *  "ChrVoIPHPPTest.ixn" be in the same directory as the executable
 *  file, and that it uses the same test addresses as this sample code.
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
    "ChrVoIPHPPTest.tst";

static
CHR_COUNT pairCount = 2;

static
CHR_STRING e1Addrs[] = {
    "172.16.1.1",
    "172.16.1.2"
};

static
CHR_STRING e2Addrs[] = {
    "172.16.2.1",
    "172.16.2.2"
};

static
CHR_VOIP_CODEC codecs[] = {
    CHR_VOIP_CODEC_G723_1A,
    CHR_VOIP_CODEC_G729
};

static
CHR_COUNT timeout = 15;    /* 15 seconds */
static
CHR_COUNT maxWait = 180;  /* 3 minutes in seconds */
static
CHR_COUNT run_duration = 60; /* 60 seconds, 1 minute */

static
CHR_STRING logFile = "voipHppTest.log";

static
CHR_STRING stream   = "C:\\Program Files\\Ixia\\IxChariot\\Streams\\udp-framesize-random.str";

static
CHR_STRING configFile = "ChrVoIPHPPTest.ixn";


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
    CHR_VOIP_PAIR_HANDLE voip_pair;

    char       errorInfo[CHR_MAX_ERROR_INFO];
    CHR_LENGTH errorLen;

    CHR_COUNT index;

    CHR_BOOLEAN isStopped;
    CHR_COUNT   timer = 0;

    CHR_API_RC rc;

    CHR_RUNOPTS_HANDLE runOpts;


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

    /* Load the Ixia configuration */
    rc = CHR_test_load_ixia_network_configuration(test, configFile, strlen(configFile));
    if (rc != CHR_OK) {
        show_error(test, rc, "test_load_ixia_network_configuration");
    }

    /* Set the test filename for saving later */
    rc = CHR_test_set_filename(test, testFile, strlen(testFile));
    if (rc != CHR_OK) {
        show_error(test, rc, "test_set_filename");
    }

    /* Define some pairs for the test */
    for( index = 0; index < pairCount; index++) {

        char comment[CHR_MAX_PAIR_COMMENT];

        /* Create a voip pair */
        printf("Create a voip hardware pair...\n");
        
        rc = CHR_hardware_voip_pair_new(&voip_pair);
        if (rc != CHR_OK) {
            show_error((CHR_HANDLE)NULL, rc, "hardware_voip_pair_new");
        }

        /* Set the voip pair attributes from our lists */
        /* Most pair calls accept voip pairs */
        printf("Set voip pair attributes...\n");
        sprintf(comment, "Pair %d", index+1);
        rc = CHR_pair_set_comment(voip_pair,
                                  comment,
                           strlen(comment));
        if (rc != CHR_OK) {
            show_error(voip_pair, rc, "pair_set_comment");
        }

        rc = CHR_pair_set_e1_addr(voip_pair,
                                  e1Addrs[index],
                           strlen(e1Addrs[index]));
        if (rc != CHR_OK) {
            show_error(voip_pair, rc, "pair_set_e1_addr");
        }

        rc = CHR_pair_set_e2_addr(voip_pair,
                                  e2Addrs[index],
                           strlen(e2Addrs[index]));
        if (rc != CHR_OK) {
            show_error(voip_pair, rc, "pair_set_e2_addr");
        }

        rc = CHR_voip_pair_set_codec(voip_pair, codecs[index]);
        if (rc != CHR_OK) {
            show_error(voip_pair, rc, "voip_pair_set_codec");
        }

        rc = CHR_voip_pair_set_dest_port_num(voip_pair, 23456);
        if (rc != CHR_OK) {
            show_error(voip_pair, rc, "voip_pair_set_dest_port_num");
        }

        rc = CHR_voip_pair_set_source_port_num(voip_pair, 1122);
        if (rc != CHR_OK) {
            show_error(voip_pair, rc, "voip_pair_set_source_port_num");
        }

        rc = CHR_voip_pair_set_datagram_delay(voip_pair, 40);
        if (rc != CHR_OK) {
            show_error(voip_pair, rc, "voip_pair_set_datagram_delay");
        }

        rc = CHR_hardware_voip_pair_set_concurrent_voice_streams(voip_pair, 111);
        if (rc != CHR_OK) {
            show_error(voip_pair, rc, "voip_pair_set_concurrent_voice_streams");
        }

        /* Add the pair to the test */
        rc = CHR_test_add_pair(test, voip_pair);
        if (rc != CHR_OK) {
            show_error(test, rc, "test_add_pair");
        }
    }

    /*
     * Set the run options to run in batch mode (for Ixia chassis)
     * and run for a duration
     */ 
    printf("Setup the run options for batch mode and run for 1 minute duration...\n");
    rc = CHR_test_get_runopts(test, &runOpts);
    if (rc != CHR_OK) {
        show_error(test, rc, "test_get_runopts");
    }
    rc = CHR_runopts_set_reporting_type(runOpts, CHR_TEST_REPORTING_BATCH);
    if (rc != CHR_OK) {
        show_error(test, rc, "runopts_set_reporting_type");
    }
    rc = CHR_runopts_set_test_end(runOpts, CHR_TEST_END_AFTER_FIXED_DURATION);
    if (rc != CHR_OK) {
        show_error(test, rc, "runopts_set_test_end");
    }
    rc = CHR_runopts_set_test_duration(runOpts, run_duration);
    if (rc != CHR_OK) {
        show_error(test, rc, "runopts_set_test_duration");
    }

    /* Finally, save the test */
    printf("Saving the test before the run..\n");
    rc = CHR_test_save(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "test_save");
    }
    
    /* The test is defined, so now run it */
    printf("Run the test... (%d seconds)\n", maxWait);
    rc = CHR_test_start(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "start_ test");
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

    /* Finally, save the test */
    printf("Save the test (incl. results)..\n");
    rc = CHR_test_save(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "test_save");
    }

    CHR_test_delete(test);

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

