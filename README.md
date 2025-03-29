# Decibel-Meter-Project-Measuring-Sound-Levels-with-Arduino
# Sound Level Meter using Arduino and LCD

## Overview
This project is a simple **sound level meter** using an Arduino, a sound sensor, and an **LCD display**. It measures the **peak-to-peak** amplitude of sound signals and maps it to **decibels (dB)** to classify the sound level as **Quiet, Moderate, or Loud**.

## Components Required
- **Arduino Uno/Nano** (or any compatible microcontroller)
- **Sound Sensor Module** (Analog output)
- **16x2 LCD with I2C module**
- **Resistors & Jumper wires**
- **3 LEDs (Optional - for visual indicators)**

## How It Works
1. The **sound sensor** captures surrounding noise levels and sends an **analog signal** to the Arduino.
2. The Arduino reads the **maximum and minimum values** in a small time window (50ms) to compute the **peak-to-peak amplitude**.
3. The **amplitude is mapped to a decibel (dB) scale**.
4. The **LCD displays the dB value and sound level** (Quiet, Moderate, or Loud).
5. **LEDs can be used as indicators** to signal different sound levels.

## Code Explanation
- Uses `LiquidCrystal_I2C.h` to control the LCD.
- Reads analog input from the **sound sensor**.
- Filters **invalid values** and calculates **signal amplitude**.
- Maps amplitude to a **dB scale** and categorizes it.
- Displays results on **LCD** and controls LEDs accordingly.

## Sound Level Classification
| dB Value | Classification |
|----------|---------------|
| <= 60 dB | Quiet |
| 61 - 84 dB | Moderate |
| >= 85 dB | Loud |

## Usage
- Power the circuit via **USB or external source**.
- Observe **LCD output** for real-time sound level monitoring.
- Can be used for **noise pollution monitoring**, **home automation**, or **security applications**.

## Future Improvements
- Store sound levels for **data logging**.
- Add **wireless communication (ESP8266/ESP32)** for **IoT integration**.
- Implement a **graphical display** instead of text-based LCD.

---
💡 This project is great for **learning analog signal processing and sensor integration** with Arduino!


