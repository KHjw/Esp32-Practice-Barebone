# 1 "c:\\Github\\Esp32-Practice-Barebone\\Esp32-Practice-Barebone.ino"
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
# 12 "c:\\Github\\Esp32-Practice-Barebone\\Esp32-Practice-Barebone.ino"
# 13 "c:\\Github\\Esp32-Practice-Barebone\\Esp32-Practice-Barebone.ino" 2

int button_status = 0;

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
# 1 "c:\\Github\\Esp32-Practice-Barebone\\dfplayer.ino"
void DFP_Setup(){
    DFP_Serial.begin(9600, 0x800001c, 39, 33);
    Serial.println(((reinterpret_cast<const __FlashStringHelper *>(("------DFPlayer_Setup Initialized------")))));
    Serial.println(((reinterpret_cast<const __FlashStringHelper *>(("Initializing DFPlayer ... (May take 3~5 seconds)")))));
    myDFPlayer.setTimeOut(1000); //Set serial communictaion time out 1000 ms

    if (!myDFPlayer.begin(DFP_Serial)) { //Use softwareSerial to communicate with mp3.
    Serial.println(((reinterpret_cast<const __FlashStringHelper *>(("Unable to begin:")))));
    Serial.println(((reinterpret_cast<const __FlashStringHelper *>(("1.Please recheck the connection!")))));
    Serial.println(((reinterpret_cast<const __FlashStringHelper *>(("2.Please insert the SD card!")))));
    // while(true);
    }

    Serial.println(((reinterpret_cast<const __FlashStringHelper *>(("DFPlayer Mini online.")))));
    myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms
    myDFPlayer.volume(30); //Set volume value (0~30).
    myDFPlayer.EQ(0);
    myDFPlayer.outputDevice(2);
}
# 1 "c:\\Github\\Esp32-Practice-Barebone\\encoder.ino"
long readEncoderValue(void){
    return encoderValue/4;
}

boolean isButtonPushDown(void){
  if(!digitalRead(4)){
    delay(5);
    if(!digitalRead(4))
      return true;
  }
  return false;
}

void Encoder_Setup(){
  pinMode(12, 0x01);
  pinMode(13, 0x01);
  pinMode(4, 0x01);

  digitalWrite(12, 0x1); //turn pullup resistor on
  digitalWrite(13, 0x1); //turn pullup resistor on

  //call updateEncoder() when any high/low changed seen
  //on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  attachInterrupt(12, updateEncoder, 0x03);
  attachInterrupt(13, updateEncoder, 0x03);
}

void Encoder_Read_Loop(){ // "encoder값, 버튼눌림" 을 표시
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
  int MSB = digitalRead(12); //MSB = most significant bit
  int LSB = digitalRead(13); //LSB = least significant bit

  int encoded = (MSB << 1) |LSB; //converting the 2 pin value to single number
  int sum = (lastEncoded << 2) | encoded; //adding it to the previous encoded value

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded; //store this value for next time
}
