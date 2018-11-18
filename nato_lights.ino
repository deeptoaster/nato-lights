#define DEBUG

#include "src/common.h"
#include "src/lights.h"
#include "src/pattern.h"
#include "src/patterns/pattern_colors.h"

int pattern_index = 0;
CRGB leds[LED_COUNT];
Lights *lights;

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif

  FastLED.addLeds<LED_TYPE, LED_PIN_1>(leds, LED_OFFSET_1, LED_COUNT_1);
  FastLED.addLeds<LED_TYPE, LED_PIN_2>(leds, LED_OFFSET_2, LED_COUNT_2);
  FastLED.addLeds<LED_TYPE, LED_PIN_3>(leds, LED_OFFSET_3, LED_COUNT_3);
  lights = new Lights();
  lights->addPattern<PatternColors>();
  lights->on();
}

void loop() {
  lights->step();
  FastLED.show();
  delay(1);
}
