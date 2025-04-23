// Include the CCS811 sensor library from DFRobot
#include "DFRobot_CCS811.h"

// Include the Adafruit NeoPixel library for controlling RGB LEDs
#include <Adafruit_NeoPixel.h>

// Define total number of NeoPixel LEDs in the strip
#define NUMPIXELS 8

// Define the digital pin connected to the NeoPixel data input
#define PIXELPIN 9

// Define the brightness level for the LEDs (0–255)
#define BRIGHTNESS 50

// Create an instance of the DFRobot CCS811 gas sensor
DFRobot_CCS811 sensor;

// Create an instance of the NeoPixel LED strip
Adafruit_NeoPixel pixels(NUMPIXELS, PIXELPIN, NEO_GRB + NEO_KHZ800);

// Define RGB color values for red, yellow, and green for easy reuse
uint32_t red = pixels.Color(255, 0, 0);
uint32_t yellow = pixels.Color(255, 255, 0);
uint32_t green = pixels.Color(0, 255, 0);

// The setup() function runs once when the program starts
void setup(void)
{
  // Start the serial communication for debugging (baud rate 115200)
  Serial.begin(115200);

  // Initialize the NeoPixel strip
  pixels.begin();
  pixels.show();  // Turn off all pixels at startup

  // Perform a quick color animation (green → yellow → red)
  pixels.fill(green, 0, 8);
  pixels.show();
  delay(300);

  pixels.fill(yellow, 0, 8);
  pixels.show();
  delay(300);

  pixels.fill(red, 0, 8);
  pixels.show();
  delay(300);

  // Clear the LEDs and set desired brightness
  pixels.clear();
  pixels.setBrightness(BRIGHTNESS);
  pixels.show();

  // Initialize the CCS811 air quality sensor, retry if failed
  while (sensor.begin() != 0) {
    Serial.println("failed to init chip, please check if the chip connection is fine");
    delay(1000);
  }

  // Set the sensor measurement interval to 1 second
  sensor.setMeasurementMode(sensor.eCycle_1s);
}

// The loop() function runs continuously after setup()
void loop() {
  // Check if new sensor data is available
  if (sensor.checkDataReady() == true) {
    // Clear any previously displayed LEDs
    pixels.clear();

    // Read the current CO₂ value in parts per million (ppm)
    float ppmVal = sensor.getCO2PPM(); 
    Serial.println(ppmVal); // Print the CO₂ value to the serial monitor

    // Update the LEDs based on CO₂ level
    setScaleColor(ppmVal);
  }

  // Write a fixed baseline value (calibration); optional & sensor-specific
  sensor.writeBaseLine(0x547A);

  delay(1000); // Wait for 1 second before next reading
}

// Function to display a color gradient based on the CO₂ value
void setScaleColor(float ppmVal) {
  // Declare RGB color components for the LED
  int rVal;
  int gVal;
  int bVal = 0;

  // Convert the CO₂ reading into a 0–100% range,
  // where 400 ppm is considered "clean", and 1400 ppm is "polluted"
  float percentage = ((ppmVal - 400) / 1000.0) * 100;

  if (percentage < 0) {
    // Below minimum threshold: turn LEDs blue
    rVal = 0;
    gVal = 0;
    bVal = 255;
  }
  else if (percentage > 100) {
    // Above maximum threshold: red alert
    rVal = 255;
    gVal = 0;
  }
  else {
    // Intermediate range: compute a gradient between green and red
    rVal = percentage * 2.55;           // Increases as CO₂ rises
    gVal = 255 - (percentage * 2.55);   // Decreases as CO₂ rises
    // Blue remains 0 during gradient
  }

  // Fill all pixels with the calculated RGB color
  pixels.fill(pixels.Color(rVal, gVal, bVal));
  pixels.show(); // Update the LEDs
}
