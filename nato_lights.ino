#include "src/common.h"
#include "src/lights.h"
#include "src/pattern.h"
#include "src/patterns/pattern_colors.h"

unsigned long debounce;
CRGB leds[LED_COUNT];
LightsControl Lights;
HardwareControl Hardware;

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif

  FastLED.addLeds<LED_TYPE, LED_PIN_1>(leds, LED_OFFSET_1, LED_COUNT_1);
  FastLED.addLeds<LED_TYPE, LED_PIN_2>(leds, LED_OFFSET_2, LED_COUNT_2);
  FastLED.addLeds<LED_TYPE, LED_PIN_3>(leds, LED_OFFSET_3, LED_COUNT_3);
  Lights = LightsControl();
  Lights.addPattern<PatternColors>();
  Hardware = HardwareControl();
}

void loop() {
  Lights.step();
  FastLED.show();
  delay(1);

  if (Hardware.getNextButtonPressed()) {
    Lights.nextPattern();
  }
}
