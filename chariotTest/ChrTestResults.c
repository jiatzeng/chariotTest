/****************************************************************
 *
 *  IxChariot API SDK              File: ChrTestResults.c
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
 *
 *  This program creates and runs a simple loopback test that
 *  uses the 802.11 and Script Embedded Payload features that
 *  were added in IxChariot 6.0.
 *
 *  All attributes of this test are defined by this program.
 *
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * The header file which defines everything in the Chariot API:
 * functions, constants, etc
 */
#include "chrapi.h"

/*
 * Local function to print results common to pairs,
 * mpairs and timing records
 */
static void
show_common(
    CHR_HANDLE handle );

/*
 * Local function to print results common to pairs and mpairs.
 */
static void
show_results(
    CHR_HANDLE handle);

/*
 * Local function to print results for all timing records.
 */
static void
show_timing_rec(
    CHR_HANDLE timingRec);

/*
 * Local function to log & print information about errors.
 */
static void
show_error(
    CHR_HANDLE handle,
    CHR_API_RC code,
    CHR_STRING where);

/*
 * Local function to print information about results get errors.
 */
static void
show_results_error(
    CHR_API_RC rc,
    CHR_STRING where);

/*
 * Local function to print common protocol string.
 */
static char*
show_protocol_string(
    CHR_PROTOCOL protocol);

/*
 * Local function to print information about how a test ended.
 */
static char*
show_how_ended_string(
    CHR_TEST_HOW_ENDED howEnded);

/*
 * Local function to print units used to express throughput
 */
static char*
show_throughput_units_string(
    CHR_THROUGHPUT_UNITS throughputUnits);

/***************************************************************
 *
 * Program main
 *
 * Command line: ChrTestResults filename [timingRecIter]
 * where:        filename is the name of the file from which
 *               to load the test. If "?", display usage.
 *               timingRecIter is the timing record iterator
 *               to display every Nth timing record's results.
 *
 * If the return code from any Chariot API function call
 * is not CHR_OK, the show_error() function is called to
 * display information about what happened then exit.
 *
 ***************************************************************/

