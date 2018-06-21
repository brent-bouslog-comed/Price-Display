// Use if you want to force the software SPI subsystem to be used for some reason (generally, you don't)
// #define FASTLED_FORCE_SOFTWARE_SPI
// Use if you want to force non-accelerated pin access (hint: you really don't, it breaks lots of things)
// #define FASTLED_FORCE_SOFTWARE_SPI
// #define FASTLED_FORCE_SOFTWARE_PINS
#include "FastLED.h"

///////////////////////////////////////////////////////////////////////////////////////////
//
// Move a white dot along the strip of leds.  This program simply shows how to configure the leds,
// and then how to turn a single pixel white and then off, moving down the line of pixels.
// 

// How many leds are in the strip?
#define NUM_LEDS 70

// Data pin that led data will be written out over
#define DATA_PIN 3

// Clock pin only needed for SPI based chipsets when not using hardware SPI
//#define CLOCK_PIN 8

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_LEDS];

int num = 0;

// This function sets up the ledsand tells the controller about them
void setup() {
  // sanity check delay - allows reprogramming if accidently blowing power w/leds
    delay(2000);

      // Uncomment one of the following lines for your leds arrangement.
      // FastLED.addLeds<TM1803, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1804, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<TM1809, DATA_PIN, RGB>(leds, NUM_LEDS);
      FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<APA104, DATA_PIN>(leds, NUM_LEDS);
      // FastLED.addLeds<WS2811_400, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<GW6205_400, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903, DATA_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<UCS1903B, DATA_PIN, RGB>(leds, NUM_LEDS);

      // FastLED.addLeds<WS2801, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, RGB>(leds, NUM_LEDS);
      
      // FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<SM16716, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<LPD8806, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<P9813, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
      // FastLED.addLeds<DOTSTAR, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
}

// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
   // Move a single white led 
   setNumber(num);
   num = (num + 1) % 10;
   delay(500);
}

void setNumber(int num){
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds[i] = CRGB::Black;
  }
  
  if(num == 0)
  {
    for(int i = 10; i < NUM_LEDS; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 1)
  {
    for(int i = 10; i < 20; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 60; i < NUM_LEDS; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 2)
  {
    for(int i = 0; i < 30; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 40; i < 60; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 3)
  {
    for(int i = 0; i < 30; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 50; i < NUM_LEDS; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 4)
  {
    for(int i = 0; i < 20; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 30; i < 40; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 60; i < NUM_LEDS; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 5)
  {
    for(int i = 0; i < 10; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 20; i < 40; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 50; i < NUM_LEDS; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 6)
  {
    for(int i = 0; i < 10; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 20; i < NUM_LEDS; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 7)
  {
    for(int i = 10; i < 30; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 60; i < NUM_LEDS; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 8)
  {
    for(int i = 0; i < NUM_LEDS; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
  }
  else
  {
    for(int i = 0; i < 40; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 60; i < NUM_LEDS; i = i + 1) {
      leds[i] = CRGB::Red;
      FastLED.show();
    }
  }
}

