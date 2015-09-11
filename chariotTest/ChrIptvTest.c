/****************************************************************
 *
 *  IxChariot API SDK              File: ChrIptvTest.c
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
 *  EXAMPLE: IPTV Test
 *  This program creates and runs a test with an IPTV receiver group,
 *  then saves the test to a file.
 *
 *  NOTE:
 *  This test requires that the Ixia network configuration file
 *  "ChrIptvTest.ixn" be in the same directory as the executable
 *  file, and that it use the same test and management addresses
 *  as the executable.
 *
 ****************************************************************/

/* Chariot API header file. */
#include "chrapi.h"

/* Standard C header files. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------*/
/*                      macro definitions                               */
/*----------------------------------------------------------------------*/

#define NO_OF_ITERATIONS        2
#define NO_OF_TIMING_RECORDS    5
#define TIMING_RECORD_DURATION  1
#define TEST_DURATION           60
#define TEST_TIMEOUT            5
#define MAX_WAIT_TIME           120

/*----------------------------------------------------------------------*/
/*                      test configuration                              */
/*----------------------------------------------------------------------*/

/**
 * Filename of the Ixia network configuration file to be loaded.
 */
static CHR_STRING lc_configFile = "ChrIptvTest.ixn";

/**
 * IP address of Endpoint 1 (the channel) on the test network.
 * Must match the value in the configuration file.
 */
static const char* lc_e1TestAddress = "172.16.1.1";

/**
 * IP address of Endpoint 2 (the receiver) on the test network. 
 * Must match the value in the configuration file. 
 */
static const char* lc_e2TestAddress = "172.16.2.1";

/**
 * Ixia port address of Endpoint 1 (the channel), in IxChariot format.
 * Must match the value in the configuration file. 
 */
static const char* lc_e1MgmtAddress = "10.200.117.11 / 02 / 01";

/**
 * Ixia port address of Endpoint 2 (the receiver), in IxChariot format.
 * Must match the value in the configuration file. 
 */
static const char* lc_e2MgmtAddress = "10.200.117.11 / 02 / 02";

/*----------------------------------------------------------------------*/
/*                      type definitions                                */
/*----------------------------------------------------------------------*/

/**
 * Channel specification structure.
 * Provides a template for the create_channel() function.
 */
struct channel_spec_s
{
    CHR_CONST_STRING m_name;
    CHR_CONST_STRING m_comment;
    CHR_CONST_STRING m_multicast_addr;
    CHR_PORT         m_multicast_port;
};

/**
 * Receiver specification structure.
 * Provides a template for the create_receiver() function.
 */
struct receiver_spec_s
{
    CHR_CONST_STRING m_name;
    CHR_CONST_STRING m_comment;
};

/*----------------------------------------------------------------------*/
/*                      data definitions                                */
/*----------------------------------------------------------------------*/

/*
 * Channel specifications.
 */
static const struct channel_spec_s lc_channelSpec1 =
{
    "ABC",
    "Antarctic Broadcasting Corporation",
    "224.0.10.1",
    22400
};

static const struct channel_spec_s lc_channelSpec2 =
{
    "EBC",
    "Estonian Broadcasting Corporation",
    "224.0.10.2",
    22402
};

static const struct channel_spec_s lc_channelSpec3 =
{
    "LBC",
    "Latvian Broadcasting Corporation",
    "224.0.10.3",
    22404
};

/*
 * Receiver specifications.
 */
static const struct receiver_spec_s lc_receiverSpec1 =
{
    "STB1",
    "International News Junkie"
};

/*
 * File specifications.
 */
static CHR_STRING lc_testFile = "chriptvtest_c.tst";
static const char* lc_logFile = "chriptvtest_c.log";

/*----------------------------------------------------------------------*/
/*                      show_error                                      */
/*----------------------------------------------------------------------*/

/**
 * Displays error information and exits. 
 *  
 * @param handle    Handle of the object that had the error.
 * @param code      Chariot API return code.
 * @param what      String describing the operation that failed.
 */
