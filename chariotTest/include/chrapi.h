/**
 * \file        chrapi.h
 * \brief       Ixia Chariot API.
 * 
 * This include file contains the constants, typedefs and
 * function prototypes for Ixia's Chariot application
 * programming interface.
 */

/***************************************************************
 *
 *  Ixia IxChariot API                       File: chrapi.h
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
 *  Copyright (C) Ixia, 2003-2007.
 *  Copyright (C) NetIQ Corporation, 1995-2000.
 *  All rights reserved.
 *
 ***************************************************************/

#ifndef CHRAPI_H_INCLUDED
#define CHRAPI_H_INCLUDED

#ifndef __voip_defs_h__
#include "voip_defs.h"
#endif

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Chariot API return codes
 */
#define CHR_RC_BASE                       100
#define CHR_OK                            0
#define CHR_HANDLE_INVALID                (CHR_RC_BASE + 1)
#define CHR_STRING_TOO_LONG               (CHR_RC_BASE + 2)
#define CHR_POINTER_INVALID               (CHR_RC_BASE + 3)
#define CHR_NO_SUCH_OBJECT                (CHR_RC_BASE + 4)
#define CHR_TEST_NOT_RUN                  (CHR_RC_BASE + 5)
#define CHR_TEST_RUNNING                  (CHR_RC_BASE + 6)
#define CHR_OBJECT_IN_USE                 (CHR_RC_BASE + 7)
#define CHR_OPERATION_FAILED              (CHR_RC_BASE + 8)
#define CHR_NO_TEST_FILE                  (CHR_RC_BASE + 9)
#define CHR_RESULTS_NOT_CLEARED           (CHR_RC_BASE + 10)
#define CHR_PAIR_LIMIT_EXCEEDED           (CHR_RC_BASE + 11)
#define CHR_OBJECT_INVALID                (CHR_RC_BASE + 12)
#define CHR_API_NOT_INITIALIZED           (CHR_RC_BASE + 13)
#define CHR_NO_RESULTS                    (CHR_RC_BASE + 14)
#define CHR_VALUE_INVALID                 (CHR_RC_BASE + 15)
#define CHR_NO_SUCH_VALUE                 (CHR_RC_BASE + 16)
#define CHR_NO_SCRIPT_IN_USE              (CHR_RC_BASE + 17)
#define CHR_TIMED_OUT                     (CHR_RC_BASE + 18)
#define CHR_BUFFER_TOO_SMALL              (CHR_RC_BASE + 19)
#define CHR_NO_MEMORY                     (CHR_RC_BASE + 20)
#define CHR_PGM_INTERNAL_ERROR            (CHR_RC_BASE + 21)
#define CHR_TRACERT_NOT_RUN               (CHR_RC_BASE + 22)
#define CHR_TRACERT_RUNNING               (CHR_RC_BASE + 23)
#define CHR_NOT_SUPPORTED                 (CHR_RC_BASE + 24)
#define CHR_NO_CODEC_IN_USE               (CHR_RC_BASE + 25)
#define CHR_NOT_LICENSED                  (CHR_RC_BASE + 26)
#define CHR_SCRIPT_TOO_LARGE              (CHR_RC_BASE + 27)
#define CHR_LICENSE_HAS_EXPIRED           (CHR_RC_BASE + 28)
#define CHR_NO_NETWORK_CONFIGURATION      (CHR_RC_BASE + 29)
#define CHR_INVALID_NETWORK_CONFIGURATION (CHR_RC_BASE + 30)
#define CHR_ERROR_ACCESSING_TESTSERVER_SESSION (CHR_RC_BASE + 31)
#define CHR_FUNCTION_NOT_SUPPORTED        (CHR_RC_BASE + 32)
#define CHR_TEST_NOT_SAVED                (CHR_RC_BASE + 33)
#define CHR_LICENSE_WILL_EXPIRE           (CHR_RC_BASE + 34)
#define CHR_APP_GROUP_NOT_VALIDATED       (CHR_RC_BASE + 35)
#define CHR_APP_GROUP_INVALID             (CHR_RC_BASE + 36)
#define CHR_APP_GROUP_DUPLICATE_NAME      (CHR_RC_BASE + 37)
#define CHR_PAYLOAD_FILE_TOO_LARGE        (CHR_RC_BASE + 38)
#define CHR_NO_APPLIFIER_CONFIGURATION    (CHR_RC_BASE + 39)
#define CHR_CHANNEL_DUPLICATE_NAME        (CHR_RC_BASE + 40)
#define CHR_RECEIVER_DUPLICATE_NAME       (CHR_RC_BASE + 41)
#define CHR_IPTV_INVALID                  (CHR_RC_BASE + 42)
#define CHR_DUPLICATE_NAME                (CHR_RC_BASE + 43)

/*
 * String buffer maximum sizes (including a terminating '\0')
 */
#define CHR_MAX_DIR_PATH              901
#define CHR_MAX_FILENAME              901
#define CHR_MAX_FILE_PATH             (CHR_MAX_DIR_PATH + CHR_MAX_FILENAME)
#define CHR_MAX_EMBEDDED_PAYLOAD_SIZE 27904
#define CHR_MAX_ERROR_INFO            4096
#define CHR_MAX_PAIR_COMMENT          65
#define CHR_MAX_ADDR                  65
#define CHR_MAX_MULTICAST_ADDR        16
#define CHR_MAX_QOS_NAME              65
#define CHR_MAX_APPL_SCRIPT_NAME      65
#define CHR_MAX_GROUP_NAME            65
#define CHR_MAX_VERSION               32
#define CHR_MAX_RETURN_MSG            256
#define CHR_MAX_SCRIPT_VARIABLE_NAME  25
#define CHR_MAX_SCRIPT_VARIABLE_VALUE 65
#define CHR_MAX_CFG_PARM              512
#define CHR_MAX_ADDR_STRING           CHR_MAX_ADDR
#define CHR_BSSID_SIZE                18
#define CHR_MAX_APP_GROUP_NAME        25
#define CHR_MAX_APP_GROUP_COMMENT     129
#define CHR_MAX_APP_GROUP_EVENT_NAME  25
#define CHR_MAX_APP_GROUP_EVENT_COMMENT 129
#define CHR_MAX_CHANNEL_NAME          33
#define CHR_MAX_RECEIVER_NAME         33
#define CHR_MAX_CHANNEL_COMMENT       65
#define CHR_MAX_RECEIVER_COMMENT      65

/*
 * Handle Definitions
 */
typedef unsigned long   CHR_HANDLE;

typedef CHR_HANDLE      CHR_TEST_HANDLE;
typedef CHR_HANDLE      CHR_PAIR_HANDLE;
typedef CHR_HANDLE      CHR_VOIP_PAIR_HANDLE;
typedef CHR_HANDLE      CHR_HARDWARE_PAIR_HANDLE;
typedef CHR_HANDLE      CHR_RUNOPTS_HANDLE;
typedef CHR_HANDLE      CHR_DGOPTS_HANDLE;
typedef CHR_HANDLE      CHR_PRESOPTS_HANDLE;
typedef CHR_HANDLE      CHR_MGROUP_HANDLE;
typedef CHR_HANDLE      CHR_MPAIR_HANDLE;
typedef CHR_HANDLE      CHR_TIMINGREC_HANDLE;
typedef CHR_HANDLE      CHR_TRACERT_PAIR_HANDLE;
typedef CHR_HANDLE      CHR_HOPREC_HANDLE;
typedef CHR_HANDLE      CHR_VIDEO_PAIR_HANDLE;
typedef CHR_HANDLE      CHR_VIDEO_MGROUP_HANDLE;
typedef CHR_HANDLE      CHR_APP_GROUP_HANDLE;
typedef CHR_HANDLE      CHR_CHANNEL_HANDLE;
typedef CHR_HANDLE      CHR_RECEIVER_HANDLE;
typedef CHR_HANDLE      CHR_VPAIR_HANDLE;
typedef CHR_HANDLE      CHR_REPORT_HANDLE;

/*
 * Type Definitions and Constants
 */
typedef char            CHR_CHAR;
typedef unsigned char   CHR_BYTE;
typedef CHR_CHAR*       CHR_STRING;
typedef const char*     CHR_CONST_STRING;
typedef unsigned long   CHR_LENGTH;
typedef unsigned long   CHR_COUNT;
typedef double          CHR_FLOAT;
typedef unsigned short  CHR_PORT;
typedef int             CHR_MESSAGE_NUMBER;
typedef int             CHR_API_RC;
typedef long            CHR_LONG;
#if defined(_MSC_VER)
typedef __int64         CHR_WLONG;
#else
typedef long long       CHR_WLONG;
#endif

typedef CHR_CHAR CHR_ADDR_STRING[CHR_MAX_ADDR_STRING];

#define CHR_NULL_HANDLE 0

typedef char CHR_BOOLEAN;
#define CHR_TRUE  1
#define CHR_FALSE 0

#define CHR_INFINITE 0xffffffff

/*
 * Protocol
 */
typedef char CHR_PROTOCOL;

#define CHR_PROTOCOL_APPC_NOT_SUPPORTED  1 /* APPC is no longer supported */
#define CHR_PROTOCOL_TCP                 2
#define CHR_PROTOCOL_IPX                 3
#define CHR_PROTOCOL_SPX                 4
#define CHR_PROTOCOL_UDP                 5
#define CHR_PROTOCOL_RTP                 6
#define CHR_PROTOCOL_TCP6                7
#define CHR_PROTOCOL_UDP6                8
#define CHR_PROTOCOL_RTP6                9

/*
 *QoS template types
 */
typedef char CHR_QOS_TEMPLATE_TYPE;

#define CHR_QOS_TEMPLATE_TOS_BIT_MASK    1
#define CHR_QOS_TEMPLATE_DIFFSERV        2


/*
 * VoIP Codecs -- map to CHR defs
 */
typedef IX_VOIP_CODEC CHR_VOIP_CODEC;

#define CHR_VOIP_CODEC_NONE      IX_VOIP_CODEC_NONE
#define CHR_VOIP_CODEC_G711u     IX_VOIP_CODEC_G711u
#define CHR_VOIP_CODEC_G723_1A   IX_VOIP_CODEC_G723_1A
#define CHR_VOIP_CODEC_G723_1M   IX_VOIP_CODEC_G723_1M
#define CHR_VOIP_CODEC_G729      IX_VOIP_CODEC_G729
#define CHR_VOIP_CODEC_G711a     IX_VOIP_CODEC_G711a
#define CHR_VOIP_CODEC_G726      IX_VOIP_CODEC_G726


/*
 * Video Codecs
 */
typedef char CHR_VIDEO_CODEC;

#define CHR_VIDEO_CODEC_NONE      1
#define CHR_VIDEO_CODEC_MPEG2     2
#define CHR_VIDEO_CODEC_CUSTOM    3


/*
 * Port Number
 */
#define CHR_PORT_AUTO  0

/*
 * Error Information Detail Level
 */
typedef unsigned long CHR_DETAIL_LEVEL;

#define CHR_DETAIL_LEVEL_NONE     0x0000
#define CHR_DETAIL_LEVEL_PRIMARY  0x00a3
#define CHR_DETAIL_LEVEL_ADVANCED (0x0014 | CHR_DETAIL_LEVEL_PRIMARY)
#define CHR_DETAIL_LEVEL_ALL      (0x0148 | CHR_DETAIL_LEVEL_ADVANCED)

/*
 * Throughput Units
 */
typedef char CHR_THROUGHPUT_UNITS;

#define CHR_THROUGHPUT_UNITS_KB 1
#define CHR_THROUGHPUT_UNITS_kB 2
#define CHR_THROUGHPUT_UNITS_Kb 3
#define CHR_THROUGHPUT_UNITS_kb 4
#define CHR_THROUGHPUT_UNITS_Mb 5
#define CHR_THROUGHPUT_UNITS_Gb 6

/*
 * When To End Test
 */
typedef char CHR_TEST_END;

#define CHR_TEST_END_WHEN_FIRST_COMPLETES 1
#define CHR_TEST_END_WHEN_ALL_COMPLETE    2
#define CHR_TEST_END_AFTER_FIXED_DURATION 3

/*
 * How Test Ended
 */
typedef char CHR_TEST_HOW_ENDED;

#define CHR_TEST_HOW_ENDED_USER_STOPPED  1
#define CHR_TEST_HOW_ENDED_ERROR         2
#define CHR_TEST_HOW_ENDED_NORMAL        3

/*
 * Test Reporting
 */
typedef char CHR_TEST_REPORTING;

#define CHR_TEST_REPORTING_REALTIME      1
#define CHR_TEST_REPORTING_BATCH         2

/*
 * Test Reporting Firewall
 */
typedef char CHR_TEST_REPORTING_FIREWALL;

#define CHR_TEST_REPORTING_NO_FIREWALL      11
#define CHR_TEST_REPORTING_USE_FIREWALL     12

/*
 * Test Poll Retrieving
 */
typedef char CHR_TEST_RETRIEVING;

#define CHR_TEST_RETRIEVE_NUMBER            1
#define CHR_TEST_RETRIEVE_TIMING_RECORD     2

/*
 * Test Results
 */
typedef char CHR_RESULTS;

#define CHR_RESULTS_THROUGHPUT            1
#define CHR_RESULTS_TRANSACTION_RATE      2
#define CHR_RESULTS_RESPONSE_TIME         3
#define CHR_RESULTS_JITTER                4     /* RFC 1889 jitter calculation */
#define CHR_RESULTS_DELAY_VARIATION       5     /* typically called jitter     */
#define CHR_RESULTS_CONSECUTIVE_LOST      6
#define CHR_RESULTS_MOS_ESTIMATE          7
#define CHR_RESULTS_ROUND_TRIP_DELAY      8
#define CHR_RESULTS_ONE_WAY_DELAY         9
#define CHR_RESULTS_R_VALUE              10
#define CHR_RESULTS_END_TO_END_DELAY     11
#define CHR_RESULTS_RSSI_E1              12
#define CHR_RESULTS_RSSI_E2              13
#define CHR_RESULTS_DF                   14
#define CHR_RESULTS_MLR                  15
#define CHR_RESULTS_JOIN_LATENCY         16
#define CHR_RESULTS_LEAVE_LATENCY        17

