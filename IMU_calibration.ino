// Connect GND, S1 and SR pins together.
// Uno,  A4 (SDA), A5 (SCL)
#include <Wire.h>

unsigned long time;


float Yaw,Roll,Pitch,magx,magy,magz,accx, accy,accz, gyrox,gyroy,gyroz,q0,q1,q2,q3,Roll2,Pitch2,Yaw2,LIAx,LIAy,LIAz,GRVx,GRVy,GRVz, Temp;
byte CALIB_STAT, c0,c1,c2,c3,c4,c5,c6,c7;
const int GY_955=0x29;
int i=0, operMode;

float ACC_OFFSET_X, ACC_OFFSET_Y,  ACC_OFFSET_Z, MAG_OFFSET_X, MAG_OFFSET_Y, MAG_OFFSET_Z, GYR_OFFSET_X, GYR_OFFSET_Y, GYR_OFFSET_Z, ACC_RADIUS,MAG_RADIUS;
float ACC_OFFSET_X_L, ACC_OFFSET_X_M, ACC_OFFSET_Y_L, ACC_OFFSET_Y_M, ACC_OFFSET_Z_L, ACC_OFFSET_Z_M;
float MAG_OFFSET_X_L, MAG_OFFSET_X_M, MAG_OFFSET_Y_L, MAG_OFFSET_Y_M, MAG_OFFSET_Z_L, MAG_OFFSET_Z_M;
float GYR_OFFSET_X_L, GYR_OFFSET_X_M, GYR_OFFSET_Y_L, GYR_OFFSET_Y_M, GYR_OFFSET_Z_L, GYR_OFFSET_Z_M;
float ACC_RADIUS_L, ACC_RADIUS_M, MAG_RADIUS_L, MAG_RADIUS_M;
void writeByte(uint8_t address, uint8_t subAddress, uint16_t data){
    Wire.beginTransmission(address);  // Initialize the Tx buffer
    Wire.write(subAddress);           // Put slave register address in Tx buffer
    Wire.write(data);                 // Put data in Tx buffer
    Wire.endTransmission();           // Send the Tx buffer
}


void setCal(){
  //Config Mode 
Wire.beginTransmission(GY_955);
Wire.write(0x3D); // Operation Mode data register
Wire.write(0x00); //CONFIG MODE: 0x00 (or B0000) , NDOF:0X0C (or B1100) , IMU:0x08 (or B1000) , NDOF_FMC_OFF: 0x0B (or B1011)
Wire.endTransmission();
delay(100);


/* Cal Parameter
ACC_OFFSET_X = -20.00 , -59.00 , -26.00,
MAG_OFFSET = -410.00 , 250.00 , 330.00 , 
GYR_OFFSET_X = -1.00 , 3.00 , 1.00 , 
ACC_RADIUS = 1000.00 , 
MAG_RADIUS = 778.00 , */

// write cal parameters

 
writeByte(GY_955, 0x55, -6);   //ax_l
delay(50); 
writeByte(GY_955, 0x56, -1);   //ax_m
delay(50); 
writeByte(GY_955, 0x57, -17);   //ay_l
delay(50); 
writeByte(GY_955, 0x58, -1);   //ay_m
delay(50); 
writeByte(GY_955, 0x59, -23);   //az_l
delay(50); 
writeByte(GY_955, 0x5A, -1);   //az_m
delay(50); 


writeByte(GY_955, 0x5B, -122);   //mx_l
delay(50); 
writeByte(GY_955, 0x5C, -2);   //mx_m
delay(50);
writeByte(GY_955, 0x5D, 9);   //my_l
delay(50); 
writeByte(GY_955, 0x5E, 1);   //my_m
delay(50); 
writeByte(GY_955, 0x5F, 106);   //mz_l
delay(50); 
writeByte(GY_955, 0x60, 1);   //mz_m
delay(50); 


writeByte(GY_955, 0x61, -1);   //gx_l
delay(50); 
writeByte(GY_955, 0x62, -1);   //gx_m
delay(50); 
writeByte(GY_955, 0x63, 3);   //gy_l
delay(50); 
writeByte(GY_955, 0x64, 0);   //gy_m
delay(50); 
writeByte(GY_955, 0x65, 1);   //gz_l
delay(50); 
writeByte(GY_955, 0x66, 0);   //gz_m
delay(50); 


writeByte(GY_955, 0x67, -24); // acc_rad_l
delay(50);
writeByte(GY_955, 0x68, 3); // acc_rad_m
delay(50);  
writeByte(GY_955, 0x69, 15); // mag_rad_l
delay(50);  
writeByte(GY_955, 0x6A, 3); // mag_rad_m
delay(50);  

// NDOF Mode
Wire.beginTransmission(GY_955);
Wire.write(0x3D); // Operation Mode data register
Wire.write(0x0C); //NDOF:0X0C (or B1100) , IMU:0x08 (or B1000) , NDOF_FMC_OFF: 0x0B (or B1011)
Wire.endTransmission();
delay(100);
  }


