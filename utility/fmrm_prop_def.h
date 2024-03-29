#ifndef __FMRM_PROP_DEF_H__
#define __FMRM_PROP_DEF_H__

/*
 *  Includes ------------------------------------------------------------------
 */

/*
 *  Definitions ---------------------------------------------------------------
 */

//==================================================================
// General Properties
//==================================================================

// GPO_IEN
#define GPO_IEN				 0x0001
#define GPO_IEN_STCIEN_MASK  0x0001
#define GPO_IEN_ASQIEN_MASK  0x0002
#define GPO_IEN_RDSIEN_MASK  0x0004
#define GPO_IEN_SAMEIEN_MASK 0x0004
#define GPO_IEN_RSQIEN_MASK  0x0008
#define GPO_IEN_ERRIEN_MASK  0x0040
#define GPO_IEN_CTSIEN_MASK  0x0080
#define GPO_IEN_STCREP_MASK  0x0100
#define GPO_IEN_ASQREP_MASK  0x0200
#define GPO_IEN_RDSREP_MASK  0x0400
#define GPO_IEN_RSQREP_MASK  0x0800
#define GPO_IEN_STCIEN_SHFT  0
#define GPO_IEN_ASQIEN_SHFT  1
#define GPO_IEN_RDSIEN_SHFT  2
#define GPO_IEN_SAMEIEN_SHFT 2
#define GPO_IEN_RSQIEN_SHFT  3
#define GPO_IEN_ERRIEN_SHFT  6
#define GPO_IEN_CTSIEN_SHFT  7
#define GPO_IEN_STCREP_SHFT  8
#define GPO_IEN_ASQREP_SHFT  9
#define GPO_IEN_RDSREP_SHFT  10
#define GPO_IEN_RSQREP_SHFT  11

// DIGITAL_OUTPUT_FORMAT
#define DIGITAL_OUTPUT_FORMAT            0x0102
#define DIGITAL_OUTPUT_FORMAT_OSIZE_MASK 0x0003
#define DIGITAL_OUTPUT_FORMAT_OMONO_MASK 0x0004
#define DIGITAL_OUTPUT_FORMAT_OMODE_MASK 0x0078
#define DIGITAL_OUTPUT_FORMAT_OFALL_MASK 0x0080
#define DIGITAL_OUTPUT_FORMAT_OSIZE_SHFT 0
#define DIGITAL_OUTPUT_FORMAT_OMONO_SHFT 2
#define DIGITAL_OUTPUT_FORMAT_OMODE_SHFT 3
#define DIGITAL_OUTPUT_FORMAT_OFALL_SHFT 7

// DIGITAL_OUTPUT_SAMPLE_RATE
#define DIGITAL_OUTPUT_SAMPLE_RATE 0x0104

// REFCLK_FREQ
#define REFCLK_FREQ 0x0201

// REFCLK_PRESCALE
#define REFCLK_PRESCALE      0x0202
#define REFCLK_PRESCALE_MASK 0x0FFF
#define REFCLK_PRESCALE_SHFT 0

//==================================================================
// FM Receive Properties
//==================================================================

// FM_DEEMPHASIS
#define FM_DEEMPHASIS      0x1100
#define FM_DEEMPHASIS_MASK 0x0003
#define FM_DEEMPHASIS_SHFT 0

// FM_CHANNEL_FILTER
#define FM_CHANNEL_FILTER      0x1102
#define FM_CHANNEL_FILTER_MASK 0x0003 //todo
#define FM_CHANNEL_FILTER_SHFT 0//todo

// FM_BLEND_STEREO_THRESHOLD
#define FM_BLEND_STEREO_THRESHOLD      0x1105
#define FM_BLEND_STEREO_THRESHOLD_MASK 0x007F
#define FM_BLEND_STEREO_THRESHOLD_SHFT 0

// FM_BLEND_MONO_THRESHOLD
#define FM_BLEND_MONO_THRESHOLD      0x1106
#define FM_BLEND_MONO_THRESHOLD_MASK 0x007F
#define FM_BLEND_MONO_THRESHOLD_SHFT 0

// FM_ANTENNA_INPUT
#define FM_ANTENNA_INPUT      0x1107
#define FM_ANTENNA_INPUT_MASK 0x0001
#define FM_ANTENNA_INPUT_SHFT 0

