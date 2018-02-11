#define MPU_addr 0x68
#define BUTTON_PIN 12

#include <EEPROM.h>
#include "EEPROMAnything.h"
#include <Wire.h>
#include <math.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7,3,POSITIVE);  // Set the correct LCD I2C address. Some 0x3F, some 0x27

//declare variables
float G = 9.81;
float G_SQR = 96.2361;
int16_t Tmp;
float x[3],y[3],z[3];
float Araw[3]; // acceleration from MPU, for calibration/alignment use
float GyRaw[3]; // gyro readings from MPU, for use in getAraw function
int signS; // either +1 or -1, sign of S based on gyros
//int angle; // angle in degrees
float S, ax, ay, az; // side acceleration (m/s^2), accelerations in chassis frame (m/s), theta in radians
float csX = 1, csY = 1, csZ = 1, coX = 0, coY = 0, coZ = 0; // slope and offset calculated by calibrations. This should be stored in EEPROM.
float GyXoffset = 0, GyYoffset = 0, GyZoffset = 0; // offsets for gyro
int theta;
int g;
// max stuff
long thetaTime = 99999;
long gTime = 99999;
int maxTheta = 0;
int maxG = 0;
long timeOut = 4000; // make this user changable
long timeOutArray[] = {5000, 10000, 15000, 25000, 50000, 120000, 100000000};
// strings
char angle[5];
char accel[5];
char maxAngle[5];
char maxAccel[5];

// declare functions  
void getA();
void getTemp();
void calibration();
void getAraw();
void alignment();
void calibrateAraw(); 

void getStheta(int average); // averages "average" number of values before it returns
void setups();
void cross(const float m[],const float n[], float p[]);
boolean buttonPressed();

void setup() {
   setups();
   lcd.setCursor(0,0); lcd.print("Now:");
   lcd.setCursor(0,1); lcd.print("Max:");
}

void loop() {

  getStheta(250);
  g = 100*az/G;
  
  if (abs(g) > abs(maxG)) {  
    maxG = g; gTime = millis();
  }
  
  if (abs(theta) > abs(maxTheta)) {
    maxTheta = theta; thetaTime = millis();
  }  
  
  if (millis() - gTime > timeOut) maxG = 0;
  if (millis() - thetaTime > timeOut) maxTheta = 0;

  sprintf(angle, "%i%c", theta, ((char) 223) );
  sprintf(accel, "%i%s", -g, "'g");
  sprintf(maxAngle, "%i%c", maxTheta, ((char) 223) );  
  sprintf(maxAccel, "%i%s", -maxG, "'g");   
  
  lcd.setCursor(5, 0); lcd.print(angle); lcd.print("   ");
  lcd.setCursor(11,0); lcd.print(accel); lcd.print("   ");
  lcd.setCursor(5, 1); lcd.print(maxAngle); lcd.print("   ");
  lcd.setCursor(11,1); lcd.print(maxAccel); lcd.print("   ");  
  
  if (buttonPressed()) changeTimeout();
  
}// end loop