void getCal(){

 //Config Mode 
Wire.beginTransmission(GY_955);
Wire.write(0x3D); // Operation Mode data register
Wire.write(0x00); //CONFIG MODE: 0x00 (or B0000) , NDOF:0X0C (or B1100) , IMU:0x08 (or B1000) , NDOF_FMC_OFF: 0x0B (or B1011)
Wire.endTransmission();
delay(100);


 //Read Oper Mode State
Wire.beginTransmission(GY_955);
Wire.write(0x3D);  
Wire.endTransmission(false);
Wire.requestFrom(GY_955,1,true);
operMode=(int8_t)(Wire.read()|Wire.read()<<8);
delay(100);
Serial.print("operMode = ");
Serial.println(operMode);


Wire.beginTransmission(GY_955);
Wire.write(0x55);  
Wire.endTransmission(false);
Wire.requestFrom(GY_955,22,true);
ACC_OFFSET_X_L=(int8_t)(Wire.read());
ACC_OFFSET_X_M=(int8_t)(Wire.read());
ACC_OFFSET_Y_L=(int8_t)(Wire.read());
ACC_OFFSET_Y_M=(int8_t)(Wire.read());
ACC_OFFSET_Z_L=(int8_t)(Wire.read());
ACC_OFFSET_Z_M=(int8_t)(Wire.read());

MAG_OFFSET_X_L=(int8_t)(Wire.read());
MAG_OFFSET_X_M=(int8_t)(Wire.read());
MAG_OFFSET_Y_L=(int8_t)(Wire.read());
MAG_OFFSET_Y_M=(int8_t)(Wire.read());
MAG_OFFSET_Z_L=(int8_t)(Wire.read());
MAG_OFFSET_Z_M=(int8_t)(Wire.read());

GYR_OFFSET_X_L=(int8_t)(Wire.read());
GYR_OFFSET_X_M=(int8_t)(Wire.read());
GYR_OFFSET_Y_L=(int8_t)(Wire.read());
GYR_OFFSET_Y_M=(int8_t)(Wire.read());
GYR_OFFSET_Z_L=(int8_t)(Wire.read());
GYR_OFFSET_Z_M=(int8_t)(Wire.read());

ACC_RADIUS_L=(int8_t)(Wire.read());
ACC_RADIUS_M=(int8_t)(Wire.read());

MAG_RADIUS_L=(int8_t)(Wire.read());
MAG_RADIUS_M=(int8_t)(Wire.read());

Serial.print("ACC_OFFSET_X_L = ");
Serial.print(ACC_OFFSET_X_L);
Serial.print(" , ");
Serial.print(ACC_OFFSET_X_M);
Serial.print(" , ");
Serial.print("ACC_OFFSET_Y_L = ");
Serial.print(ACC_OFFSET_Y_L);
Serial.print(" , ");
Serial.print(ACC_OFFSET_Y_M);
Serial.print(" , ");
Serial.print("ACC_OFFSET_Z_L = ");
Serial.print(ACC_OFFSET_Z_L);
Serial.print(" , ");
Serial.print(ACC_OFFSET_Z_M);
Serial.println(" , ");

Serial.print("MAG_OFFSET_X_L = ");
Serial.print(MAG_OFFSET_X_L);
Serial.print(" , ");
Serial.print(MAG_OFFSET_X_M);
Serial.print(" , ");
Serial.print("MAG_OFFSET_Y_L = ");
Serial.print(MAG_OFFSET_Y_L);
Serial.print(" , ");
Serial.print(MAG_OFFSET_Y_M);
Serial.print(" , ");
Serial.print("MAG_OFFSET_Z_L = ");
Serial.print(MAG_OFFSET_Z_L);
Serial.print(" , ");
Serial.print(MAG_OFFSET_Z_M);
Serial.println(" , ");

Serial.print("GYR_OFFSET_X_L = ");
Serial.print(GYR_OFFSET_X_L);
Serial.print(" , ");
Serial.print(GYR_OFFSET_X_M);
Serial.print(" , ");
Serial.print("GYR_OFFSET_Y_L = ");
Serial.print(GYR_OFFSET_Y_L);
Serial.print(" , ");
Serial.print(GYR_OFFSET_Y_M);
Serial.print(" , ");
Serial.print("GYR_OFFSET_Z_L = ");
Serial.print(GYR_OFFSET_Z_L);
Serial.print(" , ");
Serial.print(GYR_OFFSET_Z_M);
Serial.println(" , ");

Serial.print("ACC_RADIUS_L = ");
Serial.print(ACC_RADIUS_L);
Serial.print(" , ");
Serial.print(ACC_RADIUS_M);
Serial.print(" , ");
Serial.print("MAG_RADIUS_L = ");
Serial.print(MAG_RADIUS_L);
Serial.print(" , ");
Serial.print(MAG_RADIUS_M);
Serial.println(" , ");


// Reading Cal Values
Wire.beginTransmission(GY_955);
Wire.write(0x55);  
Wire.endTransmission(false);
Wire.requestFrom(GY_955,22,true);
ACC_OFFSET_X=(int16_t)(Wire.read()|Wire.read()<<8);
ACC_OFFSET_Y=(int16_t)(Wire.read()|Wire.read()<<8);
ACC_OFFSET_Z=(int16_t)(Wire.read()|Wire.read()<<8);
MAG_OFFSET_X=(int16_t)(Wire.read()|Wire.read()<<8);
MAG_OFFSET_Y=(int16_t)(Wire.read()|Wire.read()<<8);
MAG_OFFSET_Z=(int16_t)(Wire.read()|Wire.read()<<8);
GYR_OFFSET_X=(int16_t)(Wire.read()|Wire.read()<<8);
GYR_OFFSET_Y=(int16_t)(Wire.read()|Wire.read()<<8);
GYR_OFFSET_Z=(int16_t)(Wire.read()|Wire.read()<<8);
ACC_RADIUS=(int16_t)(Wire.read()|Wire.read()<<8);
MAG_RADIUS=(int16_t)(Wire.read()|Wire.read()<<8);

Serial.print("ACC_OFFSET_X = ");
Serial.print(ACC_OFFSET_X);
Serial.print(" , ");
Serial.print(ACC_OFFSET_Y);
Serial.print(" , ");
Serial.print(ACC_OFFSET_Z);
Serial.print(",");

Serial.print("MAG_OFFSET = ");
Serial.print(MAG_OFFSET_X);
Serial.print(" , ");
Serial.print(MAG_OFFSET_Y);
Serial.print(" , ");
Serial.print(MAG_OFFSET_Z);
Serial.print(" , ");

Serial.print("GYR_OFFSET_X = ");
Serial.print(GYR_OFFSET_X);
Serial.print(" , ");
Serial.print(GYR_OFFSET_Y);
Serial.print(" , ");
Serial.print(GYR_OFFSET_Z);
Serial.print(" , ");

Serial.print("ACC_RADIUS = ");
Serial.print(ACC_RADIUS);
Serial.print(" , ");

Serial.print("MAG_RADIUS = ");
Serial.print(MAG_RADIUS);
Serial.print(" , ");


// NDOF Mode
Wire.beginTransmission(GY_955);
Wire.write(0x3D); // Operation Mode data register
Wire.write(0x0C); //NDOF:0X0C (or B1100) , IMU:0x08 (or B1000) , NDOF_FMC_OFF: 0x0B (or B1011)
Wire.endTransmission();
delay(100);

 //Read operMode State
Wire.beginTransmission(GY_955);
Wire.write(0x3D);  
Wire.endTransmission(false);
Wire.requestFrom(GY_955,1,true);
operMode=(int8_t)(Wire.read()|Wire.read()<<8);
delay(100);
Serial.print("operMode = ");
Serial.println(operMode);

}


