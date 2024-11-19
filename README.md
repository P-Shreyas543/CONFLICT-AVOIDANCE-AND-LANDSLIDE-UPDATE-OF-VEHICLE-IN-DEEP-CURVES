# Conflict Avoidance and Landslide Update of Vehicles in Deep Curves

## Project Images
<div align="center">
  <img src="https://github.com/user-attachments/assets/ca3b9c91-4273-432d-8a6f-7f55d11207bb" alt="Image 1" width="30%" />
  <img src="https://github.com/user-attachments/assets/b2f93b1d-e695-46d5-8757-a363d183c3f4" alt="Image 2" width="30%" />
  <img src="https://github.com/user-attachments/assets/692ccf32-b058-4ddf-8323-9f54764f712d" alt="Image 3" width="30%" />
</div>

## Introduction
Landslides and vehicle conflicts on curved roadways pose significant risks to drivers and infrastructure. This project aims to create a safety system that detects hazardous conditions, including landslides, rainfall, and vehicle proximity, and warns drivers to prevent accidents.

## Project Overview
The system uses sensors to monitor environmental conditions and communicate warnings to drivers using ESP-NOW, a wireless protocol. The system also activates physical barriers (gates) during severe conditions, ensuring safety on curved roadways.

### Key Features
1. **Landslide Detection:** Uses vibration sensors to monitor ground stability.
2. **Rain Intensity Monitoring:** Employs rain sensors to assess rainfall levels.
3. **Collision Prevention:** Ultrasonic sensors detect nearby vehicles in blind spots.
4. **Driver Alerts:** Warnings are displayed on an LCD, accompanied by buzzer notifications.
5. **Wireless Communication:** Utilizes ESP-NOW for low-latency data transmission between microcontrollers.

---

## Objectives
- Mitigate accidents caused by vehicle conflicts on curves.
- Detect and alert about landslides and heavy rainfall conditions.
- Ensure timely and effective communication of hazards to drivers.

---

## Methodology
The system operates in two primary roles:
- **Transmitter Unit:** Collects data from sensors and sends it wirelessly to the receiver.
- **Receiver Unit:** Processes incoming data, displays warnings on an LCD, and activates a buzzer for critical alerts.

---

## Hardware Requirements
1. **ESP32 Microcontrollers** (2 units: Transmitter and Receiver)
2. **Ultrasonic Sensors** (2 units)
3. **Rain Sensor**
4. **Vibration Sensor**
5. **I2C 16x2 LCD Display**
6. **Active Buzzer**
7. **Power Supply**
8. **Push Button (for manual resets)**

---

## Connections

### Transmitter (Master) ESP32
| Sensor/Component        | Pin Connections          |
|--------------------------|--------------------------|
| **Vibration Sensor**     | Signal: GPIO 4, VCC: 3.3V, GND: GND |
| **Rain Sensor**          | Signal: GPIO 34, VCC: 3.3V, GND: GND |
| **Ultrasonic Sensor 1**  | Trig: GPIO 5, Echo: GPIO 18, VCC: 5V, GND: GND |
| **Ultrasonic Sensor 2**  | Trig: GPIO 21, Echo: GPIO 19, VCC: 5V, GND: GND |

### Receiver (Slave) ESP32
| Sensor/Component       | Pin Connections          |
|-------------------------|--------------------------|
| **I2C LCD Display**     | SDA: GPIO 21, SCL: GPIO 22, VCC: 3.3V, GND: GND |
| **Buzzer**              | Signal: GPIO 4, VCC: 3.3V/5V, GND: GND |
| **Push Button**         | Signal: GPIO 2, Other Pin: GND |

---

## Software Requirements
- **Arduino IDE:** Programming environment for ESP32.
- **ESP-NOW Library:** For wireless communication.
- **LiquidCrystal_I2C Library:** For I2C LCD display.
- **Additional Libraries:** Ensure all relevant sensor and communication libraries are installed.

---

## Usage Instructions

1. **Upload Code:**
   - Flash `master.ino` onto the transmitter ESP32.
   - Flash `slave.ino` onto the receiver ESP32.

2. **Configure MAC Address:**
   - Replace the `broadcastAddress` in `master.ino` with the receiver ESP32's MAC address.

3. **Power On:**
   - Connect both ESP32 boards to their respective power supplies.

4. **Verify Communication:**
   - Monitor the serial output to confirm successful ESP-NOW pairing and data transmission.

5. **Calibration:**
   - Adjust sensor thresholds in the code to suit specific environmental conditions.

---

## Operation

### 1. **Landslide Detection**
- If the vibration sensor detects a significant change, the system:
  - Displays "LANDSLIDE" on the LCD.
  - Activates the buzzer in a distinct pattern.

### 2. **Rain Intensity Monitoring**
- The rain sensor categorizes rainfall into "HIGH," "MEDIUM," "LOW," or "NONE":
  - Displays rain level on the LCD.
  - Activates the buzzer with varying patterns based on intensity.

### 3. **Vehicle Collision Prevention**
- Ultrasonic sensors monitor distances from nearby vehicles.
- If a vehicle is detected within 15 cm on both sensors:
  - Displays "GO SLOW" and "VEHICLE AHEAD" on the LCD.
  - Activates the buzzer in a warning pattern.

### 4. **Connection Timeout**
- If no data is received for 5 seconds:
  - Displays "Waiting for connection" on the LCD.
  - Disables the buzzer to conserve power.

---

## Applications
- **Curved Road Safety:** Enhances driver awareness on sharp curves.
- **Landslide Monitoring:** Provides real-time alerts for potential landslides.
- **Weather Alerts:** Communicates rain intensity and visibility conditions.
- **Traffic Management:** Detects and warns about vehicles ahead.

---

## Future Enhancements
- Integrate GSM/GPRS modules for cloud-based data logging and remote alerts.
- Add solar-powered modules for standalone operation.
- Implement machine learning for advanced landslide prediction.

---

This README provides a complete understanding of the project and ensures ease of setup and deployment for users. If further clarification is needed, feel free to reach out!
