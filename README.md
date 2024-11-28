# Power Optimization with MPPT Using dsPIC30F4013

This project implements an **intelligent power management and optimization system** for a **photovoltaic system**, utilizing Maximum Power Point Tracking (MPPT) techniques. The **dsPIC30F4013 microcontroller** dynamically adjusts the PWM duty cycle to maximize power extraction from the solar panel while monitoring voltage, current, and battery status.

---

## Project Objectives

1. **Maximize solar energy extraction** through dynamic adjustment of the PWM duty cycle using the MPPT algorithm.
2. **Ensure real-time monitoring** of power and battery status, displayed on an LCD screen.
3. Implement a **safe and efficient buck converter system** to regulate power flow between the solar panel, load, and battery.

---

## System Architecture Overview

### 1. Hardware Components

#### **Chopper Circuit (Buck Converter):**
- **MOSFET Switch (IRF540N):** Used for fast and efficient switching in the buck converter.
- **Inductor (470 µH):** Stores energy during the ON state of the MOSFET and releases it during the OFF state to ensure smooth power delivery.
- **Capacitor (470 µF):** Reduces output voltage ripple, ensuring a stable DC voltage.
- **Flyback Diode (1N5408):** Prevents reverse current flow, ensuring energy flow continuity during the MOSFET OFF state.
- **Current Sensor (ACS712):** Measures the current flowing through the load.
- **Voltage Divider Circuit:** Scales down high voltage levels for safe ADC measurement by the microcontroller.

#### **Microcontroller:**
- **dsPIC30F4013:** Acts as the system controller, handling:
  - ADC measurements (voltage and current).
  - PWM generation for the buck converter.
  - MPPT algorithm for power optimization.
  - LCD display interface for real-time feedback.

#### **Power Source:**
- **Photovoltaic Panel:** Provides DC power input to the system.
  - Rated voltage: 18V.
  - Maximum power: 50W.
- **Battery:** Stores excess energy for later use.
  - Nominal voltage: 12V.
  - Maximum voltage: 57.6V (protection threshold).

#### **LCD Display:**
- A 16x2 character LCD module, displaying:
  - Current power output in watts.
  - Battery voltage in real-time.

---

### 2. System Workflow

1. **Input Source:** The photovoltaic panel supplies power to the buck converter.
2. **Power Regulation:**
   - The buck converter regulates the output voltage and current delivered to the battery or load.
   - The dsPIC microcontroller generates PWM signals to control the MOSFET switching.
3. **Sensor Feedback:**
   - Voltage and current sensors provide real-time data to the microcontroller via ADC channels.
4. **Optimization:**
   - The MPPT algorithm continuously adjusts the PWM duty cycle to maximize power extraction.
5. **Data Display:**
   - The LCD screen updates in real-time, showing:
     - Power (in watts).
     - Battery voltage (in volts).
6. **Safety Monitoring:**
   - If the battery voltage exceeds 57.6V, the system reduces the PWM duty cycle to prevent overcharging.

---

## Features

1. **Dynamic Power Optimization:**
   - Real-time MPPT algorithm adjusts PWM signals to track the maximum power point of the solar panel.
2. **Battery Management:**
   - Prevents overcharging by monitoring battery voltage and limiting current flow when thresholds are exceeded.
3. **Real-Time Feedback:**
   - Displays power output and battery status on a user-friendly LCD interface.
4. **Efficient Power Conversion:**
   - Buck converter ensures minimal energy loss during DC-to-DC power regulation.

---

## Software Implementation

### MPPT Algorithm: Perturb and Observe (P&O)
- The MPPT algorithm adjusts the PWM duty cycle by comparing current and previous power values:
  - **If power increases:** Adjust the duty cycle in the same direction.
  - **If power decreases:** Reverse the adjustment direction.

### Microcontroller Configuration
1. **PWM Module:**
   - Timer2 configured to generate PWM signals.
   - OC4 pin used for output control.
2. **ADC Module:**
   - Channels configured for voltage and current measurements.
   - Resolution: 10-bit for precise readings.
3. **LCD Module:**
   - Uses the `flex_lcd.c` library for data display.

---

## Hardware Specifications

### **Chopper Circuit**
| Component         | Specification           |
|-------------------|-------------------------|
| MOSFET Switch     | IRF540N (100V, 33A)    |
| Inductor          | 470 µH                 |
| Capacitor         | 470 µF                 |
| Flyback Diode     | 1N5408 (3A, 50V)       |

### **Microcontroller**
| Feature           | Specification           |
|-------------------|-------------------------|
| Model             | dsPIC30F4013           |
| Clock Speed       | 20 MHz (external)      |
| PWM Output        | Timer2 + OC4           |
| ADC Resolution    | 10-bit                 |

### **Power Source**
| Component         | Specification           |
|-------------------|-------------------------|
| Photovoltaic Panel| 18V, 50W               |
| Battery           | 12V, 57.6V (max)      |

---

## Setup and Usage

1. **Hardware Setup:**
   - Connect the photovoltaic panel to the input of the buck converter.
   - Connect the battery to the output terminals.
   - Ensure proper wiring of the sensors (voltage divider and current sensor) to the dsPIC ADC pins.
   - Power the dsPIC microcontroller using a stable 5V supply.

2. **Software Configuration:**
   - Load the provided source code onto the dsPIC30F4013 using MPLAB IDE.
   - Configure fuses: `NOWDT`, `NOPROTECT`, `NOPUT`.

3. **Operation:**
   - Power on the system.
   - Observe real-time data on the LCD screen.
   - Adjust the system parameters (if necessary) based on the solar panel and battery ratings.

---

## Results

1. **Real-Time Data:**
   - Display of power output and battery status on the LCD.
2. **Optimized Energy Harvesting:**
   - Maximum power extracted from the solar panel under varying conditions.
3. **Safe Operation:**
   - Battery protected from overcharging through automated control.

---

## Future Improvements

- **Wireless Monitoring:** Add a Bluetooth or Wi-Fi module for remote monitoring.
- **Data Logging:** Integrate an SD card module to store historical data.
- **Advanced MPPT Techniques:** Implement algorithms such as Incremental Conductance for improved efficiency.

---

## Author

- **Name:** Mohamed Rafik Mokrani  
- **Year of Completion:** 2024  
- **Language:** C for dsPIC Microcontroller

---

**Note:** This project demonstrates the integration of power electronics and embedded systems for renewable energy optimization.