static void
show_error(
    CHR_HANDLE  handle,
    CHR_API_RC  code,
    CHR_STRING  what)
{
    char       msg[CHR_MAX_RETURN_MSG];
    CHR_LENGTH msgLen;

    char       errorInfo[CHR_MAX_ERROR_INFO];
    CHR_LENGTH errorLen;

    FILE*   fd;
    time_t  currentTime;
    char*   timestamp;

    CHR_API_RC rc;

    /*
     * Get the API message for this return code.
     */
    rc = CHR_api_get_return_msg(
            code,
            msg,
            CHR_MAX_RETURN_MSG,
            &msgLen);

    if (rc != CHR_OK)
    {
        /* Could not get the message: show why */
        printf("%s failed\n", what);
        printf(
            "Unable to get message for return code %d, rc = %d\n",
            code,
            rc);
    }
    else
    {
        /* Tell the user about the error */
        printf("%s failed: rc = %d (%s)\n", what, code, msg);
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
         handle != (CHR_HANDLE)NULL)
    {
        /* Open the log file */
        fd = fopen(lc_logFile, "a+");

        /* Get the timestamp */
        currentTime = time(NULL);
        timestamp = ctime(&currentTime);

        /* Get the extended error info */
        rc = CHR_common_error_get_info(
                handle,
                CHR_DETAIL_LEVEL_ALL,
                errorInfo,
                CHR_MAX_ERROR_INFO,
                &errorLen);

        if (rc == CHR_OK)
        {
            /*
             * We can ignore all non-success return codes here
             * because most should not occur (the api's been
             * initialized, the handle is good, the buffer
             * pointer is valid, and the detail level is okay),
             * and the NO_SUCH_VALUE return code here means
             * there is no info available.
             */
            if (fd != NULL)
            {
                /* Log it if the file was opened successfully */
                fprintf(fd, "%s %s failed\n", timestamp, what );
                fprintf(fd, "%s %s\n", timestamp, errorInfo);
                fclose(fd);
            }
        }
    }

    /*
     * We've told everything we know, so now just exit.
     */
    exit(EXIT_FAILURE);

} /* show_error */

/*----------------------------------------------------------------------*/
/*                      show_error_label                                */
/*----------------------------------------------------------------------*/

/**
 * Displays labeled error information and exits. 
 *  
 * @param i_objectHandle    Handle of the object that had the error.
 * @param i_returnCode      Chariot API return code.
 * @param i_errorLocation   String specifying what operation failed.
 * @param i_errorLabel      String specifying which item failed.
 */
static void
show_error_label(
    CHR_HANDLE      i_objectHandle,
    CHR_API_RC      i_returnCode,
    const char*     i_errorLocation,
    const char*     i_errorLabel)
{
    char what[128];
    sprintf(what, "%s(%s)", i_errorLocation, i_errorLabel);
    show_error(i_objectHandle, i_returnCode, what);
}

/*----------------------------------------------------------------------*/
/*                      process_reports                                 */
/*----------------------------------------------------------------------*/

/**
 * Processes the REPORT objects for an IPTV pair. 
 *  
 * This function enumerates the list of report objects associated with 
 * the specified IPTV pair, verifying that the attributes of each report 
 * are retrievable. 
 *  
 * @param i_pairHandle      Handle of IPTV pair object.
 * @param i_receiverIndex   Index of receiver to which pair belongs.
 * @param i_pairIndex       Index of pair in receiver.
 * @param o_reportCount     Returns the report count for the receiver.
 */
