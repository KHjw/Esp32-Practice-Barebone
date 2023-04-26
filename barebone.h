#ifndef _DONE_BAREBONE_CODE_
#define _DONE_BAREBONE_CODE_

#include "Library_and_pin.h"


//****************************************Nextion SETUP**************************************************
// HardwareSerial nexHwSerial(2);
// String nextion_str = "";
// int currner_page_num;

/*
void NextionInit();
void DisplayCheck();


void NextionReceived();
void ExpSend();
void BatteryPackSend();
*/


//****************************************Encoder SETUP**************************************************
void Encoder_Setup();
long readEncoderValue(void);
void updateEncoder();
void Encoder_Read_Loop();

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int lastMSB = 0;
int lastLSB = 0;

//****************************************DFPlayer SETUP**************************************************
HardwareSerial DFP_Serial(2); // HWserial2
DFRobotDFPlayerMini myDFPlayer;

#endif