// Connect GND, S1 and SR pins together.
// Uno,  A4 (SDA), A5 (SCL)
#include <Wire.h>

unsigned long time;


float Yaw, Roll, Pitch, magx, magy, magz, accx, accy, accz, gyrox, gyroy, gyroz, q0, q1, q2, q3, Roll2, Pitch2, Yaw2, LIAx, LIAy, LIAz, GRVx, GRVy, GRVz, Temp;
byte CALIB_STAT, c0, c1, c2, c3, c4, c5, c6, c7;
const int GY_955 = 0x29;
void setup()
{
  Wire.begin();
  Wire.setClock(400000); // I2C clock rate ,You can delete it but it helps the speed of I2C (default rate is 100000 Hz)
  delay(100);
  Wire.beginTransmission(GY_955);
  Wire.write(0x3E); // Power Mode data register
  Wire.write(0x00); // Normal:0X00 (or B00), Low Power: 0X01 (or B01) , Suspend Mode: 0X02 (orB10)
  Wire.endTransmission();
  delay(100);
  Wire.beginTransmission(GY_955);
  Wire.write(0x3D); // Operation Mode
  Wire.write(0x0C); //NDOF:0X0C (or B1100) , IMU:0x08 (or B1000) , NDOF_FMC_OFF: 0x0B (or B1011)
  Wire.endTransmission();
  delay(100);

 // Serial.begin( 500000);  //Setting the baudrate

  Serial.begin(115200);  //Setting the baudrate
  delay(100);
}
void loop()
{
  Wire.beginTransmission(GY_955);
  Wire.write(0x08);
  Wire.endTransmission(false);
  Wire.requestFrom(GY_955, 32, true);

  time = millis();


  // Accelerometer
  accx = (int16_t)(Wire.read() | Wire.read() << 8 ) / 100.00; // m/s^2
  accy = (int16_t)(Wire.read() | Wire.read() << 8 ) / 100.00; // m/s^2
  accz = (int16_t)(Wire.read() | Wire.read() << 8 ) / 100.00; // m/s^2
  // Magnetometer
  magx = (int16_t)(Wire.read() | Wire.read() << 8 ) / 16.00; // mT
  magy = (int16_t)(Wire.read() | Wire.read() << 8 ) / 16.00; // mT
  magz = (int16_t)(Wire.read() | Wire.read() << 8 ) / 16.00; // mT
  // Gyroscope
  gyrox = (int16_t)(Wire.read() | Wire.read() << 8 ) / 16.00; // Dps
  gyroy = (int16_t)(Wire.read() | Wire.read() << 8 ) / 16.00; // Dps
  gyroz = (int16_t)(Wire.read() | Wire.read() << 8 ) / 16.00; // Dps
  // Euler Angles
  Yaw = (int16_t)(Wire.read() | Wire.read() << 8 ) / 16.00; //in Degrees unit
  Roll = (int16_t)(Wire.read() | Wire.read() << 8 ) / 16.00; //in Degrees unit
  Pitch = (int16_t)(Wire.read() | Wire.read() << 8 ) / 16.00; //in Degrees unit
  // Quaternions
  q0 = (int16_t)(Wire.read() | Wire.read() << 8 ) / (pow(2, 14)); //unit less
  q1 = (int16_t)(Wire.read() | Wire.read() << 8 ) / (pow(2, 14)); //unit less
  q2 = (int16_t)(Wire.read() | Wire.read() << 8 ) / (pow(2, 14)); //unit less
  q3 = (int16_t)(Wire.read() | Wire.read() << 8 ) / (pow(2, 14)); //unit less
  //Convert Quaternions to Euler Angles
  Yaw2 = (atan2(2 * (q0 * q3 + q1 * q2), 1 - 2 * (pow(q2, 2) + pow(q3, 2)))) * 180 / PI;
  Roll2 = (asin(2 * (q0 * q2 - q3 * q1))) * 180 / PI;
  Pitch2 = (atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (pow(q1, 2) + pow(q2, 2)))) * 180 / PI;


  //Linear (Dynamic) & Gravitational (static) Acceleration
  Wire.beginTransmission(0x29);
  Wire.write(0x28);
  Wire.endTransmission(false);
  Wire.requestFrom(0x29, 14, true);
  LIAx = (int16_t)(Wire.read() | Wire.read() << 8) / 100.00; // m/s^2
  LIAy = (int16_t)(Wire.read() | Wire.read() << 8) / 100.00; // m/s^2
  LIAz = (int16_t)(Wire.read() | Wire.read() << 8) / 100.00; // m/s^2
  GRVx = (int16_t)(Wire.read() | Wire.read() << 8) / 100.00; // m/s^2
  GRVy = (int16_t)(Wire.read() | Wire.read() << 8) / 100.00; // m/s^2
  GRVz = (int16_t)(Wire.read() | Wire.read() << 8) / 100.00; // m/s^2

  Temp = (int8_t)(Wire.read() | Wire.read() << 8);

  Wire.beginTransmission(0x29);
  Wire.write(0x35);
  Wire.endTransmission(false);
  Wire.requestFrom(0x29, 1, true);
  CALIB_STAT = (int8_t)(Wire.read() | Wire.read() << 8);


  c0 = bitRead(CALIB_STAT, 5);


  // Print data
  //Serial.print("Yaw=");

  // Print data
  //Serial.print("Yaw=");

  //Serial.print(time);
  //Serial.print(" , ");

  //Serial.print(CALIB_STAT);
  //Serial.print(" , ");

  //Serial.print(c0);
  //Serial.print(" , ");

  //Serial.print(Temp);


  //Serial.println(" ");




  //Serial.print(",");

/*
  Serial.print(time);
  Serial.print(" , ");
  Serial.print(" [Roll,  Pitch,  Yaw ] =  [");
  Serial.print(Roll);
  Serial.print(", ");
  Serial.print(Pitch);
  Serial.print(", ");
  Serial.print(Yaw);
  Serial.println(" ], ");


  
    Serial.print(accx);
    Serial.print(",");
    Serial.print(accy);
    Serial.print(",");
    Serial.print(accz);
    Serial.print(",");

    Serial.print(gyrox);
    Serial.print(",");
    Serial.print(gyrox);
    Serial.print(",");
    Serial.print(gyrox);
    Serial.print(",");


    Serial.print(magx);
    Serial.print(",");
    Serial.print(magy);
    Serial.print(",");
    Serial.print(magz);

    Serial.print(" , ");
    Serial.print(CALIB_STAT);

    Serial.println(",");

  */
  delay(30);

}