static void
process_reports(
    CHR_VPAIR_HANDLE    i_pairHandle,
    CHR_COUNT           i_receiverIndex,
    CHR_COUNT           i_pairIndex,
    CHR_COUNT*          o_reportCount)
{
    CHR_REPORT_HANDLE reportHandle;
    CHR_COUNT reportCount;
    CHR_COUNT reportIndex;
    CHR_REPORT_ITEM reportItem;
    CHR_API_RC rc;

    char errorLabel[64];

    /* Number of reports. */
    rc = CHR_vpair_get_report_count(i_pairHandle, &reportCount);
    if (rc != CHR_OK)
    {
        sprintf(
            errorLabel,
            "vpair_get_report_count(%u,%u)",
            i_receiverIndex,
            i_pairIndex);
        show_error(i_pairHandle, rc, errorLabel);
    }

    /* Enumerate the list of report objects. */
    for (reportIndex = 0; reportIndex < reportCount; ++reportIndex)
    {
        sprintf(errorLabel, "%u,%u,%u", i_receiverIndex, i_pairIndex, reportIndex);

        /* Report handle. */
        rc = CHR_vpair_get_report(i_pairHandle, reportIndex, &reportHandle);
        if (rc != CHR_OK)
            show_error_label(i_pairHandle, rc, "vpair_get_report", errorLabel);

        /* Report item type. */
        rc = CHR_report_get_item_type(reportHandle, &reportItem);
        if (rc != CHR_OK)
            show_error_label(reportHandle, rc, "report_get_item_type", errorLabel);

        /* Join/leave report. */
        if (reportItem == CHR_REPORT_ITEM_JOIN_LEAVE)
        {
            CHR_FLOAT joinLatency;
            CHR_FLOAT leaveLatency;
            CHR_COUNT reportGroupId;

            /* Join latency. */
            rc = CHR_report_get_join_latency(reportHandle, &joinLatency);
            if (rc != CHR_OK)
                show_error_label(
                    reportHandle, rc, "report_get_join_latency", errorLabel);

            /* Leave latency. */
            rc = CHR_report_get_leave_latency(reportHandle, &leaveLatency);
            if (rc != CHR_OK)
                show_error_label(
                    reportHandle, rc, "report_get_leave_latency", errorLabel);

            /* Report group identifier. */
            rc = CHR_report_get_report_group_id(reportHandle, &reportGroupId);
            if (rc != CHR_OK)
                show_error_label(
                    reportHandle, rc, "report_get_report_group_id", errorLabel);
        }
        else
        {
            printf("Unknown report item type (%u)\n", reportItem);
        }
    }

    *o_reportCount = reportCount;

} /* process_reports */

/*----------------------------------------------------------------------*/
/*                      process_timing_records                          */
/*----------------------------------------------------------------------*/

/**
 * Processes the TIMING RECORDS for an IPTV pair. 
 *  
 * This function enumerates the list of timing record objects associated 
 * with the specified IPTV pair, and verifies that key attributes of the 
 * timing record can be retrieved. 
 *  
 * @param i_pairHandle      Handle of the IPTV pair object.
 * @param i_receiverIndex   Index of receiver to which pair belongs. 
 * @param i_pairIndex       Index of IPTV pair in receiver.
 * @param o_recordCount     Returns the timing record count.
 */
static void
process_timing_records(
    CHR_VPAIR_HANDLE    i_pairHandle,
    CHR_COUNT           i_receiverIndex,
    CHR_COUNT           i_pairIndex,
    CHR_COUNT*          o_recordCount)
{
    CHR_TIMINGREC_HANDLE recordHandle;
    CHR_COUNT recordCount;
    CHR_COUNT recordIndex;
    CHR_COUNT delayFactor;
    CHR_COUNT reportGroupId;
    CHR_API_RC rc;

    char errorLabel[64];

    /* Number of timing records. */
    rc = CHR_vpair_get_timing_record_count(i_pairHandle, &recordCount);
    if (rc != CHR_OK)
    {
        sprintf(
            errorLabel,
            "vpair_get_timing_record_count(%u,%u)",
            i_receiverIndex,
            i_pairIndex);
        show_error(i_pairHandle, rc, errorLabel);
    }

    /* Enumerate the list of timing records. */
    for (recordIndex = 0; recordIndex < recordCount; ++recordIndex)
    {
        sprintf(errorLabel, "%u,%u,%u", i_receiverIndex, i_pairIndex, recordIndex);

        /* Timing record handle. */
        rc = CHR_vpair_get_timing_record(i_pairHandle, recordIndex, &recordHandle);
        if (rc != CHR_OK)
            show_error_label(i_pairHandle, rc, "vpair_get_timing_record", errorLabel);

        /* Delay factor. */
        rc = CHR_timingrec_get_df(recordHandle, &delayFactor);
        if (rc != CHR_OK)
            show_error_label(i_pairHandle, rc, "timingrec_get_df", errorLabel);

        /* Report group identifier. */
        rc = CHR_timingrec_get_report_group_id(recordHandle, &reportGroupId);
        if (rc != CHR_OK)
            show_error_label(
                i_pairHandle, rc, "timingrec_get_report_group_id", errorLabel);
    }

    *o_recordCount = recordCount;

} /* process_timing_records */

/*----------------------------------------------------------------------*/
/*                      process_results                                 */
/*----------------------------------------------------------------------*/

/**
 * Processes the test results. 
 *  
 * This function retrieves each receiver group for the test and 
 * enumerates the list of IPTV pairs belong to the receiver group, 
 * processing the timing records and reports associated with the pair. 
 *  
 * @param i_testHandle  Handle of the test object.
 */
