#include "Arduino.h"
#include <Wire.h>
#include "FMRM1.h"

/**********************************************************
private Definitionen
**********************************************************/
#define FMRM_ADDR  (0xC6 >> 1)

/**********************************************************
Konstruktor
**********************************************************/
FMRM1::FMRM1()
{}

/**********************************************************
öffentliche Methoden
**********************************************************/

/*---------------------------------------------------------
Name:           FMRM_init

Beschreibung:   initialisiert das FM-RM1-Modul

Eingänge:       resetPin

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_init(int resetPin)
{
  _resetPin = resetPin;
  pinMode(_resetPin, OUTPUT);
  FMRM_PUT_IN_RESET;
  delay(100);
  FMRM_RELEASE_FROM_RESET;
  delay(500);
  FMRM_power_up();
  delay(100);
  FMRM_config();
  FMRM_frequency_set(8750);
  delay(100);
  FMRM_tune_status_get();
  timeout = 1000;
}
/*---------------------------------------------------------
Name:           FMRM_init

Beschreibung:   initialisiert das FM-RM1-Modul

Eingänge:       void

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_init()
{
  delay(100);
  FMRM_power_up();
  delay(100);
  FMRM_config();
  FMRM_frequency_set(8750);
  delay(100);
  FMRM_tune_status_get();
  timeout = 1000;
}
/*---------------------------------------------------------
Name:           FMRM_power_up

Beschreibung:   FMRM Power Up Routine für FMRM

Eingänge:       void

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_power_up()
{
  uint8_t cmd[8];
  //Powerup
  cmd[0] = POWER_UP;
  cmd[1] = POWER_UP_IN_XOSCEN|POWER_UP_IN_GPO2OEN;//|POWER_UP_IN_CTSIEN;
  cmd[2] = POWER_UP_IN_OPMODE_RX_ANALOG;
  FMRM_send(cmd, 3, 8);
}
/*---------------------------------------------------------
Name:           FMRM_power_down

Beschreibung:   FMRM Power Down Routine für FMRM

Eingänge:       void

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_power_down()
{
  uint8_t cmd[1];
  cmd[0] = POWER_DOWN;
  FMRM_send(cmd, 1, 1);
}

/*---------------------------------------------------------
Name:           FMRM_config

Beschreibung:   FMRM Konfiguration für Europa

Eingänge:       void

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_config()
{
  //Disable Debug
  //FMRM_send_property(0xFF00,0x0000);

//  //Disable soft mute
//  FMRM_send_property(FM_SOFT_MUTE_MAX_ATTENUATION,0x0000);

  //Antenna input
  //Bit 0
  //Use FMI pin for headphone (long) antenna
  //Use TXO/LPI pin for embedded (short) antenna
  FMRM_send_property(FM_ANTENNA_INPUT,FM_ANTENNA_TXO_LPI);

  // FM De-Emphasis.
  //75 µs. Used in USA
  //50 µs. Used in Europe, Australia, Japan
  FMRM_send_property(FM_DEEMPHASIS,FM_DEEMPH_50US);

  // FM Frequency-Spacing
  // 100 kHz Used in Europe
  FMRM_send_property(FM_SEEK_FREQ_SPACING, 10);
}
/*---------------------------------------------------------
Name:           FMRM_get_revision

Beschreibung:   FMRM Revision ausgeben

Eingänge:       void

Ausgang:        uint16_t revision
---------------------------------------------------------*/
uint16_t FMRM1::FMRM_get_revision()
{
  uint8_t cmd[9];
  uint8_t status ;
  uint8_t partnumber;
  uint8_t rev_major;
  uint8_t rev_minor;
  uint8_t patch_msb;
  uint8_t patch_lsb;
  uint8_t firmware_major;
  uint8_t firmware_minor;
  uint8_t chip_rev;

  cmd[0] = GET_REV;
  FMRM_send(cmd, 1, 9);

  status = cmd[0];
  partnumber = cmd[1];
  rev_major = cmd[2];
  rev_minor = cmd[3];
  patch_msb = cmd[4];
  patch_lsb = cmd[5];
  firmware_major = cmd[6];
  firmware_minor = cmd[7];
  chip_rev = cmd[8];
  return ((uint16_t)(cmd[2]<<8|cmd[3]));
}
/*---------------------------------------------------------
Name:           FMRM_seek

Beschreibung:   Suche für nächsten gültigen Sender

Eingänge:       uint8_t direction

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_seek(uint8_t direction)
{
  uint16_t u16_startfrequency = u16_frequency;
  uint8_t cmd[2];
  static uint16_t frequencys[20];
  static uint8_t valid[20];
  static uint8_t rssi[20];
  static uint8_t snr[20];
  static uint8_t i=0;
  do
  {
    cmd[0] = FM_SEEK_START;
    if (direction)
    {
        cmd[1] = FM_SEEK_START_IN_WRAP|FM_SEEK_START_IN_SEEKUP;
    }
    else
    {
        cmd[1] = FM_SEEK_START_IN_WRAP;
    }
    FMRM_send(cmd, 2, 1);
    delay(500);
    FMRM_tune_status_get();
    frequencys[i]=u16_frequency;
    valid[i] =b_valid;
    rssi[i]=u8_rssi;
    snr[i]=u8_snr;
    i++;
  }while(b_valid == 0 && b_bandlimit == 0 && u16_startfrequency != u16_frequency);
}
/*---------------------------------------------------------
Name:           FMRM_seek_manual

Beschreibung:   Suche für nächsten gültigen Sender
                manueller Durchlauf der Frequenzen

Eingänge:       uint8_t direction

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_seek_manual(uint8_t direction)
{
  uint16_t u16_startfrequency = u16_frequency;
  uint16_t u16_tempfrequency = u16_frequency;
  FMRM_audio_mute(1);

  do
  {
    if( direction )
    {
      if( (u16_tempfrequency + 10) <= 10800 )
      {
        u16_tempfrequency += 10;
      }
      else
      {
        u16_tempfrequency = 8750;
      }
    }
    else
    {
      if( (u16_tempfrequency - 10) >= 8750 )
      {
        u16_tempfrequency -= 10;
      }
      else
      {
        u16_tempfrequency = 10800;
      }
    }
    FMRM_frequency_set(u16_tempfrequency);
    delay(50);
    FMRM_rsq_status_get();
  }while( (b_valid == 0) && (u16_startfrequency != u16_tempfrequency) );
  delay(500);
  FMRM_tune_status_get();
  FMRM_audio_mute(0);
}
/*---------------------------------------------------------
Name:           FMRM_frequenzcy_set

Beschreibung:   Senderfrequenz manuell setzen

Eingänge:       uint16_t freq

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_frequency_set(uint16_t freq)
{
  uint8_t cmd[5];
  cmd[0] = 0x20;
  cmd[1] = 0x00;
  cmd[2] = (freq>>8)&0xff;
  cmd[3] = (freq)&0xff;
  cmd[4] = 0x00;
  FMRM_send(cmd, 5, 1);
}
/*---------------------------------------------------------
Name:           FMRM_frequenzcy_get

Beschreibung:   Senderfrequenz abfragen

Eingänge:       void

Ausgang:        uint16_t freq
---------------------------------------------------------*/
uint16_t FMRM1::FMRM_frequency_get()
{
    FMRM_tune_status_get();
    return u16_frequency;
}
/*---------------------------------------------------------
Name:           FMRM_tune_status_get

Beschreibung:   Empfänger Status abfragen

Eingänge:       void

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_tune_status_get()
{
  uint8_t cmd[8];
  cmd[0] = 0x22;
  cmd[1] = 0x03;

  FMRM_send(cmd, 2, 8);

  b_valid 			= (cmd[1]&0x01);
  b_afc 				= (cmd[1]&0x02);
  b_bandlimit 	= (cmd[1]&0x80);
  u16_frequency = (cmd[2]<<8)|cmd[3];
  u8_rssi 			= cmd[4];
  u8_snr 				= cmd[5];
  u8_multipath 	= cmd[6];
  u8_antennacap = cmd[7];

}
/*---------------------------------------------------------
Name:           FMRM_volume_set

Beschreibung:   Lautstärke einstellen

Eingänge:       uint8_t volume (0 - 63)

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_volume_set(uint8_t volume)
{
  // Turn off the mute
  //FMRM_send_property(RX_HARD_MUTE, 0);

  // Set the volume to the passed value
  FMRM_send_property(RX_VOLUME, (uint16_t)volume & RX_VOLUME_MASK);
}
/*---------------------------------------------------------
Name:           FMRM_volume_get

Beschreibung:   Lautstärke abfragen

Eingänge:       void

Ausgang:        uint8_t volume (0 - 63)
---------------------------------------------------------*/
uint8_t FMRM1::FMRM_volume_get()
{
  uint8_t cmd[4];
  cmd[0] = 0x13;
  cmd[1] = 0x00;
  cmd[2] = 0x40;
  cmd[3] = 0x00;
  FMRM_send(cmd, 4, 4);
  u8_volume = cmd[3];
  return u8_volume;
}
/*---------------------------------------------------------
Name:           FMRM_audio_mute

Beschreibung:   Mute Audio-Output

Eingänge:       void

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_audio_mute(uint8_t OnOff)
{
  //Set GPIO1 State
  uint8_t cmd[2];
  cmd[0] = 0x81;
  if(OnOff != 0)
  {
    cmd[1] = 0x02; //high
  }
  else
  {
    cmd[1] = 0x00; //low
  }
  FMRM_send(cmd, 2, 1);
  //Set GPIO1 as Output
    cmd[0] = 0x80;
    cmd[1] = 0x02;
  FMRM_send(cmd, 2, 1);
}
/*---------------------------------------------------------
Name:           FMRM_antenna_select

Beschreibung:   Antenneneingang auswählen

Eingänge:       0: FMI; 1: LPI

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_antenna_select(uint8_t antenna)
{
  //Antenna input
  //Bit 0
  //Use FMI pin for headphone (long) antenna
  //Use TXO/LPI pin for embedded (short) antenna
  if(antenna)
  {
    FMRM_send_property(FM_ANTENNA_INPUT,FM_ANTENNA_TXO_LPI);
  }
  else
  {
    FMRM_send_property(FM_ANTENNA_INPUT,FM_ANTENNA_FMI);
  }
}
/*---------------------------------------------------------
Name:           FMRM_status_encode

Beschreibung:   Statusbyte auswerten

Eingänge:       void

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_status_encode()
{
  b_sctint = (u8_status & STCINT);
  b_rsqint = (u8_status & RSQINT);
  b_rdsint = (u8_status & RDSINT);
  b_err = (u8_status & ERR);
  b_cts = (u8_status & CTS);
}
/*---------------------------------------------------------
Name:           FMRM_rsq_status_get

Beschreibung:   Empfänger Status abfragen

Eingänge:       void

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_rsq_status_get()
{
  uint8_t cmd[8];
  cmd[0] = 0x23;
  cmd[1] = 0x01;

  FMRM_send(cmd, 2, 8);

  b_valid       = (cmd[2]&0x01);
  b_afc         = (cmd[2]&0x02);
//b_smute       = (cmd[2]&0x08);
//b_pilot       = (cmd[3]&0x80);
//u8_stblend    = (cmd[3]&0x7F);
  u8_rssi       = cmd[4];
  u8_snr        = cmd[5];
  u8_multipath  = cmd[6];
//u8_freqoff    = cmd[7];

}
/*---------------------------------------------------------
Name:           FMRM_rds_config

Beschreibung:   Konfiguration für RDS-Empfang

Eingänge:       void

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_rds_config()
{
  // Enable the RDS and STC interrupt here
  FMRM_send_property(GPO_IEN, GPO_IEN_STCIEN_MASK | GPO_IEN_RDSIEN_MASK);

  // This interrupt will be used to determine when RDS is available.
  FMRM_send_property(FM_RDS_INTERRUPT_SOURCE, FM_RDS_INTERRUPT_SOURCE_RECV_MASK); // RDS Interrupt

  FMRM_send_property(FM_RDS_INTERRUPT_FIFO_COUNT, 4);
  // Enable the RDS and allow all blocks so we can compute the error
  // rate later.
  FMRM_send_property(FM_RDS_CONFIG, FM_RDS_CONFIG_RDSEN_MASK |
    (FM_RDS_BLETH_UNCORRECTABLE << FM_RDS_CONFIG_BLETHA_SHFT) |
    (FM_RDS_BLETH_3TO5_ERRORS << FM_RDS_CONFIG_BLETHB_SHFT) |
    (FM_RDS_BLETH_UNCORRECTABLE << FM_RDS_CONFIG_BLETHC_SHFT) |
    (FM_RDS_BLETH_UNCORRECTABLE << FM_RDS_CONFIG_BLETHD_SHFT));
}
/*---------------------------------------------------------
Name:           FMRM_read_rds

Beschreibung:   RDS Sendernamen abfragen

Eingänge:       uint8_t* buffer, long timeout

Ausgang:        void
---------------------------------------------------------*/
uint8_t FMRM1::FMRM_read_rds(uint8_t* buffer, long rds_timeout)
{
  long startTime = millis();
  uint8_t addr = 0;
  uint8_t valid = 0;
  //wait for rds int
  while(true)
  {
    uint8_t buffer[1] = {GET_INT_STATUS};
    FMRM_send(buffer,1,1);
    if( b_rdsint != 0 )
    {
      break;
    }
    if( (millis()-startTime> rds_timeout) )
    {
      return 0;
    }
  }
  //get rds data
  while(true)
  {
    uint8_t rdsbuffer[13] = {FM_RDS_STATUS, FM_RDS_STATUS_IN_INTACK,0,0,0,0,0,0,0,0,0,0,0};
    FMRM_send(rdsbuffer,2,13);

    if( valid == 0xff) //all chars received
        break;
    // no data in fifo or timeout
    if(rdsbuffer[3]==0x00 || (millis()-startTime> rds_timeout))
    {
      if( valid != 0) //not all chars received
      {
        return 2;
      }
      else
        return 0;
    }
    //rds group 0 and no error
    if( !(rdsbuffer[6]&0xF0) && !rdsbuffer[12] )
    {
      //save 2 chars for station name
      addr = ((rdsbuffer[7]&0x03)*2);
      buffer[addr]=rdsbuffer[10];
      buffer[addr+1]=rdsbuffer[11];
      valid |= (3<<addr);
    }
  }
  return 1;
}
/*---------------------------------------------------------
Name:           FMRM_is_valid

Beschreibung:   Abfrage ob kanal eingestellt ist

Eingänge:       void

Ausgang:        uint8_t
---------------------------------------------------------*/
uint8_t FMRM1::FMRM_is_valid()
{
    return b_valid;
}

