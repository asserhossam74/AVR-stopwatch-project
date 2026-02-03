# Dual-Mode Stopwatch System

A versatile digital stopwatch with increment and countdown capabilities, built on ATmega32 microcontroller. This embedded system demonstrates advanced timer management, multiplexed display control, interrupt-driven architecture, and real-time user interaction.

> **Note:** This project was developed as part of an embedded systems interfacing course at Edges For Training under the guidance of instructor Mohamed Tarek.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Tech Stack](#tech-stack)
- [Architecture](#architecture)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
- [Screenshots](#screenshots)
- [Connect With Me](#connect-with-me)

---

## Overview

This project implements a comprehensive dual-mode stopwatch system using the ATmega32 microcontroller. The system features two distinct operational modes: Increment Mode for traditional stopwatch functionality and Countdown Mode for timer-based applications with alarm notification.

The stopwatch utilizes six multiplexed seven-segment displays (common anode configuration) to present time information with high precision, while providing intuitive control through ten dedicated push buttons and visual mode indicators via LED feedback.

**Core Capabilities:**
- Dual operational modes with seamless switching
- Precise timekeeping using AVR hardware timers
- Multiplexed seven-segment display management
- Interrupt-driven button handling for responsive user interaction
- Real-time system control and status indication

**Key Learning Objectives:**
- Timer/Counter peripheral configuration and management
- Display multiplexing techniques for resource optimization
- External interrupt handling and debouncing strategies
- State machine implementation for mode management
- GPIO peripheral interfacing and control
- Bare-metal embedded C programming
- Real-time embedded system behavior

---

## Features

### Operational Modes

**Increment Mode (Counting Up)**
- Continuous counting from 00:00:00 upward
- Unlimited counting duration
- Precise second-by-second incrementation
- Default operational mode on system startup

**Countdown Mode (Counting Down)**
- User-configurable countdown timer
- Adjustable hours, minutes, and seconds
- Alarm notification upon countdown completion
- Visual and audible alert system

### Control Functions

**Time Management**
- **Reset Function**: Clears current time and returns to initial state (00:00:00)
- **Pause Function**: Halts time progression while maintaining current value
- **Resume Function**: Continues counting from paused state
- **Adjust Function**: Allows real-time modification of countdown parameters

**System Control**
- **Mode Toggle**: Seamless switching between increment and countdown modes
- **Visual Mode Indication**: Dedicated LEDs display current operational mode
- **Button-Based Interface**: Ten dedicated push buttons for comprehensive control

### Technical Features

- **Multiplexed Display**: Efficient control of six seven-segment displays
- **Interrupt-Driven Architecture**: Responsive button handling and timer management
- **Accurate Timekeeping**: Hardware timer-based precision
- **Low-Level Hardware Control**: Direct register manipulation for optimal performance
- **Modular Code Structure**: Organized driver implementation for maintainability

---

## Tech Stack

### Software Components

| Component | Technology |
|-----------|-----------|
| **Language** | C (Embedded C) |
| **Microcontroller** | ATmega32 |
| **IDE** | Eclipse CDT |
| **Compiler** | AVR-GCC |
| **Programmer** | AVRDUDE |
| **Simulation** | Proteus Design Suite |
| **Approach** | Bare-metal programming |

### Development Tools

**Proteus Design Suite**
- Circuit design and schematic capture
- Virtual testing environment
- Real-time simulation with microcontroller
- Component library for AVR and peripherals
- Debugging capabilities with breakpoints

**Eclipse CDT**
- Full-featured C/C++ development environment
- AVR plugin integration
- Code completion and syntax highlighting
- Build automation with makefiles
- Integration with AVR-GCC toolchain

### Hardware Components

| Component | Specification | Quantity |
|-----------|--------------|----------|
| **Microcontroller** | ATmega32 | 1 |
| **Display** | Seven-segment (common anode) | 6 |
| **Input Buttons** | Push buttons (active low) | 10 |
| **Mode Indicators** | LEDs | 2 |
| **Support Components** | Resistors, capacitors, wiring | As required |

### Button Configuration

| Button | Function | Description |
|--------|----------|-------------|
| **Button 0** | Reset | Clears time and returns to 00:00:00 |
| **Button 1** | Pause | Halts time progression |
| **Button 2** | Resume | Continues from paused state |
| **Button 3** | Mode Toggle | Switches between increment/countdown |
| **Buttons 4-9** | Time Adjust | Increment hours, minutes, seconds (up/down) |

---

## Architecture

The system employs a layered bare-metal architecture with clear separation between hardware abstraction and application logic.

```
┌─────────────────────────────────────────────────────────┐
│              Application Layer (main.c)                 │
│  ┌─────────────────┐  ┌──────────────────────────┐    │
│  │  Mode Manager   │  │  Time Management Logic   │    │
│  └─────────────────┘  └──────────────────────────┘    │
├─────────────────────────────────────────────────────────┤
│                    Driver Layer                         │
│  ┌──────────┐ ┌──────────┐ ┌────────┐ ┌──────────┐   │
│  │  Timer   │ │ 7-Segment│ │ Button │ │   LED    │   │
│  │  Driver  │ │  Driver  │ │ Driver │ │  Driver  │   │
│  └──────────┘ └──────────┘ └────────┘ └──────────┘   │
├─────────────────────────────────────────────────────────┤
│            Hardware Abstraction Layer (HAL)             │
│  ┌──────────────────────────────────────────────────┐  │
│  │     ATmega32 Register Interface Layer            │  │
│  └──────────────────────────────────────────────────┘  │
├─────────────────────────────────────────────────────────┤
│               ATmega32 Hardware Peripherals             │
│  Timer1 | GPIO Ports | External Interrupts | ADC        │
└─────────────────────────────────────────────────────────┘
```

### Key Architectural Components

**Timer Management**
- Timer1 configured in CTC (Clear Timer on Compare) mode
- 1-second interrupt generation for time tracking
- Prescaler configuration for accurate timing

**Display Multiplexing**
- Time-division multiplexing of six seven-segment displays
- Rapid sequential activation for persistence of vision
- Common anode configuration with current limiting

**Interrupt Handling**
- External interrupts for button press detection
- Timer interrupt for periodic time updates
- Interrupt service routines with minimal execution time

**Mode Management**
- State machine implementation for mode transitions
- LED-based visual feedback for current mode
- Persistent state maintenance across operations

---

## Project Structure

```
interfacing_1_project_stopwatch/
│
├── .metadata/                        # Eclipse workspace metadata
│
├── stop_watch.c                      # Main application source code
│   ├── Timer1 configuration (CTC mode)
│   ├── Seven-segment multiplexing logic
│   ├── Button interrupt handlers
│   └── Dual-mode state machine
│
├── project_code.txt                  # Code documentation/backup
│
├── stop_watch_simulation.pdsprj     # Proteus simulation project
├── Last Loaded stop_watch_simulation.pdsbak  # Proteus backup
│
├── Screenshots/                      # Project documentation images
│   └── image-6.png                  # Application interface
│
├── .gitignore                       # Git ignore rules for AVR projects
│
└── README.md                        # Project documentation
```

### File Descriptions

**Source Code**
- `stop_watch.c`: Complete implementation including timer configuration, display multiplexing, interrupt service routines, and dual-mode logic (Increment/Countdown)

**Simulation Files**
- `stop_watch_simulation.pdsprj`: Proteus Design Suite project for circuit simulation and testing
- Allows testing without physical hardware
- Includes complete circuit schematic with ATmega32, displays, and buttons

**Documentation**
- Multiple screenshot images documenting different aspects and modes
- `project_code.txt`: Additional code documentation or configuration details

---

## Getting Started

### Prerequisites

**Software Requirements**
- Eclipse CDT with AVR plugin installed
- AVR-GCC toolchain (version 5.4.0 or higher)
- AVRDUDE programmer software (version 6.3 or higher)
- AVR Libc library

**Hardware Requirements**
- ATmega32 microcontroller development board
- USB programmer (USBasp, Arduino as ISP, or compatible)
- Six common-anode seven-segment displays
- Ten push buttons (normally open, active low)
- Two LEDs for mode indication
- Current limiting resistors (220Ω for LEDs, appropriate values for seven-segment displays)
- Power supply (5V DC regulated)
- Breadboard and jumper wires (for prototyping)

**Optional Components**
- Buzzer for alarm functionality
- Capacitors for button debouncing (100nF ceramic)
- Pull-up resistors for buttons (10kΩ)

### Installation & Build

#### Step 1: Open Project in Eclipse

```bash
# Launch Eclipse CDT
# Navigate to: File → Import → Existing Projects into Workspace
# Browse to: interfacing_1_project_stopwatch/
# Click Finish
```

#### Step 2: Configure Toolchain

**Configure Project Properties:**
1. Right-click project → Properties
2. C/C++ Build → Settings
3. AVR Compiler → Symbols
   - Add: F_CPU=16000000UL (for 16 MHz crystal)
4. AVR Compiler → Optimization
   - Set optimization level: -O2 (recommended)
5. AVR Linker → General
   - Set MCU type: ATmega32

#### Step 3: Build Project

```bash
# In Eclipse: Project → Build Project
# Keyboard shortcut: Ctrl+B
# Build output will be in: Debug/project.hex
```

#### Step 4: Flash to Microcontroller

**Using AVRDUDE with USBasp:**

```bash
# Navigate to Debug directory
cd interfacing_1_project_stopwatch/Debug/

# Flash the HEX file to ATmega32
avrdude -c usbasp -p m32 -U flash:w:project.hex

# Verify flash operation
avrdude -c usbasp -p m32 -U flash:v:project.hex

# Set fuse bits for 16 MHz external crystal (if needed)
avrdude -c usbasp -p m32 -U lfuse:w:0xff:m -U hfuse:w:0xc9:m
```

**Parameter Explanation:**
- `-c usbasp`: Programmer type (change for your programmer)
- `-p m32`: MCU part number (ATmega32)
- `-U flash:w:file.hex`: Write operation to flash memory
- `-U flash:v:file.hex`: Verify operation

**Alternative Programmers:**

```bash
# Using Arduino as ISP
avrdude -c arduino -P /dev/ttyUSB0 -b 19200 -p m32 -U flash:w:project.hex

# Using AVR Dragon
avrdude -c dragon_isp -P usb -p m32 -U flash:w:project.hex
```

### Hardware Setup

**Pin Configuration:**

| Component | ATmega32 Port/Pin | Notes |
|-----------|------------------|-------|
| Seven-segment 1-6 (data) | PORTA (PA0-PA6) | BCD to 7-segment decoder |
| Seven-segment enable | PORTB (PB0-PB5) | Multiplexing control |
| Button 0 (Reset) | PORTD (PD2/INT0) | External interrupt |
| Button 1 (Pause) | PORTD (PD3/INT1) | External interrupt |
| Button 2 (Resume) | PORTB (PB2/INT2) | External interrupt |
| Buttons 3-9 | PORTC (PC0-PC6) | GPIO polling |
| LED Increment Mode | PORTD (PD6) | Active high |
| LED Countdown Mode | PORTD (PD7) | Active high |

**Wiring Instructions:**
1. Connect all grounds together (microcontroller, displays, buttons)
2. Wire seven-segment displays in common-anode configuration
3. Connect current-limiting resistors to each segment (typically 220Ω)
4. Wire buttons between input pins and ground (active low)
5. Add pull-up resistors to button inputs (10kΩ to Vcc)
6. Connect mode indicator LEDs with current-limiting resistors (220Ω)
7. Ensure stable 5V power supply with adequate current capacity

### Running the Project

**Initial Power-On:**
1. Power on the ATmega32 development board
2. Verify all seven-segment displays show "00:00:00"
3. Confirm Increment Mode LED is illuminated
4. Test button responsiveness

**Basic Operation:**
1. **Increment Mode** (default on startup):
   - Press Resume button to start counting
   - Press Pause button to halt
   - Press Reset button to clear to 00:00:00
   
2. **Countdown Mode**:
   - Press Mode Toggle button to switch modes
   - Use adjustment buttons to set desired time
   - Press Resume button to start countdown
   - Alarm triggers when timer reaches 00:00:00

**Troubleshooting:**
- If display shows nothing: Check power supply and segment connections
- If time doesn't increment: Verify crystal oscillator (16 MHz) installation
- If buttons unresponsive: Check pull-up resistors and interrupt configuration
- If display flickers: Adjust multiplexing frequency in code

---

## Simulation

This project includes a complete **Proteus Design Suite** simulation for testing and validation without physical hardware.

### Simulation Files

- **stop_watch_simulation.pdsprj**: Main Proteus project file
- Contains complete circuit schematic with ATmega32, seven-segment displays, push buttons, and LEDs
- Allows full functional testing of the stopwatch system

### Running the Simulation

1. Open `stop_watch_simulation.pdsprj` in Proteus Design Suite (version 8.0 or higher)
2. Load the compiled HEX file into the ATmega32 component
3. Run the simulation using the play button
4. Interact with virtual buttons to test functionality
5. Observe seven-segment displays and LED indicators

**Note**: The Proteus simulation provides an accurate representation of the physical system and is invaluable for development and testing.

---

## Screenshots

### Application Interface
![Application Interface](image-6.png)
*Control interface and display configuration*

## Connect With Me

**Asser Elhosary**  
Embedded Systems Developer

[LinkedIn](https://www.linkedin.com/in/asser-elhosary) | [GitHub](https://github.com/asserhossam74)

For inquiries, collaboration opportunities, or technical discussions, feel free to reach out via LinkedIn.

---

## Acknowledgments

This project was developed as part of the Embedded Systems Interfacing course at **Edges For Training**.

Special thanks to **Instructor Mohamed Tarek** for valuable guidance, technical mentorship, and support throughout the development process.