static void
process_results(
    CHR_TEST_HANDLE     i_testHandle)
{
    CHR_RECEIVER_HANDLE receiverHandle;
    CHR_VPAIR_HANDLE pairHandle;
    CHR_COUNT receiverCount;
    CHR_COUNT pairCount;
    CHR_COUNT receiverIndex;
    CHR_COUNT pairIndex;
    CHR_API_RC rc;

    char errorLabel[64];

    /* Number of receivers. */
    rc = CHR_test_get_receiver_count(i_testHandle, &receiverCount);
    if (rc != CHR_OK)
        show_error(i_testHandle, rc, "test_get_receiver_count");

    /* Enumerate the list of receiver groups. */
    for (receiverIndex = 0; receiverIndex < receiverCount; ++receiverIndex)
    {
        /* Receiver handle. */
        rc = CHR_test_get_receiver(i_testHandle, receiverIndex, &receiverHandle);
        if (rc != CHR_OK)
        {
            sprintf(errorLabel, "test_get_receiver(%u)", receiverIndex);
            show_error(i_testHandle, rc, errorLabel);
        }

        /* Number of IPTV pairs. */
        rc = CHR_receiver_get_vpair_count(receiverHandle, &pairCount);
        if (rc != CHR_OK)
        {
            sprintf(errorLabel, "receiver_get_vpair_count(%u)", receiverIndex);
            show_error(receiverHandle, rc, errorLabel);
        }

        /* Enumerate the pair list for this receiver. */
        for (pairIndex = 0; pairIndex < pairCount; ++pairIndex)
        {
            CHR_COUNT recordCount = 0;
            CHR_COUNT reportCount = 0;

            /* Pair handle. */
            rc = CHR_receiver_get_vpair(receiverHandle, pairIndex, &pairHandle);
            if (rc != CHR_OK)
            {
                sprintf(
                    errorLabel,
                    "receiver_get_vpair(%u,%u)",
                    receiverIndex,
                    pairIndex);
                show_error(receiverHandle, rc, errorLabel);
            }

            /* Process results for this pair. */
            process_timing_records(pairHandle, receiverIndex, pairIndex, &recordCount);
            process_reports(pairHandle, receiverIndex, pairIndex, &reportCount);

            /* Provide some feedback. */
            printf(
                "Receiver %u, pair %u, %u timing record%s, %u report%s\n",
                receiverIndex,
                pairIndex,
                recordCount,
                (recordCount != 1) ? "s" : "",
                reportCount,
                (reportCount != 1) ? "s" : "");
        }
    }

} /* process_results */

/*----------------------------------------------------------------------*/
/*                      create_channel                                  */
/*----------------------------------------------------------------------*/

/**
 * Creates a channel for the test configuration. 
 *  
 * @param i_channelSpec     Channel specification.
 * 
 * @return Handle of newly created channel object.
 */
static CHR_CHANNEL_HANDLE
create_channel(
    const struct channel_spec_s*    i_channelSpec)
{
    CHR_CHANNEL_HANDLE channelHandle;
    CHR_API_RC rc;

    /* Create a new channel object. */
    rc = CHR_channel_new(&channelHandle);
    if (rc != CHR_OK)
        show_error(CHR_NULL_HANDLE, rc, "channel_new");

    /* Channel name. */
    rc = CHR_channel_set_name(
            channelHandle,
            i_channelSpec->m_name,
            strlen(i_channelSpec->m_name));
    if (rc != CHR_OK)
        show_error(channelHandle, rc, "channel_set_name");

    /* Channel comment. */
    rc = CHR_channel_set_comment(
            channelHandle,
            i_channelSpec->m_comment,
            strlen(i_channelSpec->m_comment));
    if (rc != CHR_OK)
        show_error(channelHandle, rc, "channel_set_comment");

    /* Multicast address of channel. */
    rc = CHR_channel_set_multicast_addr(
            channelHandle,
            i_channelSpec->m_multicast_addr,
            strlen(i_channelSpec->m_multicast_addr));
    if (rc != CHR_OK)
        show_error(channelHandle, rc, "channel_set_multicast_addr");

    /* Multicast port number of channel. */
    rc = CHR_channel_set_multicast_port(
            channelHandle,
            i_channelSpec->m_multicast_port);
    if (rc != CHR_OK)
        show_error(channelHandle, rc, "channel_set_multicast_port");

    /* Test protocol. */
    rc = CHR_channel_set_protocol(
            channelHandle, 
            CHR_PROTOCOL_RTP);
    if (rc != CHR_OK)
        show_error(channelHandle, rc, "channel_set_protocol");

    /* IP address of channel on test network. */
    rc = CHR_channel_set_e1_addr(
            channelHandle,
            lc_e1TestAddress,
            strlen(lc_e1TestAddress));
    if (rc != CHR_OK)
        show_error(channelHandle, rc, "channel_set_e1_addr");

    /* Ixia port address of Endpoint 1. */
    rc = CHR_channel_set_console_e1_addr(
            channelHandle,
            lc_e1MgmtAddress,
            strlen(lc_e1MgmtAddress));
    if (rc != CHR_OK)
        show_error(channelHandle, rc, "channel_set_console_e1_addr");

    /* Use Ixia port address as management address. */
    rc = CHR_channel_set_use_console_e1_values(
            channelHandle,
            CHR_TRUE);
    if (rc != CHR_OK)
        show_error(channelHandle, rc, "channel_set_use_console_e1_values");

    /* Return handle of channel object. */
    return channelHandle;

} /* create_channel */