// FM_MAX_TUNE_ERROR
#define FM_MAX_TUNE_ERROR      0x1108
#define FM_MAX_TUNE_ERROR_MASK 0x007F
#define FM_MAX_TUNE_ERROR_SHFT 0

// FM_RSQ_INT_SOURCE
#define FM_RSQ_INT_SOURCE               0x1200
#define FM_RSQ_INT_SOURCE_RSSILIEN_MASK 0x0001
#define FM_RSQ_INT_SOURCE_RSSIHIEN_MASK 0x0002
#define FM_RSQ_INT_SOURCE_ASNRLIEN_MASK 0x0004
#define FM_RSQ_INT_SOURCE_ASNRHIEN_MASK 0x0008
#define FM_RSQ_INT_SOURCE_BLENDIEN_MASK 0x0080
#define FM_RSQ_INT_SOURCE_RSSILIEN_SHFT 0
#define FM_RSQ_INT_SOURCE_RSSIHIEN_SHFT 1
#define FM_RSQ_INT_SOURCE_ASNRLIEN_SHFT 2
#define FM_RSQ_INT_SOURCE_ASNRHIEN_SHFT 3
#define FM_RSQ_INT_SOURCE_BLENDIEN_SHFT 7

// FM_RSQ_SNR_HI_THRESHOLD
#define FM_RSQ_SNR_HI_THRESHOLD      0x1201
#define FM_RSQ_SNR_HI_THRESHOLD_MASK 0x007F
#define FM_RSQ_SNR_HI_THRESHOLD_SHFT 0

// FM_RSQ_SNR_LO_THRESHOLD
#define FM_RSQ_SNR_LO_THRESHOLD      0x1202
#define FM_RSQ_SNR_LO_THRESHOLD_MASK 0x007F
#define FM_RSQ_SNR_LO_THRESHOLD_SHFT 0

// FM_RSQ_RSSI_HI_THRESHOLD
#define FM_RSQ_RSSI_HI_THRESHOLD      0x1203
#define FM_RSQ_RSSI_HI_THRESHOLD_MASK 0x007F
#define FM_RSQ_RSSI_HI_THRESHOLD_SHFT 0

// FM_RSQ_RSSI_LO_THRESHOLD
#define FM_RSQ_RSSI_LO_THRESHOLD      0x1204
#define FM_RSQ_RSSI_LO_THRESHOLD_MASK 0x007F
#define FM_RSQ_RSSI_LO_THRESHOLD_SHFT 0

// FM_RSQ_MULTIPATH_HI_THRESHOLD
#define FM_RSQ_MULTIPATH_HI_THRESHOLD      0x1205
#define FM_RSQ_MULTIPATH_HI_THRESHOLD_MASK 0x007F //todo
#define FM_RSQ_MULTIPATH_HI_THRESHOLD_SHFT 0

// FM_RSQ_MULTIPATH_LO_THRESHOLD
#define FM_RSQ_MULTIPATH_LO_THRESHOLD      0x1206
#define FM_RSQ_MULTIPATH_LO_THRESHOLD_MASK 0x007F //todo
#define FM_RSQ_MULTIPATH_LO_THRESHOLD_SHFT 0

// FM_RSQ_BLEND_THRESHOLD
#define FM_RSQ_BLEND_THRESHOLD            0x1207
#define FM_RSQ_BLEND_THRESHOLD_BLEND_MASK 0x007F
#define FM_RSQ_BLEND_THRESHOLD_PILOT_MASK 0x0080
#define FM_RSQ_BLEND_THRESHOLD_BLEND_SHFT 0
#define FM_RSQ_BLEND_THRESHOLD_PILOT_SHFT 7

// FM_SOFT_MUTE_RATE
#define FM_SOFT_MUTE_RATE      0x1300
#define FM_SOFT_MUTE_RATE_MASK 0x00FF
#define FM_SOFT_MUTE_RATE_SHFT 0

// FM_SOFT_MUTE_SLOPE
#define FM_SOFT_MUTE_SLOPE      0x1301
#define FM_SOFT_MUTE_SLOPE_MASK 0x00FF//todo
#define FM_SOFT_MUTE_SLOPE_SHFT 0

