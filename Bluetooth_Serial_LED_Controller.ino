#include "BluetoothSerial.h"
#include <vector>

#define LED1 2
const std::vector<int> pins = { 0, 4, 17, 16 };
const std::vector<String> commands = { "POWER", "ALTERNATE", "+", "-" };
std::vector<int> state = { 0, 0, 0 };
std::vector<int> lastPinStates(pins.size(), HIGH);

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);               // USB Serial
  SerialBT.begin("ESP32LEDControl");  // Bluetooth Serial
  logMessage("Device started, pair via Bluetooth!");

  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, HIGH);  // Default to LED ON when not connected
}

void loop() {
  // Check Bluetooth connection status
  digitalWrite(LED1, SerialBT.hasClient() ? LOW : HIGH);

  // Handle button inputs
  for (size_t i = 0; i < pins.size(); i++) {
    pinMode(pins[i], INPUT);
    int currentState = digitalRead(pins[i]);
    if (lastPinStates[i] == LOW && currentState == HIGH) {
      handleInput(i, "Button");
    }
    lastPinStates[i] = currentState;
  }

  // Restore pin modes
  for (int pin : pins) pinMode(pin, OUTPUT);

  // Handle USB input
  if (Serial.available()) {
    processInput(Serial.readStringUntil('\n'), "USB");
  }

  // Handle Bluetooth input
  if (SerialBT.available()) {
    processInput(SerialBT.readStringUntil('\n'), "Bluetooth");
  }
}

void processInput(const String &input, const String &source) {
  String trimmedInput = input;
  trimmedInput.trim();

  for (size_t i = 0; i < commands.size(); i++) {
    if (trimmedInput.equalsIgnoreCase(commands[i])) {
      handleInput(i, source);
      toggleOutput(pins[i]);
      return;
    } else if (trimmedInput.equalsIgnoreCase("Timer")) {
      logMessage(source + " : Please enter the Timer duration in seconds:");
      int timeInput = waitForInput(source);  // Unified waiting function
      if (timeInput > 0) {
        timer(timeInput, source);
      } else {
        logMessage(source + " : Invalid input. Timer duration must be a positive integer.");
      }
      return;
    }
  }
  logMessage(source + " : Wrong input");
}
void handleInput(int index, const String &source) {
  if (index == 0) state[0] = !state[0];
  else if (index == 1) state[1] = (state[1] + 1) % 3;
  else if (index == 2) state[2] = constrain(state[2] + 1, 0, 9);
  else if (index == 3) state[2] = constrain(state[2] - 1, 0, 9);
  String newState = generateStateMessage(index);
  logMessage(source + " : " + newState);
}

String generateStateMessage(int index) {
  if (index == 0) return state[0] ? "ON" : "OFF";

  if (state[0] == 1) {
    if (index == 1) {
      switch (state[1]) {
        case 0: return "White";
        case 1: return "Mix";
        case 2: return "Yellow";
      }
    } else {
      return "Brightness Level: " + String(state[2]);
    }
  }
  return "OFF";
}

int waitForInput(const String &source) {
  if (source.equalsIgnoreCase("USB")) {
    while (!Serial.available()) {
      delay(10);  // Wait for USB input
    }
    return Serial.parseInt();  // Parse USB input
  } else if (source.equalsIgnoreCase("Bluetooth")) {
    while (!SerialBT.available()) {
      delay(10);  // Wait for Bluetooth input
    }
    return SerialBT.parseInt();  // Parse Bluetooth input
  }
  return -1;  // Fallback for unsupported sources
}

void toggleOutput(int pin) {
  digitalWrite(pin, LOW);
  delay(1000);
  digitalWrite(pin, HIGH);
}

void logMessage(const String &message) {
  Serial.println(message);
  SerialBT.println(message);
}

void timer(int seconds, const String &source) {
  if (state[0] == 0) handleInput(0, source), toggleOutput(pins[0]);  // Turn ON if OFF
  logMessage(source + " : Timer started, ends in " + String(seconds) + " seconds");
  delay(seconds * 1000);   // Countdown simulation
  handleInput(0, source);  // Turn OFF after timer
  toggleOutput(pins[0]);
  logMessage(source + " : Timer ended, power off");
}