/*----------------------------------------------------------------------*/
/*                      create_pair                                     */
/*----------------------------------------------------------------------*/

/**
 * Creates a pair and adds it to the specified receiver. 
 *  
 * @param i_receiverHandle  Receiver to which the pair is to be added.
 * @param i_channelHandle   Channel with which the pair is associated.
 */
static void
create_pair(
    CHR_RECEIVER_HANDLE i_receiverHandle,
    CHR_CHANNEL_HANDLE  i_channelHandle)
{
    CHR_VPAIR_HANDLE pairHandle;
    CHR_API_RC rc;

    /* Create a new IPTV pair object. */
    rc = CHR_vpair_new(&pairHandle);
    if (rc != CHR_OK)
        show_error(CHR_NULL_HANDLE, rc, "vpair_new");

    /* Associate channel with pair. */
    rc = CHR_vpair_set_channel(
            pairHandle,
            i_channelHandle);
    if (rc != CHR_OK)
        show_error(pairHandle, rc, "vpair_set_channel");

    /* Number of timing records. */
    rc = CHR_vpair_set_no_of_timing_records(
            pairHandle,
            NO_OF_TIMING_RECORDS);
    if (rc != CHR_OK)
        show_error(pairHandle, rc, "vpair_set_no_of_timing_records");

    /* Timing record duration. */
    rc = CHR_vpair_set_tr_duration(
            pairHandle,
            TIMING_RECORD_DURATION);
    if (rc != CHR_OK)
        show_error(pairHandle, rc, "vpair_set_tr_duration");

    /* Add pair to receiver. */
    rc = CHR_receiver_add_vpair(
            i_receiverHandle,
            pairHandle);
    if (rc != CHR_OK)
        show_error(pairHandle, rc, "receiver_add_vpair");

} /* create_pair */

/*----------------------------------------------------------------------*/
/*                      create_receiver                                 */
/*----------------------------------------------------------------------*/

/**
 * Creates a receiver for the test configuration. 
 *  
 * @param i_receiverSpec    Receiver specification.
 * 
 * @return Handle of newly created receiver object.
 */
static CHR_RECEIVER_HANDLE
create_receiver(
    const struct receiver_spec_s*   i_receiverSpec)
{
    CHR_RECEIVER_HANDLE receiverHandle;
    CHR_API_RC rc;

    /* Create a new receiver object. */
    rc = CHR_receiver_new(&receiverHandle);
    if (rc != CHR_OK)
        show_error(CHR_NULL_HANDLE, rc, "receiver_new");

    /* Receiver name. */
    rc = CHR_receiver_set_name(
            receiverHandle,
            i_receiverSpec->m_name,
            strlen(i_receiverSpec->m_name));
    if (rc != CHR_OK)
        show_error(receiverHandle, rc, "receiver_set_name");

    /* Receiver comment. */
    rc = CHR_receiver_set_comment(
            receiverHandle,
            i_receiverSpec->m_comment,
            strlen(i_receiverSpec->m_comment));
    if (rc != CHR_OK)
        show_error(receiverHandle, rc, "receiver_set_comment");

    /* IP address of receiver on test network. */
    rc = CHR_receiver_set_e2_addr(
            receiverHandle,
            lc_e2TestAddress,
            strlen(lc_e2TestAddress));
    if (rc != CHR_OK)
        show_error(receiverHandle, rc, "receiver_set_e2_addr");

    /* Ixia port address of Endpoint 2. */
    rc = CHR_receiver_set_setup_e1_e2_addr(
            receiverHandle,
            lc_e2MgmtAddress,
            strlen(lc_e2MgmtAddress));
    if (rc != CHR_OK)
        show_error(receiverHandle, rc, "receiver_set_setup_e1_e2_addr");

    /* Use Ixia port address as management address. */
    rc = CHR_receiver_set_use_e1_e2_values(
            receiverHandle,
            CHR_TRUE);
    if (rc != CHR_OK)
        show_error(receiverHandle, rc, "receiver_set_use_e1_e2_values");

    /* Number of iterations. */
    rc = CHR_receiver_set_no_of_iterations(
            receiverHandle,
            NO_OF_ITERATIONS);
    if (rc != CHR_OK)
        show_error(receiverHandle, rc, "receiver_set_no_of_iterations");

    /* Return handle of receiver object. */
    return receiverHandle;

} /* create_receiver */

