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
#line 23 "c:\\Github\\Esp32-Practice-Barebone\\Esp32-Practice-Barebone.ino"
void loop();
#line 16 "c:\\Github\\Esp32-Practice-Barebone\\Esp32-Practice-Barebone.ino"
void setup()
{
    Serial.begin(115200);
    Serial.println("------Esp32-Practice-Barebone Initialized------");
}


void loop()
{

}
