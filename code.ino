#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Library for LCD screen

// Create an instance of the LCD with the address 0x27 and 16x2 dimensions
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int SENSOR_PIN = A0; // Pin for the sound sensor (Analog pin A0)
const int PIN_QUIET = 3;   // Pin for "Quiet" level output
const int PIN_MODERATE = 4; // Pin for "Moderate" level output
const int PIN_LOUD = 5;    // Pin for "Loud" level output

const int sampleWindow = 50; // Sample window size in milliseconds (50 ms = 20 Hz)
unsigned int sample;

void setup() {
  Serial.begin(9600); // Start serial communication for debugging

  lcd.init(); // Initialize the LCD screen
  lcd.backlight(); // Turn on the backlight

  pinMode(SENSOR_PIN, INPUT); // Set the sound sensor pin as an input
  pinMode(PIN_QUIET, OUTPUT);  // Set the pins for sound level indicators as output
  pinMode(PIN_MODERATE, OUTPUT);
  pinMode(PIN_LOUD, OUTPUT);
  
  // Set the sound level output pins to LOW initially
  digitalWrite(PIN_QUIET, LOW);
  digitalWrite(PIN_MODERATE, LOW);
  digitalWrite(PIN_LOUD, LOW);
  
  Serial.println("LCD Initialized"); // Print a message to the Serial Monitor
}

void loop() {
  lcd.clear(); // Clear the LCD screen
  lcd.setCursor(0, 0); // Set cursor to the first line
  lcd.print("Testing LCD...");

  delay(1000); // Pause for 1 second

  unsigned long startMillis = millis(); // Start timing for the sample window
  float peakToPeak = 0;  // Variable to store the peak-to-peak value
  unsigned int signalMax = 0; // Maximum signal value during the window
  unsigned int signalMin = 1024; // Minimum signal value during the window
  
  // Collect data for the duration of the sample window (50 ms)
  while (millis() - startMillis < sampleWindow) {
    sample = analogRead(SENSOR_PIN); // Read the value from the sound sensor

    // Filter out invalid values
    if (sample < 1024) {
      if (sample > signalMax) {
        signalMax = sample; // Update the maximum value
      } else if (sample < signalMin) {
        signalMin = sample; // Update the minimum value
      }
    }
  }

  peakToPeak = signalMax - signalMin; // Calculate the peak-to-peak amplitude
  int db = map(peakToPeak, 20, 750, 49.5, 90); // Map the amplitude to decibels (dB)
  
  // Display the loudness in decibels on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Loudness: ");
  lcd.print(db);
  lcd.print(" dB");

  // Set the output level based on the dB value
  if (db <= 60) {
    lcd.setCursor(0, 1);
    lcd.print("Level: Quiet");
    digitalWrite(PIN_QUIET, HIGH); // Activate Quiet level
    digitalWrite(PIN_MODERATE, LOW); // Deactivate Moderate level
    digitalWrite(PIN_LOUD, LOW);    // Deactivate Loud level
  } else if (db > 60 && db < 85) {
    lcd.setCursor(0, 1);
    lcd.print("Level: Moderate");
    digitalWrite(PIN_QUIET, LOW);   // Deactivate Quiet level
    digitalWrite(PIN_MODERATE, HIGH); // Activate Moderate level
    digitalWrite(PIN_LOUD, LOW);    // Deactivate Loud level
  } else if (db >= 85) {
    lcd.setCursor(0, 1);
    lcd.print("Level: High");
    digitalWrite(PIN_QUIET, LOW);   // Deactivate Quiet level
    digitalWrite(PIN_MODERATE, LOW); // Deactivate Moderate level
    digitalWrite(PIN_LOUD, HIGH);   // Activate Loud level
  }

  delay(1500); // Wait for 1.5 seconds before the next reading
}