/*
 * Endpoint Config parameters
 */
typedef char CHR_CFG_PARM;

#define CHR_CFG_PARM_ENDPOINT_VERSION                         1
#define CHR_CFG_PARM_ENDPOINT_BUILD_LEVEL                     2
#define CHR_CFG_PARM_ENDPOINT_PRODUCT_TYPE                    3
#define CHR_CFG_PARM_ENDPOINT_OS                              4
#define CHR_CFG_PARM_ENDPOINT_CPU_UTIL_SUPPORT                5
#define CHR_CFG_PARM_ENDPOINT_OS_MAJOR_VER                    6
#define CHR_CFG_PARM_ENDPOINT_OS_MINOR_VER                    7
#define CHR_CFG_PARM_ENDPOINT_OS_BUILD_NUM                    8
#define CHR_CFG_PARM_ENDPOINT_CSD_VERSION                     9
#define CHR_CFG_PARM_ENDPOINT_MEMORY                          10
#define CHR_CFG_PARM_ENDPOINT_APPC_DEFAULT_SEND_NOT_SUPPORTED 11 /* APPC is no longer supported */     
#define CHR_CFG_PARM_ENDPOINT_IPX_DEFAULT_SEND                12
#define CHR_CFG_PARM_ENDPOINT_SPX_DEFAULT_SEND                13
#define CHR_CFG_PARM_ENDPOINT_TCP_DEFAULT_SEND                14
#define CHR_CFG_PARM_ENDPOINT_UDP_DEFAULT_SEND                15
#define CHR_CFG_PARM_ENDPOINT_RTP_DEFAULT_SEND                16
#define CHR_CFG_PARM_ENDPOINT_APPC_STACK_NOT_SUPPORTED        17 /* APPC is no longer supported */
#define CHR_CFG_PARM_ENDPOINT_APPC_API_VERSION_NOT_SUPPORTED  18 /* APPC is no longer supported */
#define CHR_CFG_PARM_ENDPOINT_WINSOCK_API                     19
#define CHR_CFG_PARM_ENDPOINT_WINSOCK_STACK_VER               20
#define CHR_CFG_PARM_ENDPOINT_WINSOCK_API_VER                 21

/*
 * Traceroute run status
 */
typedef char CHR_TRACERT_RUNSTATUS_TYPE;

#define CHR_TRACERT_RUNSTATUS_UNINITIALIZED  0
#define CHR_TRACERT_RUNSTATUS_INITIALIZING   1
#define CHR_TRACERT_RUNSTATUS_RUNNING        2
#define CHR_TRACERT_RUNSTATUS_STOPPING       3
#define CHR_TRACERT_RUNSTATUS_ERROR          4
#define CHR_TRACERT_RUNSTATUS_FINISHED       5
#define CHR_TRACERT_RUNSTATUS_USER_STOPPED   6

/*
 * Pair run status
 */
typedef char CHR_PAIR_RUNSTATUS_TYPE;

#define CHR_PAIR_RUNSTATUS_UNINITIALIZED       0
#define CHR_PAIR_RUNSTATUS_INITIALIZING_1      1
#define CHR_PAIR_RUNSTATUS_INITIALIZING_2      2
#define CHR_PAIR_RUNSTATUS_INITIALIZING_3      3
#define CHR_PAIR_RUNSTATUS_INITIALIZED         4
#define CHR_PAIR_RUNSTATUS_RUNNING             5
#define CHR_PAIR_RUNSTATUS_STOPPING            6
#define CHR_PAIR_RUNSTATUS_REQUESTED_STOP      7
#define CHR_PAIR_RUNSTATUS_ERROR               8
#define CHR_PAIR_RUNSTATUS_RESOLVING_NAMES     9
#define CHR_PAIR_RUNSTATUS_POLLING            10
#define CHR_PAIR_RUNSTATUS_FINISHED           11
#define CHR_PAIR_RUNSTATUS_REQUESTING_STOP    12
#define CHR_PAIR_RUNSTATUS_FINISHED_WARNINGS  13
#define CHR_PAIR_RUNSTATUS_TRANSFERRING_PAYLOAD 14
#define CHR_PAIR_RUNSTATUS_APPLYING_IXIA_CONFIG 15
#define CHR_PAIR_RUNSTATUS_WAITING_FOR_REINIT 16
#define CHR_PAIR_RUNSTATUS_ABANDONED          17


/*
 * HPP measure/stats option.
 */
typedef char CHR_MEASURE_STATS;

#define CHR_MEASURE_STATS_NO_STATS_FILTERS  0
#define CHR_MEASURE_STATS_STATS_FILTERS     1
#define CHR_MEASURE_STATS_FILTERS           2

/*
 * Pair type
 */
typedef char CHR_PAIR_TYPE;

#define CHR_PAIR_TYPE_REGULAR                   1 /* Pairs with non-streaming scripts */
#define CHR_PAIR_TYPE_STREAMING                 2
#define CHR_PAIR_TYPE_VOIP                      3
#define CHR_PAIR_TYPE_VIDEO                     4
#define CHR_PAIR_TYPE_HARDWARE                  5
#define CHR_PAIR_TYPE_HARDWARE_VOIP             6


/*
 * License type
 */
typedef char CHR_LICENSE_TYPE;

#define CHR_LICENSE_TYPE_NONE                   1
#define CHR_LICENSE_TYPE_NODE_LOCKED            2
#define CHR_LICENSE_TYPE_FLOATING               3
#define CHR_LICENSE_TYPE_FLOATING_BORROW        4

/**
 * Report item.
 */
typedef char CHR_REPORT_ITEM;

#define CHR_REPORT_ITEM_JOIN_LEAVE      1       /**< Join/leave latencies. */


#ifndef CHR_API_FN
#define CHR_API_FN __cdecl /* api's calling convention */
#endif

/*
 * API Utility Functions
 */

CHR_API_RC CHR_API_FN
CHR_api_get_max_pairs(
  CHR_COUNT* maxPairs);

CHR_API_RC CHR_API_FN
CHR_api_get_license_type(
    CHR_LICENSE_TYPE* licenseType);

CHR_API_RC CHR_API_FN
CHR_api_get_license_expiration_time(
      CHR_LONG* expirationTime);

CHR_API_RC CHR_API_FN
CHR_api_get_reporting_port(
  CHR_PROTOCOL protocol,
  CHR_PORT* port);