byte getCalStat(){
  
Wire.beginTransmission(GY_955);
Wire.write(0x35);  
Wire.endTransmission(false);
Wire.requestFrom(GY_955,1,true);
CALIB_STAT=(int8_t)(Wire.read()|Wire.read()<<8);
delay(50);

return CALIB_STAT;
}


  
void setup()
{

Serial.begin(256000);  //Setting the baudrate
delay(100);


Wire.begin();
Wire.setClock(400000); // I2C clock rate ,You can delete it but it helps the speed of I2C (default rate is 100000 Hz)
delay(100);


Wire.beginTransmission(GY_955);
Wire.write(0x3E); // Power Mode data register
Wire.write(0x00); // Normal:0X00 (or B00), Low Power: 0X01 (or B01) , Suspend Mode: 0X02 (orB10)
Wire.endTransmission();
delay(100);

Wire.beginTransmission(GY_955);
Wire.write(0x3D); // Operation Mode data register
Wire.write(0x0C); //NDOF:0X0C (or B1100) , IMU:0x08 (or B1000) , NDOF_FMC_OFF: 0x0B (or B1011)
Wire.endTransmission();
delay(100);


/*
for (i=0; i<10; i++){
// Reading calibration status data register
CALIB_STAT = getCalStat();
Serial.print("CALIB_STAT = ");
Serial.print(CALIB_STAT);
Serial.println(" , ");
}

*/
setCal();
//getCal();

}



