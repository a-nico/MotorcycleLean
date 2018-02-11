void getStheta(int average) // updates the S, theta floats, and accelerations -- "int average" is the number of readings to be averaged
{

  float axAxPlusAyay = 0; // this gets averaged
  float axaveraged=0, ayaveraged=0, azaveraged=0;
  int signSaveraged=0; 
  
  for(int k=0; k < average ; k++) { // loop adds up "int average" number of readings
    getA();
    axaveraged = axaveraged + ax;
    ayaveraged = ayaveraged + ay;
    azaveraged = azaveraged + az;
    
    signSaveraged = signSaveraged + signS; // signS comes from getA function
  }// end for loop which averages readings

// now divide by "int average" to get the average except for signS
    axaveraged = axaveraged/average;
    ayaveraged = ayaveraged/average;
    az = azaveraged/average; // this is a bit weird, bad style to overwrite az like this
    axAxPlusAyay = axaveraged*axaveraged + ayaveraged*ayaveraged;
    
  if (signSaveraged > 0) signSaveraged = 1;
  else if (signSaveraged < 0) signSaveraged = -1;
  else signSaveraged = 0;
  //Serial.print("ax^2 + ay^2=   "); Serial.println(axaxplusayay);
  
  float absS_squared = axAxPlusAyay - G_SQR; // this should always be >=0 but inaccuracies can make it negative
  
if (absS_squared <=0) S=0; // sometimes the sqrt gets negative argument which returns "nan" (no imaginary). This prevents it. 
else S = signSaveraged*sqrt( absS_squared ); // sqrtf is on floats, sqrt() is on doubles
// S = signSaveraged * sqrt( absS_squared );
  //Serial.print("S=   "); Serial.println(S);


  //theta = round(57.29578*acos( (axaveraged*G+ayaveraged*S)/axAxPlusAyay )-90);
  theta = round(57.29578*asin( (axaveraged*G-ayaveraged*S)/axAxPlusAyay ) ); // asin takes double, also converts to degrees
  //Serial.print("theta "); Serial.println(theta);
  
  
} //end getStheta function