void main(int argc, char* argv[]) {

    CHR_TEST_HANDLE      test;
    CHR_PAIR_HANDLE      pair;
    CHR_MGROUP_HANDLE    mgroup;
    CHR_MPAIR_HANDLE     mpair;
    CHR_TIMINGREC_HANDLE timingRec;

    int timingRecIter = 0;

    char errorInfo[CHR_MAX_ERROR_INFO];

    char buffer[CHR_MAX_FILE_PATH]; /* test filename needs the
                                     * biggest buffer, so we'll
                                     * make the general buffer
                                     * that big and use it for
                                     * everything */
    struct tm            when;
    CHR_THROUGHPUT_UNITS throughput;
    CHR_PROTOCOL         protocol;
    CHR_PORT             multicastPort;
    CHR_BOOLEAN          useConsoleE1;
    CHR_TEST_HOW_ENDED   endCode;

    CHR_COUNT            pairCount,   prIndex;
    CHR_COUNT            mgroupCount, mgrpIndex;
    CHR_COUNT            mpairCount,  mprIndex;
    CHR_COUNT            timingRecCount, index;
    CHR_COUNT            lastPrinted, lastIndex;

    CHR_MESSAGE_NUMBER   msgNumber;

    CHR_LENGTH len;

    CHR_API_RC rc;


    /*
     * Get what's on the command line
     *  argv[0] = program name
     *  argv[1] = test filename to load
     *  argv[2] = display every Nth timing record (optional)
     */
    if (argc < 2 || argc > 3 || strcmp(argv[1], "?") == 0) {
        printf(
        "Usage: ChrTestResults filename [timingRecIter]\n");
        printf(" filename = test file to load\n");
        printf(
        " timingRecIter = show Nth timing rec (optional)\n");
        exit(EXIT_FAILURE);
    }
    strcpy(buffer, argv[1]);
    if (argc == 3) {
        timingRecIter = atoi(argv[2]);
    }

    /*
     * Initialize the Chariot API
     */
    rc = CHR_api_initialize(CHR_DETAIL_LEVEL_ALL, errorInfo,
                            CHR_MAX_ERROR_INFO, &len);
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

    /*
     * Create a test object and load the test from disk
     */
    printf("Create the test...\n");
    rc = CHR_test_new(&test);
    if (rc != CHR_OK ) {
        show_error((CHR_HANDLE)NULL, rc, "test_new");
    }
    printf("Load the test...\n");
    rc = CHR_test_load(test, buffer, strlen(buffer));
    if (rc != CHR_OK ) {
        show_error(test, rc, "test_load");
    }

    /*
     * Print the Test definition
     */
    printf("===========================\n");
    printf("Test definition and results:\n");
    rc = CHR_test_get_filename(test, buffer,
                               CHR_MAX_FILENAME, &len);
    if (rc != CHR_OK ) {
        show_error(test, rc, "test_get_filename");
    }
    printf("  Filename        : %s\n", buffer);
    rc = CHR_test_get_throughput_units(test, &throughput);
    if (rc != CHR_OK ) {
        show_error(test, rc, "test_get_throughput_units");
    }
    printf("  Throughput units: %s\n", show_throughput_units_string(throughput));

    /*
     * We may not be able to get these if the test
     * was stopped by an initialization error.
     */
    rc = CHR_test_get_local_start_time(test, &when);
    if (rc != CHR_OK ) {
        show_results_error(rc, "start time");
    }
    else {
        printf("  Start time: %s", asctime(&when));
    }
    rc = CHR_test_get_local_stop_time(test, &when);
    if (rc != CHR_OK ) {
        show_results_error(rc, "stop time");
    }
    else {
        printf("  Stop time : %s", asctime(&when));
    }
    rc = CHR_test_get_how_ended(test, &endCode);
    if (rc != CHR_OK ) {
        show_error(test, rc, "test_get_how_ended");
    }
    printf("  How ended : %s\n", show_how_ended_string(endCode));
    rc = CHR_test_get_pair_count(test, &pairCount);
    if (rc != CHR_OK ) {
        show_error(test, rc, "test_get_pair_count");
    }
    printf("  Number of pairs   = %d\n", pairCount);
    rc = CHR_test_get_mgroup_count(test, &mgroupCount);
    if (rc != CHR_OK ) {
        show_error(test, rc, "test_get_mgroup_count");
    }
    printf("  Number of mgroups = %d\n", mgroupCount);

    /*
     * Print the definition and results for each pair
     */
    for (prIndex = 0; prIndex < pairCount; prIndex++ ) {

        /* Print pair definition */
        printf("\nPair %d:\n", prIndex+1);
        rc = CHR_test_get_pair(test, prIndex, &pair);
        if (rc != CHR_OK ) {
            show_error(test, rc, "test_get_pair");
        }
        rc = CHR_pair_get_comment(pair, buffer,
                                  CHR_MAX_PAIR_COMMENT, &len);
        if (rc != CHR_OK ) {
            show_error(pair, rc, "pair_get_comment");
        }
        printf("  Comment            : %s\n", buffer);
        rc = CHR_pair_get_e1_addr(pair, buffer,
                                  CHR_MAX_ADDR, &len);
        if (rc != CHR_OK ) {
            show_error(pair, rc, "pair_get_e1_addr");
        }
        printf("  E1 address         : %s\n", buffer);
        rc = CHR_pair_get_e2_addr(pair, buffer,
                                  CHR_MAX_ADDR, &len);
        if (rc != CHR_OK ) {
            show_error(pair, rc, "pair_get_e2_addr");
        }
        printf("  E2 address         : %s\n", buffer);
        /*Please remove this comment if you are not using a VoIPHPP script
        rc = CHR_pair_get_protocol(pair, &protocol);
        if (rc != CHR_OK ) {
            show_error(pair, rc, "pair_get_protocol");
        }
        printf("  Protocol           : %s\n", show_protocol_string(protocol));
        */
        /*Please remove this comment if you are not using a VoIP, Video or VoIPHPP sript
        rc = CHR_pair_get_script_filename(pair, buffer,
                                          CHR_MAX_FILENAME,
                                         &len);
        if (rc != CHR_OK ) {
            show_error(pair, rc, "pair_get_script_filename");
        }
        printf("  Script filename    : %s\n", buffer);
        rc = CHR_pair_get_appl_script_name(pair, buffer,
             CHR_MAX_APPL_SCRIPT_NAME, &len);
        if (rc != CHR_OK ) {
            show_error(pair, rc, "pair_get_appl_script_name");
        }
        printf("  Appl script name   : %s\n", buffer);
        */
        rc = CHR_pair_get_qos_name(pair, buffer,
                                   CHR_MAX_QOS_NAME,
                                  &len);
        if (rc != CHR_OK ) {
            show_error(pair, rc, "pair_get_qos_name");
        }
        printf("  QOS name           : %s\n", buffer);
        
        /* Show console-e1 values only if being used */
        /*Please remove this comment if you are not using a VoIPHPP sript
        rc = CHR_pair_get_use_console_e1_values(pair,
            &useConsoleE1);
        if (rc != CHR_OK ) {
            show_error(pair, rc,
                      "pair_get_use_console_e1_values");
        }
        if (useConsoleE1) {

            rc = CHR_pair_get_console_e1_addr(pair, buffer,
                                              CHR_MAX_ADDR,
                                             &len);
            if (rc != CHR_OK ) {
                show_error(pair, rc,
                          "pair_get_console_e1_addr");
            }
            printf("  Console-E1 address : %s\n", buffer);
            rc = CHR_pair_get_console_e1_protocol(pair,
                                                 &protocol);
            if (rc != CHR_OK ) {
                show_error(pair, rc,
                          "pair_get_console_e1_protocol");
            }
            printf("  Console-E1 protocol: %s\n", show_protocol_string(protocol));
        }
        */
        /* Print pair results */
        printf("\nPair %d results:\n", prIndex+1);

        /*
         * Was there an error for this pair?
         * NO_SUCH_VALUE means there was no run error
         */
        rc = CHR_common_error_get_msg_num(pair,
                                         &msgNumber);
        if (rc != CHR_OK && rc != CHR_NO_SUCH_VALUE) {
            show_error(pair, rc, "get_msg_num");
        }
        if (rc == CHR_OK) {

            /*
             * If there is a message number, there
             * is extended error info showing what
             * happened for this pair during the run.
             */
            printf("Pair error! Msg num = %d\n", msgNumber);
            rc = CHR_common_error_get_info(pair,
                 CHR_DETAIL_LEVEL_ALL, errorInfo,
                 CHR_MAX_ERROR_INFO, &len);
            if (rc != CHR_OK ) {
                show_error(pair, rc,
                          "common_error_get_info");
            }
            printf("%s\n", errorInfo);
        }

        /*
         * Show results for this pair.
         * Even if there was a run error,
         * there could be some results.
         */
        show_results(pair);

        /* Show timing records if selected */
        rc = CHR_pair_get_timing_record_count(pair,
                                             &timingRecCount);
        if (rc != CHR_OK) {
          show_error(pair, rc,
                     "pair_get_timing_record_count");
        }
        printf("  Number of timing records = %d\n",
               timingRecCount);
        if (timingRecIter != 0 && timingRecCount != 0) {

            printf("\n");
            for (index = 0;
                 index <  timingRecCount;
                 index += timingRecIter) {

                printf("Timing record %d:\n", index+1);
                rc = CHR_pair_get_timing_record(pair,
                     index, &timingRec);
                if (rc != CHR_OK) {
                    show_error(pair, rc,
                              "pair_get_timing_record");}
                show_timing_rec(timingRec);
            }
            lastPrinted = index - timingRecIter;
            lastIndex   = timingRecCount - 1;
            if (lastPrinted != lastIndex) {

                /* Always show last timing record */
                index = timingRecCount - 1;
                printf("Timing record %d:\n", index+1);
                rc = CHR_pair_get_timing_record(pair,
                     index, &timingRec);
                if (rc != CHR_OK) {
                    show_error(pair, rc,
                              "pair_get_timing_record");
                }
                show_timing_rec(timingRec);
            }
        }
    }

    /*
     * Print the definition and results for each mgroup
     */
    for (mgrpIndex = 0; mgrpIndex < mgroupCount; mgrpIndex++ ) {

        /* Print mgroup definition */
        printf("\nMGroup %d:\n", mgrpIndex+1);
        rc = CHR_test_get_mgroup(test, mgrpIndex, &mgroup);
        if (rc != CHR_OK ) {
            show_error(test, rc, "test_get_mgroup");
        }
        rc = CHR_mgroup_get_name(mgroup, buffer,
                                 CHR_MAX_GROUP_NAME, &len);
        if (rc != CHR_OK ) {
            show_error(mgroup, rc, "mgroup_get_name");
        }
        printf("  Name               : %s\n", buffer);
        rc = CHR_mgroup_get_comment(mgroup, buffer,
                                    CHR_MAX_PAIR_COMMENT,
                                   &len);
        if (rc != CHR_OK ) {
            show_error(mgroup, rc, "mgroup_get_comment");
        }
        printf("  Comment            : %s\n", buffer);
        rc = CHR_mgroup_get_multicast_addr(mgroup,
             buffer, CHR_MAX_ADDR, &len);
        if (rc != CHR_OK ) {
            show_error(mgroup, rc,
                      "mgroup_get_multicast_addr");
        }
        printf("  Multicast address  : %s\n", buffer);
        rc = CHR_mgroup_get_multicast_port(mgroup,
                                          &multicastPort);
        if (rc != CHR_OK ) {
            show_error(mgroup, rc,
                      "mgroup_get_multicast_port");
        }
        printf("  Multicast port     : %d\n", multicastPort);
        rc = CHR_mgroup_get_e1_addr(mgroup, buffer,
                                    CHR_MAX_ADDR, &len);
        if (rc != CHR_OK ) {
            show_error(mgroup, rc, "mgroup_get_e1_addr");
        }
        printf("  E1 address         : %s\n", buffer);
        rc = CHR_mgroup_get_protocol(mgroup, &protocol);
        if (rc != CHR_OK ) {
            show_error(mgroup, rc, "mgroup_get_protocol");
        }
        printf("  Protocol           : %s\n", show_protocol_string(protocol));
        rc = CHR_mgroup_get_script_filename(mgroup, buffer,
                                            CHR_MAX_FILENAME,
                                           &len);
        if (rc != CHR_OK ) {
            show_error(mgroup, rc,
                      "mgroup_get_script_filename");
        }
        printf("  Script filename    : %s\n", buffer);
        rc = CHR_mgroup_get_appl_script_name(mgroup, buffer,
             CHR_MAX_APPL_SCRIPT_NAME, &len);
        if (rc != CHR_OK ) {
            show_error(mgroup, rc,
                      "mgroup_get_appl_script_name");
        }
        printf("  Appl script name   : %s\n", buffer);
        rc = CHR_mgroup_get_qos_name(mgroup, buffer,
                                     CHR_MAX_QOS_NAME, &len);
        if (rc != CHR_OK ) {
            show_error(mgroup, rc, "mgroup_get_qos_name");
        }
        printf("  QOS name           : %s\n", buffer);

        /* Show console-e1 values only if being used */
        rc = CHR_mgroup_get_use_console_e1_values(mgroup,
            &useConsoleE1);
        if (rc != CHR_OK ) {
            show_error(mgroup, rc,
                      "mgroup_get_use_console_e1_values");
        }
        if (useConsoleE1) {

            rc = CHR_mgroup_get_console_e1_addr(mgroup,
                                                buffer,
                                                CHR_MAX_ADDR,
                                               &len);
            if (rc != CHR_OK ) {
                show_error(mgroup, rc,
                          "mgroup_get_console_e1_addr");
            }
            printf("  Console-E1 address : %s\n", buffer);
            rc = CHR_mgroup_get_console_e1_protocol(mgroup,
                                                   &protocol);
            if (rc != CHR_OK ) {
                show_error(mgroup, rc,
                          "mgroup_get_console_e1_protocol");
            }
            printf("  Console-E1 protocol: %s\n", show_protocol_string(protocol));
        }

        /* Print out each mpair & its results */
        rc = CHR_mgroup_get_mpair_count(mgroup, &mpairCount);
        if (rc != CHR_OK ) {
            show_error(mgroup, rc, "mgroup_get_mpair_count");
        }
        printf("  Number of mpairs = %d\n", mpairCount);

        for (mprIndex = 0;
             mprIndex < mpairCount;
             mprIndex++ ) {

            printf("\nMPair %d:\n", mprIndex+1);
            rc = CHR_mgroup_get_mpair(mgroup,
                                      mprIndex, &mpair);
            if (rc != CHR_OK ) {
                show_error(mgroup, rc, "mgroup_get_mpair");
            }

            rc = CHR_mpair_get_e2_addr(mpair, buffer,
                                       CHR_MAX_ADDR, &len);
            if (rc != CHR_OK ) {
                show_error(mpair, rc, "mpair_get_e2_addr");
            }
            printf("  E2 address: %s\n", buffer);

            /* Print mpair results */
            printf("\nMPair %d results:\n", mprIndex+1);

            /*
             * Was there an error for this pair?
             * NO_SUCH_VALUE means there was no run error
             */
            rc = CHR_common_error_get_msg_num(mpair,
                                             &msgNumber);
            if (rc != CHR_OK && rc != CHR_NO_SUCH_VALUE) {
                show_error(pair, rc, "get_msg_num");
            }
            if (rc == CHR_OK) {

                /*
                 * If there is a message number, there
                 * is extended error info showing what
                 * happened for this pair during the run.
                 */
                printf("MPair error! Msg num = %d\n", msgNumber);
                rc = CHR_common_error_get_info(mpair,
                     CHR_DETAIL_LEVEL_ALL, errorInfo,
                     CHR_MAX_ERROR_INFO, &len);
                if (rc != CHR_OK ) {
                    show_error(pair, rc,
                               "common_error_get_info");
                }
                printf("%s\n", errorInfo);
            }

            /*
             * Show results for this pair.
             * Even if there was a run error,
             * there could be some results.
             */
            show_results(mpair);

            /* Show timing records if selected */
            rc = CHR_mpair_get_timing_record_count(mpair,
                &timingRecCount);
            if (rc != CHR_OK) {
                show_error(mpair, rc,
                          "mpair_get_timing_record_count");
            }
            printf("  Number of timing records = %d\n",
                   timingRecCount);
            if (timingRecIter != 0 && timingRecCount != 0) {

                printf("\n");
                for (index = 0;
                    index <  timingRecCount;
                    index += timingRecIter) {

                    printf("Timing record %d:\n", index+1);
                    rc = CHR_mpair_get_timing_record(mpair,
                                                     index,
                                                    &timingRec);
                    if (rc != CHR_OK) {
                        show_error(mpair, rc,
                                   "mpair_get_timing_record");
                    }
                    show_timing_rec(timingRec);
                }
                lastPrinted = index - timingRecIter;
                lastIndex   = timingRecCount - 1;
                if (lastPrinted != lastIndex) {

                    /* Always show last timing record */
                    index = timingRecCount - 1;
                    printf("Timing record %d:\n", index+1);
                    rc = CHR_mpair_get_timing_record(mpair,
                                                     index,
                                                    &timingRec);
                    if (rc != CHR_OK) {
                        show_error(pair, rc,
                                   "mpair_get_timing_record");
                    }
                    show_timing_rec(timingRec);
                }
            }
        }
    }

    /* All done! */
    exit(EXIT_SUCCESS);
}

