# B31DG-Assignment-1

## Project Overview
This project is designed for waveform generation using the **ESP32 microcontroller**. The generated waveform consists of **DATA (Signal A) and SYNC (Signal B) outputs**, where:
- The **DATA signal** is a modulated pulse train based on user-defined parameters.
- The **SYNC signal** serves as a reference trigger.

The ESP32 firmware is written in **C** and is structured for real-time waveform generation.

---

## Hardware Requirements
To implement this project, you will need:
- **ESP32 development board**
- **Push Buttons** (Connected to GPIOs for mode selection)
- **LEDs** (Optional for debugging)
- **Oscilloscope** (For signal visualization)
- **Resistors** (Appropriate values to limit current)

---

## Software Requirements
To compile and upload the firmware, ensure you have:
- **Arduino IDE** with ESP32 support installed
- **ESP-IDF Framework** (For low-level ESP32 development)
- **Git** (For version control and collaboration)
- **Python** (For simulation if needed)

---

## Features & Functionalities
- **Two operating modes:**
  - **Normal mode:** Generates waveform with increasing pulse widths.
  - **Alternative mode:** Generates waveform with decreasing pulse widths.
- **Push-button control:**
  - Button 1: Toggles waveform output ON/OFF.
  - Button 2: Switches between Normal and Alternative mode.
- **Real-time signal synchronization using SYNC pulse.**

---

## Installation & Usage

### 1️⃣ **Setup ESP32 Development Environment**
1. Install **Arduino IDE** and configure it for **ESP32**.
2. Install the necessary ESP32 **board support package**.
3. Clone this GitHub repository:
   ```bash
   git clone https://github.com/DMF-GHF/B31DG-Assignment-1.git
   cd B31DG-Assignment-1
