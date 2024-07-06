# Conflict Avoidance and Landslide Update of Vehicle in Deep Curves

## Introduction
Landslides are hazardous geographical processes that cause damage to civil infrastructure and property, and can result in loss of life. This project aims to develop a system to reduce the number of accidents on curved roadways due to landslides and vehicle conflicts.

## Project Overview
The system uses a combination of vibration and rain sensors to detect landslide conditions and heavy rainfall. When such conditions are detected, gates on either side of the ghat road close until the conditions normalize. Additionally, ultrasonic sensors detect vehicles approaching from the opposite side of a curve and warn drivers via an LCD display.

## Objectives
- To decrease the number of accidents on curved roadways.
- To implement a warning system for vehicles approaching from opposite directions.
- To use vibration and rain sensors for detecting landslide conditions and heavy rainfall.

## Methodology
The system consists of:
- Vibration sensors to detect landslides.
- Rain sensors to detect heavy rainfall.
- Ultrasonic sensors connected to an ESP-32 microcontroller to detect approaching vehicles.
- LCD displays to warn drivers of approaching vehicles and hazardous conditions throug ESP-NOW communication protocol.

## Hardware Requirements
- Vibration Sensors
- Rain Sensors
- Ultrasonic Sensors
- ESP-32 Microcontroller
- LCD Display
- Gates for blocking the road

## Software Requirements
- Arduino IDE for programming the ESP-32
- Libraries for interfacing sensors and display

## Wireless communication protocol
- ESP-NOW

## Results and Discussions

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
This project successfully demonstrates a system to enhance road safety on curved roadways by using sensors to detect hazardous conditions and warn drivers.