/*----------------------------------------------------------------------*/
/*                      build_test                                      */
/*----------------------------------------------------------------------*/

/**
 * Builds the Chariot test.
 *  
 * @param i_testHandle   Test object to be configured.
 */
static void
build_test(
    CHR_TEST_HANDLE i_testHandle)
{
    CHR_CHANNEL_HANDLE channel1;
    CHR_CHANNEL_HANDLE channel2;
    CHR_CHANNEL_HANDLE channel3;
    CHR_RECEIVER_HANDLE receiver1;
    CHR_RUNOPTS_HANDLE runOptionsHandle;
    CHR_API_RC rc;

    rc = CHR_test_set_filename(
            i_testHandle,
            lc_testFile,
            strlen(lc_testFile));
    if (rc != CHR_OK)
        show_error(i_testHandle, rc, "test_set_filename");

    /*
     * Create channel objects.
     */
    channel1 = create_channel(&lc_channelSpec1);
    channel2 = create_channel(&lc_channelSpec2);
    channel3 = create_channel(&lc_channelSpec3);

    /*
     * Add channels to test.
     */
    rc = CHR_test_add_channel(i_testHandle, channel1);
    if (rc != CHR_OK)
        show_error(i_testHandle, rc, "test_add_channel");

    rc = CHR_test_add_channel(i_testHandle, channel2);
    if (rc != CHR_OK)
        show_error(i_testHandle, rc, "test_add_channel");

    rc = CHR_test_add_channel(i_testHandle, channel3);
    if (rc != CHR_OK)
        show_error(i_testHandle, rc, "test_add_channel");

    /*
     * Create receiver objects.
     */
    receiver1 = create_receiver(&lc_receiverSpec1);

    /*
     * Create IPTV pairs.
     */
    create_pair(receiver1, channel1);
    create_pair(receiver1, channel2);
    create_pair(receiver1, channel3);

    /*
     * Add receivers to test.
     */
    rc = CHR_test_add_receiver(i_testHandle, receiver1);
    if (rc != CHR_OK)
        show_error(i_testHandle, rc, "test_add_receiver");

    /*
     * Set a time limit on the test.
     */
    rc = CHR_test_get_runopts(i_testHandle, &runOptionsHandle);
    if (rc != CHR_OK)
        show_error(i_testHandle, rc, "test_get_runopts");

    rc = CHR_runopts_set_test_duration(
            runOptionsHandle,
            TEST_DURATION);
    if (rc != CHR_OK)
        show_error(i_testHandle, rc, "runopts_set_test_duration");

    rc = CHR_runopts_set_test_end(
            runOptionsHandle,
            CHR_TEST_END_AFTER_FIXED_DURATION);
    if (rc != CHR_OK)
        show_error(i_testHandle, rc, "runopts_set_test_end");

} /* build_test */

/*----------------------------------------------------------------------*/
/*                      initialize_api                                  */
/*----------------------------------------------------------------------*/

/**
 * Initializes the Chariot API.
 */
static void
initialize_api(void)
{
    char errorInfo[CHR_MAX_ERROR_INFO];
    CHR_LENGTH errorLen;
    CHR_API_RC rc;

    /**
     * Initialize the Chariot API.
     */
    rc = CHR_api_initialize(
            CHR_DETAIL_LEVEL_ALL,
            errorInfo,
            CHR_MAX_ERROR_INFO,
            &errorLen);

    if (rc != CHR_OK)
    {
        printf("Initialization failed: rc = %d\n", rc);
        printf("Extended error info:\n%s\n", errorInfo);
        exit(EXIT_FAILURE);
    }

} /* initialize_api */