/**************************************************************
 *
 * Print results common to pairs mpairs, and timing records.
 * Show "n/a" is NO_SUCH_VALUE is returned.
 *
 * Parameters: handle to object for which to get results
 *
 * Note: If the attempt to get any results fails, a message
 *       is printed showing the reason and we return rather
 *       than force exit of the program, since an error when
 *       getting results is not necessarily a fatal condition.
 **************************************************************/
static void
show_common(
    CHR_HANDLE handle)
{
    CHR_API_RC rc;
    CHR_FLOAT  float_result;
    CHR_COUNT  count_result;

    /*
     * These do not have NO_SUCH_VALUE as a possible return,
     * so anything other than success is an error
     */
    rc = CHR_common_results_get_meas_time(handle, &float_result);
    if (rc != CHR_OK ) {
        show_results_error(rc, "meas_time");
        return;
    }
    printf("  Measured time           : %.3f\n", float_result);

    rc = CHR_common_results_get_trans_count(handle, &float_result);
    if (rc != CHR_OK ) {
        show_results_error(rc, "trans_count");
        return;
    }
    printf("  Transaction count       : %.0f\n", float_result);

    /*
     * These could have NO_SUCH_VALUE as a valid return,
     * depending on the specifics of the test.
     */
    /*Please remove this comment if you are not using a VoIPHPP sript
    rc = CHR_common_results_get_bytes_sent_e1(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Bytes sent E1            : n/a\n");
        }
        else {
            show_results_error(rc, "bytes_sent_e1");
            return;
        }
    }
    else {
        printf("  Bytes sent E1           : %.0f\n", float_result);
    }

    rc = CHR_common_results_get_bytes_recv_e1(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Bytes recv E1           : n/a\n");
        }
        else {
            show_results_error(rc, "bytes_recv_e1");
            return;
        }
    }
    else {
        printf("  Bytes recv E1           : %.0f\n", float_result);
    }

    rc = CHR_common_results_get_bytes_recv_e2(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Bytes recv E2           : n/a\n");
        }
        else {
            show_results_error(rc, "bytes_recv_e2");
            return;
        }
    }
    else {
        printf("  Bytes recv E2           : %.0f\n", float_result);
    }

    rc = CHR_common_results_get_dg_sent_e1(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  DGs sent E1             : n/a\n");
        }
        else {
            show_results_error(rc, "dg_sent_e1");
            return;
        }
    }
    else {
        printf("  DGs sent E1             : %.0f\n", float_result);
    }

    rc = CHR_common_results_get_dg_recv_e2(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  DGs recv E2             : n/a\n");
        }
        else {
            show_results_error(rc, "dg_recv_e2");
            return;
        }
    }
    else {
        printf("  DGs recv E2             : %.0f\n", float_result);
    }

    rc = CHR_common_results_get_dg_dup_recv_e2(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  DGs dup recv E2         : n/a\n");
        }
        else {
            show_results_error(rc, "dg_dup_recv_e2");
            return;
        }
    }
    else {
        printf("  DGs dup recv E2         : %.0f\n", float_result);
    }

    rc = CHR_common_results_get_dg_lost_e1_to_e2(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  DGs lost E1 to E2       : n/a\n");
        }
        else {
            show_results_error(rc, "dg_lost_e1_to_e2");
            return;
        }
    }
    else {
        printf("  DGs lost E1 to E2       : %.0f\n", float_result);
    }

    rc = CHR_common_results_get_dg_out_of_order(handle, &float_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  DGs out of order        : n/a\n");
        }
        else {
            show_results_error(rc, "dg_out_of_order");
            return;
        }
    }
    else {
        printf("  DGs out of order        : %.0f\n", float_result);
    }
    */ 
    /* TCP Statistics */
    /*Please remove this comment if you are not using a VoIPHPP sript
    rc = CHR_common_results_get_e1_syn_tx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Syn sent                : n/a\n");
        }
        else {
            show_results_error(rc, "Syn sent");
            return;
        }
    }
    else {
        printf("  Syn sent                : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_syn_rx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Syn received            : n/a\n");
        }
        else {
            show_results_error(rc, "Syn received");
            return;
        }
    }
    else {
        printf("  Syn received            : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_syn_failed(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Syn failed              : n/a\n");
        }
        else {
            show_results_error(rc, "Syn failed");
            return;
        }
    }
    else {
        printf("  Syn failed              : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_conn_established(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Connections established : n/a\n");
        }
        else {
            show_results_error(rc, "Connections established");
            return;
        }
    }
    else {
        printf("  Connections established : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_fin_tx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Fin sent                : n/a\n");
        }
        else {
            show_results_error(rc, "Fin sent");
            return;
        }
    }
    else {
        printf("  Fin sent                : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_fin_rx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Fin received            : n/a\n");
        }
        else {
            show_results_error(rc, "Fin received");
            return;
        }
    }
    else {
        printf("  Fin received            : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_ack_to_fin_tx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Ack to Fin sent         : n/a\n");
        }
        else {
            show_results_error(rc, "Ack to Fin sent");
            return;
        }
    }
    else {
        printf("  Ack to Fin sent         : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_ack_to_fin_rx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Ack to Fin received     : n/a\n");
        }
        else {
            show_results_error(rc, "Ack to Fin received");
            return;
        }
    }
    else {
        printf("  Ack to Fin received     : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_rst_tx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Reset sent              : n/a\n");
        }
        else {
            show_results_error(rc, "Reset sent");
            return;
        }
    }
    else {
        printf("  Reset sent              : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_rst_rx(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Reset received          : n/a\n");
        }
        else {
            show_results_error(rc, "Reset received");
            return;
        }
    }
    else {
        printf("  Reset received          : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_tcp_retransmissions(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  TCP retransmissions     : n/a\n");
        }
        else {
            show_results_error(rc, "TCP retransmissions");
            return;
        }
    }
    else {
        printf("  TCP retransmissions     : %d\n", count_result);
    }

    rc = CHR_common_results_get_e1_tcp_timeouts(handle, &count_result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  TCP timeouts            : n/a\n");
        }
        else {
            show_results_error(rc, "TCP timeouts");
            return;
        }
    }
    else {
        printf("  TCP timeouts            : %d\n", count_result);
    }
    */
}

