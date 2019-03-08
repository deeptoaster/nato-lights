#include "pattern_colors.h"

#include "../common.h"

void PatternColors::init() {
  offset = 0;
}

unsigned char PatternColors::step() {
  for (i = 0; i < LED_COUNT; i++) {
    leds[i] = CHSV(map(i + offset, 0, LED_COUNT, 0, 255), 255, 255);
  }

  offset += map(Hardware.getPot1Value(), 0, POT_1_MAX, 0, COLORS_SPEED_MAX);

  if (offset >= LED_COUNT) {
    offset -= LED_COUNT;
  }

  return 10;
}
