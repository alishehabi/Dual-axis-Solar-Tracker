# Autonomous Dual-Axis Solar Tracker

## Overview
This README file provides an overview of the files included.

## Files Included

### 1. Main Report (Solar_Tracker_Report.pdf)
- This is the primary document that details the entire project, including:
  - Objectives
  - Literature review
  - Design
  - Hardware implementation
  - Software implementation
  - Testing
  - Conclusions
  - Further work

### 3. Supporting Material (Supporting Material.pdf)
This document provides an in-depth explanation of the code line by line. It includes:
- Breakdown of the code into its functions, explaining the importance of each
- Rationale behind their implementation
- Logic and reasoning for selecting the Arduino UNO R4 board

### 4. Source Code (SmartSolarTracker.ino)
- This file contains the Arduino source code for the Smart Solar Tracker project.
- Includes the full code with comments that control the hardware to perform its functionality.

### 5. Libraries Included (LibrariesUsed.zip)
- This zip file contains all the libraries used in the source code.
- Ensure that each library zip file is included; otherwise, the code won’t work.

### 6. Component Datasheets (Component Datasheets.zip)
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
The system integrates multiple components to autonomously track and align the solar panel to the optimal position. Refer to the [block diagram](path/to/diagram) for details.

---

## Hardware Setup
1. **Connect the Components:** Refer to the provided schematic ([Circuit Diagram](path/to/circuit)) for detailed wiring.
2. **Position the Sensors:** Place four LDRs to detect light intensity in all directions (North, South, East, West).
3. **Mount the Solar Panel:** Attach the panel securely to the servo motor assembly.

---