/**************************************************************
 *
 * Local function to print results common to pairs and mpairs.
 * Show "n/a" if NO_SUCH_VALUE is returned.
 *
 * Parameters: handle to object for which to get results
 *
 * Note: If the attempt to get any results fails, a message
 *       is printed showing the reason and we return to rather
 *       than force exit of the program, since an error when
 *       getting results is not necessarily a fatal condition.
 **************************************************************/
static void
show_results(
    CHR_HANDLE handle)
{
    CHR_FLOAT  avg, min, max;
    CHR_FLOAT  result;
    CHR_CHAR   format[1024];
    CHR_API_RC rc;


    /*
     * These could have NO_SUCH_VALUE as a valid return,
     * depending on the specifics of the test.
     */
    rc = CHR_pair_results_get_average(handle,
         CHR_RESULTS_TRANSACTION_RATE, &avg);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Transaction rate  : n/a\n");
        }
        else {
            show_results_error(rc, "transaction rate avg");
            return;
        }
    }
    else {

        /*
         * If we get the average, we should be able
         * to get the minimum and maximum too
         */
        rc = CHR_pair_results_get_minimum(handle,
             CHR_RESULTS_TRANSACTION_RATE, &min);
        if (rc != CHR_OK ) {
            show_results_error(rc, "transaction rate min");
            return;
        }
        rc = CHR_pair_results_get_maximum(handle,
             CHR_RESULTS_TRANSACTION_RATE, &max);
        if (rc != CHR_OK ) {
            show_results_error(rc, "transaction rate max");
            return;
        }
        printf("  Transaction rate  :\n");
        printf("    avg %.3f  min %.3f  max %.3f\n",
                    avg, min, max);
    }

    rc = CHR_pair_results_get_average(handle,
        CHR_RESULTS_RESPONSE_TIME, &avg);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Response time     : n/a\n");
        }
        else {
            show_results_error(rc, "response time avg");
            return;
        }
    }
    else {

        rc = CHR_pair_results_get_minimum(handle,
             CHR_RESULTS_RESPONSE_TIME, &min);
        if (rc != CHR_OK ) {
            show_results_error(rc, "response time min");
            return;
        }
        rc = CHR_pair_results_get_maximum(handle,
             CHR_RESULTS_RESPONSE_TIME, &max);
        if (rc != CHR_OK ) {
            show_results_error(rc, "response time max");
            return;
        }
        printf("  Response time     :\n");
        printf("    avg %.5f min %.5f max %.5f\n",
                   avg, min, max);
    }

    rc = CHR_pair_results_get_average(handle,
         CHR_RESULTS_THROUGHPUT, &avg);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Throughput        : n/a\n");
        }
        else {
            show_results_error(rc, "throughput avg");
            return;
        }
    }
    else {

        rc = CHR_pair_results_get_minimum(handle,
             CHR_RESULTS_THROUGHPUT, &min);
        if (rc != CHR_OK ) {
            show_results_error(rc, "throughput min");
            return;
        }
        rc = CHR_pair_results_get_maximum(handle,
             CHR_RESULTS_THROUGHPUT, &max);
        if (rc != CHR_OK ) {
            show_results_error(rc, "throughput max");
            return;
        }
        printf("  Throughput        :\n");
        printf("    avg %.3f   min %.3f   max %.3f\n",
                    avg, min, max);
    }

    rc = CHR_pair_results_get_average(handle,
         CHR_RESULTS_JITTER, &avg);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Jitter            : n/a\n");
        }
        else {
            show_results_error(rc, "jitter avg");
            return;
        }
    }
    else {

        rc = CHR_pair_results_get_minimum(handle,
             CHR_RESULTS_JITTER, &min);
        if (rc != CHR_OK ) {
            show_results_error(rc, "jitter min");
            return;
        }
        rc = CHR_pair_results_get_maximum(handle,
             CHR_RESULTS_JITTER, &max);
        if (rc != CHR_OK ) {
            show_results_error(rc, "jitter max");
            return;
        }
        printf("  Jitter            :\n");
        printf("    avg %.3f   min %.3f   max %.3f\n",
                    avg, min, max);
    }

    /*
     * These do not have NO_SUCH_VALUE as a valid return,
     * so everything other than success is an error.
     */
    /* Please remove this comment if you are not using a VoIPHPP
    rc = CHR_pair_results_get_rel_precision(handle, &result);
    if (rc != CHR_OK ) {
        show_results_error(rc, "rel_precision");
        return;
    }
    printf("  Relative precision: %.3f\n", result);

    rc = CHR_pair_results_get_95pct_confidence(handle, CHR_RESULTS_THROUGHPUT, &result);
    if (rc != CHR_OK) {
        show_results_error(rc, "Throughput 95%% confidence interval");
        return;
    }
    else {
        sprintf(format, "-%.3f / +%.3f", result, result);
        printf("  Throughput 95%% confidence interval       : %s\n", format);
    }
    */

    /*
     * These could have NO_SUCH_VALUE as a valid return,
     * depending on the specifics of the test.
     */
    /* Please remove this comment if you are not using a VoIPHPP
    rc = CHR_pair_results_get_95pct_confidence(handle, CHR_RESULTS_TRANSACTION_RATE, &result);
    if (rc != CHR_OK) {
        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Transaction rate 95%% confidence interval : n/a\n");
        }
        else {
            show_results_error(rc, "Transaction rate 95%% confidence interval");
            return;
        }
    }
    else {
        sprintf(format, "-%.3f / +%.3f", result, result);
        printf("  Transaction rate 95%% confidence interval : %s\n", format);
    }

    rc = CHR_pair_results_get_95pct_confidence(handle, CHR_RESULTS_RESPONSE_TIME, &result);
    if (rc != CHR_OK) {
        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Response time 95%% confidence interval    : n/a\n");
        }
        else {
            show_results_error(rc, "Response time 95%% confidence interval");
            return;
        }
    }
    else {
        sprintf(format, "-%.3f / +%.3f", result, result);
        printf("  Response time 95%% confidence interval    : %s\n", format);
    }

    rc = CHR_pair_results_get_95pct_confidence(handle, CHR_RESULTS_DF, &result);
    if (rc != CHR_OK) {
        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Delay factor 95%% confidence interval     : n/a\n");
        }
        else {
            show_results_error(rc, "Delay factor 95%% confidence interval");
            return;
        }
    }
    else {
        sprintf(format, "-%.3f / +%.3f", result, result);
        printf("  Delay factor 95%% confidence interval     : %s\n", format);
    }

    rc = CHR_pair_results_get_95pct_confidence(handle, CHR_RESULTS_MLR, &result);
    if (rc != CHR_OK) {
        if (rc == CHR_NO_SUCH_VALUE ) {
            printf("  Media loss rate 95%% confidence interval  : n/a\n");
        }
        else {
            show_results_error(rc, "Media loss rate 95%% confidence interval");
            return;
        }
    }
    else {
        sprintf(format, "-%.3f / +%.3f", result, result);
        printf("  Media loss rate 95%% confidence interval  : %s\n", format);
    }
    */
    /* Show common results */
    show_common(handle);
}

