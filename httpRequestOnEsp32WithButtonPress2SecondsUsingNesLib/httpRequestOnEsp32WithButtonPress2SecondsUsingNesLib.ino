#include <ArduinoJson.h>
#include "NES_HTTPClient.h"

const char* ssid = "benten";
const char* password = "1234567890";
const char* serverName = "http://10.104.128.94/espHTTP/json/receiver.php";

NES_HTTPClient nesClient(ssid, password, serverName);

#define BUTTON_PIN  4   // GPIO where your button is connected (change as needed)

unsigned long buttonPressTime = 0;  // When button was first pressed
bool buttonHeld = false;            // Track if button was held long enough
bool buttonPreviouslyPressed = false; // Track last state for sanity checks

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button active LOW (connect one side to GND)

  nesClient.connectWiFi();
  Serial.println(WiFi.localIP());
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == LOW) {  // Button pressed
    if (!buttonPreviouslyPressed) {
      Serial.println("Button Pressed");
      buttonPreviouslyPressed = true;
      buttonPressTime = millis();  // Record when pressed
    }

    // Check if held for 2 seconds
    if ((millis() - buttonPressTime) >= 2000 && !buttonHeld) {
      buttonHeld = true;  // Mark as handled so we don’t send repeatedly
      Serial.println("Button held for 2 seconds → Sending Request");

      if(nesClient.isConnected()) {
        // 🔹 Example JSON POST
        StaticJsonDocument<200> postDoc;
        postDoc["team"] = "Dueñas";
        postDoc["espName"] = "ESP";

        // Approach ni Sir
        // String jsonStr;
        // serializeJson(postDoc, jsonStr);  // print JSON for debugging
        // Serial.println(jsonStr);

        // Approach ni chatgpt
        serializeJson(postDoc, Serial);  // print JSON for debugging
        Serial.println();

        int response = nesClient.sendJSON(postDoc);
        Serial.printf("POST Response code: %d\n", response);
      } else {
        Serial.println("Error: Not connected to WiFi");
      }

    }
  } else {  
    // Button released
    if (buttonPreviouslyPressed) {
      Serial.println("Button Released");
      buttonPreviouslyPressed = false;
    }
    // Reset state
    buttonPressTime = 0;
    buttonHeld = false;
  }
}
  