/**********************************************************
private Methoden
**********************************************************/
/*---------------------------------------------------------
Name:           FMRM_I2C_write

Beschreibung:   I2C Schreibroutine für FM-RM1

Eingänge:       uint8_t addr, uint8_t* buffer, uint8_t send_num

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_I2C_write(uint8_t addr, uint8_t* buffer, uint8_t send_num)
{
  Wire.beginTransmission(addr);
  for(uint8_t i =0; i< send_num; i++)
  {
    Wire.write(buffer[i]);
  }
  Wire.endTransmission();
}
/*---------------------------------------------------------
Name:           FMRM_I2C_read

Beschreibung:   I2C Leseroutine für FM-RM1

Eingänge:       uint8_t addr, uint8_t* buffer, uint8_t read_num

Ausgang:        void
---------------------------------------------------------*/
uint8_t FMRM1::FMRM_I2C_read(uint8_t addr, uint8_t* buffer, uint8_t read_num)
{
  long startTime = millis();
  Wire.requestFrom(addr, read_num); //We want to read read_num bytes.
  if (millis()-startTime > timeout)
  {
      return -1;
  }
  for(uint8_t x = 0 ; x<read_num; x++)
  { //Read in these bytes
    buffer[x] = Wire.read();
  }
  // clean buffer
  while(Wire.available() >0 )
  {
    Wire.read();
  }
  return 0;
}
/*---------------------------------------------------------
Name:           FMRM_send

Beschreibung:   FMRM Lese-/Schreibroutine für FM-RM1

Eingänge:       uint8_t* buffer, uint8_t send_num, uint8_t read_num

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_send(uint8_t* buffer, uint8_t send_num, uint8_t read_num)
{
  uint16_t i = 1000;
  FMRM_wait_cts();
  if(send_num!=0)
  {
    FMRM_I2C_write(FMRM_ADDR, buffer, send_num);
  }
  if(read_num!=0)
  {
    FMRM_wait_cts();
    FMRM_I2C_read(FMRM_ADDR, buffer, read_num);
    u8_status = *buffer;
    FMRM_status_encode();
  }
}
/*---------------------------------------------------------
Name:           FMRM_wait_cts

Beschreibung:   warte auf Bereitschaft von FM-RM1

Eingänge:       void

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_wait_cts()
{
  uint16_t i = 1000;
  uint8_t buffer[1];
  while( i-- && b_cts == 0 )
  {
    FMRM_I2C_read(FMRM_ADDR, buffer, 1);
    u8_status = *buffer;
    FMRM_status_encode();
    delayMicroseconds(500);
  }
}
/*---------------------------------------------------------
Name:           FMRM_send_property

Beschreibung:   FMRM Schreibroutine für FMRM Property

Eingänge:       uint16_t propNumber, uint16_t propValue

Ausgang:        void
---------------------------------------------------------*/
void FMRM1::FMRM_send_property(uint16_t propNumber, uint16_t propValue)
{
  uint8_t cmd[6];
  cmd[0] = SET_PROPERTY; //command
  cmd[1] = 0x00; //reserved
  cmd[2] = (uint8_t)(propNumber >> 8);
  cmd[3] = (uint8_t)(propNumber & 0x00FF);
  cmd[4] = (uint8_t)(propValue >> 8);
  cmd[5] = (uint8_t)(propValue & 0x00FF);
  FMRM_send(cmd, 6, 1);
}

/**********************************************************
Vorinstantiiertes Objekt
**********************************************************/
FMRM1 Radio = FMRM1();
