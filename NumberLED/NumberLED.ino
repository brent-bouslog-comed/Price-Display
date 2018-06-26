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
#define MAX_LEDS 72
#define NUM_CHAR 3

// Data pin that led data will be written out over
#define TENS_PIN 6
#define ONES_PIN 7
#define DEC_PIN 8

#define TENS_POS 0
#define ONES_POS 1
#define DEC_POS 2

// Clock pin only needed for SPI based chipsets when not using hardware SPI
//#define CLOCK_PIN 8

// This is an array of leds.  One item for each led in your strip.
CRGB leds[NUM_CHAR][MAX_LEDS];
double prevNum[3] = {-1,-1,-1};

double num = 0.0;
int count = 0;

// This function sets up the ledsand tells the controller about them
void setup() {
     // Serial.begin(9600);
  
      FastLED.addLeds<WS2811, TENS_PIN, GRB>(leds[TENS_POS], MAX_LEDS);
      FastLED.addLeds<WS2811, ONES_PIN, GRB>(leds[ONES_POS], MAX_LEDS);
      FastLED.addLeds<WS2811, DEC_PIN, GRB>(leds[DEC_POS], MAX_LEDS);

      clearNumber(TENS_POS);
      clearNumber(ONES_POS);
      clearNumber(DEC_POS);

      setDecPoint();
      Serial.print("Dec Done");
}

// This function runs over and over, and is where you do the magic to light
// your leds.
void loop() {
   count++;
   if(count % 1 == 0)
   {
      num += .1;// * ((count % 4) - 1);
      //fgnum += (random(0,3)/10.0)*(random(0,3) - 1);
      if(num < 0)
        num == 0;
   }
   if(count % 20 == 0)
   {
      for(int i = 0; i < 3; i++)
      {
        prevNum[i] = -1;
        clearNumber(i);
      }
      
      delay(1000);
   }

   //Serial.println(String(num, 1));
   writeNum2(num);
   
   delay(500);
}

void writeNum2(double value)
{
    int val = (int)(value * 10);

    double num[3];
    num[DEC_POS] = val % 10;
    val = (val - (val % 10))/10;
    num[ONES_POS] = val % 10;
    val = (val - (val % 10))/10;
    num[TENS_POS] = val % 10;

    for(int i = 0; i < 3; i++)
    {
      if(num[i] != prevNum[i])
      {
        setNumber(num[i], i);
        prevNum[i] = num[i];
      }
    }
}

void writeNum(double value)
{
  int val = (int)(value * 10);

  if(val > 0 && val < 10)
  {
    clearNumber(TENS_POS);
    clearNumber(ONES_POS);

    if(val % 10 != prevNum[DEC_POS])
    {
      setNumber((val % 10), DEC_POS);
      prevNum[DEC_POS] = val % 10;
    }
  }
  else if(val >= 10 && val < 100)
  {
    clearNumber(TENS_POS);

    if(val % 10 != prevNum[DEC_POS])
    {
      setNumber((val % 10), DEC_POS);
      prevNum[DEC_POS] = val % 10;
    }
    
    val = (val - (val % 10))/10;

    if(val % 10 != prevNum[ONES_POS])
    {
      setNumber((val % 10), ONES_POS);
      prevNum[ONES_POS] = val % 10;
    }
    Serial.print(val);
  }
  else if(val >= 100)
  {
    if(val % 10 != prevNum[DEC_POS])
    {
      setNumber((val % 10), DEC_POS);
      prevNum[DEC_POS] = val % 10;
    }
    
    val = (val - (val % 10))/10;
    
    if(val % 10 != prevNum[ONES_POS])
    {
      setNumber((val % 10), ONES_POS);
      prevNum[ONES_POS] = val % 10;
    }
    
    val = (val - (val % 10))/10;
    
    if(val % 10 != prevNum[TENS_POS])
    {
      setNumber((val % 10), TENS_POS);
      prevNum[TENS_POS] = val % 10;
    }
  }
}

void setDecPoint(void)
{
   for(int i = NUM_LEDS; i < MAX_LEDS; i++)
   {
      leds[1][i] = CRGB::Red;
      FastLED.show();
   }
}

void clearNumber(int pos)
{
  for(int i = 0; i < NUM_LEDS; i++)
  {
    leds[pos][i] = CRGB::Black;
    FastLED.show();
  }
}

void setNumber(int num, int pos){
  clearNumber(pos);
  
  if(num == 0)
  {
    for(int i = 10; i < NUM_LEDS; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 1)
  {
    for(int i = 10; i < 20; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 60; i < NUM_LEDS; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 2)
  {
    for(int i = 0; i < 30; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 40; i < 60; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 3)
  {
    for(int i = 0; i < 30; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 50; i < NUM_LEDS; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 4)
  {
    for(int i = 0; i < 20; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 30; i < 40; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 60; i < NUM_LEDS; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 5)
  {
    for(int i = 0; i < 10; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 20; i < 40; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 50; i < NUM_LEDS; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 6)
  {
    for(int i = 0; i < 10; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 20; i < NUM_LEDS; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 7)
  {
    for(int i = 10; i < 30; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 60; i < NUM_LEDS; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
  }
  else if(num == 8)
  {
    for(int i = 0; i < NUM_LEDS; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
  }
  else
  {
    for(int i = 0; i < 40; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
    for(int i = 60; i < NUM_LEDS; i = i + 1) {
      leds[pos][i] = CRGB::Red;
      FastLED.show();
    }
  }
}

