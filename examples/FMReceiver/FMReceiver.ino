/******************************************************************************
Beispiel:	FMReceiver

Beschreibung:  	Dieses Beispiel zeigt die Benutzung des FMRM1 über die serielle Schnittstelle.
				
		Eingaben des Anwenders:
		r - Auslesen des aktuellen Kalibrierwertes aus dem RTC-Chip
	            und Ausgabe über die serielle Schnittstelle
				    
		w - Schreiben eines neuen Kalibriertwertes an den RTC-Chip
******************************************************************************/
#include "Wire.h"
#include "FMRM1.h"

/******************************************************************************
globale Variablen
******************************************************************************/
uint16_t temp_u16;
uint8_t temp_u8;
/******************************************************************************
Funktionen
******************************************************************************/
void setup() 
{
  Serial.begin(9600);
  Wire.begin();
  Radio.FMRM_init();
  //if resetpin used
  //Radio.FMRM_init(3); //D2 used for reset
  Radio.FMRM_config();
  Radio.FMRM_rds_config();
  Radio.FMRM_frequenzcy_set(10490);
  Radio.FMRM_audio_mute(0);
}

void loop() 
{
  processSerial();
}
uint8_t station_name[9] = {0};
void processSerial()
{
  if(Serial.available()>0)
  { 
    // call the returned value from GetFromSerial() function
    switch(GetFromSerial())
    {
      case 'r':  // rds
        Serial.print("rds:");
        temp_u8 = Radio.FMRM_read_rds(&station_name[0], 2000 );
        if( temp_u8 != 0)
        {
          station_name[8] = 0; //end of string
          Serial.println((char*)station_name);
        }
        else
        {
          Serial.println("RDS ERROR");
        }
        break;

      case 'f':  // Set Frequency
        temp_u16 = Serial.parseInt();
        Radio.FMRM_frequenzcy_set(temp_u16);
        delay(1000);
        Radio.FMRM_tune_status_get();
        break;
        
      case 'm':   //Mute
        Radio.FMRM_audio_mute(1);
        Serial.println("mute");
        break;
      case 'n':   //UnMute
        Radio.FMRM_audio_mute(0);
        Serial.println("unmute");
        break;
      case 'z':   //Get Revision
        temp_u16 = Radio.FMRM_get_revision();
        Serial.print("rev:");
        Serial.print((temp_u16>>8&0xff),DEC);
        Serial.print(".");
        Serial.println((temp_u16&0xff),DEC);
        break;
       case 's':   //Seek
        Serial.println("seek");
        Radio.FMRM_seek(1);
        //break;
      
       case 't':   //Get Tune Status
        Radio.FMRM_tune_status_get();
        Serial.print("tune:");
        Serial.println(Radio.b_valid,DEC);
        Serial.print("freq:");
        Serial.println(Radio.u16_frequency,DEC);
        Serial.print("rssi:");
        Serial.println(Radio.u8_rssi,DEC);
        Serial.print("snr:");
        Serial.println(Radio.u8_snr,DEC);
        Serial.print("ant_cap:");
        Serial.println(Radio.u8_antennacap,DEC);
        break;
      case 'v':   //Set Volume
        temp_u8 = Serial.parseInt();
        Serial.print("set volume:");
        Serial.println(temp_u8,DEC);
        Radio.FMRM_volume_set(temp_u8);
        break;
      case 'u':   //Get Volume
        Serial.print("volume:");
        Serial.println(Radio.FMRM_volume_get(),DEC);
        break;
      default:
        break;
    }
  }
}

byte GetFromSerial()
{
  while (Serial.available()<=0) {
  }
  return Serial.read();
}