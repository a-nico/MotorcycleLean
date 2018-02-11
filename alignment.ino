void alignment() //determines the x[] y[] and z[] which are used to transform from sensor frame (Araw from getAraw) to chassis frame (ax ay az from getA).
{
  
  int steps = 1000;
  int delaytime = 5*1000/steps; // put in seconds to calibrate, want at least 1 sec or so.
  float ax1=0, ay1=0, az1=0, ax2=0, ay2=0, az2=0; // these are values in sensor frame (with calibration applied): ax1 on kick stand, ax2 on rear stand
  
  lcd.clear(); lcd.setCursor(0,0);
  lcd.print("    Entering");  lcd.setCursor(0,1); lcd.print(" alignment mode");
  delay(200);
  while(buttonPressed());  // wait for button to be released
  delay(1500);
  if (buttonPressed()) calibration();
  
  // ************get data on kickstand *******************
  lcd.clear(); lcd.setCursor(0,0);
  lcd.print(" Place bike flat");  lcd.setCursor(0,1); lcd.print("  on KICKSTAND");
  while (!buttonPressed()); //wait for button press
  lcd.clear(); lcd.setCursor(1,0); lcd.print("Acquiring data"); lcd.setCursor(2,1); lcd.print("HOLD STEADY!");
  delay(1000); // make sure bike isn't being touched
  for(int k=0; k<steps ; k++)
  {
    delay(delaytime);
    getAraw(); //update accel values
    calibrateAraw(); // apply calibration to Araw[] array
    ax2=ax2+Araw[0]; // sum values to compute average (divide later)
    ay2=ay2+Araw[1];
    az2=az2+Araw[2];
  }
  ax2=ax2/steps; //divide to give the average
  ay2=ay2/steps;
  az2=az2/steps;
  
  // ************* get data on rear stand *******************
  lcd.clear(); lcd.setCursor(0,0);
  lcd.print("Place bike flat");  lcd.setCursor(0,1); lcd.print(" on REAR STAND");
  while (!buttonPressed()); //wait for button press
  lcd.clear(); lcd.print(" Acquiring in");
  for(int j=5;j>0;j--) // countdown until it starts taking data. Gives enough time to level rear stand
  {lcd.setCursor(14,0);  lcd.print(j); delay(1000); }
  lcd.clear(); lcd.setCursor(1,0); lcd.print("Acquiring data"); lcd.setCursor(2,1); lcd.print("HOLD STEADY!");
  
  for(int k=0; k<steps ; k++)
  {
    delay(delaytime);
    getAraw();
    calibrateAraw();
    ax1=ax1+Araw[0]; // sum values to compute average (divide later)
    ay1=ay1+Araw[1];
    az1=az1+Araw[2];
  }
  ax1=ax1/steps; //divide to give the average
  ay1=ay1/steps;
  az1=az1/steps;
  //***** that's it for data collection
  
  // compute vectors which become components of the rotation matrix
  float yvec[3]; // y is vector gotten from kick stand test
  yvec[0]=ax1/G;   yvec[1]=ay1/G;   yvec[2]=az1/G; // make yvec a unit vector
  
  float a2magnitude=sqrt(ax2*ax2+ay2*ay2+az2*az2); // compute the magnitude so that a2 can be made an unit vector
  // float a2[]={ax2/a2magnitude , ay2/a2magnitude , az2/a2magnitude}; // unit vector of acceleration on rear stand
  float a2[3]; a2[0]=ax2; a2[1]=ay2; a2[2]=az2;
  
  float zvec[3]; //initiate this so that the cross function can edit it
  cross(yvec,a2,zvec); // crosses yvec, a2, and writes it into zvec
  float zvecmagnitude=sqrt(zvec[0]*zvec[0]+zvec[1]*zvec[1]+zvec[2]*zvec[2]); // get it's magnitude because it's not a unit vector ( sin(alpha) is the length), alpha is angle of tilt on kickstand
  zvec[0]=zvec[0]/zvecmagnitude;   zvec[1]=zvec[1]/zvecmagnitude;   zvec[2]=zvec[2]/zvecmagnitude; // make zvec a unit vector
  
  float xvec[]={0,0,0}; // initiate x vector to pass to cross function.
  cross(yvec,zvec,xvec); // y cross z = x, all unit vectors.
  
  // now update alignment constants which are loaded in memory in setups() and used by getA function
  for(int k = 0; k < 3; k++) {
    EEPROM_writeAnything(4*k,xvec[k]);
    EEPROM_writeAnything(4*k+12,yvec[k]);
    EEPROM_writeAnything(4*k+24,zvec[k]);
  }//end for loop
  
  EEPROM.write(72, B01100100); // sets the alignment check register (72) = to 100 = B01100100 to flag that it's been done.
  lcd.clear(); lcd.setCursor(0,0);
  lcd.print("   Alignment"); lcd.setCursor(0,1); lcd.print("   finished.");
  delay(3000);
  lcd.clear();
  
}// end alignment function
