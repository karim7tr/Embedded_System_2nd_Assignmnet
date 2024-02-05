# README

## Autonomous Ground Vehicle Control System

This firmware is designed for an autonomous ground vehicle to navigate a simple racetrack. It includes features such as motor control, lights management, battery sensing, and UART communication.

### Table of Contents

1. [Introduction](#introduction)
2. [Firmware Overview](#firmware-overview)
3. [Requirements](#requirements)
4. [Pin Mapping](#pin-mapping)
5. [Getting Started](#getting-started)
6. [UART Communication](#uart-communication)
7. [Motor Control](#motor-control)
8. [Lights Management](#lights-management)
9. [Battery Sensing](#battery-sensing)
10. [Contributing](#contributing)
11. [License](#license)

---

### Introduction

The goal of this firmware is to implement a basic control system for an autonomous ground vehicle. It operates in two main states: "Wait for start" and "Moving." The control loop runs at a frequency of 1 kHz, ensuring precise motor PWM updates and IR sensor readings.

### Firmware Overview

The firmware is written in C and uses several modules, including Timer, Interrupt, UART, PWM, ADC, Algorithm, IO, and Action. The main loop handles the states, motor control, lights, battery sensing, and UART communication.

### Requirements

The main loop requirements are as follows:

- The control loop runs at 1 kHz.
- Motor PWM is updated at 1 kHz.
- IR sensor is read at 1 kHz.
- Initial state is "Wait for start."
- Button RE8 transitions the state to "Moving" and back to "Wait for start" on a second press.
- Motor PWM values are computed based on surge and yaw_rate signals.
- LED A0 blinks at 1 Hz in both states.

For detailed requirements, refer to the provided specifications.

### Pin Mapping

- RB8: Left side lights
- RF1: Right-side lights
- RF0: Brakes
- RG1: Low intensity lights
- RA7: Beam headlights
- AN11: Battery sensing
- RD1/RP65: Left PWM backward motion
- RD2/RP66: Left PWM forward motion
- RD3/RP67: Right PWM backward motion
- RD4/RP68: Right PWM forward motion
- AN14: IR sensor voltage
- RB9: IR sensor enable
- RD0/RP64: UART TX
- RD11/RPI75: UART RX

For detailed hardware setup, refer to the provided specifications.

### Getting Started

1. Clone the repository.
2. Open the project in your preferred development environment.
3. Ensure proper hardware connections as per the provided pin mapping.
4. Configure the UART module for communication.
5. Build and program the firmware to the target microcontroller.

### UART Communication

The UART module is used for data logging and command interface. The microcontroller sends the following messages at specific frequencies:

- `$MBATT,v_batt*`: Sensed battery voltage at 1 Hz.
- `$MDIST,distance*`: Sensed distance at 10 Hz.
- `$MPWM,dc1,dc2,dc3,dc4*`: PWM duty cycles at 10 Hz.

The microcontroller receives the following message:

- `$PCTH,minth,maxth*`: Set MINTH and MAXTH thresholds.

Ensure proper UART baud rate configuration to avoid message loss.

### Motor Control

Motor control is implemented based on surge and yaw_rate signals. PWM signals are generated for left and right wheels, controlling forward and backward motion.

### Lights Management

Lights are controlled based on the state of the vehicle. Different light configurations are set for "Wait for start" and "Moving" states, considering forward motion, turning, and stationary conditions.

### Battery Sensing

Battery voltage is sensed using the AN11 pin, and the value is sent to the PC at 1 Hz.

### Contributing

Contributions are welcome. Please follow the coding standards, and create a pull request with a clear description of the changes.

### License

This firmware is licensed under the [MIT License](LICENSE). Feel free to use, modify, and distribute it.
