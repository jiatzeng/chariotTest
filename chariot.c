/****************************************************************
 *
 *  IxChariot API SDK              File: ChrPairsTest.c
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
 *  EXAMPLE: Endpoint Pairs Test
 *  This program creates and runs a test with just endpoint
 *  pairs, then saves the test to a file.
 *
 *  All attributes of this test are defined by this program.
 *
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <libconfig.h>

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
    "TXRX.tst";

static
CHR_STRING testFile1 =
    "TX.tst";
     
static
CHR_STRING testFile2 =
    "RX.tst";




static
CHR_COUNT pairCount = 8;

static
CHR_COUNT pairCount1 = 6;

static
CHR_COUNT pairCount2 = 4;



static
CHR_STRING e1Addrs[] = {
    "192.168.3.100",
    "192.168.3.100",
	"192.168.3.100",
    "192.168.3.100",
    "192.168.3.100",
	"192.168.3.100",
	"192.168.3.100",
	"192.168.3.100"
};

static
CHR_STRING e2Addrs[] = {
    "192.168.3.100",
    "192.168.3.100",
	"192.168.3.100",
    "192.168.3.100",
	"192.168.3.100",
	"192.168.3.100",
	"192.168.3.100",
    "192.168.3.100"
};

static
CHR_PROTOCOL protocols[] = {
    CHR_PROTOCOL_TCP,
    CHR_PROTOCOL_TCP,
	CHR_PROTOCOL_TCP,
	CHR_PROTOCOL_TCP,
    CHR_PROTOCOL_TCP,
	CHR_PROTOCOL_TCP,
	CHR_PROTOCOL_TCP,
    CHR_PROTOCOL_TCP
};

static
CHR_TEST_END test_end[] = {
    CHR_TEST_END_AFTER_FIXED_DURATION,
    CHR_TEST_END_AFTER_FIXED_DURATION,
	CHR_TEST_END_AFTER_FIXED_DURATION,
	CHR_TEST_END_AFTER_FIXED_DURATION,
    CHR_TEST_END_AFTER_FIXED_DURATION,
	CHR_TEST_END_AFTER_FIXED_DURATION,
	CHR_TEST_END_AFTER_FIXED_DURATION,
    CHR_TEST_END_AFTER_FIXED_DURATION
};




static
CHR_STRING scripts[] = {
    "c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr",
    "c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr",
	"c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr",
	"c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr",
    "c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr",
	"c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr",
	"c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr",
    "c:/Program Files/Ixia/IxChariot/Scripts/High_Performance_Throughput.scr"
};

static
CHR_COUNT timeout = 1;    /* 5 seconds */
static
CHR_COUNT maxWait = 120;  /* 2 minutes in seconds */

static
CHR_COUNT duration = 120;



static
CHR_STRING logFile = "pairsTest.log";


static

