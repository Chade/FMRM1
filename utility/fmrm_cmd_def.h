#ifndef __FMRM_CMD_DEF_H__
#define __FMRM_CMD_DEF_H__

/*
 *  Includes ------------------------------------------------------------------
 */

/*
 *  Definitions ---------------------------------------------------------------
 */

//==================================================================
// General Commands
//==================================================================

// STATUS bits
#define STCINT  0x01
#define RDSINT  0x04
#define RSQINT  0x08
#define ERR     0x40
#define CTS     0x80

// POWER_UP
#define POWER_UP                        0x01
#define POWER_UP_IN_FUNC_FMRX           0x00
#define POWER_UP_IN_FUNC_QUERY          0x0F
#define POWER_UP_IN_XOSCEN              0x10
#define POWER_UP_IN_PATCH               0x20
#define POWER_UP_IN_GPO2OEN             0x40
#define POWER_UP_IN_CTSIEN              0x80
#define POWER_UP_IN_OPMODE_RX_ANALOG    0x05
#define POWER_UP_IN_OPMODE_RX_DIGITAL   0x0B  //DCLK, LOUT/DFS, ROUT/DIO with XOSCEN = 0
#define POWER_UP_IN_OPMODE_RX_DIGITAL2  0xB0  //DCLK, DFS, DIO with XOSCEN = 0

// GET_REV
#define GET_REV 0x10

// POWER_DOWN
#define POWER_DOWN 0x11

// SET_PROPERTY
#define SET_PROPERTY 0x12

// GET_PROPERTY
#define GET_PROPERTY 0x13

// GET_INT_STATUS
#define GET_INT_STATUS 0x14

//==================================================================
// FM Receive Commands
//==================================================================

// FM_TUNE_FREQ
#define FM_TUNE_FREQ 0x20

// FM_SEEK_START
#define FM_SEEK_START           0x21
#define FM_SEEK_START_IN_WRAP   0x04
#define FM_SEEK_START_IN_SEEKUP 0x08

// FM_TUNE_STATUS
#define FM_TUNE_STATUS           0x22
#define FM_TUNE_STATUS_IN_INTACK 0x01
#define FM_TUNE_STATUS_IN_CANCEL 0x02
#define FM_TUNE_STATUS_OUT_VALID 0x01
#define FM_TUNE_STATUS_OUT_AFCRL 0x02
#define FM_TUNE_STATUS_OUT_BTLF  0x80

// FM_RSQ_STATUS
#define FM_RSQ_STATUS              0x23
#define FM_RSQ_STATUS_IN_INTACK    0x01
#define FM_RSQ_STATUS_OUT_RSSILINT 0x01
#define FM_RSQ_STATUS_OUT_RSSIHINT 0x02
#define FM_RSQ_STATUS_OUT_ASNRLINT 0x04
#define FM_RSQ_STATUS_OUT_ASNRHINT 0x08
#define FM_RSQ_STATUS_OUT_BLENDINT 0x80
#define FM_RSQ_STATUS_OUT_VALID    0x01
#define FM_RSQ_STATUS_OUT_AFCRL    0x02
#define FM_RSQ_STATUS_OUT_SMUTE    0x08
#define FM_RSQ_STATUS_OUT_PILOT    0x80
#define FM_RSQ_STATUS_OUT_STBLEND  0x7F

// FM_RDS_STATUS
#define FM_RDS_STATUS               0x24
#define FM_RDS_STATUS_IN_INTACK     0x01
#define FM_RDS_STATUS_IN_MTFIFO     0x02
#define FM_RDS_STATUS_OUT_RECV      0x01
#define FM_RDS_STATUS_OUT_SYNCLOST  0x02
#define FM_RDS_STATUS_OUT_SYNCFOUND 0x04
#define FM_RDS_STATUS_OUT_SYNC      0x01
#define FM_RDS_STATUS_OUT_GRPLOST   0x04
#define FM_RDS_STATUS_OUT_BLED      0x03
#define FM_RDS_STATUS_OUT_BLEC      0x0C
#define FM_RDS_STATUS_OUT_BLEB      0x30
#define FM_RDS_STATUS_OUT_BLEA      0xC0
#define FM_RDS_STATUS_OUT_BLED_SHFT 0
#define FM_RDS_STATUS_OUT_BLEC_SHFT 2
#define FM_RDS_STATUS_OUT_BLEB_SHFT 4
#define FM_RDS_STATUS_OUT_BLEA_SHFT 6

#endif /* __FMRM_CMD_DEF_H__ */