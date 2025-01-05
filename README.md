# Bluetooth Serial LED Controller

This project is an ESP32-based Bluetooth Serial LED Controller designed to allow users to control LEDs via Bluetooth using custom commands. The system also includes functionality to read button inputs and respond accordingly, making it versatile for various applications.

---

## Features

- **Bluetooth Connectivity**: Communicate with the ESP32 through Bluetooth for wireless control.
- **LED Control**: Manage LED states (ON/OFF) and toggle modes based on received commands.
- **Button Integration**: Read button states for additional physical control.
- **Custom Commands**: Supports commands such as `POWER`, `ALTERNATE`, `+`, and `-` for advanced LED control.
- **Real-Time Status Update**: Uses USB Serial and Bluetooth Serial for device communication and status monitoring.

---

## Components Used

- **Microcontroller**: ESP32
- **LEDs**: At least one LED (connected to GPIO 2 by default).
- **Push Buttons**: Connected to GPIOs 0, 4, 17, and 16 (modifiable in code).
- **Power Supply**: 5V for the ESP32 module.

---

## Installation and Setup

### Prerequisites

- **Hardware**:
  - ESP32 microcontroller
  - LEDs and resistors
  - Push buttons (optional)
  
- **Software**:
  - [Arduino IDE](https://www.arduino.cc/en/software) with ESP32 board support installed.

### Steps

1. **Clone the Repository**
   ```bash
   git clone https://github.com/TheLonelyOtaku315/ESP32-LED-Controller.git
   ```
   Or download the project files and extract them.

2. **Open the Project**
   - Open `Bluetooth_Serial_LED_Controller.ino` in the Arduino IDE.

3. **Configure the Code**
   - Modify the `pins` and `commands` vectors as needed to suit your setup.

4. **Upload the Code**
   - Connect the ESP32 to your computer via USB.
   - Select the correct COM port and board in the Arduino IDE.
   - Click on `Upload` to flash the program to the ESP32.

5. **Test the Setup**
   - Pair your ESP32 with your device using Bluetooth (`ESP32LEDControl` as default name).
   - Use a Bluetooth terminal app (e.g., Serial Bluetooth Terminal) to send commands.

---

## Usage

1. **Pair with the ESP32**:
   - Search for the device named `ESP32LEDControl` and pair with it.

2. **Send Commands**:
   - Use a Bluetooth terminal app to send predefined commands:
     - `POWER`: Toggle all LEDs ON/OFF.
     - `ALTERNATE`: Switch LEDs in an alternating pattern.
     - `+`: Increase brightness (if PWM is implemented).
     - `-`: Decrease brightness (if PWM is implemented).

3. **Monitor via Serial**:
   - Open the Serial Monitor in the Arduino IDE to view logs and debug messages.

---

## Code Structure

- **Setup**: Initializes Bluetooth, serial communication, and pin configurations.
- **Loop**:
  - Checks Bluetooth connection status.
  - Monitors button states and updates the corresponding LED actions.
  - Processes received Bluetooth commands.

---

## Customization

- Update the `pins` array to define GPIOs connected to buttons.
- Add or modify commands in the `commands` array for additional functionality.
- Expand LED control logic as needed.

---

## Troubleshooting

- **Bluetooth Not Connecting**: Ensure the ESP32 is powered and in range. Try unpairing and pairing again.
- **Commands Not Working**: Verify the correct commands are sent through the terminal app.
- **LEDs Not Responding**: Check wiring and ensure the LEDs are functional.

---

## Repository

The source code and related files for this project are available on GitHub:
[ESP32 LED Controller](https://github.com/TheLonelyOtaku315/ESP32-LED-Controller)

---

## License

This project is open-source and available under the MIT License. Feel free to use, modify, and distribute the code.

---

## Acknowledgments

Special thanks to the Arduino and ESP32 communities for providing extensive resources and support.

---

## Contact

For questions or feedback, please reach out to [Your Name/Email].

