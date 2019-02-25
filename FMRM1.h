#ifndef FMRM1_H
#define FMRM1_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
extern "C"
{
#include "utility/fmrm_cmd_def.h"
#include "utility/fmrm_prop_def.h"
}

/**********************************************************
Definitionen
**********************************************************/
#define FMRM_PUT_IN_RESET           digitalWrite( _resetPin, HIGH )
#define FMRM_RELEASE_FROM_RESET     digitalWrite( _resetPin, LOW )

/**********************************************************
Klasse FMRM1
**********************************************************/
class FMRM1
{
private:
  int  _resetPin;
  uint16_t timeout;
  void FMRM_I2C_write(uint8_t addr, uint8_t* buffer, uint8_t send_num);
  uint8_t FMRM_I2C_read(uint8_t addr, uint8_t* buffer, uint8_t read_num);
  void FMRM_send(uint8_t* buffer, uint8_t send_num, uint8_t read_num);
  void FMRM_wait_cts(void);
  void FMRM_send_property(uint16_t propNumber, uint16_t propValue);
  void FMRM_status_encode(void);
  void FMRM_rsq_status_get(void);

public:
  uint8_t u8_status;
  uint8_t b_cts;
  uint8_t b_err;
  uint8_t b_rsqint;
  uint8_t b_rdsint;
  uint8_t b_sctint;

  uint8_t u8_volume;
  uint16_t u16_frequency;
  uint8_t b_bandlimit;
  uint8_t b_valid;
  uint8_t b_afc;
  uint8_t u8_rssi;
  uint8_t u8_snr;
  uint8_t u8_multipath;
  uint8_t u8_antennacap;

	FMRM1();
  void FMRM_init();
  void FMRM_init(int resetPin);
  void FMRM_power_up(void);
  void FMRM_power_down(void);
  void FMRM_config(void);
  void FMRM_volume_set(uint8_t volume);
  uint8_t FMRM_volume_get(void);
  void FMRM_audio_mute(uint8_t OnOff);
  void FMRM_antenna_select(uint8_t antenna);
  void FMRM_frequency_set(uint16_t freq);
  uint16_t FMRM_frequency_get(void);
  void FMRM_tune_status_get(void);
  void FMRM_seek(uint8_t direction);
  void FMRM_seek_manual(uint8_t direction);
  uint16_t FMRM_get_revision(void);
  void FMRM_rds_config(void);
  uint8_t FMRM_read_rds(uint8_t* buffer, long timeout);
  uint8_t FMRM_is_valid();
};

extern FMRM1 Radio;

#endif /* FMRM1_H */
