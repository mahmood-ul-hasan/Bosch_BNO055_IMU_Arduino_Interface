# Bosch BNO055 IMU Data Interface with Arduino

This project demonstrates how to read IMU (Inertial Measurement Unit) data from an Arduino, which is connected to the IMU via I2C and to a PC via a serial port. The data is read using a C++ program, stored in a CSV file, and visualized using the `matplotlibcpp` library.

## Files Explanations

- **BST_BNO055_DS000_12.pdf:** 
  - This is the datasheet of the Bosch BNO055 sensor, providing detailed technical information about the sensor's features, specifications, and usage.

- **IMU_calibration.ino and IMU_data.ino:**
  - These are Arduino IDE files used to interact with the Bosch BNO055 IMU sensor:
    - **IMU_calibration.ino:** This file is used for calibrating the IMU sensor and uploading calibration parameters.
    - **IMU_data.ino:** This file is used to read IMU data from the sensor, including accelerometer, magnetometer, gyroscope, Euler angles, and quaternions.

- **get_imu_data_in_PC.cpp:**
  - This C++ file is used to retrieve data from the Arduino connected to the PC:
    - **Uses the following library files:**
      - **SimpleSerial.cpp and SimpleSerial.h:** These files provide serial communication capabilities for the C++ program.
    - **Compilation and Execution:**
      - To compile and run the program:
        ```sh
        g++ get_imu_data_in_PC.cpp SimpleSerial.cpp -o get_imu_data_in_PC -std=c++11
        ./get_imu_data_in_PC
        ```
    - **Functionality:**
      - Reads IMU data from the Arduino via serial communication.
      - Extracts relevant data values and stores them in a CSV file (`result.csv`).
      - Plots the acceleration data along the X-axis using `matplotlibcpp`.

## Requirements

- Arduino board (e.g., Uno)
- Bosch BNO055 IMU sensor
- Jumper wires
- Arduino IDE
- Adafruit BNO055 library
- Adafruit Unified Sensor library
- C++ Compiler (e.g., GCC, Clang)
- `matplotlibcpp` library for data visualization
- `SimpleSerial` library for serial communication

## Wiring

Connect the BNO055 sensor to the Arduino as follows:

- **VIN** to **3.3V** or **5V** on the Arduino (depending on the sensor version)
- **GND** to **GND**
- **SCL** to **A5** (on Uno) or the dedicated SCL pin (on other boards)
- **SDA** to **A4** (on Uno) or the dedicated SDA pin (on other boards)
- **GND**, **S1**, and **SR** pins together

Connect the Arduino to the PC using a USB port.

## Installation

1. **Arduino Libraries:**
   - Install the Adafruit BNO055 and Adafruit Unified Sensor libraries using the Arduino Library Manager.
   - Clone this repository or download the code and open it in the Arduino IDE.

2. **PC Libraries:**
   - Install `matplotlibcpp` for plotting (make sure you have Python and `matplotlib` installed as well).
   - Ensure the `SimpleSerial` library is available for serial communication.

## Usage

1. **Arduino Setup:**
   - Upload the provided Arduino code (`IMU_data.ino` or `IMU_calibration.ino`) to your Arduino board.
   - Open the Serial Monitor (Ctrl+Shift+M) and set the baud rate to 256000. The sensor data will be displayed on the Serial Monitor.

2. **PC Setup:**
   - Save the provided C++ code (`get_imu_data_in_PC.cpp`) to your PC.
   - Compile the C++ code using a suitable compiler:
     ```sh
     g++ get_imu_data_in_PC.cpp SimpleSerial.cpp -o get_imu_data_in_PC -std=c++11
     ```
   - Run the compiled executable:
     ```sh
     ./get_imu_data_in_PC
     ```

## Code Explanation

### Arduino Code

The Arduino code initializes the BNO055 sensor, reads various sensor data, and prints them to the Serial Monitor. It includes functions for reading calibration data, setting calibration parameters, and acquiring sensor data such as accelerometer, magnetometer, gyroscope, Euler angles, and quaternions.

### C++ Code

The provided C++ code (`get_imu_data_in_PC.cpp`) reads IMU data from the serial port, extracts relevant values, stores them in a CSV file, and plots the acceleration along the X-axis.

- **Includes Required Libraries:**
  - `iostream` for input and output operations.
  - `SimpleSerial.h` for serial communication.
  - `sstream` for string stream operations.
  - `fstream` for file operations.
  - `string` for string operations.
  - `vector` for using vectors.
  - `matplotlibcpp.h` for plotting.

- **Initializes Serial Communication:**
  - Sets up the serial port and baud rate.
  - Defines the syntax type for reading from the serial port.

- **Extracts Float Values from String:**
  - Uses a string stream to extract float values from the incoming serial data.

- **Main Function:**
  - Opens a CSV file for writing data.
  - Reads data from the serial port in a loop, extracts values, and stores them in corresponding variables and vectors.
  - Saves the extracted data to the CSV.

- **Data Visualization:**
  - Plots the accelerometer data along the X-axis using `matplotlibcpp`.

## References

- [Adafruit BNO055 Arduino Library](https://github.com/adafruit/Adafruit_BNO055)
- [matplotlibcpp](https://github.com/lava/matplotlib-cpp)
- [SimpleSerial Library](https://github.com/cwalk/SimpleSerial)

## License

This project is licensed under the MIT License - see the LICENSE file for details.