CHR_API_RC CHR_API_FN
CHR_api_get_return_msg(
  CHR_API_RC returnCode,
  CHR_STRING returnMsg,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_api_get_version(
  CHR_STRING version,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_api_get_build_level(
  CHR_STRING version,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_api_get_aptixia_version(
  CHR_STRING version,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_api_initialize(
  CHR_DETAIL_LEVEL detailLevel,
  CHR_STRING errorInfo,
  CHR_LENGTH errorInfoMaxLength,
  CHR_LENGTH* errorInfoLength);

CHR_API_RC CHR_API_FN
CHR_api_set_reporting_port(
  CHR_PROTOCOL protocol,
  CHR_PORT port);

CHR_API_RC CHR_API_FN
CHR_api_get_pair_type(
  CHR_HANDLE handle,
  CHR_PAIR_TYPE* type);

/* Ixia */
CHR_API_RC CHR_API_FN
CHR_api_get_port_mgmt_ip_list(
    CHR_COUNT ip_addr_count, 
    CHR_ADDR_STRING*ip_list, 
    CHR_COUNT* ip_addr_read);

CHR_API_RC CHR_API_FN
CHR_api_get_network_ip_list( 
    CHR_CHAR port_mgmt_ip[CHR_MAX_ADDR_STRING], 
    CHR_COUNT ip_addr_count, 
    CHR_ADDR_STRING*ip_list, 
    CHR_COUNT* ip_addr_read);


/*
 * Licensing Control Functions
 */
 
CHR_API_RC CHR_API_FN
CHR_api_license_get_test_pair_count(
    CHR_STRING testFileName,
    CHR_LENGTH testFileNameLength,
    CHR_COUNT *pairCount);

CHR_API_RC CHR_API_FN
CHR_api_license_checkout_pairs(
    CHR_COUNT noPairs);

CHR_API_RC CHR_API_FN
CHR_api_license_checkin_pairs(void);

CHR_API_RC CHR_API_FN
CHR_api_license_change_borrow_time(
    CHR_COUNT daysToBorrow);

/*
 * QoS functions
 */
CHR_API_RC CHR_API_FN
CHR_api_new_qos_tos_template(
    CHR_QOS_TEMPLATE_TYPE templateType,
    CHR_STRING templateName,
    CHR_LENGTH templateLength,
    CHR_BYTE tosMask);

CHR_API_RC CHR_API_FN
CHR_api_delete_qos_template(
    CHR_STRING templateName,
    CHR_LENGTH templateLength);

CHR_API_RC CHR_API_FN
CHR_api_modify_qos_tos_template(
    CHR_QOS_TEMPLATE_TYPE templateType,
    CHR_STRING templateName,
    CHR_LENGTH templateLength,
    CHR_BYTE tosMask);

/*
 * Common Error Functions
 * (CHR_TEST_HANDLE/CHR_PAIR_HANDLE/CHR_MGROUP_HANDLE/CHR_MPAIR_HANDLE)
 */

CHR_API_RC CHR_API_FN
CHR_common_error_get_info(
  CHR_HANDLE handle,
  CHR_DETAIL_LEVEL detailLevel,
  CHR_STRING errorInfo,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_common_error_get_msg_num(
  CHR_HANDLE handle,
  CHR_MESSAGE_NUMBER* msgNumber);

/*
 * Common Results Extraction Functions
 * (CHR_PAIR_HANDLE/CHR_MPAIR_HANDLE/CHR_TIMINGREC_HANDLE) 
 */

CHR_API_RC CHR_API_FN
CHR_common_results_get_bytes_recv_e1(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_bytes_recv_e2(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_bytes_sent_e1(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_dg_dup_recv_e1(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_dg_dup_recv_e2(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_dg_dup_sent_e1(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_dg_dup_sent_e2(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_dg_lost_e1_to_e2(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_dg_out_of_order(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_dg_recv_e1(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_dg_recv_e2(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_dg_sent_e1(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_est_clock_error(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_jitter_buffer_lost(
  CHR_HANDLE handle,
  CHR_COUNT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_max_clock_error(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_meas_time(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_rtd(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_rtd_95pct_confidence(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_trans_count(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_e1_syn_tx(
  CHR_HANDLE handle,
  CHR_COUNT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_e1_syn_rx(
  CHR_HANDLE handle,
  CHR_COUNT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_e1_syn_failed(
  CHR_HANDLE handle,
  CHR_COUNT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_e1_conn_established(
  CHR_HANDLE handle,
  CHR_COUNT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_e1_fin_tx(
  CHR_HANDLE handle,
  CHR_COUNT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_e1_fin_rx(
  CHR_HANDLE handle,
  CHR_COUNT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_e1_fin_ack_tx(
  CHR_HANDLE handle,
  CHR_COUNT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_e1_fin_ack_rx(
  CHR_HANDLE handle,
  CHR_COUNT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_e1_ack_to_fin_tx(
  CHR_HANDLE handle,
  CHR_COUNT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_e1_ack_to_fin_rx(
  CHR_HANDLE handle,
  CHR_COUNT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_e1_rst_tx(
  CHR_HANDLE handle,
  CHR_COUNT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_e1_rst_rx(
  CHR_HANDLE handle,
  CHR_COUNT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_e1_tcp_retransmissions(
  CHR_HANDLE handle,
  CHR_COUNT* result);

CHR_API_RC CHR_API_FN
CHR_common_results_get_e1_tcp_timeouts(
  CHR_HANDLE handle,
  CHR_COUNT* result);

/*
 * Datagram Options Object Functions
 * (CHR_DGOPTS_HANDLE)
 */

CHR_API_RC CHR_API_FN
CHR_dgopts_get_recv_timeout(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_COUNT* recvTimeout);

CHR_API_RC CHR_API_FN
CHR_dgopts_get_retrans_count(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_COUNT* retransCount);

CHR_API_RC CHR_API_FN
CHR_dgopts_get_retrans_timeout(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_COUNT* retransTimeout);

CHR_API_RC CHR_API_FN
CHR_dgopts_get_TTL(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_COUNT* ttl);

CHR_API_RC CHR_API_FN
CHR_dgopts_get_window_size(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_COUNT* windowSize);

CHR_API_RC CHR_API_FN
CHR_dgopts_get_low_sender_jitter(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_BOOLEAN* flag);

CHR_API_RC CHR_API_FN
CHR_dgopts_get_limit_data_rate(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_BOOLEAN* flag);

CHR_API_RC CHR_API_FN
CHR_dgopts_get_data_rate_limit(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_COUNT* dataRateLimit);

CHR_API_RC CHR_API_FN
CHR_dgopts_get_measured_interval(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_COUNT* measuredInterval);

CHR_API_RC CHR_API_FN
CHR_dgopts_get_RTP_use_extended_headers(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_BOOLEAN* flag);

CHR_API_RC CHR_API_FN
CHR_dgopts_set_recv_timeout(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_COUNT recvTimeout);

CHR_API_RC CHR_API_FN
CHR_dgopts_set_retrans_count(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_COUNT retransCount);

CHR_API_RC CHR_API_FN
CHR_dgopts_set_retrans_timeout(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_COUNT retransTimeout);

CHR_API_RC CHR_API_FN
CHR_dgopts_set_TTL(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_COUNT ttl);

CHR_API_RC CHR_API_FN
CHR_dgopts_set_window_size(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_COUNT windowSize);

CHR_API_RC CHR_API_FN
CHR_dgopts_set_low_sender_jitter(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_BOOLEAN flag);

CHR_API_RC CHR_API_FN
CHR_dgopts_set_limit_data_rate(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_BOOLEAN flag);

CHR_API_RC CHR_API_FN
CHR_dgopts_set_data_rate_limit(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_COUNT dataRateLimit);

CHR_API_RC CHR_API_FN
CHR_dgopts_set_measured_interval(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_COUNT measuredInterval);

CHR_API_RC CHR_API_FN
CHR_dgopts_set_RTP_use_extended_headers(
  CHR_DGOPTS_HANDLE datagramOptionsHandle,
  CHR_BOOLEAN flag);


/*
 * Traceroute Hop Record Object Functions
 * (CHR_HOPREC_HANDLE)
 */

CHR_API_RC CHR_API_FN
CHR_hoprec_get_hop_address(
  CHR_HOPREC_HANDLE hoprecHandle,
  CHR_STRING hop_address,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_hoprec_get_hop_latency(
  CHR_HOPREC_HANDLE hoprecHandle,
  CHR_COUNT* hop_latency);

CHR_API_RC CHR_API_FN
CHR_hoprec_get_hop_name(
  CHR_HOPREC_HANDLE hoprecHandle,
  CHR_STRING hop_name,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_hoprec_get_hop_number(
  CHR_HOPREC_HANDLE hoprecHandle,
  CHR_COUNT* hop_number);

/*
 * Multicast Group Object Functions
 * (CHR_MGROUP_HANDLE)
 */

CHR_API_RC CHR_API_FN
CHR_mgroup_add_mpair(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_MPAIR_HANDLE mpairHandle);

CHR_API_RC CHR_API_FN
CHR_mgroup_copy(
  CHR_MGROUP_HANDLE toMgroupHandle,
  CHR_MGROUP_HANDLE fromMgroupHandle);

CHR_API_RC CHR_API_FN
CHR_mgroup_delete(
  CHR_MGROUP_HANDLE mgroupHandle);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_appl_script_name(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING scriptName,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_comment(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING comment,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_console_e1_addr(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING consoleE1Name,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_console_e1_protocol(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_PROTOCOL* protocol);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_e1_addr(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING e1Name,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_e1_config_value(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_CFG_PARM parameter,
  CHR_STRING value,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_mpair(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_COUNT index,
  CHR_MPAIR_HANDLE* mpairHandle);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_mpair_count(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_COUNT* mpairCount);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_multicast_addr(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING addr,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_multicast_port(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_PORT* port);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_name(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING name,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_protocol(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_PROTOCOL* protocol);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_qos_name(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING qosName,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_script_filename(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING fileName,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_use_console_e1_values(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_BOOLEAN* useValues);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_script_variable(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING name,
  CHR_LENGTH nameLength,
  CHR_STRING value,
  CHR_LENGTH valueMaxLength,
  CHR_LENGTH* valueLength);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_script_embedded_payload(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING variableName,
  CHR_LENGTH variableNameLength,
  CHR_STRING payload,
  CHR_LENGTH payloadMaxLength,
  CHR_LENGTH* payloadLength);

CHR_API_RC CHR_API_FN
CHR_mgroup_get_payload_file(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING variableName,
  CHR_LENGTH variableNameLength,
  CHR_STRING filename,
  CHR_LENGTH filenameMaxLength,
  CHR_LENGTH* filenameLength,
  CHR_BOOLEAN* embedded);

CHR_API_RC CHR_API_FN
CHR_mgroup_is_udp_RFC768_streaming(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_BOOLEAN* used);

CHR_API_RC CHR_API_FN
CHR_mgroup_is_disabled(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_BOOLEAN* disabled);

CHR_API_RC CHR_API_FN 
CHR_mgroup_new(
  CHR_MGROUP_HANDLE* mgroupHandle);

CHR_API_RC CHR_API_FN
CHR_mgroup_remove_mpair(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_MPAIR_HANDLE mpairHandle);

CHR_API_RC CHR_API_FN
CHR_mgroup_set_comment(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING comment,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_mgroup_set_console_e1_addr(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING consoleE1Name,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_mgroup_set_console_e1_protocol(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_PROTOCOL protocol);

CHR_API_RC CHR_API_FN
  CHR_mgroup_set_e1_addr(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING e1Name,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_mgroup_set_lock(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_BOOLEAN lock);

CHR_API_RC CHR_API_FN
CHR_mgroup_set_multicast_addr(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING addr,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_mgroup_set_multicast_port(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_PORT port);

CHR_API_RC CHR_API_FN
CHR_mgroup_set_name(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING name,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_mgroup_set_protocol(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_PROTOCOL protocol);

CHR_API_RC CHR_API_FN
CHR_mgroup_set_qos_name(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING qosName,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_mgroup_set_script_variable(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING name,
  CHR_LENGTH nameLength,
  CHR_STRING value,
  CHR_LENGTH valueLength);

CHR_API_RC CHR_API_FN
CHR_mgroup_set_script_embedded_payload(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING variableName,
  CHR_LENGTH variableNameLength,
  CHR_STRING payload,
  CHR_LENGTH payloadLength);

CHR_API_RC CHR_API_FN
CHR_mgroup_set_payload_file(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING variableName,
  CHR_LENGTH variableNameLength,
  CHR_STRING filename,
  CHR_LENGTH filenameLength,
  CHR_BOOLEAN embedded);

CHR_API_RC CHR_API_FN
CHR_mgroup_set_use_console_e1_values(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_BOOLEAN useValues);

CHR_API_RC CHR_API_FN
CHR_mgroup_use_script_filename(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_STRING fileName,
  CHR_LENGTH fileNameLength);

CHR_API_RC CHR_API_FN
CHR_mgroup_disable(
  CHR_MGROUP_HANDLE mgroupHandle,
  CHR_BOOLEAN disable);


/*
 * Multicast Pair Object Functions
 * (CHR_MPAIR_HANDLE)
 */

CHR_API_RC CHR_API_FN
CHR_mpair_delete(
  CHR_MPAIR_HANDLE mpairHandle);

CHR_API_RC CHR_API_FN
CHR_mpair_get_e2_addr(
  CHR_MPAIR_HANDLE mpairHandle,
  CHR_STRING e2Name,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_mpair_get_e2_config_value(
  CHR_MPAIR_HANDLE pairHandle,
  CHR_CFG_PARM parameter,
  CHR_STRING value,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_mpair_get_setup_e1_e2_addr(
  CHR_MPAIR_HANDLE mpairHandle,
  CHR_STRING e2Name,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_mpair_get_timing_record(
  CHR_MPAIR_HANDLE mpairHandle,
  CHR_COUNT index,
  CHR_TIMINGREC_HANDLE* timingRecordHandle);

CHR_API_RC CHR_API_FN
CHR_mpair_get_timing_record_count(
  CHR_MPAIR_HANDLE mpairHandle,
  CHR_COUNT* count);

CHR_API_RC CHR_API_FN
CHR_mpair_get_use_setup_e1_e2_values(
  CHR_MPAIR_HANDLE mpairHandle,
  CHR_BOOLEAN* use);

CHR_API_RC CHR_API_FN
CHR_mpair_get_runStatus(
  CHR_MPAIR_HANDLE mpairHandle,
  CHR_PAIR_RUNSTATUS_TYPE *runStatus);

CHR_API_RC CHR_API_FN
CHR_mpair_new(
  CHR_MPAIR_HANDLE* mpairHandle);

CHR_API_RC CHR_API_FN
CHR_mpair_set_e2_addr(
  CHR_MPAIR_HANDLE mpairHandle,
  CHR_STRING e2Name,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_mpair_set_lock(
  CHR_MPAIR_HANDLE mpairHandle,
  CHR_BOOLEAN lock);

CHR_API_RC CHR_API_FN
CHR_mpair_set_setup_e1_e2_addr(
  CHR_MPAIR_HANDLE mpairHandle,
  CHR_STRING e2Name,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_mpair_set_use_setup_e1_e2_values(
  CHR_MPAIR_HANDLE mpairHandle,
  CHR_BOOLEAN use);


/*
 * Pair Object Functions
 * (CHR_PAIR_HANDLE)
 */

CHR_API_RC CHR_API_FN
CHR_pair_copy(
  CHR_PAIR_HANDLE toPairHandle,
  CHR_PAIR_HANDLE fromPairHandle);

CHR_API_RC CHR_API_FN
CHR_pair_delete(
  CHR_PAIR_HANDLE pairHandle);

CHR_API_RC CHR_API_FN
CHR_pair_get_appl_script_name(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING scriptName,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_pair_get_comment(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING comment,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_pair_get_console_e1_addr(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING consoleE1Name,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_pair_get_console_e1_protocol(
  CHR_PAIR_HANDLE pairHandle,
  CHR_PROTOCOL* protocol);

CHR_API_RC CHR_API_FN
CHR_pair_get_e1_addr(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING e1Name,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_pair_get_e2_addr(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING e2Name,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_pair_get_e1_config_value(
  CHR_PAIR_HANDLE pairHandle,
  CHR_CFG_PARM parameter,
  CHR_STRING value,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_pair_get_e2_config_value(
  CHR_PAIR_HANDLE pairHandle,
  CHR_CFG_PARM parameter,
  CHR_STRING value,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_pair_get_protocol(
  CHR_PAIR_HANDLE pairHandle,
  CHR_PROTOCOL* protocol);

CHR_API_RC CHR_API_FN
CHR_pair_get_qos_name(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING qosName,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_pair_get_runStatus (
  CHR_PAIR_HANDLE pairHandle,
  CHR_PAIR_RUNSTATUS_TYPE *runStatus);

CHR_API_RC CHR_API_FN
CHR_pair_get_script_filename(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING fileName,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_pair_get_setup_e1_e2_addr(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING e1E2Name,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_pair_get_timing_record(
  CHR_PAIR_HANDLE pairHandle,
  CHR_COUNT index,
  CHR_TIMINGREC_HANDLE* timingRecordHandle);

CHR_API_RC CHR_API_FN
CHR_pair_get_timing_record_count(
  CHR_PAIR_HANDLE pairHandle,
  CHR_COUNT* count);

CHR_API_RC CHR_API_FN
CHR_pair_get_use_console_e1_values(
  CHR_PAIR_HANDLE pairHandle,
  CHR_BOOLEAN* useValues);

CHR_API_RC CHR_API_FN
CHR_pair_get_use_setup_e1_e2_values(
  CHR_PAIR_HANDLE pairHandle,
  CHR_BOOLEAN* useValues);

CHR_API_RC CHR_API_FN
CHR_pair_is_udp_RFC768_streaming(
  CHR_PAIR_HANDLE pairHandle,
  CHR_BOOLEAN* used);

CHR_API_RC CHR_API_FN
CHR_pair_is_disabled(
  CHR_PAIR_HANDLE pairHandle,
  CHR_BOOLEAN* disabled);

CHR_API_RC CHR_API_FN
CHR_pair_new(
  CHR_PAIR_HANDLE* pairHandle);

CHR_API_RC CHR_API_FN
CHR_pair_set_comment(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING comment,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_pair_set_console_e1_addr(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING consoleE1Name,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_pair_set_console_e1_protocol(
  CHR_PAIR_HANDLE pairHandle,
  CHR_PROTOCOL protocol);

CHR_API_RC CHR_API_FN
CHR_pair_set_e1_addr(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING e1Name,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_pair_set_e2_addr(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING e2Name,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_pair_set_lock(
  CHR_PAIR_HANDLE pairHandle,
  CHR_BOOLEAN lock);

CHR_API_RC CHR_API_FN
CHR_pair_set_protocol(
  CHR_PAIR_HANDLE pairHandle,
  CHR_PROTOCOL protocol);

CHR_API_RC CHR_API_FN
CHR_pair_set_qos_name(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING qosName,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_pair_set_script_variable(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING name,
  CHR_LENGTH nameLength,
  CHR_STRING value,
  CHR_LENGTH valueLength);

CHR_API_RC CHR_API_FN
CHR_pair_get_script_variable(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING name,
  CHR_LENGTH nameLength,
  CHR_STRING value,
  CHR_LENGTH valueMaxLength,
  CHR_LENGTH* valueLength);

CHR_API_RC CHR_API_FN
CHR_pair_set_script_embedded_payload(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING variableName,
  CHR_LENGTH variableNameLength,
  CHR_STRING payload,
  CHR_LENGTH payloadLength);

CHR_API_RC CHR_API_FN
CHR_pair_get_script_embedded_payload(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING variableName,
  CHR_LENGTH variableNameLength,
  CHR_STRING payload,
  CHR_LENGTH payloadMaxLength,
  CHR_LENGTH* payloadLength);

CHR_API_RC CHR_API_FN
CHR_pair_set_payload_file(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING variableName,
  CHR_LENGTH variableNameLength,
  CHR_STRING filename,
  CHR_LENGTH filenameLength,
  CHR_BOOLEAN embedded);

CHR_API_RC CHR_API_FN
CHR_pair_get_payload_file(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING variableName,
  CHR_LENGTH variableNameLength,
  CHR_STRING filename,
  CHR_LENGTH filenameMaxLength,
  CHR_LENGTH* filenameLength,
  CHR_BOOLEAN* embedded);

CHR_API_RC CHR_API_FN
CHR_pair_set_setup_e1_e2_addr(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING e1E2Name,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_pair_set_use_console_e1_values(
  CHR_PAIR_HANDLE pairHandle,
  CHR_BOOLEAN useValues);

CHR_API_RC CHR_API_FN
CHR_pair_set_use_setup_e1_e2_values(
  CHR_PAIR_HANDLE pairHandle,
  CHR_BOOLEAN useValues);

CHR_API_RC CHR_API_FN
CHR_pair_use_script_filename(
  CHR_PAIR_HANDLE pairHandle,
  CHR_STRING fileName,
  CHR_LENGTH fileNameLength);

CHR_API_RC CHR_API_FN
CHR_pair_disable(
  CHR_PAIR_HANDLE pairHandle,
  CHR_BOOLEAN     disable);


/*
 * Pair/Multicast Group Pair Results Extraction Functions
 * (CHR_PAIR_HANDLE/CHR_MPAIR_HANDLE)
 */

CHR_API_RC CHR_API_FN
CHR_pair_results_get_average(
  CHR_HANDLE handle,
  CHR_RESULTS resultType,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_pair_results_get_CPU_util_e1(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_pair_results_get_CPU_util_e2(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_pair_results_get_maximum(
  CHR_HANDLE handle,
  CHR_RESULTS resultType,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_pair_results_get_minimum(
  CHR_HANDLE handle,
  CHR_RESULTS resultType,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_pair_results_get_rel_precision(
  CHR_HANDLE handle,
  CHR_FLOAT* result);

CHR_API_RC CHR_API_FN
CHR_pair_results_get_95pct_confidence(
  CHR_HANDLE handle,
  CHR_RESULTS resultType,
  CHR_FLOAT* result);

/*
 * Run Options Object Functions
 * (CHR_RUNOPTS_HANDLE)
 */

CHR_API_RC CHR_API_FN
CHR_runopts_get_connect_timeout(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT* connectTimeout);

CHR_API_RC CHR_API_FN
CHR_runopts_get_CPU_util(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN* cpuUtil);

CHR_API_RC CHR_API_FN
CHR_runopts_get_collect_TCP_stats(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN* collectTCPStats);

CHR_API_RC CHR_API_FN
CHR_runopts_get_allow_pair_reinit(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN* allowPairReinit);

CHR_API_RC CHR_API_FN
CHR_runopts_get_pair_reinit_max(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT* pairReinitMax);

CHR_API_RC CHR_API_FN
CHR_runopts_get_pair_reinit_retry_interval(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT* pairReinitRetryInterval);
CHR_API_RC CHR_API_FN
CHR_runopts_get_allow_pair_reinit_run(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN* allowPairReinit);

CHR_API_RC CHR_API_FN
CHR_runopts_get_pair_reinit_max_run(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT* pairReinitMax);

CHR_API_RC CHR_API_FN
CHR_runopts_get_pair_reinit_retry_interval_run(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT* pairReinitRetryInterval);

CHR_API_RC CHR_API_FN
CHR_runopts_get_HW_timestamps(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN* hwTimestamps);

CHR_API_RC CHR_API_FN
CHR_runopts_get_fewer_setup_connections(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN* fewerConnections);

CHR_API_RC CHR_API_FN
CHR_runopts_get_apply_dod_only(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN* iep_dod_only);

CHR_API_RC CHR_API_FN
CHR_runopts_get_num_result_ranges(
  CHR_RUNOPTS_HANDLE handle,
  CHR_RESULTS resultType,
  CHR_COUNT* number);

CHR_API_RC CHR_API_FN
CHR_runopts_get_poll_endpoints(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN* pollEndpoints);

CHR_API_RC CHR_API_FN
CHR_runopts_get_poll_interval(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT* pollInterval);

CHR_API_RC CHR_API_FN
CHR_runopts_get_random_new_seed(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN* randomNewSeed);

CHR_API_RC CHR_API_FN
CHR_runopts_get_reporting_type(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_TEST_REPORTING* testReporting);

CHR_API_RC CHR_API_FN
CHR_runopts_get_poll_retrieving_type(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_TEST_RETRIEVING* testRetrieving);

CHR_API_RC CHR_API_FN
CHR_runopts_get_reporting_firewall(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_TEST_REPORTING_FIREWALL* testReportingFirewall);

CHR_API_RC CHR_API_FN
CHR_runopts_get_result_range(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_RESULTS resultType,
  CHR_COUNT index,
  CHR_COUNT *minValue,
  CHR_COUNT *maxValue);

CHR_API_RC CHR_API_FN
CHR_runopts_get_stop_after_num_pairs_fail(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT* numPairs);

CHR_API_RC CHR_API_FN
CHR_runopts_get_stop_on_init_failure(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN* stopOnInitFailure);

CHR_API_RC CHR_API_FN
CHR_runopts_get_test_duration(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT* testDuration);

CHR_API_RC CHR_API_FN
CHR_runopts_get_test_end(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_TEST_END* testEnd);

CHR_API_RC CHR_API_FN
CHR_runopts_get_validate_on_recv(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN* validateOnRecv);

CHR_API_RC CHR_API_FN
CHR_runopts_get_clksync_hardware_ts(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN* clksync_hardware_ts);

CHR_API_RC CHR_API_FN
CHR_runopts_get_clksync_external(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN* clksync_external);

CHR_API_RC CHR_API_FN
CHR_runopts_set_connect_timeout(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT connectTimeout);

CHR_API_RC CHR_API_FN
CHR_runopts_set_CPU_util(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN cpuUtil);

CHR_API_RC CHR_API_FN
CHR_runopts_set_collect_TCP_stats(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN collectTCPStats);

CHR_API_RC CHR_API_FN
CHR_runopts_set_allow_pair_reinit(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN allowPairReinit);

CHR_API_RC CHR_API_FN
CHR_runopts_set_pair_reinit_max(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT pairReinitMax);

CHR_API_RC CHR_API_FN
CHR_runopts_set_pair_reinit_retry_interval(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT pairReinitRetryInterval);
CHR_API_RC CHR_API_FN
CHR_runopts_set_allow_pair_reinit_run(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN allowPairReinit);

CHR_API_RC CHR_API_FN
CHR_runopts_set_pair_reinit_max_run(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT pairReinitMax);

CHR_API_RC CHR_API_FN
CHR_runopts_set_pair_reinit_retry_interval_run(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT pairReinitRetryInterval);

CHR_API_RC CHR_API_FN
CHR_runopts_set_HW_timestamps(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN hwTimestamps);

CHR_API_RC CHR_API_FN
CHR_runopts_set_fewer_setup_connections(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN fewerConnections);

CHR_API_RC CHR_API_FN
CHR_runopts_set_apply_dod_only(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN ep_dod_only);

CHR_API_RC CHR_API_FN
CHR_runopts_set_num_result_ranges(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_RESULTS resultType,
  CHR_COUNT number);

CHR_API_RC CHR_API_FN
CHR_runopts_set_poll_endpoints(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN pollEndpoints);

CHR_API_RC CHR_API_FN
CHR_runopts_set_poll_interval(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT pollInterval);

CHR_API_RC CHR_API_FN
CHR_runopts_set_random_new_seed(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN randomNewSeed);

CHR_API_RC CHR_API_FN
CHR_runopts_set_reporting_type(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_TEST_REPORTING testReporting);

CHR_API_RC CHR_API_FN
CHR_runopts_set_poll_retrieving_type(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_TEST_RETRIEVING testRetrieving);

CHR_API_RC CHR_API_FN
CHR_runopts_set_reporting_firewall(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_TEST_REPORTING_FIREWALL testReportingFirewall);

CHR_API_RC CHR_API_FN
CHR_runopts_set_result_range(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_RESULTS resultType,
  CHR_COUNT index,
  CHR_COUNT minValue,
  CHR_COUNT maxValue);

CHR_API_RC CHR_API_FN
CHR_runopts_set_stop_after_num_pairs_fail(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT numPairs);

CHR_API_RC CHR_API_FN
CHR_runopts_set_stop_on_init_failure(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN stopOnInitFailure);

CHR_API_RC CHR_API_FN
CHR_runopts_set_test_duration(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_COUNT testDuration);

CHR_API_RC CHR_API_FN
CHR_runopts_set_test_end(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_TEST_END testEnd);

CHR_API_RC CHR_API_FN
CHR_runopts_set_validate_on_recv(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN validateOnRecv);

CHR_API_RC CHR_API_FN
CHR_runopts_set_clksync_hardware_ts(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN clksync_hardware_ts);

CHR_API_RC CHR_API_FN
CHR_runopts_set_clksync_external(
  CHR_RUNOPTS_HANDLE runOptionsHandle,
  CHR_BOOLEAN clksync_external);

CHR_API_RC CHR_API_FN
CHR_runopts_get_management_qos_console_name(
    CHR_RUNOPTS_HANDLE runOptionsHandle,
    CHR_STRING qosName, 
    CHR_LENGTH maxLength, 
    CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_runopts_get_management_qos_endpoint_name(
    CHR_RUNOPTS_HANDLE runOptionsHandle,
    CHR_STRING qosName, 
    CHR_LENGTH maxLength, 
    CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_runopts_set_management_qos_console_name(
    CHR_RUNOPTS_HANDLE runOptionsHandle,
    CHR_STRING qosName, 
    CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_runopts_set_management_qos_endpoint_name(
    CHR_RUNOPTS_HANDLE runOptionsHandle,
    CHR_STRING qosName, 
    CHR_LENGTH length);

/*
 * Test Object Functions
 * (CHR_TEST_HANDLE)
 */

CHR_API_RC CHR_API_FN
CHR_test_abandon(
  CHR_TEST_HANDLE testHandle);

CHR_API_RC CHR_API_FN
CHR_test_add_mgroup(
  CHR_TEST_HANDLE testHandle,
  CHR_MGROUP_HANDLE mgroupHandle);

CHR_API_RC CHR_API_FN
CHR_test_add_pair(
  CHR_TEST_HANDLE testHandle,
  CHR_PAIR_HANDLE pairHandle);

CHR_API_RC CHR_API_FN
CHR_test_clear_results(
  CHR_TEST_HANDLE testHandle);

CHR_API_RC CHR_API_FN
CHR_test_delete(
  CHR_TEST_HANDLE testHandle);

CHR_API_RC CHR_API_FN
CHR_test_force_delete(
  CHR_TEST_HANDLE testHandle);

CHR_API_RC CHR_API_FN
CHR_test_get_dgopts(
  CHR_TEST_HANDLE testHandle,
  CHR_DGOPTS_HANDLE* dgoptsHandle);

CHR_API_RC CHR_API_FN
CHR_test_get_filename(
  CHR_TEST_HANDLE testHandle,
  CHR_STRING saveFileName,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_test_get_how_ended(
  CHR_TEST_HANDLE testHandle,
  CHR_TEST_HOW_ENDED* howEnded);

CHR_API_RC CHR_API_FN
CHR_test_get_local_start_time(
  CHR_TEST_HANDLE testHandle,
  struct tm* localstartTime);

CHR_API_RC CHR_API_FN
CHR_test_get_local_stop_time(
  CHR_TEST_HANDLE testHandle,
  struct tm* localstopTime);

CHR_API_RC CHR_API_FN
CHR_test_get_mgroup(
  CHR_TEST_HANDLE testHandle,
  CHR_COUNT index,
  CHR_MGROUP_HANDLE* mgroupHandle);

CHR_API_RC CHR_API_FN
CHR_test_get_mgroup_count(
  CHR_TEST_HANDLE testHandle,
  CHR_COUNT* mgroupCount);

CHR_API_RC CHR_API_FN
CHR_test_get_pair(
  CHR_TEST_HANDLE testHandle,
  CHR_COUNT index,
  CHR_PAIR_HANDLE* pairHandle);

CHR_API_RC CHR_API_FN
CHR_test_get_pair_count(
  CHR_TEST_HANDLE testHandle,
  CHR_COUNT* pairCount);

CHR_API_RC CHR_API_FN
CHR_test_get_runopts(
  CHR_TEST_HANDLE testHandle,
  CHR_RUNOPTS_HANDLE* runoptsHandle);

CHR_API_RC CHR_API_FN
CHR_test_get_start_time(
  CHR_TEST_HANDLE testHandle,
  time_t* startTime);

CHR_API_RC CHR_API_FN
CHR_test_get_stop_time(
  CHR_TEST_HANDLE testHandle,
  time_t* stopTime);

CHR_API_RC CHR_API_FN
CHR_test_get_throughput_units(
  CHR_TEST_HANDLE testHandle,
  CHR_THROUGHPUT_UNITS* throughputUnits);

CHR_API_RC CHR_API_FN
CHR_test_load(
  CHR_TEST_HANDLE testHandle,
  CHR_STRING testFileName,
  CHR_LENGTH testFileNameLength);

CHR_API_RC CHR_API_FN
CHR_test_new(
  CHR_TEST_HANDLE* testHandle);

CHR_API_RC CHR_API_FN
CHR_test_query_stop(
  CHR_TEST_HANDLE testHandle,
  CHR_COUNT timeout);

CHR_API_RC CHR_API_FN
CHR_test_save(
  CHR_TEST_HANDLE testHandle);

CHR_API_RC CHR_API_FN
CHR_test_set_filename(
  CHR_TEST_HANDLE testHandle,
  CHR_STRING saveFileName,
  CHR_LENGTH saveFileNameLength);

CHR_API_RC CHR_API_FN
CHR_test_set_throughput_units(
  CHR_TEST_HANDLE testHandle,
  CHR_THROUGHPUT_UNITS throughputUnits);

CHR_API_RC CHR_API_FN
CHR_test_start(
  CHR_TEST_HANDLE testHandle);

CHR_API_RC CHR_API_FN
CHR_test_stop(
  CHR_TEST_HANDLE testHandle);

CHR_API_RC CHR_API_FN
CHR_test_load_app_groups(
    CHR_TEST_HANDLE                 testHandle,
    CHR_STRING                      filename,
    CHR_LENGTH                      filenameLength);

CHR_API_RC CHR_API_FN
CHR_test_add_app_group(
  CHR_TEST_HANDLE testHandle,
  CHR_APP_GROUP_HANDLE appGroupHandle);

CHR_API_RC CHR_API_FN
CHR_test_remove_app_group(
  CHR_TEST_HANDLE testHandle,
  CHR_APP_GROUP_HANDLE appGroupHandle);

CHR_API_RC CHR_API_FN
CHR_test_get_app_group_by_index(
  CHR_TEST_HANDLE testHandle,
  CHR_COUNT index,
  CHR_APP_GROUP_HANDLE* appGroupHandle);

CHR_API_RC CHR_API_FN
CHR_test_get_app_group_by_name(
  CHR_TEST_HANDLE testHandle,
  CHR_STRING name,
  CHR_LENGTH nameLength,
  CHR_APP_GROUP_HANDLE* appGroupHandle);

CHR_API_RC CHR_API_FN
CHR_test_get_app_group_count(
  CHR_TEST_HANDLE testHandle,
  CHR_COUNT* appGroupCount);

/*
 * These are Ixia hardware specfic functions to
 * manipulate the stack manager configuration in the
 * file.
 */
CHR_API_RC CHR_API_FN
CHR_test_set_test_server_session(
    CHR_TEST_HANDLE testHandle,
    CHR_STRING testServerAddress,
    CHR_COUNT testServerSize,
    CHR_COUNT testServerPort,
    CHR_WLONG sessionObjectId );

CHR_API_RC CHR_API_FN
CHR_test_get_test_server_session(
    CHR_TEST_HANDLE testHandle,
    CHR_STRING testServerAddress,
    CHR_COUNT testServerAddressMaxSize,
    CHR_COUNT * testServerAddressSize,
    CHR_COUNT * testServerPort,
    CHR_WLONG * sessionObjectId );

CHR_API_RC CHR_API_FN
CHR_test_set_ixia_network_configuration(
    CHR_TEST_HANDLE testHandle,
    CHR_BYTE * dataPtr,
    CHR_LENGTH dataSize );


CHR_API_RC CHR_API_FN
CHR_test_get_ixia_network_configuration(
    CHR_TEST_HANDLE testHandle,
    CHR_BYTE * dataPtr,
    CHR_LENGTH maximumSize,
    CHR_LENGTH * dataSize );

CHR_API_RC CHR_API_FN
CHR_test_load_ixia_network_configuration(
    CHR_TEST_HANDLE testHandle,
    CHR_STRING fileName,
    CHR_LENGTH fileNameLength );

CHR_API_RC CHR_API_FN
CHR_test_save_ixia_network_configuration(
    CHR_TEST_HANDLE testHandle,
    CHR_STRING fileName,
    CHR_LENGTH fileMaximumLength );

CHR_API_RC CHR_API_FN
CHR_test_clear_ixia_network_configuration(
    CHR_TEST_HANDLE testHandle );

/*
 * Timing Record Obect Functions
 * (CHR_TIMINGREC_HANDLE)
 */

CHR_API_RC CHR_API_FN
CHR_timingrec_get_elapsed(
  CHR_TIMINGREC_HANDLE timingrecHandle,
  CHR_FLOAT* elapsed);

CHR_API_RC CHR_API_FN
CHR_timingrec_get_end_to_end_delay(
    CHR_TIMINGREC_HANDLE timingrecHandle,
    CHR_FLOAT* delay);

CHR_API_RC CHR_API_FN
CHR_timingrec_get_inactive(
  CHR_TIMINGREC_HANDLE timingrecHandle,
  CHR_FLOAT* inactive);

CHR_API_RC CHR_API_FN
CHR_timingrec_get_jitter(
  CHR_TIMINGREC_HANDLE timingrecHandle,
  CHR_FLOAT* jitter);

CHR_API_RC CHR_API_FN
CHR_timingrec_get_max_consecutive_lost(
    CHR_TIMINGREC_HANDLE timingrecHandle,
    CHR_COUNT* lost);

CHR_API_RC CHR_API_FN
CHR_timingrec_get_max_delay_variation(
    CHR_TIMINGREC_HANDLE timingrecHandle,
    CHR_COUNT* variation);

CHR_API_RC CHR_API_FN
CHR_timingrec_get_MOS_estimate(
    CHR_TIMINGREC_HANDLE timingrecHandle,
    CHR_FLOAT* estimate);

CHR_API_RC CHR_API_FN
CHR_timingrec_get_one_way_delay(
    CHR_TIMINGREC_HANDLE timingrecHandle,
    CHR_COUNT* delay);

CHR_API_RC CHR_API_FN
CHR_timingrec_get_R_value(
    CHR_TIMINGREC_HANDLE timingrecHandle,
    CHR_FLOAT* Rvalue);

CHR_API_RC CHR_API_FN
CHR_timingrec_get_result_frequency(
    CHR_TIMINGREC_HANDLE timingrecHandle,
    CHR_RESULTS resultType,
    CHR_COUNT index,
    CHR_COUNT* frequency);

CHR_API_RC CHR_API_FN
CHR_timingrec_get_e1_rssi(
    CHR_TIMINGREC_HANDLE timingrecHandle,
    CHR_LONG* rssi);

CHR_API_RC CHR_API_FN
CHR_timingrec_get_e2_rssi(
    CHR_TIMINGREC_HANDLE timingrecHandle,
    CHR_LONG* rssi);

CHR_API_RC CHR_API_FN
CHR_timingrec_get_e1_bssid(
    CHR_TIMINGREC_HANDLE timingrecHandle,
    CHR_STRING bssid,
    CHR_LENGTH maxLength,
    CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_timingrec_get_e2_bssid(
    CHR_TIMINGREC_HANDLE timingrecHandle,
    CHR_STRING bssid,
    CHR_LENGTH maxLength,
    CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_timingrec_get_df(
    CHR_TIMINGREC_HANDLE timingrecHandle,
    CHR_COUNT* df);

CHR_API_RC CHR_API_FN
CHR_timingrec_get_mlr(
    CHR_TIMINGREC_HANDLE timingrecHandle,
    CHR_FLOAT* mlr);

/**
 * Returns the Report Group Identifier field from the timing record.
 * 
 * @param i_recordHandle    Timing record handle.
 * @param o_reportGroupId   Report group identifier.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_timingrec_get_report_group_id(
    CHR_TIMINGREC_HANDLE    i_recordHandle,
    CHR_COUNT*              o_reportGroupId);

/*
 * Traceroute Object Functions
 * (CHR_TRACERT_PAIR_HANDLE)
 */

CHR_API_RC CHR_API_FN
CHR_tracert_pair_delete(
  CHR_TRACERT_PAIR_HANDLE pairHandle);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_get_e1_addr(
  CHR_TRACERT_PAIR_HANDLE pairHandle,
  CHR_STRING e1Name,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_get_e2_addr(
  CHR_TRACERT_PAIR_HANDLE pairHandle,
  CHR_STRING e1Name,
  CHR_LENGTH maxLength,
  CHR_LENGTH* length);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_get_hop_record(
  CHR_TRACERT_PAIR_HANDLE trpairHandle,
  CHR_COUNT index,
  CHR_HOPREC_HANDLE* hopRecordHandle);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_get_max_hops(
  CHR_TRACERT_PAIR_HANDLE pairHandle,
  CHR_COUNT* max_hops);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_get_max_timeout(
  CHR_TRACERT_PAIR_HANDLE pairHandle,
  CHR_COUNT* max_timeout);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_get_resolve_hop_name(
  CHR_TRACERT_PAIR_HANDLE pairHandle,
  CHR_BOOLEAN* resolve_name);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_get_runStatus(
  CHR_TRACERT_PAIR_HANDLE pairHandle,
  CHR_TRACERT_RUNSTATUS_TYPE* status);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_new(
  CHR_TRACERT_PAIR_HANDLE* pairHandle);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_query_stop(
  CHR_TRACERT_PAIR_HANDLE pairHandle,
  CHR_COUNT timeout);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_results_get_hop_count(
  CHR_TRACERT_PAIR_HANDLE pairHandle,
  CHR_COUNT* count);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_run(
  CHR_TRACERT_PAIR_HANDLE pairHandle);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_set_e1_addr(
  CHR_TRACERT_PAIR_HANDLE pairHandle,
  CHR_STRING e1Name,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_set_e2_addr(
  CHR_TRACERT_PAIR_HANDLE pairHandle,
  CHR_STRING e1Name,
  CHR_LENGTH length);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_set_max_hops(
  CHR_TRACERT_PAIR_HANDLE pairHandle,
  CHR_COUNT max_hops);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_set_max_timeout(
  CHR_TRACERT_PAIR_HANDLE pairHandle,
  CHR_COUNT max_timeout);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_set_resolve_hop_name(
  CHR_TRACERT_PAIR_HANDLE pairHandle,
  CHR_BOOLEAN resolve_name);

CHR_API_RC CHR_API_FN
CHR_tracert_pair_stop(
  CHR_TRACERT_PAIR_HANDLE pairHandle);


/*----------------------------------------------------------------------*/
/*                  VoIP Pair functions                                 */
/*                  (CHR_VOIP_PAIR_HANDLE)                              */
/*----------------------------------------------------------------------*/

CHR_API_RC CHR_API_FN
CHR_voip_pair_get_codec(
  CHR_VOIP_PAIR_HANDLE pairHandle,
  CHR_VOIP_CODEC* codec);

CHR_API_RC CHR_API_FN
CHR_voip_pair_new(
  CHR_VOIP_PAIR_HANDLE* pairHandle);

CHR_API_RC CHR_API_FN
CHR_voip_pair_set_additional_delay(
  CHR_VOIP_PAIR_HANDLE pairHandle,
  CHR_COUNT size);

CHR_API_RC CHR_API_FN
CHR_voip_pair_set_codec(
  CHR_VOIP_PAIR_HANDLE pairHandle,
  CHR_VOIP_CODEC codec);

CHR_API_RC CHR_API_FN
CHR_voip_pair_set_datagram_delay(
  CHR_VOIP_PAIR_HANDLE pairHandle,
  CHR_COUNT delay);

CHR_API_RC CHR_API_FN
CHR_voip_pair_set_dest_port_num(
  CHR_VOIP_PAIR_HANDLE pairHandle,
  CHR_PORT port);

CHR_API_RC CHR_API_FN
CHR_voip_pair_set_initial_delay(
  CHR_VOIP_PAIR_HANDLE pairHandle,
  CHR_STRING delay,
  CHR_LENGTH len);

CHR_API_RC CHR_API_FN
CHR_voip_pair_set_jitter_buffer_size(
  CHR_VOIP_PAIR_HANDLE pairHandle,
  CHR_COUNT size);

CHR_API_RC CHR_API_FN
CHR_voip_pair_set_source_port_num(
  CHR_VOIP_PAIR_HANDLE pairHandle,
  CHR_PORT port);

CHR_API_RC CHR_API_FN
CHR_voip_pair_set_tr_duration(
  CHR_VOIP_PAIR_HANDLE pairHandle,
  CHR_COUNT seconds);

CHR_API_RC CHR_API_FN
CHR_voip_pair_set_no_of_timing_records(
  CHR_VOIP_PAIR_HANDLE pairHandle,
  CHR_COUNT no_of_tr);

CHR_API_RC CHR_API_FN
CHR_voip_pair_set_use_PLC(
  CHR_VOIP_PAIR_HANDLE pairHandle,
  CHR_BOOLEAN use);

CHR_API_RC CHR_API_FN
CHR_voip_pair_set_use_silence_sup(
  CHR_VOIP_PAIR_HANDLE pairHandle,
  CHR_BOOLEAN use);

CHR_API_RC CHR_API_FN
CHR_voip_pair_set_voice_activ_rate(
  CHR_VOIP_PAIR_HANDLE pairHandle,
  CHR_COUNT rate);

CHR_API_RC CHR_API_FN
CHR_voip_pair_set_payload_file(
  CHR_VOIP_PAIR_HANDLE  pairHandle,
  CHR_STRING            filename,
  CHR_LENGTH            filenameLength,
  CHR_BOOLEAN           embedded);

CHR_API_RC CHR_API_FN
CHR_voip_pair_set_payload_random(
  CHR_VOIP_PAIR_HANDLE  pairHandle);


/*----------------------------------------------------------------------*/
/*                  Video Unicast Pair functions                        */
/*                    (CHR_VIDEO_PAIR_HANDLE)                           */
/*----------------------------------------------------------------------*/

CHR_API_RC CHR_API_FN
CHR_video_pair_new(
  CHR_VIDEO_PAIR_HANDLE* pairHandle);

CHR_API_RC CHR_API_FN
CHR_video_pair_get_codec(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_VIDEO_CODEC *codec);

CHR_API_RC CHR_API_FN
CHR_video_pair_set_codec(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_VIDEO_CODEC codec);

CHR_API_RC CHR_API_FN
CHR_video_pair_get_dest_port_num(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_PORT *port);

CHR_API_RC CHR_API_FN
CHR_video_pair_set_dest_port_num(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_PORT port);

CHR_API_RC CHR_API_FN
CHR_video_pair_get_initial_delay(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_STRING delay,
  CHR_LENGTH len,
  CHR_LENGTH *rtnlen);

CHR_API_RC CHR_API_FN
CHR_video_pair_set_initial_delay(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_STRING delay,
  CHR_LENGTH len);

CHR_API_RC CHR_API_FN
CHR_video_pair_get_source_port_num(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_PORT *port);

CHR_API_RC CHR_API_FN
CHR_video_pair_set_source_port_num(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_PORT port);

CHR_API_RC CHR_API_FN
CHR_video_pair_get_tr_duration(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_COUNT *seconds);

CHR_API_RC CHR_API_FN
CHR_video_pair_set_tr_duration(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_COUNT seconds);

CHR_API_RC CHR_API_FN
CHR_video_pair_get_no_of_timing_records(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_COUNT *no_of_tr);

CHR_API_RC CHR_API_FN
CHR_video_pair_set_no_of_timing_records(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_COUNT no_of_tr);

CHR_API_RC CHR_API_FN
CHR_video_pair_get_frames_per_datagram(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_COUNT *frames);

CHR_API_RC CHR_API_FN
CHR_video_pair_set_frames_per_datagram(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_COUNT frames);

CHR_API_RC CHR_API_FN
CHR_video_pair_get_bitrate(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_FLOAT *bitrate,
  CHR_THROUGHPUT_UNITS *rate_um);

CHR_API_RC CHR_API_FN
CHR_video_pair_set_bitrate(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_FLOAT bitrate,
  CHR_THROUGHPUT_UNITS rate_um);

CHR_API_RC CHR_API_FN
CHR_video_pair_get_rtp_payload_type(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_BYTE *rtp_payload_type);

CHR_API_RC CHR_API_FN
CHR_video_pair_set_rtp_payload_type(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_BYTE rtp_payload_type);

CHR_API_RC CHR_API_FN
CHR_video_pair_get_media_frame_size(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_COUNT *media_frame_size);

CHR_API_RC CHR_API_FN
CHR_video_pair_set_media_frame_size(
  CHR_VIDEO_PAIR_HANDLE pairHandle,
  CHR_COUNT media_frame_size);

/*----------------------------------------------------------------------*/
/*                  Video Multicast Group functions                     */
/*                     (CHR_VIDEO_MGROUP_HANDLE)                        */
/*----------------------------------------------------------------------*/

CHR_API_RC CHR_API_FN
CHR_video_mgroup_new(
  CHR_VIDEO_MGROUP_HANDLE* mgroupHandle);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_get_codec(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_VIDEO_CODEC *codec);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_set_codec(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_VIDEO_CODEC codec);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_get_initial_delay(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_STRING delay,
  CHR_LENGTH len,
  CHR_LENGTH *rtnlen);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_set_initial_delay(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_STRING delay,
  CHR_LENGTH len);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_get_source_port_num(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_PORT *port);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_set_source_port_num(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_PORT port);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_get_tr_duration(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_COUNT *seconds);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_set_tr_duration(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_COUNT seconds);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_get_no_of_timing_records(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_COUNT *no_of_tr);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_set_no_of_timing_records(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_COUNT no_of_tr);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_get_frames_per_datagram(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_COUNT *frames);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_set_frames_per_datagram(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_COUNT frames);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_get_bitrate(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_FLOAT *bitrate,
  CHR_THROUGHPUT_UNITS *rate_um);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_set_bitrate(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_FLOAT bitrate,
  CHR_THROUGHPUT_UNITS rate_um);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_get_rtp_payload_type(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_BYTE *rtp_payload_type);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_set_rtp_payload_type(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_BYTE rtp_payload_type);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_get_media_frame_size(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_COUNT *media_frame_size);

CHR_API_RC CHR_API_FN
CHR_video_mgroup_set_media_frame_size(
  CHR_VIDEO_MGROUP_HANDLE mgroupHandle,
  CHR_COUNT media_frame_size);


/*----------------------------------------------------------------------*/
/*                  Hardware Performance Pair functions                 */
/*                      (CHR_HARDWARE_PAIR_HANDLE)                      */
/*----------------------------------------------------------------------*/

CHR_API_RC CHR_API_FN 
CHR_hardware_pair_new(
  CHR_HARDWARE_PAIR_HANDLE* pairHandle);

CHR_API_RC CHR_API_FN
CHR_hardware_pair_set_line_rate(
  CHR_HARDWARE_PAIR_HANDLE pairHandle,
  CHR_FLOAT line_rate);

CHR_API_RC CHR_API_FN
CHR_hardware_pair_get_override_line_rate(
  CHR_HARDWARE_PAIR_HANDLE pairHandle,
  CHR_BOOLEAN *override_line_rate);

CHR_API_RC CHR_API_FN
CHR_hardware_pair_set_override_line_rate(
  CHR_HARDWARE_PAIR_HANDLE pairHandle,
  CHR_BOOLEAN override_line_rate);

CHR_API_RC CHR_API_FN
CHR_hardware_pair_get_line_rate(
  CHR_HARDWARE_PAIR_HANDLE pairHandle,
  CHR_FLOAT *line_rate);

CHR_API_RC CHR_API_FN
CHR_hardware_pair_set_measure_statistics(
  CHR_HARDWARE_PAIR_HANDLE pairHandle,
  CHR_MEASURE_STATS measure_statistics);

CHR_API_RC CHR_API_FN
CHR_hardware_pair_get_measure_statistics(
  CHR_HARDWARE_PAIR_HANDLE pairHandle,
  CHR_MEASURE_STATS *measure_statistics);


/*----------------------------------------------------------------------*/
/*                  VoIP Hardware Performance Pair functions            */
/*                        (CHR_HARDWARE_PAIR_HANDLE)                    */
/*----------------------------------------------------------------------*/

CHR_API_RC CHR_API_FN 
CHR_hardware_voip_pair_new(
  CHR_HARDWARE_PAIR_HANDLE* pairHandle);

CHR_API_RC CHR_API_FN
CHR_hardware_voip_pair_set_concurrent_voice_streams(
  CHR_HARDWARE_PAIR_HANDLE pairHandle,
  int concurrent_voice_streams);

CHR_API_RC CHR_API_FN
CHR_hardware_voip_pair_get_concurrent_voice_streams(
  CHR_HARDWARE_PAIR_HANDLE pairHandle, 
  int* concurrent_voice_streams);


/*----------------------------------------------------------------------*/
/*                  Application Group functions                         */
/*                    (CHR_APP_GROUP_HANDLE)                            */
/*----------------------------------------------------------------------*/

CHR_API_RC CHR_API_FN
CHR_app_group_new(
    CHR_APP_GROUP_HANDLE*           appGroupHandle);

CHR_API_RC CHR_API_FN
CHR_app_group_set_filename(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_STRING                      filename,
    CHR_LENGTH                      filenameLength);

CHR_API_RC CHR_API_FN
CHR_app_group_get_filename(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_STRING                      buffer,
    CHR_LENGTH                      bufferLength,
    CHR_LENGTH*                     retLength);

CHR_API_RC CHR_API_FN
CHR_app_group_copy(
    CHR_APP_GROUP_HANDLE            toAppGroupHandle,
    CHR_APP_GROUP_HANDLE            fromAppGroupHandle);

CHR_API_RC CHR_API_FN
CHR_app_group_delete(
    CHR_APP_GROUP_HANDLE            appGroupHandle);

CHR_API_RC CHR_API_FN
CHR_app_group_save(
    CHR_APP_GROUP_HANDLE            appGroupHandle);

CHR_API_RC CHR_API_FN
CHR_app_group_force_delete(
    CHR_APP_GROUP_HANDLE            appGroupHandle);

CHR_API_RC CHR_API_FN
CHR_app_group_set_name(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_STRING                      name,
    CHR_LENGTH                      length);

CHR_API_RC CHR_API_FN
CHR_app_group_get_name(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_STRING                      name,
    CHR_LENGTH                      maxLength,
    CHR_LENGTH*                     length);

CHR_API_RC CHR_API_FN
CHR_app_group_set_comment(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_STRING                      comment,
    CHR_LENGTH                      length);

CHR_API_RC CHR_API_FN
CHR_app_group_get_comment(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_STRING                      comment,
    CHR_LENGTH                      maxLength,
    CHR_LENGTH*                     length);

CHR_API_RC CHR_API_FN
CHR_app_group_add_pair(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_PAIR_HANDLE                 pairHandle);

CHR_API_RC CHR_API_FN
CHR_app_group_remove_pair(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_PAIR_HANDLE                 pairHandle);

CHR_API_RC CHR_API_FN
CHR_app_group_get_pair_count(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_COUNT*                      pairCount);

CHR_API_RC CHR_API_FN
CHR_app_group_get_pair(
  CHR_APP_GROUP_HANDLE appGroupHandle,
  CHR_COUNT index,
  CHR_PAIR_HANDLE* pairHandle);

CHR_API_RC CHR_API_FN
CHR_app_group_add_event(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_STRING                      eventName,
    CHR_LENGTH                      eventNameLength,
    CHR_STRING                      eventComment,
    CHR_LENGTH                      eventCommentLength);

CHR_API_RC CHR_API_FN
CHR_app_group_remove_event(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_STRING                      eventName,
    CHR_LENGTH                      eventNameLength);

CHR_API_RC CHR_API_FN
CHR_app_group_get_event_count(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_COUNT*                      eventCount);

CHR_API_RC CHR_API_FN
CHR_app_group_get_event(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_COUNT                       index,
    CHR_STRING                      eventName,
    CHR_LENGTH                      eventNameMaxLength,
    CHR_LENGTH*                     eventNameLength,
    CHR_STRING                      eventComment,
    CHR_LENGTH                      eventCommentMaxLength,
    CHR_LENGTH*                     eventCommentLength);

CHR_API_RC CHR_API_FN
CHR_app_group_set_pair_protocol(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_COUNT                       pairIndex,
    CHR_PROTOCOL                    protocol);

CHR_API_RC CHR_API_FN
CHR_app_group_get_pair_protocol(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_COUNT                       pairIndex,
    CHR_PROTOCOL*                   protocol);

CHR_API_RC CHR_API_FN
CHR_app_group_set_pair_management_protocol(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_COUNT                       pairIndex,
    CHR_PROTOCOL                    protocol);

CHR_API_RC CHR_API_FN
CHR_app_group_get_pair_management_protocol(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_COUNT                       pairIndex,
    CHR_PROTOCOL*                   protocol);

CHR_API_RC CHR_API_FN
CHR_app_group_set_pair_qos_name(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_COUNT                       pairIndex,
    CHR_STRING                      qosName,
    CHR_LENGTH                      qosNameLength);

CHR_API_RC CHR_API_FN
CHR_app_group_get_pair_qos_name(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_COUNT                       pairIndex,
    CHR_STRING                      qosName,
    CHR_LENGTH                      maxLength,
    CHR_LENGTH*                     length);

CHR_API_RC CHR_API_FN
CHR_app_group_get_address_count(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_COUNT*                      addressCount);

CHR_API_RC CHR_API_FN
CHR_app_group_set_address(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_COUNT                       addressIndex,
    CHR_STRING                      address,
    CHR_LENGTH                      addressLength);

CHR_API_RC CHR_API_FN
CHR_app_group_get_address(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_COUNT                       addressIndex,
    CHR_STRING                      address,
    CHR_LENGTH                      maxLength,
    CHR_LENGTH*                     length);

CHR_API_RC CHR_API_FN
CHR_app_group_get_management_address_count(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_COUNT*                      addressCount);

CHR_API_RC CHR_API_FN
CHR_app_group_set_management_address(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_COUNT                       addressIndex,
    CHR_STRING                      address,
    CHR_LENGTH                      addressLength);

CHR_API_RC CHR_API_FN
CHR_app_group_get_management_address(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_COUNT                       addressIndex,
    CHR_STRING                      address,
    CHR_LENGTH                      maxLength,
    CHR_LENGTH*                     length);

CHR_API_RC CHR_API_FN
CHR_app_group_set_lock(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_BOOLEAN                     lock);

CHR_API_RC CHR_API_FN
CHR_app_group_get_lock(
    CHR_APP_GROUP_HANDLE            appGroupHandle,
    CHR_BOOLEAN*                    lock);

CHR_API_RC CHR_API_FN
CHR_app_group_is_disabled(
  CHR_APP_GROUP_HANDLE              appGroupHandle,
  CHR_BOOLEAN*                      disabled);

CHR_API_RC CHR_API_FN
CHR_app_group_disable(
  CHR_APP_GROUP_HANDLE              appGroupHandle,
  CHR_BOOLEAN                       disable);

CHR_API_RC CHR_API_FN
CHR_app_group_validate(
    CHR_APP_GROUP_HANDLE            appGroupHandle);


/*----------------------------------------------------------------------*/
/*                  IPTV Channel Object functions                       */
/*                      (CHR_CHANNEL_HANDLE)                            */
/*----------------------------------------------------------------------*/

/**
 * Deletes the specified IPTV channel object.
 * 
 * @param i_channelHandle   Channel Object handle.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_OBJECT_IN_USE
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_delete(
    CHR_CHANNEL_HANDLE      i_channelHandle);

/**
 * Gets the bit rate value and unit of measurement defined for the given
 * channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_bitrate         Transmission bit rate.
 * @param o_units           Unit of measurement in which the
 *                          transmission rate is expressed.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_bitrate(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_FLOAT*              o_bitrate,
    CHR_THROUGHPUT_UNITS*   o_units);

/**
 * Returns the codec type defined for the specified IPTV channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_videoCodec      Video codec type (MPEG2 or CUSTOM).
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_codec(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_VIDEO_CODEC*        o_videoCodec);

/**
 * Returns the comment string for the specified channel object.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_comment         Character buffer to receive the comment.
 * @param i_maxLength       Size of the return buffer.
 * @param o_length          Actual number of bytes returned.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_BUFFER_TOO_SMALL
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_comment(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_STRING              o_comment,
    CHR_LENGTH              i_maxLength,
    CHR_LENGTH*             o_length);

/**
 * Returns the send buffer size to be specified in the CONNECT. 
 *  
 * @param i_channelHandle   Channel Object handle.
 * @param o_bufferSize      Send buffer size.
 * 
 * @return Chariot API return code. 
 * - CHR_OK 
 * - CHR_HANDLE_INVALID 
 * - CHR_POINTER_INVALID 
 *  
 * @since IxChariot 6.50 
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_conn_send_buff_size(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_COUNT*              o_bufferSize);

/**
 * Returns the IP address of Endpoint 1 on the management network.
 * This is the address the console will use to perform pair setup.
 * 
 * This parameter will only be used if the use_e1_e2_values attribute is
 * false.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_mgmtAddr        Character buffer to receive the address.
 * @param i_maxLength       Size of the IP address buffer.
 * @param o_length          Actual number of bytes returned.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_BUFFER_TOO_SMALL
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_console_e1_addr(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_STRING              o_mgmtAddr,
    CHR_LENGTH              i_maxLength,
    CHR_LENGTH*             o_length);

/**
 * Returns the network protocol the console will use when connecting to
 * Endpoint 1 to perform pair setup.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_protocol        Management network protocol.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_console_e1_protocol(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_PROTOCOL*           o_protocol);

/**
 * Returns the IP address of Endpoint 1 on the test network.
 * The channel will use this as the source IP address of the multicast.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_address         Buffer to receive IP address.
 * @param i_maxLength       Size of the return buffer.
 * @param o_length          Actual number of bytes returned.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_BUFFER_TOO_SMALL
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_e1_addr(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_STRING              o_address,
    CHR_LENGTH              i_maxLength,
    CHR_LENGTH*             o_length);

/**
 * Returns the number of media frames per datagram defined for the
 * specified IPTV channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_frames          Number of media frames per datagram.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_frames_per_datagram(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_COUNT*              o_frames);

/**
 * Gets the media frame size defined for the given IPTV channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_frameSize       The media frame size.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_media_frame_size(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_COUNT*              o_frameSize);

/**
 * Returns the multicast IP address of the IPTV channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_multicastAddr   Buffer to receive the multicast address.
 * @param i_maxLength       Size of the result buffer.
 * @param o_length          Number of bytes stored in result buffer.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_BUFFER_TOO_SMALL
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_multicast_addr(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_STRING              o_multicastAddr,
    CHR_LENGTH              i_maxLength,
    CHR_LENGTH*             o_length);

/**
 * Returns the multicast port number of the IPTV channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_multicastPort   Multicast port number.
 * 
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_multicast_port(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_PORT*               o_multicastPort);

/**
 * Returns the name assigned to the specified IPTV channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_name            Buffer to receive the channel name.
 * @param i_maxLength       Size of the result buffer.
 * @param o_length          Number of bytes stored in result buffer.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_BUFFER_TOO_SMALL
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_name(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_STRING              o_name,
    CHR_LENGTH              i_maxLength,
    CHR_LENGTH*             o_length);

/**
 * Returns the test protocol of the IPTV channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_protocol        Protocol type.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_protocol(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_PROTOCOL*           o_protocol);

/**
 * Returns the quality-of-service template name for the channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_qosName         Buffer to receive the qos name.
 * @param i_maxLength       Size of the result buffer.
 * @param o_length          Number of bytes stored in result buffer.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_BUFFER_TOO_SMALL
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_qos_name(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_STRING              o_qosName,
    CHR_LENGTH              i_maxLength,
    CHR_LENGTH*             o_length);

/**
 * Returns the RTP payload type defined for the given IPTV channel. This
 * function will only be successful if the code type is set to CUSTOM
 * and the protocol is set to RTP or RTP6. Otherwise, the function
 * returns CHR_NO_SUCH_VALUE.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_payloadType     RTP payload type.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_rtp_payload_type(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_BYTE*               o_payloadType);

/**
 * Gets the UDP source port number for the specified IPTV channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_sourcePort      UDP source port number.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_source_port_num(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_PORT*               o_sourcePort);

/**
 * Indicates whether the console will use the management network or the
 * test network to perform pair setup.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_useValues       CHR_TRUE if the console will use
 *                          the management network; CHR_FALSE if it
 *                          will use the test network.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_use_console_e1_values(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_BOOLEAN*            o_useValues);

/**
 * Creates a new IPTV channel object and initializes it to the default
 * values.
 * 
 * The handle returned by this function is needed for other function
 * calls to operate on the channel object.
 * 
 * @param o_channelHandle   Channel Object handle.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_LICENSE_HAS_EXPIRED
 * - CHR_NO_MEMORY
 * - CHR_NOT_LICENSED
 * - CHR_POINTER_INVALID
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_new(
    CHR_CHANNEL_HANDLE*     o_channelHandle);

/**
 * Specifies the bit rate value and unit of measurement for the given
 * IPTV channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_bitrate         Transmission rate of channel.
 * @param i_units           Units in which transmission rate is
 *                          specified.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_PGM_INTERNAL_ERROR
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_bitrate(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_FLOAT               i_bitrate,
    CHR_THROUGHPUT_UNITS    i_units);

/**
 * Specifies the type of codec for the IPTV channel object.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_videoCodec      Codec type.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_codec(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_VIDEO_CODEC         i_videoCodec);

/**
 * Specifies the comment string for the channel object.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_comment         Comment string to be assigned to channel.
 * @param i_length          Length of comment string.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_POINTER_INVALID
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_comment(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_CONST_STRING        i_comment,
    CHR_LENGTH              i_length);

/**
 * Specifies the send buffer size to be specified in the CONNECT. 
 *  
 * @param i_channelHandle   Channel Object handle.
 * @param i_bufferSize      Send buffer size.
 * 
 * @return Chariot API return code. 
 * - CHR_OK 
 * - CHR_HANDLE_INVALID 
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_conn_send_buff_size(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_COUNT               i_bufferSize);

/**
 * Specifies the IP address on the management network that the console
 * uses to connect to Endpoint 1 during test setup.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_mgmtAddr        Management address of Endpoint 1.
 * @param i_length          Length of management address.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_POINTER_INVALID
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_console_e1_addr(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_CONST_STRING        i_mgmtAddr,
    CHR_LENGTH              i_length);

/**
 * Specifies the network protocol the console will use when connecting
 * to Endpoint 1 to perform pair setup.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_protocol        Management network protocol.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_console_e1_protocol(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_PROTOCOL            i_protocol);

/**
 * Specifies the IP address of Endpoint 1 on the test network. Will be
 * used as the source IP address for the multicast.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_address         Source IP address of channel.
 * @param i_length          Length of IP address.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_POINTER_INVALID
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_e1_addr(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_CONST_STRING        i_address,
    CHR_LENGTH              i_length);

/**
 * Specifies the number of media frames per datagram for the channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_frames          Media frames per datagram.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_frames_per_datagram(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_COUNT               i_frames);

/**
 * Specifies the media frame size used for the channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_frameSize       Media frame size.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_media_frame_size(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_COUNT               i_frameSize);

/**
 * Specifies the multicast IP address on which traffic will be
 * transmitted.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_multicastAddr   Multicast address.
 * @param i_length          Length of multicast address.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_POINTER_INVALID
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_multicast_addr(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_CONST_STRING        i_multicastAddr,
    CHR_LENGTH              i_length);

/**
 * Specifies the source port number on which multicast traffic will be
 * transmitted.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_multicastPort   Multicast port number.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_multicast_port(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_PORT                i_multicastPort);

/**
 * Specifies the name of the channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_name            Name to be assigned to channel object.
 * @param i_length          Length of channel name.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_POINTER_INVALID
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_name(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_CONST_STRING        i_name,
    CHR_LENGTH              i_length);

/**
 * Specifies the test protocol of the IPTV channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_protocol        Protocol type.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_protocol(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_PROTOCOL            i_protocol);

/**
 * Specifies the quality-of-service template for the channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_qosName         QoS template name.
 * @param i_length          Length of QoS template name.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_POINTER_INVALID
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_qos_name(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_CONST_STRING        i_qosName,
    CHR_LENGTH              i_length);

/**
 * Specifies the RTP payload type for the given channel. This function
 * will only succeed if the codec type is set to CUSTOM and the protocol
 * is set to RTP or RTP6. Otherwise, the function returns
 * CHR_VALUE_INVALID.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_payloadType     RTP payload type.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_rtp_payload_type(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_BYTE                i_payloadType);

/**
 * Specifies the UDP source port for the IPTV channel.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_sourcePort      UDP source port number.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_source_port_num(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_PORT                i_sourcePort);

/**
 * Specifies whether to use the management network (true) or the
 * test network (false) for pair setup.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_useValues       CHR_TRUE to use the management network; CHR_FALSE
 *                          to use the test network.
 * 
 * @return Chariot API return code.
 * - CHR_OK
 * - CHR_HANDLE_INVALID
 * - CHR_NOT_SUPPORTED
 * - CHR_OBJECT_IN_USE
 * - CHR_RESULTS_NOT_CLEARED
 * - CHR_TEST_RUNNING
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_use_console_e1_values(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_BOOLEAN             i_useValues);

/**
 * Specifies whether the channel object is locked.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param o_useValues       CHR_TRUE for locked; CHR_FALSE for
 *                          unlocked.
 * 
 * @since IxChariot 6.70
 */
CHR_API_RC CHR_API_FN
CHR_channel_get_lock(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_BOOLEAN*            o_useValues);

/**
 * Specifies whether to lock or not the channel object. Locking
 * allows editing a channel owned by a test.
 * 
 * @param i_channelHandle   Channel Object handle.
 * @param i_useValues       CHR_TRUE to lock; CHR_FALSE to
 *                          unlock.
 * 
 * @since IxChariot 6.70
 */
CHR_API_RC CHR_API_FN
CHR_channel_set_lock(
    CHR_CHANNEL_HANDLE      i_channelHandle,
    CHR_BOOLEAN             i_useValues);

/*----------------------------------------------------------------------*/
/*                  IPTV Receiver Object functions                      */
/*                      (CHR_RECEIVER_HANDLE)                           */
/*----------------------------------------------------------------------*/

/**
 * Adds an IPTV pair to the list for this receiver.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param i_pairHandle      IPTV pair to be added to receiver.
 * 
 * @return Chariot API return code.
 */
CHR_API_RC CHR_API_FN
CHR_receiver_add_vpair(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_VPAIR_HANDLE        i_pairHandle);

/**
 * Removes an IPTV pair from the list for this receiver.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param i_pairHandle      IPTV pair to be removed.
 * 
 * @return Chariot API return code.
 */
CHR_API_RC CHR_API_FN
CHR_receiver_remove_vpair(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_VPAIR_HANDLE        i_pairHandle);

/**
 * Deletes the specified IPTV receiver object.
 * 
 * @param i_receiverHandle  Handle of receiver object to be deleted.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_delete(
    CHR_RECEIVER_HANDLE     i_receiverHandle);

/**
 * Returns the comment string for the specified receiver object.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param o_comment         Buffer to receive the comment string.
 * @param i_maxLength       Size of the return buffer.
 * @param o_length          Actual number of bytes returned.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_get_comment(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_STRING              o_comment,
    CHR_LENGTH              i_maxLength,
    CHR_LENGTH*             o_length);

/**
 * Returns the receive buffer size to be specified in the CONNECT. 
 *  
 * @param i_receiverHandle  Handle of receiver object.
 * @param o_bufferSize      Receiver buffer size.
 * 
 * @return Chariot API return code. 
 *  
 * @since IxChariot 6.50 
 */
CHR_API_RC CHR_API_FN
CHR_receiver_get_conn_recv_buff_size(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_COUNT*              o_bufferSize);

/**
 * Returns the IP address of the receiver on the test network.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param o_address         Buffer to receive the IP address.
 * @param i_maxLength       Size of the return buffer.
 * @param o_length          Actual number of bytes returned.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_get_e2_addr(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_STRING              o_address,
    CHR_LENGTH              i_maxLength,
    CHR_LENGTH*             o_length);

/**
 * Returns the name assigned to the receiver object.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param o_name            Buffer to receive the receiver name.
 * @param i_maxLength       Size of the return buffer.
 * @param o_length          Actual number of bytes returned.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_get_name(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_STRING              o_name,
    CHR_LENGTH              i_maxLength,
    CHR_LENGTH*             o_length);


/**
 * Returns the number of times the JOIN/LEAVE loop will be repeated.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param o_iterations      JOIN/LEAVE repeat count.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_get_no_of_iterations(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_COUNT*              o_iterations);

/**
 * Returns the specified IPTV pair object from the list of pairs
 * assigned to this receiver.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param i_pairIndex       Index of the desired entry in the pair list,
 *                          in the range 0..pair_count-1.
 * @param o_pairHandle      Handle of the IPTV pair object.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_get_vpair(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_COUNT               i_pairIndex,
    CHR_VPAIR_HANDLE*       o_pairHandle);

/**
 * Returns the number of pairs that have been assigned to this receiver.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param o_pairCount       Number of entries in the pair list.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_get_vpair_count(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_COUNT*              o_pairCount);

/**
 * Returns the management IP address of the receiver.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param o_address         Buffer to receive the IP address.
 * @param i_maxLength       Size of the return buffer.
 * @param o_length          Actual number of bytes returned.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_get_setup_e1_e2_addr(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_STRING              o_address,
    CHR_LENGTH              i_maxLength,
    CHR_LENGTH*             o_length);

/**
 * Returns the channel switch delay (the interval between a LEAVE and
 * the next JOIN).
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param o_switchDelay     Channel switch delay, in milliseconds.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_get_switch_delay(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_COUNT*              o_switchDelay);

/**
 * Indicates whether IxChariot will use the management network or the 
 * test network when setting up the test.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param o_useValues       CHR_TRUE if IxChariot will use the
 *                          management network; CHR_FALSE if it will
 *                          perform pair setup over the test
 *                          network.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_get_use_e1_e2_values(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_BOOLEAN*            o_useValues);

CHR_API_RC CHR_API_FN
CHR_receiver_is_disabled(
  CHR_RECEIVER_HANDLE       i_receiverHandle,
  CHR_BOOLEAN*              o_disabled);

/**
 * Creates a new IPTV receiver object and initializes it to the default
 * values.
 * 
 * The handle returned by this function is needed for other function
 * calls to operate on the receiver object.
 * 
 * @param o_receiverHandle  Handle of receiver object.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_new(
    CHR_RECEIVER_HANDLE*    o_receiverHandle);

/**
 * Specifies the comment string for the receiver object.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param i_comment         Comment string to be assigned to receiver.
 * @param i_length          Length of comment string.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_set_comment(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_CONST_STRING        i_comment,
    CHR_LENGTH              i_length);

/**
 * Specifies the receive buffer size to be used in the CONNECT. 
 *  
 * @param i_receiverHandle  Handle of receiver object.
 * @param i_bufferSize      Receiver buffer size.
 * 
 * @return Chaript API return code. 
 *  
 * @since IxChariot 6.50 
 */
CHR_API_RC CHR_API_FN
CHR_receiver_set_conn_recv_buff_size(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_COUNT               i_bufferSize);

/**
 * Specifies the IP address of the receiver on the test network.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param i_address         IP address to be assigned to receiver.
 * @param i_length          Length of IP address.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_set_e2_addr(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_CONST_STRING        i_address,
    CHR_LENGTH              i_length);

/**
 * Specifies the name of the receiver object.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param i_name            Name to be assigned to receiver.
 * @param i_length          Length of name string.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_set_name(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_CONST_STRING        i_name,
    CHR_LENGTH              i_length);

/**
 * Specifies the number of times the JOIN/LEAVE loop is to be repeated.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param i_iterations      Number of JOINs/LEAVEs to perform.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_set_no_of_iterations(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_COUNT               i_iterations);

/**
 * Specifies the IP address of the receiver on the management network.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param i_address         Management IP address.
 * @param i_length          Length of management IP address.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_set_setup_e1_e2_addr(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_CONST_STRING        i_address,
    CHR_LENGTH              i_length);

/**
 * Specifies the channel switch delay (the interval between a LEAVE and
 * the next JOIN).
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param i_switchDelay     Channel switch delay, in milliseconds.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_set_switch_delay(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_COUNT               i_switchDelay);

/**
 * Specifies whether IxChariot should use the management network
 * (true) or the test network (false) for pair setup.
 * 
 * @param i_receiverHandle  Handle of receiver object.
 * @param i_useValues       CHR_TRUE to use the management network;
 *                          CHR_FALSE to use the test network.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_receiver_set_use_e1_e2_values(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_BOOLEAN             i_useValues);

CHR_API_RC CHR_API_FN
CHR_receiver_disable(
  CHR_RECEIVER_HANDLE       i_receiverHandle,
  CHR_BOOLEAN               i_disable);


/*----------------------------------------------------------------------*/
/*                      Report Object functions                         */
/*                        (CHR_REPORT_HANDLE)                           */
/*----------------------------------------------------------------------*/

/**
 * Returns the type of the specified report item.
 * 
 * @param i_reportHandle    Report handle.
 * @param o_reportItem      Report item type.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_report_get_item_type(
    CHR_REPORT_HANDLE       i_reportHandle,
    CHR_REPORT_ITEM*        o_reportItem);

/**
 * Returns the join latency field from the specified report.
 * 
 * @param i_reportHandle    Report handle.
 * @param o_joinLatency     Join latency, in milliseconds.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_report_get_join_latency(
    CHR_REPORT_HANDLE       i_reportHandle,
    CHR_FLOAT*              o_joinLatency);

/**
 * Returns the leave latency field from the specified report.
 * 
 * @param i_reportHandle    Report handle.
 * @param o_leaveLatency    Leave latency, in milliseconds.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_report_get_leave_latency(
    CHR_REPORT_HANDLE       i_reportHandle,
    CHR_FLOAT*              o_leaveLatency);

/**
 * Returns the report group identifier from the specified report.
 * 
 * @param i_reportHandle    Report handle.
 * @param o_reportGroupId   Report group identifier.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_report_get_report_group_id(
    CHR_REPORT_HANDLE       i_reportHandle,
    CHR_COUNT*              o_reportGroupId);

/**
 * Specifies whether the receiver object is locked.
 * 
 * @param i_receiverHandle  Receiver Object handle.
 * @param o_useValues       CHR_TRUE for locked; CHR_FALSE for
 *                          unlocked.
 * 
 * @since IxChariot 6.70
 */
CHR_API_RC CHR_API_FN
CHR_receiver_get_lock(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_BOOLEAN*            o_useValues);

/**
 * Specifies whether to lock or not the receiver object. Locking
 * allows editing a receiver owned by a test.
 * 
 * @param i_receiverHandle  Receiver Object handle.
 * @param i_useValues       CHR_TRUE to lock; CHR_FALSE to
 *                          unlock.
 * 
 * @since IxChariot 6.70
 */
CHR_API_RC CHR_API_FN
CHR_receiver_set_lock(
    CHR_RECEIVER_HANDLE     i_receiverHandle,
    CHR_BOOLEAN             i_useValues);


/*----------------------------------------------------------------------*/
/*                  IPTV Test Object functions                          */
/*                      (CHR_TEST_HANDLE)                               */
/*----------------------------------------------------------------------*/

/**
 * Adds a channel object to the test.
 * 
 * @param i_testHandle      Test Object handle.
 * @param i_channelHandle   Handle of the Channel Object to be added to
 *                          the configuration.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_test_add_channel(
    CHR_TEST_HANDLE         i_testHandle,
    CHR_CHANNEL_HANDLE      i_channelHandle);

/**
 * Removes a channel object from the test.
 * 
 * @param i_testHandle      Test Object handle.
 * @param i_channelHandle   Handle of the Channel Object to be
 *                          removed.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.70
 */
CHR_API_RC CHR_API_FN
CHR_test_remove_channel(
    CHR_TEST_HANDLE         i_testHandle,
    CHR_CHANNEL_HANDLE      i_channelHandle);

/**
 * Adds a receiver object to the test.
 * 
 * @param i_testHandle      Test Object handle.
 * @param i_receiverHandle  Handle of the Receiver object to be added to
 *                          the configuration.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_test_add_receiver(
    CHR_TEST_HANDLE         i_testHandle,
    CHR_RECEIVER_HANDLE     i_receiverHandle);

/**
 * Removes a receiver object from the test.
 * 
 * @param i_testHandle      Test Object handle.
 * @param i_receiverHandle  Handle of the Receiver object to be
 *                          removed
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.70
 */
CHR_API_RC CHR_API_FN
CHR_test_remove_receiver(
    CHR_TEST_HANDLE         i_testHandle,
    CHR_RECEIVER_HANDLE     i_receiverHandle);

/**
 * Gets the specified channel object from the test.
 * 
 * @param i_testHandle      Test Object handle.
 * @param i_listIndex       Index of the item in the list of channel
 *                          objects, in the range 0..channel_count-1.
 * @param o_channelHandle   Handle of the requested channel object.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_test_get_channel(
    CHR_TEST_HANDLE         i_testHandle,
    CHR_COUNT               i_listIndex,
    CHR_CHANNEL_HANDLE*     o_channelHandle);

/**
 * Returns the channel object with the specified name.
 * 
 * @param i_testHandle      Test Object handle.
 * @param i_channelName     String specifying the name of the channel.
 * @param i_nameLength      Length of the channel name string.
 * @param o_channelHandle   Handle of the requested channel object.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_test_get_channel_by_name(
    CHR_TEST_HANDLE         i_testHandle,
    CHR_CONST_STRING        i_channelName,
    CHR_LENGTH              i_nameLength,
    CHR_CHANNEL_HANDLE*     o_channelHandle);

/**
 * Returns the number of channel objects in the test.
 * 
 * @param i_testHandle      Test Object handle.
 * @param o_channelCount    The channel object count.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_test_get_channel_count(
    CHR_TEST_HANDLE         i_testHandle,
    CHR_COUNT*              o_channelCount);

/**
 * Gets the specified receiver object from the test.
 * 
 * @param i_testHandle      Test Object handle.
 * @param i_listIndex       Index of the object in the receive list, in
 *                          the range 0..receiver_count-1.
 * @param o_receiverHandle  Handle of the requested receiver object.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_test_get_receiver(
    CHR_TEST_HANDLE         i_testHandle,
    CHR_COUNT               i_listIndex,
    CHR_RECEIVER_HANDLE*    o_receiverHandle);

/**
 * Returns the receiver object with the specified name.
 * 
 * @param i_testHandle      Test Object handle.
 * @param i_receiverName    String specifying the name of the receiver.
 * @param i_nameLength      Length of the receiver name string.
 * @param o_receiverHandle  Handle of the requested receiver object.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_test_get_receiver_by_name(
    CHR_TEST_HANDLE         i_testHandle,
    CHR_CONST_STRING        i_receiverName,
    CHR_LENGTH              i_nameLength,
    CHR_RECEIVER_HANDLE*    o_receiverHandle);

/**
 * Returns the number of receiver objects in the test.
 * 
 * @param i_testHandle      Test Object handle.
 * @param o_receiverCount   The receiver object count.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_test_get_receiver_count(
    CHR_TEST_HANDLE         i_testHandle,
    CHR_COUNT*              o_receiverCount);


/*----------------------------------------------------------------------*/
/*                  IPTV Pair object functions                          */
/*                      (CHR_VPAIR_HANDLE)                              */
/*----------------------------------------------------------------------*/

/**
 * Deletes the specified IPTV pair object.
 * 
 * @param i_pairHandle      Pair handle.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_vpair_delete(
    CHR_VPAIR_HANDLE        i_pairHandle);

/**
 * Returns the channel with which this pair is associated.
 * 
 * @param i_pairHandle      Pair handle.
 * @param o_channelHandle   Channel handle.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_vpair_get_channel(
    CHR_VPAIR_HANDLE        i_pairHandle,
    CHR_CHANNEL_HANDLE*     o_channelHandle);

/**
 * Returns the number of timing records the pair should generate.
 * 
 * @param i_pairHandle      Pair handle.
 * @param o_count           Number of timing records.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_vpair_get_no_of_timing_records(
    CHR_VPAIR_HANDLE        i_pairHandle,
    CHR_COUNT*              o_count);

/**
 * Returns the specified report for this pair.
 * 
 * @param i_pairHandle      Pair handle.
 * @param i_reportIndex     Index of the requested report (zero-based).
 * @param o_reportHandle    Report handle.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_vpair_get_report(
    CHR_VPAIR_HANDLE        i_pairHandle,
    CHR_COUNT               i_reportIndex,
    CHR_REPORT_HANDLE*      o_reportHandle);

/**
 * Returns the number of reports collected for this pair.
 * 
 * @param i_pairHandle      Pair handle.
 * @param o_reportCount     Number of reports collected.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_vpair_get_report_count(
    CHR_VPAIR_HANDLE        i_pairHandle,
    CHR_COUNT*              o_reportCount);

/**
 * Returns the specified timing record for this pair.
 * 
 * @param i_pairHandle      Pair handle.
 * @param i_recordIndex     Index of the requested timing record.
 * @param o_recordHandle    Timing record handle.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_vpair_get_timing_record(
    CHR_VPAIR_HANDLE        i_pairHandle,
    CHR_COUNT               i_recordIndex,
    CHR_TIMINGREC_HANDLE*   o_recordHandle);

/**
 * Returns the number of timing records collected for this pair.
 * 
 * @param i_pairHandle      Pair handle.
 * @param o_recordCount     Number of timing records collected.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_vpair_get_timing_record_count(
    CHR_VPAIR_HANDLE        i_pairHandle,
    CHR_COUNT*              o_recordCount);

/**
 * Returns the timing record duration, in seconds.
 * 
 * @param i_pairHandle      Pair handle.
 * @param o_duration        Timing record duration, in seconds.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_vpair_get_tr_duration(
    CHR_VPAIR_HANDLE        i_pairHandle,
    CHR_COUNT*              o_duration);

/**
 * Creates a new IPTV pair object.
 * 
 * @param o_pairHandle      Pair handle.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_vpair_new(
    CHR_VPAIR_HANDLE*       o_pairHandle);

/**
 * Specifies the number of timing records the pair should generate.
 * 
 * @param i_pairHandle      Pair handle.
 * @param i_count           Timing record count.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_vpair_set_no_of_timing_records(
    CHR_VPAIR_HANDLE        i_pairHandle,
    CHR_COUNT               i_count);

/**
 * Specifies the channel with which this pair is associated.
 * 
 * @param i_pairHandle      Pair handle.
 * @param i_channelHandle   Channel handle.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_vpair_set_channel(
    CHR_VPAIR_HANDLE        i_pairHandle,
    CHR_CHANNEL_HANDLE      i_channelHandle);

/**
 * Specifies the timing record duration, in seconds.
 * 
 * @param i_pairHandle      Pair handle.
 * @param i_duration        Timing record duration, in seconds.
 * 
 * @return Chariot API return code.
 * 
 * @since IxChariot 6.50
 */
CHR_API_RC CHR_API_FN
CHR_vpair_set_tr_duration(
    CHR_VPAIR_HANDLE        i_pairHandle,
    CHR_COUNT               i_duration);

/**
 * Returns the runstatus of the specified pair
 * 
 * @param i_pairHandle      Pair handle.
 * @param runStatus         Runstatus to be filled in.
 * 
 * @return Chariot API return code.
 */
CHR_API_RC CHR_API_FN
CHR_vpair_get_runStatus(
    CHR_VPAIR_HANDLE        i_pairHandle, 
    CHR_PAIR_RUNSTATUS_TYPE *runStatus);

/**
 * Specifies whether the pair object is locked.
 * 
 * @param i_pairHandle      Pair Object handle.
 * @param o_useValues       CHR_TRUE for locked; CHR_FALSE for
 *                          unlocked.
 * 
 * @since IxChariot 6.70
 */
CHR_API_RC CHR_API_FN
CHR_vpair_get_lock(
    CHR_VPAIR_HANDLE        i_pairHandle,
    CHR_BOOLEAN*            o_useValues);

/**
 * Specifies whether to lock or not the pair object. Locking
 * allows editing a pair owned by a test.
 * 
 * @param i_pairHandle      Pair Object handle.
 * @param i_useValues       CHR_TRUE to lock; CHR_FALSE to
 *                          unlock.
 * 
 * @since IxChariot 6.70
 */
CHR_API_RC CHR_API_FN
CHR_vpair_set_lock(
    CHR_VPAIR_HANDLE        i_pairHandle,
    CHR_BOOLEAN             i_useValues);


/*----------------------------------------------------------------------*/
/*                  end of C definitions                                */
/*----------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif  /* !CHRAPI_H_INCLUDED */
