# Conflict Avoidance and Landslide Update of Vehicles in Deep Curves

## Introduction
Landslides and vehicle conflicts on curved roadways can lead to severe accidents and infrastructure damage. This project aims to develop a safety system designed to mitigate such risks by using sensor technology to detect hazardous conditions and warn drivers accordingly.

## Project Overview
The system integrates vibration and rain sensors to monitor landslide conditions and heavy rainfall. In the event of hazardous conditions, gates on either side of the road close until conditions normalize. Additionally, ultrasonic sensors detect vehicles approaching from the opposite side of a curve, and warnings are displayed on an LCD through a wireless communication protocol (ESP-NOW).

## Objectives
- Reduce the number of accidents on curved roadways.
- Implement a vehicle warning system for oncoming traffic.
- Utilize vibration and rain sensors to detect landslides and heavy rainfall.

## Methodology
The system is composed of:
- **Vibration Sensors:** Detect landslides.
- **Rain Sensors:** Monitor heavy rainfall.
- **Ultrasonic Sensors:** Measure vehicle distance.
- **ESP-32 Microcontroller:** Manages sensor data and wireless communication.
- **LCD Display:** Provides visual warnings to drivers.
- **Gates:** Automatically block the road when hazardous conditions are detected.

### Wireless Communication Protocol
**ESP-NOW** is a low-power, peer-to-peer wireless communication protocol developed by Espressif. It allows devices to communicate with each other without requiring a Wi-Fi network. ESP-NOW enables efficient, low-latency, and reliable communication between multiple ESP32 devices.

## Hardware Requirements
- Vibration Sensors
- Rain Sensors
- Ultrasonic Sensors
- ESP-32 Microcontroller (two units: one for the transmitter, one for the receiver)
- LCD Display
- Gates for blocking the road

## Software Requirements
- Arduino IDE for programming the ESP-32
- Libraries for interfacing with sensors and displays

## Connections

### Master (Transmitter) ESP-32
1. **Vibration Sensor**: 
   - **Signal Pin** to **GPIO 4**
   - **VCC** to **3.3V**
   - **GND** to **GND**

2. **Rain Sensor**:
   - **Signal Pin** to **GPIO 34**
   - **VCC** to **3.3V**
   - **GND** to **GND**

3. **Ultrasonic Sensor 1**:
   - **Trig Pin** to **GPIO 5**
   - **Echo Pin** to **GPIO 18**
   - **VCC** to **5V**
   - **GND** to **GND**

4. **Ultrasonic Sensor 2**:
   - **Trig Pin** to **GPIO 21**
   - **Echo Pin** to **GPIO 19**
   - **VCC** to **5V**
   - **GND** to **GND**

### Slave (Receiver) ESP-32
1. **LCD Display**:
   - **SDA** to **GPIO 21**
   - **SCL** to **GPIO 22**
   - **VCC** to **3.3V**
   - **GND** to **GND**

2. **Buzzer**:
   - **Pin** to **GPIO 4**
   - **VCC** to **3.3V** (or **5V** depending on the buzzer)
   - **GND** to **GND**

3. **Pushbutton (Clear Pin)**:
   - **One Pin** to **GPIO 2**
   - **Other Pin** to **GND**

## Usage Instructions

1. **Upload Code**:
   - Load `master.ino` onto the transmitter ESP-32.
   - Load `slave.ino` onto the receiver ESP-32.

2. **Power Up**:
   - Connect both ESP-32 units to a power source.## Usage Instructions

1. **Upload Code**:
   - Load `master.ino` onto the transmitter ESP-32.
   - Load `slave.ino` onto the receiver ESP-32.

2. **Update MAC Address**:
   - In the `master.ino` file, replace `broadcastAddress1[]` with the MAC address of the receiver ESP-32.

3. **Power Up**:
   - Connect both ESP-32 units to a power source.

4. **Verify Communication**:
   - Ensure that the transmitter ESP-32 is properly sending data and that the receiver ESP-32 is displaying the received information on the LCD.

5. **Calibration**:
   - Adjust sensor thresholds as necessary for your specific application and environment.

### Applications
- Road safety enhancement on curved roadways.
- Landslide monitoring and warning system.

### Advantages
- Real-time warning system for drivers.
- Automated response to hazardous conditions.

### Limitations
- Dependent on sensor accuracy and reliability.
- Requires maintenance and periodic testing.

### Future Scope
- Integration with a centralized traffic management system.
- Enhanced prediction models for landslide and weather conditions.

## Conclusion
This project successfully demonstrates a system to enhance road safety on curved roadways by using sensors to detect hazardous conditions and warn drivers. The use of ESP-NOW protocol allows for efficient wireless communication between the transmitter and receiver ESP-32 units, providing timely and accurate information to improve road safety.
