void calibration() // makes Araw into meters/second (float) and gyros read z when steady
{
  float xmin=0,xmax=0,ymin=0,ymax=0,zmin=0,zmax=0,GyroX=0,GyroY=0,GyroZ=0; // add up raw values then divide by number in for loop (e.g. 100)
  int steps = 1000;
  int delaytime = 2.5*1000/steps; // put in seconds to calibrate, want at least 1 sec or so.
 
  lcd.clear(); lcd.setCursor(0,0);
  lcd.print("    Entering");  lcd.setCursor(0,1); lcd.print("CALIBRATION mode");  
  delay(1500);
  while(buttonPressed());  // wait for button to be released

 
//********************* X calibration **********************************************     
   
 lcd.clear(); lcd.setCursor(0,0); lcd.print("Align X vertical"); lcd.setCursor(0,1); lcd.print("& press button.");
 while (!buttonPressed()); //wait for button press
 lcd.clear(); lcd.setCursor(0,0); lcd.print("Calibrating X"); lcd.setCursor(0,1); lcd.print("HOLD STEADY!");
    for(int k=0 ; k<steps ; k++)
    {
     delay(delaytime);
     getAraw(); //update accel values
     if(Araw[0]<0) xmin=xmin+Araw[0]; // figures out if you have x down or -x down
     else xmax=xmax+Araw[0];
    }
  lcd.clear(); lcd.setCursor(0,0); lcd.print("Flip X");  lcd.setCursor(0,1); lcd.print("& press button.");
  while (!buttonPressed()); //wait for button press
  lcd.clear(); lcd.setCursor(0,0); lcd.print("Calibrating X"); lcd.setCursor(0,1); lcd.print("HOLD STEADY!");
     for(int k=0; k<steps ; k++)
    {
     delay(delaytime);
     getAraw(); //update accel values
     if(Araw[0]<0) xmin=xmin+Araw[0]; // figures out if you have x down or -x down
     else xmax=xmax+Araw[0];
    }
          //now scale back
    xmax=xmax/steps;
    xmin=xmin/steps;
    // done with x calibration
  

//********************* Y calibration **********************************************   
 lcd.clear(); lcd.setCursor(0,0); lcd.print("Align Y vertical"); lcd.setCursor(0,1); lcd.print("& press button.");
 while (!buttonPressed()); //wait for button press
 lcd.clear(); lcd.setCursor(0,0); lcd.print("Calibrating Y"); lcd.setCursor(0,1); lcd.print("HOLD STEADY!");
    for(int k=0; k<steps; k++)
    {
     delay(delaytime);
     getAraw(); //update accel values
     if(Araw[1]<0) ymin=ymin+Araw[1]; // figures out if you have y down or -y down
     else ymax=ymax+Araw[1];
    }
  lcd.clear(); lcd.setCursor(0,0); lcd.print("Flip Y");  lcd.setCursor(0,1); lcd.print("& press button.");
  while (!buttonPressed()); //wait for button press
  lcd.clear(); lcd.setCursor(0,0); lcd.print("Calibrating Y"); lcd.setCursor(0,1); lcd.print("HOLD STEADY!");
    for(int k=0; k<steps; k++)
    {
     delay(delaytime);
     getAraw(); //update accel values
     if(Araw[1]<0) ymin=ymin+Araw[1]; // figures out if you have y down or -y down
     else ymax=ymax+Araw[1];
    }    
    
    ymax=ymax/steps;
    ymin=ymin/steps;
    // done with y calibration   



//********************* Z calibration **********************************************  
 lcd.clear(); lcd.setCursor(0,0); lcd.print("Align Z vertical"); lcd.setCursor(0,1); lcd.print("& press button.");
 while (!buttonPressed()); //wait for button press
 lcd.clear(); lcd.setCursor(0,0); lcd.print("Calibrating Z"); lcd.setCursor(0,1); lcd.print("HOLD STEADY!");
    for(int k=0; k<steps; k++)
    {
     delay(delaytime);
     getAraw(); //update accel values
     if(Araw[2]<0) zmin=zmin+Araw[2]; // figures out if you have z down or -z down
     else zmax=zmax+Araw[2];
    }
  lcd.clear(); lcd.setCursor(0,0); lcd.print("Flip Z");  lcd.setCursor(0,1); lcd.print("& press button.");
  while (!buttonPressed()); //wait for button press
  lcd.clear(); lcd.setCursor(0,0); lcd.print("Calibrating Z"); lcd.setCursor(0,1); lcd.print("HOLD STEADY!");
    for(int k=0; k<steps; k++)
    {
     delay(delaytime);
     getAraw(); //update accel values
     if(Araw[2]<0) zmin=zmin+Araw[2]; // figures out if you have z down or -z down
     else zmax=zmax+Araw[2];
    }    
    
    zmax=zmax/steps;
    zmin=zmin/steps;
    // done with z calibration   
 
    // now do the gyro accelerations
  lcd.clear(); lcd.setCursor(0,0); lcd.print("Hold STILL"); lcd.setCursor(0,1); lcd.print("& press button.");
   while (!buttonPressed()); //wait for button press
    lcd.clear(); lcd.setCursor(0,0); lcd.print("Calibrating GYRO"); lcd.setCursor(0,1); lcd.print("HOLD STEADY!");
      for(int k=0; k<steps; k++)
      {
        getAraw();
        GyroX=GyroX+GyRaw[0];
        GyroY=GyroY+GyRaw[1];
        GyroZ=GyroZ+GyRaw[2];
        delay(delaytime);
      }

// Now compute coefficients
csX=2*G/(xmax-xmin);
coX=-G*(xmax+xmin)/(xmax-xmin);

csY=2*G/(ymax-ymin);
coY=-G*(ymax+ymin)/(ymax-ymin);

csZ=2*G/(zmax-zmin);
coZ=-G*(zmax+zmin)/(zmax-zmin);

GyXoffset=GyroX/steps;
GyYoffset=GyroY/steps;
GyZoffset=GyroZ/steps;

// write coefficients to EEPROM as in excel list
EEPROM_writeAnything(36,GyXoffset);
EEPROM_writeAnything(40,GyYoffset);
EEPROM_writeAnything(44,GyZoffset);

EEPROM_writeAnything(48,csX);
EEPROM_writeAnything(52,coX);
EEPROM_writeAnything(56,csY);
EEPROM_writeAnything(60,coY);
EEPROM_writeAnything(64,csZ);
EEPROM_writeAnything(68,coZ);

EEPROM.write(73, B01100100); // sets the calibration check register (73) = to 100 to flag that it's been done.



lcd.clear(); lcd.setCursor(0,0); lcd.print("Calibration"); lcd.setCursor(0,1); lcd.print("complete."); delay(2000); lcd.clear();
}// end calibration function