// FM_SOFT_MUTE_MAX_ATTENUATION
#define FM_SOFT_MUTE_MAX_ATTENUATION      0x1302
#define FM_SOFT_MUTE_MAX_ATTENUATION_MASK 0x001F
#define FM_SOFT_MUTE_MAX_ATTENUATION_SHFT 0

// FM_SOFT_MUTE_SNR_THRESHOLD
#define FM_SOFT_MUTE_SNR_THRESHOLD      0x1303
#define FM_SOFT_MUTE_SNR_THRESHOLD_MASK 0x000F
#define FM_SOFT_MUTE_SNR_THRESHOLD_SHFT 0

// FM_SEEK_BAND_BOTTOM
#define FM_SEEK_BAND_BOTTOM 0x1400

// FM_SEEK_BAND_TOP
#define FM_SEEK_BAND_TOP 0x1401

// FM_SEEK_FREQ_SPACING
#define FM_SEEK_FREQ_SPACING      0x1402
#define FM_SEEK_FREQ_SPACING_MASK 0x001F
#define FM_SEEK_FREQ_SPACING_SHFT 0

// FM_SEEK_TUNE_SNR_THRESHOLD
#define FM_SEEK_TUNE_SNR_THRESHOLD      0x1403
#define FM_SEEK_TUNE_SNR_THRESHOLD_MASK 0x007F
#define FM_SEEK_TUNE_SNR_THRESHOLD_SHFT 0

// FM_SEEK_TUNE_RSSI_THRESHOLD
#define FM_SEEK_TUNE_RSSI_THRESHOLD      0x1404
#define FM_SEEK_TUNE_RSSI_THRESHOLD_MASK 0x007F
#define FM_SEEK_TUNE_RSSI_THRESHOLD_SHFT 0

// FM_RDS_INTERRUPT_SOURCE
#define FM_RDS_INTERRUPT_SOURCE                0x1500
#define FM_RDS_INTERRUPT_SOURCE_RECV_MASK      0x0001
#define FM_RDS_INTERRUPT_SOURCE_SYNCLOST_MASK  0x0002
#define FM_RDS_INTERRUPT_SOURCE_SYNCFOUND_MASK 0x0004
#define FM_RDS_INTERRUPT_SOURCE_RECV_SHFT      0
#define FM_RDS_INTERRUPT_SOURCE_SYNCLOST_SHFT  1
#define FM_RDS_INTERRUPT_SOURCE_SYNCFOUND_SHFT 2

// FM_RDS_INTERRUPT_FIFO_COUNT
#define FM_RDS_INTERRUPT_FIFO_COUNT      0x1501
#define FM_RDS_INTERRUPT_FIFO_COUNT_MASK 0x00FF
#define FM_RDS_INTERRUPT_FIFO_COUNT_SHFT 0

// FM_RDS_CONFIG
#define FM_RDS_CONFIG             0x1502
#define FM_RDS_CONFIG_RDSEN_MASK  0x0001
#define FM_RDS_CONFIG_BLETHD_MASK 0x0300
#define FM_RDS_CONFIG_BLETHC_MASK 0x0C00
#define FM_RDS_CONFIG_BLETHB_MASK 0x3000
#define FM_RDS_CONFIG_BLETHA_MASK 0xC000
#define FM_RDS_CONFIG_RDSEN_SHFT  0
#define FM_RDS_CONFIG_BLETHD_SHFT 8
#define FM_RDS_CONFIG_BLETHC_SHFT 10
#define FM_RDS_CONFIG_BLETHB_SHFT 12
#define FM_RDS_CONFIG_BLETHA_SHFT 14
// FM_RDS_CONFIDENCE
#define FM_RDS_CONFIDENCE             0x1503

// FM_BLEND_RSSI_STEREO_THRESHOLD
#define FM_BLEND_RSSI_STEREO_THRESHOLD      0x1800
#define FM_BLEND_RSSI_STEREO_THRESHOLD_MASK 0x007F
#define FM_BLEND_RSSI_STEREO_THRESHOLD_SHFT 0

