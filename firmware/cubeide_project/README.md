# Motor Control System (PWM & Direction Reversal)

## Project Overview

This project is a simple motor control system implemented on an STM32 microcontroller. It uses **Pulse Width Modulation (PWM)** to control the speed of three motors, with the ability to **reverse the direction** of the motors at different speeds. The motor speeds are controlled through timers (TIM1, TIM2, TIM3) and PWM signals. The project is implemented using the STM32 HAL library with STM32CubeIDE.

## Features

- **PWM-based motor speed control**: The project allows you to control the speed of three motors using PWM.
- **Direction reversal**: The motors can change direction by adjusting the PWM values and modifying GPIO pins.
- **Timer-based control**: The motors are controlled via STM32's timers, which allow for precise frequency generation and duty cycle adjustments.

## Hardware

- **STM32 Microcontroller** (e.g., STM32F103 series)
- **Three DC motors** connected to the corresponding PWM outputs on the microcontroller
- **GPIO pins** configured for controlling the direction of the motors
- **Power supply** for the motors (via motor drivers, if necessary)

## Software

- **STM32CubeIDE** for developing and compiling the code
- **STM32 HAL Library** for peripheral configuration and abstraction

## How It Works

- The motors are controlled using **PWM signals** on specific timer channels (TIM1, TIM2, and TIM3).
- Each motor’s speed is adjusted by modifying the PWM duty cycle.
  - **Motor 1**: Initially set to 50% speed
  - **Motor 2**: Initially set to 75% speed
  - **Motor 3**: Initially set to 25% speed
- The motors reverse their direction by altering the PWM values in a loop, changing their speed from 0% to 100% and back, in steps of 5%.
- The system simulates a continuous **PWM signal adjustment** to visualize motor behavior.

## Code Walkthrough

1. **PWM Initialization**: 
   - The timers (TIM1, TIM2, TIM3) are configured to generate PWM signals.
   - `HAL_TIM_PWM_Start()` is used to start PWM output on each motor.
   
2. **Motor Speed Control**: 
   - The PWM duty cycle for each motor is set using `__HAL_TIM_SET_COMPARE()` with values ranging from 0 to 999 (corresponding to 0% to 100% duty cycle).
   
3. **Direction Reversal**:
   - A loop gradually increases and decreases the duty cycle, simulating speed ramping and direction reversal.
   - The direction of rotation is reversed by modifying the duty cycle values in steps.

4. **GPIO Control**:
   - Motor direction is controlled using GPIO pins (PA11, PA12, PA13) which are set to `HIGH` or `LOW` based on the required motor direction.

## Installation and Setup

1. **Install STM32CubeIDE**: If you haven’t already, download and install STM32CubeIDE from the [STMicroelectronics website](https://www.st.com/en/development-tools/stm32cubeide.html).
   
2. **Clone the Repository**

## Further Additions or Improvements
While the current version provides a solid foundation, there are numerous ways you can improve and expand the functionality of the motor control system. This is just a preliminary base to learn the ARM Microcontroller architectures.
1. **Adding Sensors to Trigger Motor Control**
2. **Encoder Integration for Closed-Loop Control**
3. **Advanced Motor Control Algorithms**
4. **Real-time Monitoring and Diagnostics**
And many more.
