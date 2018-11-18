#include "pattern_colors.h"

#include "../common.h"

void PatternColors::init() {
  offset = 0;
}

int PatternColors::step() {
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CHSV(map(i + offset, 0, LED_COUNT, 0, 255), 255, 255);
  }

#ifdef DEBUG
  Serial.println(analogRead(POT_PIN));
#endif

  offset += map(analogRead(POT_PIN), 0, POT_MAX, 0, LED_COUNT / 16);

  if (offset >= LED_COUNT) {
    offset -= LED_COUNT;
  }

  return 10;
}
