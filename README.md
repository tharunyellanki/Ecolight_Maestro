# Ecolight_Maestro
EcoLight Maestro Focuses on Smart Control of LED Streetlights, Ensuring they Operate Automatically using Preset Time Slots and Real-Time Ambient Light Detection.
## Project Overview  
EcoLight Maestro is a smart energy management system designed on **ARM7TDMI-S (LPC2148)** microcontroller.  
The project automatically controls lights based on environmental conditions, optimizing energy usage and reducing wastage.  
It demonstrates the real-time working of embedded systems for **sustainable smart living**.  

## Features  
•	Automatic switching of lights based on ambient light.  
•	Real-Time Clock (RTC) integration for scheduled control.  
•	Energy-efficient design using ARM7-based microcontroller.  
•	LCD Display for system status & monitoring.  
•	User-friendly configuration and easy expandability.

# Block Diagram
<img width="750" height="450" alt="image" src="https://github.com/user-attachments/assets/e29aa197-0020-4275-af90-915c8d0ec12e" />

## Tech Specifications  
### 🔹 Hardware  
- LPC2148 Microcontroller  
- Light Dependent Resistor (LDR)  
- LEDS(Street Lights)
- 16x2 LCD Display  
- Switch


---
### 🔹 Software  
- Embedded C (Keil µVision)  
- Flash Magic for programming  
- Proteus (for simulation)  

## System Workflow

- Startup → Initialize LCD, RTC, ADC, LEDs, Relay.
- RTC Check → If current time matches schedule → Light ON.
- Else → LDR sensor checks brightness →
     - Dark → Light ON
     - Bright → Light OFF
- LCD Display → Shows RTC time + Light status(ON/OFF).
- User Mode → Press switch → directly update RTC / modify schedules.


  
