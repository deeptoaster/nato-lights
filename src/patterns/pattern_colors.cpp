#include "pattern_colors.h"

#include "../common.h"

void PatternColors::init() {
  offset = 0;
}

int PatternColors::step() {
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = CHSV(map(i + offset, 0, LED_COUNT, 0, 255), 255, 255);
  }

  int pot = analogRead(POT_PIN);

#ifdef DEBUG
  Serial.print("[PatternColors] Potentiometer value: ");
  Serial.println(pot);
#endif

  offset += map(pot, 0, POT_MAX, 0, LED_COUNT / 16);

  if (offset >= LED_COUNT) {
    offset -= LED_COUNT;
  }

  return 10;
}
