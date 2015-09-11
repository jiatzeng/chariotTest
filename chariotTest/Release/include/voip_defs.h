/**
 * \file        voip_defs.h
 * \brief       Base VoIP definitions.
 * 
 * This include file contains the constants, typedefs and base
 * definitions for application programming for VoIP functionality.
 * 
 * Copyright (c) 2004-2006 Ixia. All rights reserved.
 */

/***************************************************************
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
 ***************************************************************/

#ifndef __voip_defs_h__
#define __voip_defs_h__

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Definition of a unique signature, characterizing an ASD of type VoIP.
 * Used when instantiating ASD objects.
 */
#define IX_VOIP_ASD_TYPE_UUID "eef7b8d5-d249-45e5-8179-b4cf1d0605e8"


/**
 * ASD subtypes that are handled by ASE VoIP.
 * 
 * When adding new types, be sure to updated IX_VOIP_ASD_TYPE_COUNT below.
 */
#define IX_VOIP_ASD_TYPE_VOIP 0

#define IX_VOIP_ASD_TYPE_COUNT 1


/*
 * VoIP Codecs
 * These are guaranteed to be contiguous in value.
 */
typedef char IX_VOIP_CODEC;
#define IX_VOIP_CODEC_NONE      1
#define IX_VOIP_CODEC_G711u     2
#define IX_VOIP_CODEC_G723_1A   3
#define IX_VOIP_CODEC_G723_1M   4
#define IX_VOIP_CODEC_G729      5
#define IX_VOIP_CODEC_G711a     6
#define IX_VOIP_CODEC_G726      7

/* 
 * Map the first and last codec, trust they are
 * contiguous and use the definitions below for
 * index arithmetic.
 * BEGIN is the start of the codec list, inclusive
 * END   is the end of the codec list, exclusive
 *       END points to the first invalid position
 *       after the last codec.
 */
#define IX_VOIP_CODEC_BEGIN  IX_VOIP_CODEC_G711u
#define IX_VOIP_CODEC_END   (IX_VOIP_CODEC_G726+1)
#define IX_VOIP_CODEC_COUNT (IX_VOIP_CODEC_END-IX_VOIP_CODEC_BEGIN)


/*
 * Max and min permittable values for VoIP parameters.
 */

#define IX_VOIP_IPV4 4
#define IX_VOIP_IPV6 6

#define IX_VOIP_IP_ADDRESS_LENGTH 40 /* IPv6: FEDC:BA98:7654:3210:FEDC:BA98:7654:3210 */

#define IX_VOIP_INTER_DATAGRAM_GAP_MIN       1
#define IX_VOIP_INTER_DATAGRAM_GAP_DEFAULT  10
#define IX_VOIP_INTER_DATAGRAM_GAP_MAX     200

#define IX_VOIP_CONCURRENT_VOICE_STREAM_MIN           1
#define IX_VOIP_CONCURRENT_VOICE_STREAM_DEFAULT      10
#define IX_VOIP_CONCURRENT_VOICE_STREAM_MAX     INT_MAX

#define IX_VOIP_SRC_PORT_MIN            1
#define IX_VOIP_SRC_PORT_DEFAULT     1024
#define IX_VOIP_SRC_PORT_MAX        65535


#define IX_VOIP_DST_PORT_MIN            1
#define IX_VOIP_DST_PORT_DEFAULT    16384
#define IX_VOIP_DST_PORT_MAX        65535

#define DELAY_MINIMUM (10)
#define DELAY_MAXIMUM (200)
#define ACTIVITY_RATE_MINIMUM (1)
#define ACTIVITY_RATE_MAXIMUM (100)
#define INITIAL_DELAY_MINIMUM (0)
#define INITIAL_DELAY_MAXIMUM (999999999)
#define ADDITIONAL_DELAY_MINIMUM (0)
#define ADDITIONAL_DELAY_MAXIMUM (300)
#define TR_DURATION_MINIMUM (1)
#define TR_DURATION_MAXIMUM (3600)
#define PORT_MINIMUM (1)
#define PORT_MAXIMUM (65535)
#define JITTER_BUFFER_MILLISECONDS_MINIMUM (10)
#define JITTER_BUFFER_MILLISECONDS_MAXIMUM (1600)
#define JITTER_BUFFER_DATAGRAMS_MINIMUM (1)
#define JITTER_BUFFER_DATAGRAMS_MAXIMUM (8)
#define FRAMES_PER_DG_MINIMUM (1)
#define FRAMES_PER_DG_MAXIMUM (10000)
#define VARIABLE_RATE_MAX   4294967295
#define RTP_PAYLOAD_MINIMUM   (0)
#define RTP_PAYLOAD_MAXIMUM   (127)

#ifdef __cplusplus
}
#endif

#endif /* __voip_defs_h__ */