void loop()
{
Wire.beginTransmission(GY_955);
Wire.write(0x08);  
Wire.endTransmission(false);
Wire.requestFrom(GY_955,32,true);

time = millis();


// Accelerometer
accx=(int16_t)(Wire.read()|Wire.read()<<8 )/100.00; // m/s^2
accy=(int16_t)(Wire.read()|Wire.read()<<8 )/100.00; // m/s^2
accz=(int16_t)(Wire.read()|Wire.read()<<8 )/100.00; // m/s^2
// Magnetometer
magx=(int16_t)(Wire.read()|Wire.read()<<8 )/16.00; // mT
magy=(int16_t)(Wire.read()|Wire.read()<<8 )/16.00; // mT
magz=(int16_t)(Wire.read()|Wire.read()<<8 )/16.00; // mT
// Gyroscope
gyrox=(int16_t)(Wire.read()|Wire.read()<<8 )/16.00; // Dps
gyroy=(int16_t)(Wire.read()|Wire.read()<<8 )/16.00; // Dps
gyroz=(int16_t)(Wire.read()|Wire.read()<<8 )/16.00; // Dps
// Euler Angles
Yaw=(int16_t)(Wire.read()|Wire.read()<<8 )/16.00;  //in Degrees unit
Roll=(int16_t)(Wire.read()|Wire.read()<<8 )/16.00;  //in Degrees unit
Pitch=(int16_t)(Wire.read()|Wire.read()<<8 )/16.00;  //in Degrees unit
// Quaternions
q0=(int16_t)(Wire.read()|Wire.read()<<8 )/(pow(2,14)); //unit less
q1=(int16_t)(Wire.read()|Wire.read()<<8 )/(pow(2,14)); //unit less
q2=(int16_t)(Wire.read()|Wire.read()<<8 )/(pow(2,14)); //unit less
q3=(int16_t)(Wire.read()|Wire.read()<<8 )/(pow(2,14)); //unit less
//Convert Quaternions to Euler Angles
Yaw2=(atan2(2*(q0*q3+q1*q2),1-2*(pow(q2,2)+pow(q3,2))))*180/PI;
Roll2=(asin(2*(q0*q2-q3*q1)))*180/PI;
Pitch2=(atan2(2*(q0*q1+q2*q3),1-2*(pow(q1,2)+pow(q2,2))))*180/PI;


//Linear (Dynamic) & Gravitational (static) Acceleration
Wire.beginTransmission(0x29);
Wire.write(0x28);  
Wire.endTransmission(false);
Wire.requestFrom(0x29,14,true);
LIAx=(int16_t)(Wire.read()|Wire.read()<<8)/100.00; // m/s^2
LIAy=(int16_t)(Wire.read()|Wire.read()<<8)/100.00; // m/s^2
LIAz=(int16_t)(Wire.read()|Wire.read()<<8)/100.00; // m/s^2
GRVx=(int16_t)(Wire.read()|Wire.read()<<8)/100.00; // m/s^2
GRVy=(int16_t)(Wire.read()|Wire.read()<<8)/100.00; // m/s^2
GRVz=(int16_t)(Wire.read()|Wire.read()<<8)/100.00; // m/s^2

Temp=(int8_t)(Wire.read()|Wire.read()<<8);




CALIB_STAT = getCalStat();
//getCal();










//Serial.print(",");
Serial.print("<");
Serial.print(time);
Serial.print(" , ");

Serial.print(Roll);
Serial.print(" , ");
 
Serial.print(Pitch);
Serial.print(" , ");

Serial.print(Yaw);
Serial.print(" , ");


Serial.print(accx);
Serial.print(" , ");
Serial.print(accy);
Serial.print(" , ");
Serial.print(accz);
Serial.print(" , ");

Serial.print(gyrox);
Serial.print(" , ");
Serial.print(gyrox);
Serial.print(" , ");
Serial.print(gyrox);
Serial.print(" , ");


Serial.print(magx);
Serial.print(" , ");
Serial.print(magy);
Serial.print(" , ");
Serial.print(magz);


Serial.print(" , ");
Serial.print(CALIB_STAT);

Serial.print(" , ");
Serial.print(q0);
Serial.print(" , ");
Serial.print(q1);
Serial.print(" , ");
Serial.print(q2);
Serial.print(" , ");
Serial.print(q3);

Serial.println(">");

delay(30);




}