/**************************************************************
 *
 * Local function to print results common to timing records.
 * Show "n/a" if NO_SUCH_VALUE is returned.
 *
 * Parameters: handle to object for which to get results
 *
 * Note: If the attempt to get any results fails, a message
 *       is printed showing the reason and we return to rather
 *       than force exit of the program, since an error when
 *       getting results is not necessarily a fatal condition.
 **************************************************************/
static void
show_timing_rec(
    CHR_HANDLE timingRec)
{
    CHR_FLOAT  result;

    CHR_API_RC rc;


    /* These should be available in all timing records */
    rc = CHR_timingrec_get_elapsed(timingRec, &result);
    if (rc != CHR_OK ) {
        show_results_error(rc, "elapsed");
        return;
    }
    printf("  Elapsed time      : %.3f\n", result);

    rc = CHR_timingrec_get_inactive(timingRec, &result);
    if (rc != CHR_OK ) {
        show_results_error(rc, "inactive");
        return;
    }
    printf("  Inactive time     : %.3f\n", result);

    /* Jitter is only available sometimes */
    rc = CHR_timingrec_get_jitter(timingRec, &result);
    if (rc != CHR_OK ) {

        if (rc == CHR_NO_SUCH_VALUE) {
            printf(  "  Jitter time       : n/a\n");
        }
        else {
            show_results_error(rc, "jitter");
            return;
        }
    }
    else {
        printf("  Jitter time       : %.3f\n", result);
    }

    /* Show common results */
    show_common(timingRec);
}


