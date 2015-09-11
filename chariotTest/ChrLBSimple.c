/****************************************************************
 *
 *  IxChariot API SDK              File: ChrLBSimple.c
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
 *  EXAMPLE: Your First Program
 *
 *  This program creates and runs a simple loopback test using
 *  the File Send, Short Connection script, prints some results,
 *  and saves it to disk.
 *
 *  All attributes of this test are defined by this program.
 *
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * The header file which defines everything in the Chariot API:
 * functions, constants, etc.
 */
#include "chrapi.h"

/*
 * Local function to print information about errors.
 */
static void
show_error(
    CHR_HANDLE handle,
    CHR_API_RC code,
    CHR_STRING where);

/*
 * Data for the test:
 * Change these for your local network if desired.
 */
static
CHR_STRING e1 = "localhost";
static
CHR_STRING e2 = "localhost";
static
CHR_STRING script   = "c:/Program Files/Ixia/IxChariot/Scripts/Throughput.scr";
static
CHR_STRING testfile = "lbtest.tst";
static
CHR_COUNT timeout   = 120;  /* 2 minutes in seconds */


/**************************************************************
 *
 * Program main
 *
 * If the return code from any Chariot API function call
 * is not CHR_OK, the show_error() function is called to
 * display information about what happened then exit.
 *
 * The numbers is parentheses in the comments refer to the
 * Program Notes section of the Chariot API Programming Guide.
 *
 **************************************************************/

