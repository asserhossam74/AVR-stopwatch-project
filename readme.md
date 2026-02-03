# AVR Stopwatch Project

A digital stopwatch application built with AVR microcontroller, demonstrating embedded systems concepts including timer peripherals, GPIO interfacing, and bare-metal C programming.

> **Note:** This project was developed as part of an embedded systems interfacing course for learning and practice purposes.

---

##  Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Tech Stack](#tech-stack)
- [Architecture](#architecture)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Testing](#testing)
- [Future Improvements](#future-improvements)
- [Screenshots](#screenshots)
- [Connect With Me](#connect-with-me)
- [License](#license)

---

##  Overview

This project implements a digital stopwatch system using an AVR microcontroller. It measures elapsed time with precision and displays the output through external peripherals such as LEDs or 7-segment displays.

**Key Learning Objectives:**
- Hardware timer configuration and usage
- GPIO peripheral interfacing
- Bare-metal embedded C programming
- Real-time system behavior
- Low-level register manipulation

---

##  Features

-  **Start/Stop/Reset** functionality
-  **Accurate timekeeping** using AVR hardware timers
-  **Direct hardware interfacing** with no abstraction layers
-  **Efficient implementation** in embedded C
-  **Educational focus** with clean, readable code

---

##  Tech Stack

| Component | Technology |
|-----------|-----------|
| **Language** | C (Embedded C) |
| **Microcontroller** | AVR (ATmega series) |
| **IDE** | Eclipse CDT |
| **Compiler** | AVR-GCC |
| **Programmer** | AVRDUDE |
| **Approach** | Bare-metal programming |

---

##  Architecture

The project follows a **bare-metal embedded architecture** with direct hardware access:

```
┌─────────────────────────────────────┐
│     Application Layer (main.c)      │
├─────────────────────────────────────┤
│  Timer Driver │  GPIO Driver  │ UI  │
├─────────────────────────────────────┤
│      AVR Hardware Registers         │
├─────────────────────────────────────┤
│   ATmega Microcontroller Hardware   │
└─────────────────────────────────────┘
```


**Key Components:**
- Hardware-level register access
- Timer-based precise time measurement
- Polling or interrupt-driven execution model
- Modular driver architecture

---

## 📁 Project Structure

```
interfacing_1_project_stopwatch/
│
├── src/                    # Application source files
│   ├── main.c             # Main application logic
│   └── drivers/           # Hardware driver modules
│
├── include/               # Header files
│   └── *.h               # Driver and application headers
│
├── Debug/                 # Build output directory
│   └── *.hex             # Compiled firmware
│
├── .metadata/            # Eclipse workspace metadata
│
├── screenshots/          # Project images
│   └── image-6.png      # Application interface
│
└── README.md            # Project documentation
```

---

## 🚀 Getting Started

### Prerequisites

- Eclipse CDT with AVR plugin
- AVR-GCC toolchain
- AVRDUDE (or compatible programmer)
- AVR development board (ATmega series)
- USB programmer (USBasp, Arduino as ISP, etc.)

### Installation & Build

#### 1️⃣ Open Project in Eclipse

```bash
# Open Eclipse CDT
# File → Import → Existing Projects into Workspace
# Select the project directory
```

####  Configure Toolchain

- Verify AVR-GCC is selected as the toolchain
- Set correct MCU type (e.g., ATmega32)
- Configure optimization level if needed

####  Build Project

```bash
# In Eclipse: Project → Build Project
# Or use keyboard shortcut: Ctrl+B
```

####  Flash to Microcontroller

```bash
# Using AVRDUDE (adjust parameters for your setup)
avrdude -c usbasp -p m32 -U flash:w:Debug/project.hex

# Parameters:
# -c: Programmer type (usbasp, arduino, etc.)
# -p: MCU model (m32 for ATmega32)
# -U: Memory operation (flash:w for write)
```

### Running the Project

1. **Power on** the AVR development board
2. **Connect display** (7-segment or LED indicators)
3. **Connect control buttons** (Start, Stop, Reset)
4. **Observe** stopwatch behavior on output peripherals
5. **Test** all functions (start, stop, reset)

---

##  Testing

The project was validated through:

-  **Manual hardware testing** on AVR development board
-  **Step-by-step debugging** in Eclipse CDT
-  **Timer accuracy verification** against reference timing
-  **Boundary testing** (reset, overflow behavior)
-  **Integration testing** with display peripherals

### Test Cases

| Test Case | Expected Result | Status |
|-----------|----------------|--------|
| Start stopwatch | Counter begins incrementing | ✅ Pass |
| Stop stopwatch | Counter pauses | ✅ Pass |
| Reset stopwatch | Counter returns to 00:00 | ✅ Pass |
| Timer overflow | Proper rollover handling | ✅ Pass |

---

##  Future Improvements

- [ ] **Button debouncing** for cleaner input handling
- [ ] **LCD display support** (16x2 character LCD)
- [ ] **Lap timing feature** with memory
- [ ] **Interrupt-driven architecture** for better efficiency
- [ ] **Modular driver library** for reusability
- [ ] **Unit testing framework** for embedded logic
- [ ] **Power optimization** (sleep modes)
- [ ] **EEPROM storage** for lap times

---

## 📸 Screenshots

### Application Interface
![Application Menu](screenshots/image-6.png)
*Stopwatch control interface*

---

## 🤝 Connect With Me

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/asser-elhosary)
[![GitHub](https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white)](https://github.com/asserhossam74)

**Asser Elhosary**  
Embedded Systems Developer