/***************************************************************
 *
 * Print information about an error and exit. If there is
 * extended error information, print that too.
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
            printf("%s\n", errorInfo);
        }
    }

    /*
     * We've told everything we know, so now just exit.
     */
    exit(EXIT_FAILURE);
}

/***************************************************************
 *
 * Print information about an error that occurred while
 * getting results information. There is no extended error
 * information in these cases and we do not want to exit
 * this program as these are not fatal errors.
 *
 * Parameters: code   - the Chariot API return code
 *             what  - what function call failed
 ***************************************************************/
static void
show_results_error(
    CHR_API_RC rc,
    CHR_STRING what)
{
    char msg[CHR_MAX_RETURN_MSG];

    CHR_LENGTH len;

    CHR_API_RC msgRc;


    printf("Get %s failed: ", what);
    msgRc = CHR_api_get_return_msg(rc, msg,
                                   CHR_MAX_RETURN_MSG,
                                  &len);
    if (msgRc == CHR_OK) {
        printf("%s\n", msg);
    }
    else {
        printf("rc = %d\n", rc );
    }
}

/***************************************************************
 *
 * Print the protocol string that corresponds to the macro
 * passed to the function (macros defined in chrapi.h)
 *
 * Parameters: protocol - macro defined in chrapi.h
 *
 ***************************************************************/
