#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#define BUTTON_PIN   2
#define PIXEL_PIN    6  // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 16  // Number of NeoPixels

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

boolean oldState = HIGH;
int     mode     = 0;    // Currently-active animation mode, 0-9

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'
}

void loop() {
  boolean newState = digitalRead(BUTTON_PIN);
  if((newState == LOW) && (oldState == HIGH)) {
    delay(20);
    newState = digitalRead(BUTTON_PIN);
    if(newState == LOW) {      // Yes, still low
      if(++mode > 3) mode = 0; // Advance to next mode, wrap around after #8
      switch(mode) {           // Start the new animation...
        case 0:
          colorWipe(strip.Color(  0,   0,   0), 50);    // Black/off
          break;
        case 1: // warm colours
          colorWipe(strip.Color(100,   0,   0), 50);    // Red
          delay(50);
          colorWipe(strip.Color(100,   100,   0), 50);    // Yellow
          delay(50);
          colorWipe(strip.Color(100,   0,   0), 50);    // Red
          delay(50);
          colorWipe(strip.Color(100,   100,   0), 50);    // Yellow
          delay(500);
          colorWipe(strip.Color(100,   0,   0), 50);    // Red
          delay(500);
          colorWipe(strip.Color(100,   100,   0), 50);    // Yellow
          break;
        case 2: // bright lights
          colorWipe(strip.Color(255, 255,   255), 50);    // White
          delay(100);
          colorWipe(strip.Color(0,   255,   0), 50);      // Green
          delay(100);
          colorWipe(strip.Color(0,   0,   255), 50);      // Blue
          delay(100);
          colorWipe(strip.Color(255,   0,   255), 50);      // Purple
          delay(100);
          colorWipe(strip.Color(255, 255,   255), 50);    // White
          break;
        case 3:
          rainbow(20);
          break;
        
      }
    }
  }

  // Set the last-read button state to the old state.
  oldState = newState;
}
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 10*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}
