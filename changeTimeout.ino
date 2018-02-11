void changeTimeout() {
 
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Set timeout:");
 while(buttonPressed());
 delay(200);
 long timer = millis();
 byte k = 0;
 char timerString[16];
 
 while (millis() - timer < 4000) {
   delay(150);
   if (buttonPressed()) {
     
     if ( k > 6 ) k = 0; 
     timeOut = timeOutArray[k];
     
     sprintf(timerString, "%li%s", timeOut/1000, " seconds      ");
     
     delay(200);
     lcd.setCursor(0,1);
     lcd.print(timerString);
     
     k++;
     timer = millis(); 
   }
 }

  EEPROM.write(75, k);
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Setting saved!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("Now:");
  lcd.setCursor(0,1); lcd.print("Max:");
}