static char*
show_protocol_string(
    CHR_PROTOCOL protocol)
{
    switch (protocol) {
        case CHR_PROTOCOL_IPX:
            return "IPX";
        case CHR_PROTOCOL_SPX:
            return "SPX";
        case CHR_PROTOCOL_TCP:
            return "TCP";
        case CHR_PROTOCOL_TCP6:
            return "TCP-IPv6";
        case CHR_PROTOCOL_UDP:
            return "UDP";
        case CHR_PROTOCOL_UDP6:
            return "UDP-IPv6";
        case CHR_PROTOCOL_RTP:
            return "RTP";
        case CHR_PROTOCOL_RTP6:
            return "RTP-IPv6";
        default:
            return "Unknown protocol or protocol not set";
    };
}


/***************************************************************
 *
 * Print the method by which the test was stopped, denoted by
 * macro set and passed as a parameter into this function.
 *
 * Parameters: howEnded - macro defined in chrapi.h
 *
 ***************************************************************/
static char*
show_how_ended_string(
    CHR_TEST_HOW_ENDED howEnded)
{
    switch (howEnded) {
        case CHR_TEST_HOW_ENDED_USER_STOPPED:
            return "USER STOPPED";
        case CHR_TEST_HOW_ENDED_ERROR:
            return "ERROR";
        case CHR_TEST_HOW_ENDED_NORMAL:
            return "NORMAL";
        default:
            return "Undefined";
    };
}

/***************************************************************
 *
 * Print the units in which throughput is expressed in the
 * function.
 *
 * Parameters: throughputUnits - one of MB,Mb,KB,Kb,Gb,kb as
 *             defined in chrapi.h
 *
 ***************************************************************/

static char*
show_throughput_units_string(
    CHR_THROUGHPUT_UNITS throughputUnits)
{
    switch (throughputUnits) {
        case CHR_THROUGHPUT_UNITS_KB:
            return "KB";
        case CHR_THROUGHPUT_UNITS_kB:
            return "kB";
        case CHR_THROUGHPUT_UNITS_Kb:
            return "Kb";
        case CHR_THROUGHPUT_UNITS_kb:
            return "kb";
        case CHR_THROUGHPUT_UNITS_Mb:
            return "Mb";
        case CHR_THROUGHPUT_UNITS_Gb:
            return "Gb";
        default:
            return "Unknown units or units not set";
    };
}
