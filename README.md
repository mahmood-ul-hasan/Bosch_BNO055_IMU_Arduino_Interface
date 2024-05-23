# Bosch_BNO055_IMU_Arduino_Interface
This project demonstrates how to interface with the GY-955 BNO055 sensor using an Arduino Uno. It includes functions for reading calibration data, setting calibration parameters, and acquiring sensor data such as accelerometer, magnetometer, gyroscope, Euler angles, and quaternions.

# Bosch BNO055 IMU Data Interface with Arduino

This repository contains code to interface with the Bosch BNO055 IMU sensor using an Arduino. The code reads various sensor data including acceleration, magnetometer, gyroscope, Euler angles, quaternions, and temperature, and prints them to the Serial Monitor.

## Requirements

- Arduino board (e.g., Uno)
- Bosch BNO055 IMU sensor
- Jumper wires
- Arduino IDE
- Adafruit BNO055 library
- Adafruit Unified Sensor library

## Wiring

Connect the BNO055 sensor to the Arduino as follows:

- **VIN** to **3.3V** or **5V** on the Arduino (depending on the sensor version)
- **GND** to **GND**
- **SCL** to **A5** (on Uno) or the dedicated SCL pin (on other boards)
- **SDA** to **A4** (on Uno) or the dedicated SDA pin (on other boards)
- **GND**, **S1**, and **SR** pins together

## Installation

1. Install the Adafruit BNO055 and Adafruit Unified Sensor libraries using the Arduino Library Manager.
2. Clone this repository or download the code and open it in the Arduino IDE.

## Usage

1. Upload the code to your Arduino board.
2. Open the Serial Monitor (Ctrl+Shift+M) and set the baud rate to 115200.
3. The sensor data will be displayed on the Serial Monitor.

## Code Explanation

The code initializes the BNO055 sensor, reads various sensor data, and prints them to the Serial Monitor.
