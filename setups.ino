void setups() { // sets the accelerometer settings, starts LCD
   // configure accelerometer registers
   Wire.begin();
   Wire.beginTransmission(MPU_addr);
   Wire.write(0x6B);  // PWR_MGMT_1 register, sets clock reference, sleep mode, and temp sensor
   Wire.write(0b00000011);     // set to zero (wakes up the MPU-6050), use gyro Z for clock ref
   Wire.endTransmission(true);
   
   Wire.beginTransmission(MPU_addr);
   Wire.write(26);  // Frame Synchronization and Filtering register
   Wire.write(0b00000110);     // set to pretty hardcore filtering (last 3 bits chose between 0-6)
   Wire.endTransmission(true);
   
   Wire.beginTransmission(MPU_addr);
   Wire.write(28);  // Self-test and sensitivity (g-range) register.
   Wire.write(0b00000000);     // last 3 bits are nothing. all 0 is +/- 2g
   Wire.endTransmission(true);
   
   
   // initialize LCD 16x2
   lcd.begin(16,2);
   lcd.backlight();
   lcd.setCursor(0,0); //Start at character 4 on line 0
   lcd.print("Starting...");
   delay(500);
   lcd.clear();
   
   pinMode(BUTTON_PIN,INPUT_PULLUP); // button pin default high
   //Serial.begin(9600);
   
   // load EEPROM, if EEPROM bytes are all 255, message that it needs alignment. Or make byte 72 = 0 if alignment done.
   /*byte checkCalibration;
   byte checkAlignment;
   byte checkCalibration=EEPROM.read(73);
   EEPROM.read(72, checkAlignment);*/
   if(EEPROM.read(73)!=B01100100){
      lcd.setCursor(0,0);
      lcd.print("Calibration not");
      lcd.setCursor(0,1);
      lcd.print("yet done.");
      delay(4000); calibration();
   }
   
   if(EEPROM.read(72) != B01100100){
      lcd.print("Alignment not");
      lcd.setCursor(0,1);
      lcd.print("yet done.");
      delay(4000); alignment();
   }
   
   // show temperature while waiting for any button presses
   getTemp();
   while (!buttonPressed() && millis() < 2000);
   lcd.clear();
   // now read calibration constants from EEPROM
   EEPROM_readAnything(36,GyXoffset);
   EEPROM_readAnything(40,GyYoffset);
   EEPROM_readAnything(44,GyZoffset);
   
   EEPROM_readAnything(48,csX);
   EEPROM_readAnything(52,coX);
   EEPROM_readAnything(56,csY);
   EEPROM_readAnything(60,coY);
   EEPROM_readAnything(64,csZ);
   EEPROM_readAnything(68,coZ);
   
   // perform alignment if button pressed
   if(buttonPressed()) alignment();
   
   // now read alignment constants from EEPROM
   for(int k=0; k < 3; k++) {
      EEPROM_readAnything(4*k,x[k]);
      EEPROM_readAnything(4*k+12,y[k]);
      EEPROM_readAnything(4*k+24,z[k]);
   }//end for loop
   
   // read timeOut preference
   int w = EEPROM.read(75);
   if (w > 6) w = 2;
   timeOut = timeOutArray[ w ];
   
}//end setups function
