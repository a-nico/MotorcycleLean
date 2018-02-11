void calibrateAraw()
{
// apply calibration to raw sensor values  
Araw[0]=Araw[0]*csX+coX;
Araw[1]=Araw[1]*csY+coY;
Araw[2]=Araw[2]*csZ+coZ; // really these aren't Araw anymore, they're now A in sensor frame

GyRaw[0]=GyRaw[0]-GyXoffset;
GyRaw[1]=GyRaw[1]-GyYoffset;
GyRaw[2]=GyRaw[2]-GyZoffset; // these become calibrated "raw" readigns, float

} // end calibrateAraw function
