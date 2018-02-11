void getTemp() // returns int value of temperature in Fahrengehgiehgeht
{
  getAraw(); delay(100); getAraw();
  int tempF = Tmp*0.0052941+97.754; // converstion formula
  lcd.setCursor(0,0); lcd.print("Chip temp:");
  lcd.print(tempF); lcd.print((char) 223); lcd.print("F"); delay(250);

} // end getTemp function
