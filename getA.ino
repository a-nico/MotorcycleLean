void getA() // takes Araw[] data and transforms to chassis frame, both accel and gyro, also sets sign of S
{

getAraw(); // first, loads raw values straight from MPU6050
calibrateAraw(); // apply calibration to Araw[] array

// transorm to chassis frame, x[],y[],z[] computed from alignment
ax=Araw[0]*x[0]+Araw[1]*x[1]+Araw[2]*x[2];
ay=Araw[0]*y[0]+Araw[1]*y[1]+Araw[2]*y[2];
az=Araw[0]*z[0]+Araw[1]*z[1]+Araw[2]*z[2]; 

int16_t gyy=GyRaw[0]*y[0]+GyRaw[1]*y[1]+GyRaw[2]*y[2]; // only care about angular rate about y axis (bike is in a turn)


//determine sign of S
if(gyy>0) signS=1;
else signS=-1;

}// end getA function
