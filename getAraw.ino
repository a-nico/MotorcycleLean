void getAraw()// gets raw sensor values for calibration and alignment
{
//  Wire.beginTransmission(MPU_addr);
//  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
//  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
//  if (Wire.available() < 2) {Wire.endTransmission(true); return;}
//// while(Wire.available()<2);
//Araw[0]=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
//if (Wire.available() < 2) {Wire.endTransmission(true); return;}
//// while(Wire.available()<2);
//Araw[1]=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
//if (Wire.available() < 2) {Wire.endTransmission(true); return;}
//// while(Wire.available()<2);
//Araw[2]=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
//if (Wire.available() < 2) {Wire.endTransmission(true); return;}
//// while(Wire.available()<2);
//Tmp = Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
//if (Wire.available() < 2) {Wire.endTransmission(true); return;}
//// while(Wire.available()<2);
//GyRaw[0]=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
//if (Wire.available() < 2) {Wire.endTransmission(true); return;}
//// while(Wire.available()<2);
//GyRaw[1]=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
//if (Wire.available() < 2) {Wire.endTransmission(true); return;}
//// while(Wire.available()<2);
//GyRaw[2]=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
//if (Wire.available() < 2) {Wire.endTransmission(true); return;}
//
//// note, Araw[] and GyRaw[] are float, but they come off as uint16_t from << thing, it gets re-cast.
//Wire.endTransmission(true);    

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  if (Wire.endTransmission(true)) return;  
  if(Wire.requestFrom(MPU_addr,14,true) == 14)  // request a total of 14 registers
  {
    Araw[0]=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
    Araw[1]=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    Araw[2]=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Tmp = Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
    GyRaw[0]=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyRaw[1]=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    GyRaw[2]=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  }

// note, Araw[] and GyRaw[] are float, but they come off as uint16_t from << thing, it gets re-cast.

}// end getAraw