void main()
{
    /*
     * The object handles we'll need
     */
    CHR_TEST_HANDLE test = (CHR_TEST_HANDLE)NULL;
    CHR_PAIR_HANDLE pair = (CHR_PAIR_HANDLE)NULL;

    /*
     * Variables and buffers for the attributes and results
     */
    CHR_COUNT    pairCount;
    CHR_PROTOCOL protocol;

    char addr[CHR_MAX_ADDR];
    char scriptName[CHR_MAX_FILENAME];
    char applScriptName[CHR_MAX_APPL_SCRIPT_NAME];

    CHR_LENGTH len;

    CHR_COUNT timingRecCount;
    CHR_FLOAT avg, min, max;

    /*
     * Buffer for extended error info for initialization
     */
    char errorInfo[CHR_MAX_ERROR_INFO];


    /*
     * Chariot API return code
     */
    CHR_API_RC rc;


    /* (1)
     * You have to initialize the Chariot API
     * before you can use the functions in it.
     * This is the only Chariot API function
     * which includes extended error information
     * in its calling parameters, since it is
     * not associated with an object.
     */
    rc = CHR_api_initialize(CHR_DETAIL_LEVEL_ALL, errorInfo,
                            CHR_MAX_ERROR_INFO, &len);
    if (CHR_OK != rc) {
        /*
         * Because initialization failed, we can't
         * ask the API for the message for this
         * return code, so we can't call our
         * show_error() function. Instead, we'll
         * print what we do know before exiting.
         */
        printf("Initialization failed: rc = %d\n", rc);
        printf("Extended error info:\n%s\n", errorInfo);
    }

    /* (2)
     * You must create a test object to define a new test
     * or to load an existing test from disk.
     */
    if (CHR_OK == rc) {
        printf("Create the test...\n");
        rc = CHR_test_new(&test);
        if (rc != CHR_OK) {
            show_error((CHR_HANDLE)NULL, rc, "test_new");
        }
    }

    /* (3)
     * You must create a pair object in order to define it.
     */
    if (CHR_OK == rc) {
        printf("Create the pair...\n");
        rc = CHR_pair_new(&pair);
        if (rc != CHR_OK) {
            show_error((CHR_HANDLE)NULL, rc, "pair_new");
        }
    }

    /* (4)
     * Once you have a pair, you can define its attributes.
     */
    if (CHR_OK == rc) {
        printf("Set required pair attributes...\n");
        rc = CHR_pair_set_e1_addr(pair, e1, strlen(e1));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e1_addr");
        }
    }

    if (CHR_OK == rc) {
        rc = CHR_pair_set_e2_addr(pair, e2, strlen(e2));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_set_e2_addr");
        }
    }

    /* (5)
     * You must define a script for use in the test.
     */
    if (CHR_OK == rc) {
        printf("Use a script...\n");
        rc = CHR_pair_use_script_filename(pair,
                                          script, strlen(script));
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_use_script_filename");
        }
    }

    /* (6)
     * Now that the pair is defined, you can add it to the test.
     */
    if (CHR_OK == rc) {
        printf("Add the pair to the test...\n");
        rc = CHR_test_add_pair(test, pair);
        if (rc != CHR_OK) {
            show_error(test, rc, "test_add_pair");
        }
    }

    /* (7)
     * We have a test defined, so now we can run it.
     */
    if (CHR_OK == rc) {
        printf("Run the test...\n");
        rc = CHR_test_start(test);
        if (rc != CHR_OK) {
            show_error(test, rc, "test_start");
        }
    }

    /* (8)
     * We have to wait for the test to stop before we can look
     * at the results from it. We'll wait for 2 minutes here,
     * then call it an error if it has not yet stopped.
     */
    if (CHR_OK == rc) {
        printf("Wait for the test to stop...\n");
        rc = CHR_test_query_stop(test, timeout);
        if (rc != CHR_OK) {
            show_error(test, rc, "test_query_stop");
        }
    }

    /* (9)
     * Let's print out how we defined the test before printing
     * results from running it. Since we have the pair handle
     * from when we created it, we don't need to get it from
     * the test.
     */

    if (CHR_OK == rc) {
        printf("===========\n");
        printf("Test setup:\n----------\n");
    
        rc = CHR_test_get_pair_count(test, &pairCount);
        if (rc != CHR_OK) {
            show_error(test, rc, "get_pair_count");
        }
        printf("Number of pairs = %d\n", pairCount);
    }

    if (CHR_OK == rc) {
        rc = CHR_pair_get_e1_addr(pair, addr, CHR_MAX_ADDR, &len);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_get_e1_addr");
        }
        printf("E1 address      : %s\n", addr);
    }

    if (CHR_OK == rc) {
        rc = CHR_pair_get_e2_addr(pair, addr, CHR_MAX_ADDR, &len);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_get_e2_addr");
        }
        printf("E2 address      : %s\n", addr);
    }

    /*
     * We didn't set protocol, but let's show it anyway .
     */
    if (CHR_OK == rc) {
        rc = CHR_pair_get_protocol(pair, &protocol);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_get_protocol");
        }
        printf("Protocol        : %d\n", protocol);
    }

    /*
     * We'll show both the script filename and
     * the application script name.
     */
    if (CHR_OK == rc) {
        rc = CHR_pair_get_script_filename(pair, scriptName,
                                           CHR_MAX_FILENAME, &len);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_get_script_filename");
        }
        printf("Script filename : %s\n", scriptName);
    }

    if (CHR_OK == rc) {
        rc = CHR_pair_get_appl_script_name(pair, applScriptName,
                                           CHR_MAX_APPL_SCRIPT_NAME,
                                           &len);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_get_appl_script_name");
        }
        printf("Appl script name: %s\n", applScriptName);
    }

    /* (10)
     * Now let's get some results:
     * the number of timing records and
     * the throughput (avg, min, max),
     */
    if (CHR_OK == rc) {
        printf("\nTest results:\n------------\n");
        rc = CHR_pair_get_timing_record_count(pair, &timingRecCount);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_get_timing_record_count");
        }
        printf("Number of timing records = %d\n", timingRecCount);
    }

    /* (11)
     * We're not going to check for NO_SUCH_VALUE here
     * although we should. This return code signals that
     * the requested result is not available for this
     * particular test. These kinds of results are shown
     * as "n/a" in the Chariot console display. In this case,
     * though, we should be able to get throughput. we'll call
     * any other return code except CHR_OK an error.
     */
    if (CHR_OK == rc) {
        rc = CHR_pair_results_get_average(pair,
                                          CHR_RESULTS_THROUGHPUT,
                                         &avg);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_results_get_average");
        }
    }
    if (CHR_OK == rc) {
        rc = CHR_pair_results_get_minimum(pair,
                                          CHR_RESULTS_THROUGHPUT,
                                         &min);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_results_get_minimum");
        }
    }
    if (CHR_OK == rc) {
        rc = CHR_pair_results_get_maximum(pair,
                                          CHR_RESULTS_THROUGHPUT,
                                         &max);
        if (rc != CHR_OK) {
            show_error(pair, rc, "pair_results_get_maximum");
        }

        /*
         * We'll format these to look like the way the Chariot
         * console displays these kinds of numbers.
         */
        printf("Throughput:\n  avg %.3f  min %.3f  max %.3f\n",
                avg, min, max);
    }

    /* (12)
     * Finally, let's save the test so we can look at it again.
     * We have to set the filename before we can save it.
     */
    if (CHR_OK == rc) {
        printf("==========\nSave the test...\n");
        rc = CHR_test_set_filename(test,
                                   testfile, strlen(testfile));
        if (rc != CHR_OK) {
            show_error(test, rc, "test_set_filename");
        } else {
            rc = CHR_test_save(test);
        }

        if (rc != CHR_OK) {
            show_error(test, rc, "test_save");
        }
    }


    /* (13)
     * Explicitly free allocated resources 
     */
    if ( pair != (CHR_PAIR_HANDLE)NULL ) {
        CHR_pair_delete(pair);
    }
    if ( test != (CHR_TEST_HANDLE)NULL ) {
        CHR_test_delete(test);
    }

    /*
     * Exit test with success or error code.
     */
    exit(rc);
}


/**************************************************************
 *
 * Print information about an error and exit.
 *
 * Parameters: handle - what object had the error
 *             code   - the Chariot API return code
 *             where  - what function call failed
 *
 **************************************************************/

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
            printf("Extended error info:\n%s\n", errorInfo);
        }
    }
}

