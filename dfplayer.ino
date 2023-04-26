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