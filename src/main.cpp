#include <Arduino.h>
const int pinRelay = 2;
const int pinLed = 1;
#ifdef NEO
#include <Adafruit_NeoPixel.h>
const int numLeds = 16;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numLeds, pinLed, NEO_GRB + NEO_KHZ800);
#endif
void LoopRelay();
void LoopLed();
void OnLed();
void OffLed();
void OnRelay();
void OffRelay();

const double baseFreq = 130;
const double beatFreqOffset = 0.8;
const double relayDutyCycle = 0.5;
const double ledDutyCycle = 0.2;



void setup() {
  // put your setup code here, to run once:
  #ifdef NEO
    pixels.begin();
  #else
    pinMode(pinLed, OUTPUT);
  #endif
  pinMode(pinRelay, OUTPUT);
}

void loop() {
  LoopLed();
  LoopRelay();  
}

void LoopLed() {
  static unsigned long lastSwitch_us = 0;
  static bool IsOn = false;

  static unsigned long timePeriod = 1 / (baseFreq - beatFreqOffset) * 1000 * 1000;
  static unsigned long onTime_us = timePeriod * ledDutyCycle;
  static unsigned long offTime_us = timePeriod * (1 - ledDutyCycle);
  
  const unsigned long timeSinceLastSwitch_us = micros() - lastSwitch_us;
  if(IsOn)
  {
    if(timeSinceLastSwitch_us >= onTime_us)
    {
      
        lastSwitch_us = micros();
        IsOn = !IsOn;
        OffLed();
    }
  }
  else 
  {
    if(timeSinceLastSwitch_us >= offTime_us)
    {
        lastSwitch_us = micros();
        IsOn = !IsOn;
        OnLed();
    }
  }
}

void LoopRelay() {
  static unsigned long lastSwitch_us = 0;
  static bool IsOn = false;
  
  static unsigned long timePeriod = 1 / baseFreq * 1000 * 1000;
  static unsigned long onTime_us = timePeriod * relayDutyCycle;
  static unsigned long offTime_us = timePeriod * (1 - relayDutyCycle);
  
  const unsigned long timeSinceLastSwitch_us = micros() - lastSwitch_us;
  if(IsOn)
  {
    if(timeSinceLastSwitch_us >= onTime_us)
    {
      
        lastSwitch_us = micros();
        IsOn = !IsOn;
        OffRelay();
    }
  }
  else 
  {
    if(timeSinceLastSwitch_us >= offTime_us)
    {
        lastSwitch_us = micros();
        IsOn = !IsOn;
        OnRelay();
    }
  }
}



void OnLed() {
  #ifdef NEO
    pixels.fill(pixels.Color(255, 0, 0), 0, numLeds);
    pixels.show();
  #else
    digitalWrite(pinLed, HIGH);
  #endif

}

void OffLed() {
  #ifdef NEO
    pixels.clear();
    pixels.show();
  #else
    digitalWrite(pinLed, LOW);
  #endif

}


void OnRelay() {
  digitalWrite(pinRelay, HIGH);
}

void OffRelay() {
  digitalWrite(pinRelay, LOW);
}
