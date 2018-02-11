boolean buttonPressed() { // should include some sort of debouncing
  if (!digitalRead(BUTTON_PIN)) {
    delay(20);
    if (!digitalRead(BUTTON_PIN)) {
      return true;
    }
  }
  return false;  
}// end buttonPrssed() function
