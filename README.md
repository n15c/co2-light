# CO₂ Monitor with RGB LED Indicator

This Arduino project uses a DFRobot CCS811 air quality sensor and an Adafruit NeoPixel LED strip to monitor indoor CO₂ levels and display real-time air quality using color-coded indicators (green, yellow, red, blue).

📈 Project Features

- 🟢 Green: Good air quality (CO₂ < ~600ppm)
- 🟡 Yellow: Moderate level (CO₂ around 1000ppm)
- 🔴 Red: High CO₂ concentration (CO₂ > 1400ppm)
- 🔵 Blue: Sensor returns unexpected low value (<400ppm)

🛠 Hardware Requirements

- Arduino-compatible board (Uno, Nano, Mega, etc.)
- DFRobot CCS811 digital gas sensor
- Adafruit NeoPixel strip (8 pixels)
- 5V Power supply
- Breadboard and jumper wires

🔌 Wiring Guide

CCS811 to Arduino:

| CCS811 Pin | Arduino Pin |
|------------|-------------|
| VIN        | 3.3V or 5V  |
| GND        | GND         |
| SDA        | A4 (SDA)    |
| SCL        | A5 (SCL)    |
| WAKE       | GND         (tie low) |

NeoPixel:

| NeoPixel  | Arduino Pin |
|-----------|-------------|
| DIN       | D9          |
| VCC       | 5V          |
| GND       | GND         |

Note: Use a 300–500 Ω resistor between Arduino pin D9 and DIN, and a 1000 µF capacitor across the power supply for NeoPixels to prevent spikes (recommended for long-term use).

🚀 Getting Started

1. Clone or download this repository:

   git clone https://github.com/n15c/co2-light.git

2. Install Arduino libraries via Library Manager:

   - Adafruit NeoPixel
   - DFRobot_CCS811

3. Open the sketch in Arduino IDE.
4. Select your board and COM port.
5. Upload the sketch.
6. Open the Serial Monitor at 115200 baud to see live readings.

💡 Behavior & Visualization

The NeoPixel LEDs scale from green to red based on the measured CO₂ PPM value using a simple linear gradient:

- 400 ppm: Green (clean air)
- ~1000 ppm: Yellow
- 1400+ ppm: Solid red
- Below 400 ppm: Blue (possibly sensor startup or error)

You can visually monitor air quality and take action (e.g., open a window) if the LED turns red.

📄 Code Overview

- setup(): Initializes Serial, NeoPixels, and CCS811.
- loop(): Reads CO₂ levels and displays the status on LEDs.
- setScaleColor(): Maps sensor values to RGB color range.



📝 License

MIT License  

📬 Acknowledgments

- DFRobot CCS811 Library
- Adafruit NeoPixel Library