CHR_RUNOPTS_HANDLE run;





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
    CHR_PAIR_HANDLE pair;

    char       errorInfo[CHR_MAX_ERROR_INFO];
    CHR_LENGTH errorLen;

    CHR_COUNT index;

    CHR_BOOLEAN isStopped;
    CHR_COUNT   timer = 0;

    CHR_API_RC rc;

	//config_t cfg;
    //config_setting_t *setting;
    //const char *str;

    //config_init(&cfg);

    ///* Read the file. If there is an error, report it and exit. */
    //if(! config_read_file(&cfg, "example.cfg"))
    //{
    // fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
    //        config_error_line(&cfg), config_error_text(&cfg));
    //  config_destroy(&cfg);
    //  /*return(EXIT_FAILURE);*/
    //}

    ///* Get the store name. */
    //if(config_lookup_string(&cfg, "name", &str))
    //  printf("Store name: %s\n\n", str);
    //else
    //  fprintf(stderr, "No 'name' setting in configuration file.\n");





	rc = CHR_runopts_set_test_duration(run,duration);

	rc = CHR_runopts_set_test_end(run,test_end[0]);




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
    for( index = 0; index < pairCount; index++) {

        char comment[CHR_MAX_PAIR_COMMENT];

        /* Create a pair */
        printf("Create a pair...\n");
        rc = CHR_pair_new(&pair);
        if (rc != CHR_OK) {
            show_error((CHR_HANDLE)NULL, rc, "pair_new");
        }

        /* Set the pair attributes from our lists */
        printf("Set pair attributes...\n");
        sprintf(comment, "Pair %d", index+1);
        rc = CHR_pair_set_comment(pair,
                                  comment,
                           strlen(comment));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_comment");
        }
        rc = CHR_pair_set_e1_addr(pair,
                                  e1Addrs[index],
                           strlen(e1Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e1_addr");
        }
        rc = CHR_pair_set_e2_addr(pair,
                                  e2Addrs[index],
                           strlen(e2Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e2_addr");
        }
        rc = CHR_pair_set_protocol(pair, protocols[index]);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_protocol");
        }
        rc = CHR_pair_use_script_filename(pair,
                                          scripts[index],
                                   strlen(scripts[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_use_script_filename");
        }

        /* Add the pair to the test */
        rc = CHR_test_add_pair(test, pair);
        if (rc != CHR_OK) {
            show_error(test, rc, "test_add_pair");
        }
    }

    /* The test is defined, so now run it */
    /*printf("Run the test...\n");
    rc = CHR_test_start(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "start_ test");
    }

    /*
     * Wait for the test to stop
     * We'll check in a loop here every 5 seconds
     * then call it an error after two minutes if
     * the test is still not stopped.
     */
    /*printf("Wait for the test to stop...\n");
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
    printf("Save the test..\n");
    rc = CHR_test_save(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "test_save");
    }

    /*
     * The test was successfully saved, so we're done!
     */
    /*exit(EXIT_SUCCESS);*/



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
    rc = CHR_test_set_filename(test, testFile1, strlen(testFile1));
    if (rc != CHR_OK) {
        show_error(test, rc, "test_set_filename");
    }

    /* Define some pairs for the test */
    for( index = 0; index < pairCount1; index++) {

        char comment[CHR_MAX_PAIR_COMMENT];

        /* Create a pair */
        printf("Create a pair...\n");
        rc = CHR_pair_new(&pair);
        if (rc != CHR_OK) {
            show_error((CHR_HANDLE)NULL, rc, "pair_new");
        }

        /* Set the pair attributes from our lists */
        printf("Set pair attributes...\n");
        sprintf(comment, "Pair %d", index+1);
        rc = CHR_pair_set_comment(pair,
                                  comment,
                           strlen(comment));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_comment");
        }
        rc = CHR_pair_set_e1_addr(pair,
                                  e1Addrs[index],
                           strlen(e1Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e1_addr");
        }
        rc = CHR_pair_set_e2_addr(pair,
                                  e2Addrs[index],
                           strlen(e2Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e2_addr");
        }
        rc = CHR_pair_set_protocol(pair, protocols[index]);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_protocol");
        }
        rc = CHR_pair_use_script_filename(pair,
                                          scripts[index],
                                   strlen(scripts[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_use_script_filename");
        }

        /* Add the pair to the test */
        rc = CHR_test_add_pair(test, pair);
        if (rc != CHR_OK) {
            show_error(test, rc, "test_add_pair");
        }
    }

    /* The test is defined, so now run it */
    /*printf("Run the test...\n");
    rc = CHR_test_start(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "start_ test");
    }

    /*
     * Wait for the test to stop
     * We'll check in a loop here every 5 seconds
     * then call it an error after two minutes if
     * the test is still not stopped.
     */
    /*printf("Wait for the test to stop...\n");
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
    printf("Save the test..\n");
    rc = CHR_test_save(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "test_save");
    }

    /*
     * The test was successfully saved, so we're done!
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
        exit(255);
    }

    /* Create a new test */
    printf("Create the test...\n");
    rc = CHR_test_new(&test);
    if (rc != CHR_OK) {
        show_error((CHR_HANDLE)NULL, rc, "test_new");
    }

    /* Set the test filename for saving later */
    rc = CHR_test_set_filename(test, testFile2, strlen(testFile2));
    if (rc != CHR_OK) {
        show_error(test, rc, "test_set_filename");
    }

    /* Define some pairs for the test */
    for( index = 0; index < pairCount2; index++) {

        char comment[CHR_MAX_PAIR_COMMENT];

        /* Create a pair */
        printf("Create a pair...\n");
        rc = CHR_pair_new(&pair);
        if (rc != CHR_OK) {
            show_error((CHR_HANDLE)NULL, rc, "pair_new");
        }

        /* Set the pair attributes from our lists */
        printf("Set pair attributes...\n");
        sprintf(comment, "Pair %d", index+1);
        rc = CHR_pair_set_comment(pair,
                                  comment,
                           strlen(comment));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_comment");
        }
        rc = CHR_pair_set_e1_addr(pair,
                                  e1Addrs[index],
                           strlen(e1Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e1_addr");
        }
        rc = CHR_pair_set_e2_addr(pair,
                                  e2Addrs[index],
                           strlen(e2Addrs[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e2_addr");
        }
        rc = CHR_pair_set_protocol(pair, protocols[index]);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_protocol");
        }
        rc = CHR_pair_use_script_filename(pair,
                                          scripts[index],
                                   strlen(scripts[index]));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_use_script_filename");
        }

        /* Add the pair to the test */
        rc = CHR_test_add_pair(test, pair);
        if (rc != CHR_OK) {
            show_error(test, rc, "test_add_pair");
        }
    }

    /* The test is defined, so now run it */
    /*printf("Run the test...\n");
    rc = CHR_test_start(test);
    if (rc != CHR_OK) {
        show_error(test, rc, "start_ test");
    }

    /*
     * Wait for the test to stop
     * We'll check in a loop here every 5 seconds
     * then call it an error after two minutes if
     * the test is still not stopped.
     */
    /*printf("Wait for the test to stop...\n");
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