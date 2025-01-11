# Autonomous Dual-Axis Solar Tracker

## Overview
This README file provides an overview of the files included.

## Files Included

### 1. Source Code (SmartSolarTracker.ino)
- This file contains the Arduino source code for the Smart Solar Tracker project.
- Includes the full code with comments that control the hardware to perform its functionality.

### 2. Libraries Included (LibrariesUsed.zip)
- This zip file contains all the libraries used in the source code.
- Ensure that each library zip file is included; otherwise, the code won’t work.

### 3. Component Datasheets (Component Datasheets.zip)
- This zip file contains datasheets for all components used in the project, providing technical details and specifications.

---

## Features
- **Dual-Axis Tracking:** Adjusts both horizontal and vertical angles of the solar panel.
- **Real-Time Light Detection:** Utilizes Light Dependent Resistors (LDRs) to track the sun's position.
- **Power Management:** Self-sustaining system with solar-powered battery charging.
- **User Interface:** Real-time data display (voltage, current, power) on an LCD.
- **Cost-Effective Design:** Prototype developed for under **£58** using widely available components.

---

## System Design
### Components
- **Arduino UNO R4 Wi-Fi**: Central microcontroller.
- **SG90 Servo Motors**: Control horizontal and vertical panel movement.
- **Light Dependent Resistors (LDRs)**: Detect sunlight intensity in four cardinal directions.
- **LCD Display**: Displays real-time electrical output.
- **Solar Panel (5.5V, 1W)**: Generates power for the system.
- **Solar Power Management Module**: Regulates and stores energy in a battery.
- **INA219 Current Sensor**: Measures real-time voltage, current, and power.

### Block Diagram
The system integrates multiple components to autonomously track and align the solar panel to the optimal position. 

<img width="548" alt="Screenshot 2025-01-11 at 18 00 12" src="https://github.com/user-attachments/assets/35af153e-6980-44c6-881a-916d9aaf6938" />


---

## Hardware Setup
1. **Connect the Components:** Refer to the provided schematic for detailed wiring.
<img width="730" alt="Screenshot 2025-01-11 at 17 56 59" src="https://github.com/user-attachments/assets/3df75761-e3a2-441d-b54c-f5133e185631" />

<img width="469" alt="Screenshot 2025-01-11 at 18 00 39" src="https://github.com/user-attachments/assets/7830cef7-f1a4-44eb-9096-1f530025902d" />

2. **Position the Sensors:** Place four LDRs to detect light intensity in all directions (North, South, East, West).
3. **Mount the Solar Panel:** Attach the panel securely to the servo motor assembly.

---
## Testing and Evaluation
### Static vs. Dynamic Performance
- **Static Panel Efficiency:** ~20%.
- **Dynamic Panel Efficiency:** ~34.6% higher power output compared to static panels.

### Panel Alignment Accuracy
- Average deviation: **2.2°**
- Percentage difference: **2.51%**

#### Testing Process
1. **Power Output Test:**
   - Simulate sunlight at different angles and compare power output between static and dynamic panels.
   - Measure voltage and current with the INA219 sensor and calculate power using \( P = IV \).
2. **Panel Alignment Test:**
   - Measure alignment of the panel with respect to the light source across various angles.
   - Ensure minimal deviation between the panel and light angles.
---

## Future Improvements
1. **Machine Learning Integration:**
   - Implement predictive algorithms to optimize panel movement based on historical sun movement patterns.
2. **Enhanced Solar Panels:**
   - Upgrade to bifacial panels to capture sunlight on both sides, increasing energy output.
3. **Advanced Cooling Mechanisms:**
   - Introduce passive or active cooling systems to prevent overheating, improving efficiency.
4. **Remote Monitoring:**
   - Add IoT capabilities for real-time monitoring and control via a mobile app or web dashboard.
5. **Energy Storage Optimization:**
   - Integrate more efficient battery systems and management to enhance energy storage and usage.
