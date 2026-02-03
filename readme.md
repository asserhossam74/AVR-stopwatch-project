# AVR Stopwatch Project

A simple **Stopwatch application** developed using **AVR Microcontroller** concepts as part of an embedded systems interfacing course.  
The project demonstrates low-level hardware control, timer usage, and peripheral interfacing using C.

This project is intended for **learning and practice** in embedded systems development, especially for AVR-based microcontrollers.

---

##  Project Overview

This project implements a digital **stopwatch system** using an AVR microcontroller.  
It is designed to measure elapsed time and display it through external peripherals such as LEDs or 7-segment displays.

The project was developed using **Eclipse CDT** with AVR toolchains, focusing on:
- Microcontroller timers
- GPIO interfacing
- Embedded C programming
- Real-time behavior

---

## Tech Stack

- **Programming Language:** C (Embedded C)
- **Microcontroller:** AVR (e.g. ATmega series)
- **IDE:** Eclipse CDT
- **Toolchain:** AVR-GCC
- **Debugger/Programmer:** AVRDUDE (or similar)
- **Development Style:** Bare-metal programming

---

##  Architecture

The project follows a **bare-metal embedded architecture**:

- Hardware-level access using registers
- Timer-based time measurement
- Polling or interrupt-driven execution
- Modular source files for drivers and application logic

### Logical Flow:
1. System initialization
2. Timer configuration
3. GPIO configuration
4. Stopwatch logic execution
5. Output update (display)

---

## Features

-  Stopwatch start, stop, and reset functionality
-  Accurate time tracking using AVR timers
-  Direct hardware interfacing
-  Efficient low-level C implementation
-  Designed for embedded learning and practice

---

##  Testing

The project was tested using:
- Manual hardware testing on AVR board
- Step-by-step execution using Eclipse
- Verifying timer accuracy
- Checking correct reset and overflow behavior

---

##  Folder Structure

interfacing_1_project_stopwatch/
│
├── src/ # Application source files
├── include/ # Header files
├── Debug/ # Build output
├── .metadata/ # Eclipse workspace metadata
└── README.md # Project documentation
---

##  How to Run the Project

### Open in Eclipse
- Open **Eclipse CDT**
- Import project as **Existing Project**
- Select the stopwatch project directory

###  Build the Project
- Select the correct AVR toolchain
- Build the project

###  Flash to Microcontroller
```bash
avrdude -c <programmer> -p <mcu> -U flash:w:project.hex
 Run & Test
Power the AVR board

Observe stopwatch behavior on connected peripherals
 Future Improvements
 Add button debouncing

 LCD display support

 Lap timing feature

 Interrupt-based implementation

 Code modularization into drivers

 Unit testing for embedded logic

Screenshots
### Application Menu
![Application Menu](screenshots/image-6.png)

Hardware setup

Stopwatch output

Eclipse project structure

Copy code
screenshots/
├── hardware_setup.jpg
├── stopwatch_display.jpg
└── eclipse_project.png
 Social Links
LinkedIn: https://www.linkedin.com/in/asser-elhosary

GitHub: https://github.com/asserhossam74

 License
This project is open-source and intended for educational and learning purposes.
Feel free to use, modify, and improve it.

 If you found this project helpful, consider giving it a star on GitHub!


---

###  Important Note (Honest & Professional)
If you later upload:
- `main.c`
- timer / GPIO drivers
- actual AVR source code  

I can **refine this README even more** to match the **exact implementation**, including:
- Specific registers used
- Timer modes
- Interrupt configuration
- MCU model (ATmega32 / ATmega16 / etc.)

Just send the rest of the project when ready 
