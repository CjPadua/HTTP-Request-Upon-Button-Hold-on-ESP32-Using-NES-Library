# ESP32 Button-Hold HTTP JSON Sender

This project demonstrates how to send an HTTP POST request with JSON data from an **ESP32** when a button is held for at least 2 seconds.  
It uses the [`NES_HTTPClient`](./NES_HTTPClient.h) wrapper (custom library) along with the [ArduinoJson](https://arduinojson.org/) library.

---

## Features
- Connects the ESP32 to WiFi using given SSID and password.  
- Monitors a button connected to a GPIO pin with `INPUT_PULLUP`.  
- Detects when the button is **held down for 2 seconds**.  
- Sends a JSON payload via HTTP POST to a defined server endpoint.  
- Prints debug information to the Serial Monitor.

---

## Dependencies
Make sure to install the following libraries before uploading the sketch:
- [ArduinoJson](https://arduinojson.org/)  
- [WiFi.h](https://www.arduino.cc/en/Reference/WiFi) (comes with ESP32 core)  
- `NES_HTTPClient.h` (included in this repository)  

You must also have the **ESP32 board support** installed in the Arduino IDE.  
Follow [Espressif’s official instructions](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).

---

## Hardware Setup
- **ESP32** board.  
- **Button** connected between GPIO 4 and GND.  
  - Uses `INPUT_PULLUP`, so no external pull-up resistor is needed.  

---

## Code Explanation
1. Connects to WiFi on boot.  
2. Waits for button press:
   - If pressed, starts a timer (`millis()`).
   - If held for ≥ 2000 ms, marks as "held" and sends JSON.  
3. JSON Payload Example:
   ```json
   {
     "team": "Dueñas",
     "espName": "ESP"
   }
