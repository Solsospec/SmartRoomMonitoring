# SmartRoomMonitoring

## Overview
This project implements an energy-conservative, automatic power management system using an Arduino. It counts the number of individuals in a room via two-way IR sensor detection and controls power (through a relay) based on occupancy. Designed for applications in offices, schools, hospitals, and homes, this system offers a practical solution to reduce energy waste.

## Features
- **Two-Way Occupant Counter:** Uses two IR sensors with interrupt-driven detection to accurately determine entry and exit.
- **Automatic Power Control:** Switches power on or off based on the real-time occupancy count.
- **Dual LCD Displays:** Provides immediate visual feedback on room occupancy and current power status.
- **Energy Savings:** Demonstrated reduction in energy consumption through intelligent power management.
- **Future Enhancements:** Potential integration of AI for predictive occupancy analytics and further optimization.

## Components
- Arduino Uno
- 2 x IR Sensors (with INPUT_PULLUP configuration)
- 1 x Relay Module
- 2 x 16x2 I2C LCD Displays (addresses 0x27 and 0x20)
- *(Optional)* HLK-LD2410C human presence radar sensor for extended functionality

## Wiring and Setup
- **IR Sensors:** Connect to digital pins 2 and 3.
- **Relay:** Connect to digital pin 8.
- **LCD Displays:** Connect via the I2C interface; ensure correct addresses (0x27 and 0x20).

## Code Structure
- **Interrupt Service Routines (ISRs):** Efficiently handle sensor triggers for accurate occupancy counting.
- **Main Loop:** Monitors sensor triggers, updates the occupancy count, and manages the relay state.
- **Helper Functions:** 
  - `updateDisplay()` – Refreshes LCD output based on current room status.
  - `initLCD()` – Configures and initializes the LCDs.

## Usage
1. Wire the components as described above.
2. Upload the Arduino sketch to your board.
3. Observe the LCD displays for real-time updates on occupancy and power status.

## Future Enhancements
- **AI Integration:** Explore using machine learning models to predict occupancy patterns and further optimize energy usage.
- **Expanded Sensor Array:** Incorporate additional sensors (e.g., radar-based) to enhance detection accuracy.

## License
This project is open source under the MIT License. See the LICENSE file for details.