// FM_BLEND_RSSI_MONO_THRESHOLD
#define FM_BLEND_RSSI_MONO_THRESHOLD      0x1801
#define FM_BLEND_RSSI_MONO_THRESHOLD_MASK 0x007F
#define FM_BLEND_RSSI_MONO_THRESHOLD_SHFT 0

// FM_BLEND_RSSI_ATTACK_RATE
#define FM_BLEND_RSSI_ATTACK_RATE      0x1802

// FM_BLEND_RSSI_RELEASE_RATE
#define FM_BLEND_RSSI_RELEASE_RATE      0x1803

// FM_BLEND_SNR_STEREO_THRESHOLD
#define FM_BLEND_SNR_STEREO_THRESHOLD      0x1804
#define FM_BLEND_SNR_STEREO_THRESHOLD_MASK 0x007F
#define FM_BLEND_SNR_STEREO_THRESHOLD_SHFT 0

// FM_BLEND_SNR_MONO_THRESHOLD
#define FM_BLEND_SNR_MONO_THRESHOLD      0x1805
#define FM_BLEND_SNR_MONO_THRESHOLD_MASK 0x007F
#define FM_BLEND_SNR_MONO_THRESHOLD_SHFT 0

// FM_BLEND_SNR_ATTACK_RATE
#define FM_BLEND_SNR_ATTACK_RATE      0x1806

// FM_BLEND_SNR_RELEASE_RATE
#define FM_BLEND_SNR_RELEASE_RATE      0x1807

// FM_BLEND_MULTIPATH_STEREO_THRESHOLD
#define FM_BLEND_MULTIPATH_STEREO_THRESHOLD      0x1808
#define FM_BLEND_MULTIPATH_STEREO_THRESHOLD_MASK 0x007F
#define FM_BLEND_MULTIPATH_STEREO_THRESHOLD_SHFT 0

// FM_BLEND_MULTIPATH_MONO_THRESHOLD
#define FM_BLEND_MULTIPATH_MONO_THRESHOLD      0x1809
#define FM_BLEND_MULTIPATH_MONO_THRESHOLD_MASK 0x007F
#define FM_BLEND_MULTIPATH_MONO_THRESHOLD_SHFT 0

// FM_BLEND_MULTIPATH_ATTACK_RATE
#define FM_BLEND_MULTIPATH_ATTACK_RATE      0x180A

// FM_BLEND_MULTIPATH_RELEASE_RATE
#define FM_BLEND_MULTIPATH_RELEASE_RATE      0x180B
//==================================================================
// General Receive Properties
//==================================================================

// RX_VOLUME
#define RX_VOLUME      0x4000
#define RX_VOLUME_MASK 0x003F
#define RX_VOLUME_SHFT 0

// RX_HARD_MUTE
#define RX_HARD_MUTE 0x4001
#define RX_HARD_MUTE_RMUTE_MASK 0x0001
#define RX_HARD_MUTE_LMUTE_MASK 0x0002
#define RX_HARD_MUTE_RMUTE_SHFT 0
#define RX_HARD_MUTE_LMUTE_SHFT 1

//==================================================================
// Bit Definitions for Properties
//==================================================================

// DIGITAL_MODE - used for input or output
#define DIGITAL_MODE_I2S    0x0
#define DIGITAL_MODE_LEFT   0x6
#define DIGITAL_MODE_MSB1ST 0xC
#define DIGITAL_MODE_MSB2ND 0x8

// DIGITAL_SIZE - used for input or output
#define DIGITAL_SIZE_16 0x0
#define DIGITAL_SIZE_20 0x1
#define DIGITAL_SIZE_24 0x2
#define DIGITAL_SIZE_8  0x3

// FM_DEEMPH
#define FM_DEEMPH_75US 0x2
#define FM_DEEMPH_50US 0x1

// FM_ANTENNA_INPUT
#define FM_ANTENNA_FMI 0x0
#define FM_ANTENNA_TXO_LPI 0x1
// FM_RDS_BLETH - used for all block error thresholds
#define FM_RDS_BLETH_NO_ERRORS     0x0
#define FM_RDS_BLETH_1OR2_ERRORS   0x1
#define FM_RDS_BLETH_3TO5_ERRORS   0x2
#define FM_RDS_BLETH_UNCORRECTABLE 0x3

#endif /* __FMRM_PROP_DEF_H__ */