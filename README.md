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
- KeyPad Matrix(4x4)


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
## Hardware Setup (Proteus)
<img width="1180" height="834" alt="image" src="https://github.com/user-attachments/assets/5b9068df-3f85-487c-8ccd-d1d4f8b16f9e" />

## Output (Proteus)
<img width="1185" height="833" alt="image" src="https://github.com/user-attachments/assets/87b92457-e2a1-47a6-b20c-b21411a98fe5" />
<img width="1179" height="831" alt="image" src="https://github.com/user-attachments/assets/225d7db1-9818-4581-b3ac-1d2f1f8ad4e8" />
<img width="1183" height="834" alt="image" src="https://github.com/user-attachments/assets/cbb7f341-f21f-4acb-aa36-c5c3d19faff9" />

## 📂 Project Structure
ECOlight-Maestro/
│── README.md                 # Project documentation
│
│── adc.c                     # ADC (LDR sensor) source file
│── adc.h                     # ADC function prototypes
│── adc_defines.h             # ADC related macros & definitions
│
│── defines.h                 # Global macros & constants
│
│── delay.c                   # Delay function implementations
│── delay.h                   # Delay function prototypes
│
│── edit_rtc.c                # RTC edit/update logic (time set/change)
│── edit_rtc.h                # RTC edit function prototypes
│
│── kpm.c                     # Keypad module implementation
│── kpm.h                     # Keypad module prototypes
│── kpm_defines.h             # Keypad-related macros
│
│── lcd.c                     # LCD driver implementation
│── lcd.h                     # LCD function prototypes
│── lcd_defines.h             # LCD control macros
│
│── main_file.c               # Main application logic (system workflow)
│
│── pin_connect_block.c       # Pin configuration routines
│── pin_connect_block.h       # Pin definitions & macros
│
│── rtc.c                     # RTC (DS1307/DS3231) functions
│── rtc.h                     # RTC interface prototypes
│── rtc_defines.h             # RTC register addresses & macros
│
│── types.h                   # Common typedefs (u8, u16, etc.)


  
