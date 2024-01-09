#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// Define pins for the buttons
#define RIGHT_BUTTON_PIN 2
#define LEFT_BUTTON_PIN 1

// Display pins
#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8

// Button state variables
int rightButtonState;         
int lastRightButtonState = LOW;
int leftButtonState;         
int lastLeftButtonState = LOW;

// Debounce variables
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// Other variables
const int interval = 50; // Interval in milliseconds
unsigned long previousMillis = 0;
int button_clicks = 0;

// Initialize display
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  pinMode(RIGHT_BUTTON_PIN, INPUT);
  pinMode(LEFT_BUTTON_PIN, INPUT);
  
  tft.begin();
  tft.setRotation(0);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.println(button_clicks);
}

void loop() {
  int rightReading = digitalRead(RIGHT_BUTTON_PIN);
  int leftReading = digitalRead(LEFT_BUTTON_PIN);
  unsigned long currentMillis = millis();

  // Debounce logic for the right button
  if (rightReading != lastRightButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (rightReading != rightButtonState) {
      rightButtonState = rightReading;
      if (rightButtonState == HIGH) {
        // Right button logic
        button_clicks++;
        updateDisplay();
      }
    }
  }
  lastRightButtonState = rightReading;

  // Debounce logic for the left button
  if (leftReading != lastLeftButtonState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (leftReading != leftButtonState) {
      leftButtonState = leftReading;
      if (leftButtonState == HIGH) {
        // Left button logic
        button_clicks--;
        updateDisplay();
      }
    }
  }
  lastLeftButtonState = leftReading;

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
  }
}

void updateDisplay() {
  tft.setCursor(0, 0);
  clearLine(0);
  tft.println(button_clicks);
}

void clearLine(int line) {
  // Clear the line on the display where the text is printed
  tft.fillRect(0, line * 16, tft.width(), 16, ILI9341_BLACK);
}
