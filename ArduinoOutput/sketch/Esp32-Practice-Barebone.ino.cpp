#include <Arduino.h>
#line 1 "c:\\Github\\Esp32-Practice-Barebone\\Esp32-Practice-Barebone.ino"
 /*
 * @file Esp32-Practice-Barebone.ino
 * @author 홍진우 KH.jinu (kevinlike@naver.com)
 * @brief
 * @version 1.0
 * @date 2023-04-21
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "barebone.h"

int button_status = 0;

#line 16 "c:\\Github\\Esp32-Practice-Barebone\\Esp32-Practice-Barebone.ino"
void setup();
#line 25 "c:\\Github\\Esp32-Practice-Barebone\\Esp32-Practice-Barebone.ino"
void loop();
#line 1 "c:\\Github\\Esp32-Practice-Barebone\\dfplayer.ino"
void DFP_Setup();
#line 1 "c:\\Github\\Esp32-Practice-Barebone\\encoder.ino"
long readEncoderValue(void);
#line 5 "c:\\Github\\Esp32-Practice-Barebone\\encoder.ino"
boolean isButtonPushDown(void);
#line 14 "c:\\Github\\Esp32-Practice-Barebone\\encoder.ino"
void Encoder_Setup();
#line 28 "c:\\Github\\Esp32-Practice-Barebone\\encoder.ino"
void Encoder_Read_Loop();
#line 41 "c:\\Github\\Esp32-Practice-Barebone\\encoder.ino"
void updateEncoder();
#line 16 "c:\\Github\\Esp32-Practice-Barebone\\Esp32-Practice-Barebone.ino"
void setup()
{
    Serial.begin(115200);
    Serial.println("------Esp32-Practice-Barebone Initialized------");
    Encoder_Setup();
    DFP_Setup();
}


void loop()
{
    Encoder_Read_Loop();
}
#line 1 "c:\\Github\\Esp32-Practice-Barebone\\dfplayer.ino"
void DFP_Setup(){
    DFP_Serial.begin(9600, SERIAL_8N1, DFPLAYER_RX_PIN, DFPLAYER_TX_PIN);
    Serial.println(F("------DFPlayer_Setup Initialized------"));
    Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
    myDFPlayer.setTimeOut(1000); //Set serial communictaion time out 1000 ms

    if (!myDFPlayer.begin(DFP_Serial)) { //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    // while(true);
    }

    Serial.println(F("DFPlayer Mini online."));
    myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
    myDFPlayer.volume(30);  //Set volume value (0~30).
    myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
    myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
}
#line 1 "c:\\Github\\Esp32-Practice-Barebone\\encoder.ino"
long readEncoderValue(void){
    return encoderValue/4;
}

boolean isButtonPushDown(void){
  if(!digitalRead(buttonPin)){
    delay(5);
    if(!digitalRead(buttonPin))
      return true;
  }
  return false;
}

void Encoder_Setup(){
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(buttonPin, INPUT);

  digitalWrite(encoderPinA, HIGH); //turn pullup resistor on
  digitalWrite(encoderPinB, HIGH); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  attachInterrupt(encoderPinA, updateEncoder, CHANGE);
  attachInterrupt(encoderPinB, updateEncoder, CHANGE);
}

void Encoder_Read_Loop(){                                // "encoder값, 버튼눌림" 을 표시
  if(isButtonPushDown()){
    Serial.print(readEncoderValue());
    Serial.print(", ");
    Serial.println("1");
  }else{
    Serial.print(readEncoderValue());
    Serial.print(", ");
    Serial.println("0");
  }
  delay(50);
}

void updateEncoder(){
  int MSB = digitalRead(encoderPinA); //MSB = most significant bit
  int LSB = digitalRead(encoderPinB); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum  = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}
