
#include <HamShield.h>
#include <DDS.h>
#include <packet.h>

#include "FastLED.h"

#define PWM_PIN 3
#define RESET_PIN A3
#define SWITCH_PIN 2

#define NUM_LEDS 70
#define MAX_LEDS 72

#define TENS_PIN 6
#define ONES_PIN 7
#define DEC_PIN 8

#define TENS_POS 0
#define ONES_POS 1
#define DEC_POS 2

HamShield radio;
DDS dds;
AFSK afsk;

String hamPrice = "";
String price = "";
String prevPrice = "";
char* arr;

CRGB leds[3][MAX_LEDS];
char prevNum[3] = {-1,-1,-1};

void setup() {
  // NOTE: if not using PWM out, it should be held low to avoid tx noise
  pinMode(PWM_PIN, OUTPUT);
  digitalWrite(PWM_PIN, LOW);
  
  // prep the switch
  pinMode(SWITCH_PIN, INPUT_PULLUP);
  
  // set up the reset control pin
  pinMode(RESET_PIN, OUTPUT);
  // turn on radio
  digitalWrite(RESET_PIN, HIGH);

  //Serial3.begin(9600);
  Serial.begin(9600);
  
  delay(100);
  radio.initialize();
  radio.frequency(145010);
  //radio.frequency(152840);
  radio.setSQOff();
  delay(100);
  radio.setModeReceive();
  delay(100);
  dds.start();
  delay(100);
  afsk.start(&dds);
  delay(100);
  dds.setAmplitude(255);
  
  FastLED.addLeds<WS2811, TENS_PIN, GRB>(leds[TENS_POS], MAX_LEDS);
  FastLED.addLeds<WS2811, ONES_PIN, GRB>(leds[ONES_POS], MAX_LEDS);
  FastLED.addLeds<WS2811, DEC_PIN, GRB>(leds[DEC_POS], MAX_LEDS);

  clearNumber(TENS_POS);
  clearNumber(ONES_POS);
  clearNumber(DEC_POS);
  
  //setDecPoint();
}

uint32_t last = 0;
void loop() {
  if(afsk.decoder.read() || afsk.rxPacketCount()) {
      // A true return means something was put onto the packet FIFO
      // If we actually have data packets in the buffer, process them all now
      while(afsk.rxPacketCount()) {
        AFSK::Packet *packet = afsk.getRXPacket();
        //Serial.print(F("Packet: "));
        if(packet) {
          Serial.println("Got Packet");
          arr = packet->printPacket();
          String myString = String(arr);
          if(!myString.equals(hamPrice))
          {
            hamPrice = myString;
            price = stringToPrice(hamPrice);
          }
          AFSK::PacketBuffer::freePacket(packet);
          //Serial.println("The price of Energy is " + price + " cents/kWh");
        }
      }
    }

  if(!prevPrice.equals(price))
  {
      for(int i = 0; i < 3; i++)
      {
        prevNum[i] = -1;
        clearNumber(i);
        clearDecPoint();
      }

    Serial.println("New Number");
    setDecPoint();
    writeNum(price.toDouble());
    prevPrice = price;
    delay(500);
  }

}

//TODO: d2 is the switch input, so remove this
ISR(ADC_vect) {
  static uint8_t tcnt = 0;
  TIFR1 = _BV(ICF1); // Clear the timer flag
  //PORTD |= _BV(2); // Diagnostic pin (D2)
  //dds.clockTick();
  afsk.timer();
  //PORTD &= ~(_BV(2)); // Pin D2 off again
}

String stringToPrice(String s){
  int pos = 0;
  String toReturn;
  while(s.substring(pos, pos + 1) != ":"){
    pos++;  
  }
  pos++;
  toReturn = s.substring(pos, pos + 3);
  return toReturn;
}

void writeNum(double value)
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

void setDecPoint(void)
{
   for(int i = NUM_LEDS; i < MAX_LEDS; i++)
   {
      leds[1][i] = CRGB::Red;
      FastLED.show();
   }
}

void clearDecPoint(void)
{
  for(int i = NUM_LEDS; i < MAX_LEDS; i++)
   {
      leds[1][i] = CRGB::Black;
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