/*----------------------------------------------------------------------*/
/*                      run_test                                        */
/*----------------------------------------------------------------------*/

/**
 * Runs the Chariot test. 
 *  
 * @param i_testHandle      Test object to be run.
 */
static void run_test(
    CHR_TEST_HANDLE i_testHandle)
{
    CHR_BOOLEAN isStopped;
    CHR_COUNT runTime;
    CHR_API_RC rc;

    /* Start the test. */
    rc = CHR_test_start(i_testHandle);
    if (rc != CHR_OK)
        show_error(i_testHandle, rc, "test_start");

    /*
     * Wait for the test to stop. 
     *  
     * We'll check in a loop here every TEST_TIMEOUT (5) seconds, 
     * then call it an error after MAX_WAIT_TIME (two minutes) if 
     * the test is still not stopped. 
     */
    isStopped = CHR_FALSE;
    runTime = 0;
    printf("Waiting for the test to finish...\n");
    while (!isStopped && runTime < MAX_WAIT_TIME)
    {
        rc = CHR_test_query_stop(i_testHandle, TEST_TIMEOUT);
        if (rc == CHR_OK)
        {
            isStopped = CHR_TRUE;
        }
        else if (rc == CHR_TIMED_OUT)
        {
            runTime += TEST_TIMEOUT;
            printf("Waiting for test to stop... (%u)\n", runTime);
        }
        else
        {
            show_error(i_testHandle, rc, "test_query_stop");
        }
    }
    if (!isStopped)
        show_error(i_testHandle, CHR_TIMED_OUT, "test_query_stop");

} /* run_test */

/*----------------------------------------------------------------------*/
/*                      main program                                    */
/*----------------------------------------------------------------------*/

/**
 * Main program.
 */
void main(int argc, char** argv)
{
    CHR_TEST_HANDLE testHandle;
    CHR_API_RC rc;
    int argNo;
    int loadTestEnabled = 0;

    /* Get command-line parameters. */
    for (argNo = 1; argNo < argc; ++argNo)
    {
        const char* ap = argv[argNo];

        if (strcmp(ap, "--load") == 0)
            loadTestEnabled = 1;
        else if (strcmp(ap, "--noload") == 0)
            loadTestEnabled = 0;
        else
        {
            printf("Unrecognized option: %s\n", ap);
            exit(EXIT_FAILURE);
        }
    }

    /* Initialize the Chariot API. */
    printf("Initializing the API...\n");
    initialize_api();

    /* Create test object. */
    rc = CHR_test_new(&testHandle);
    if (rc != CHR_OK)
        show_error(CHR_NULL_HANDLE, rc, "test_new");

    if (loadTestEnabled)
    {
        /* Load results into test object. */
        printf("Loading test results... (%s)\n", lc_testFile);
        rc = CHR_test_load(
                testHandle,
                lc_testFile,
                strlen(lc_testFile));
        if (rc != CHR_OK)
            show_error(testHandle, rc, "test_load");
    }
    else
    {
        /* Load network configuration. */
        printf("Loading the configuration... (%s)\n", lc_configFile);
        rc = CHR_test_load_ixia_network_configuration(
                testHandle,
                lc_configFile,
                strlen(lc_configFile));
        if (rc != CHR_OK)
            show_error(testHandle, rc, "test_load_ixia_network_configuration");
    
        /* Create the test. */
        printf("Building the test...\n");
        build_test(testHandle);
    
        /* Save the test before running it. */
        printf("Saving the test... (%s)\n", lc_testFile);
        rc = CHR_test_save(testHandle);
        if (rc != CHR_OK)
            show_error(testHandle, rc, "test_save");

        /* Run the test. */
        printf("Starting the test...\n");
        run_test(testHandle);

        /* Save results of test. */
        printf("Saving the results... (%s)\n", lc_testFile);
        rc = CHR_test_save(testHandle);
        if (rc != CHR_OK)
            show_error(testHandle, rc, "test_save");
    }

    /* Process the results. */
    printf("Processing the results...\n");
    process_results(testHandle);

    /* We're finished! */
    exit(EXIT_SUCCESS);

} /* main */
