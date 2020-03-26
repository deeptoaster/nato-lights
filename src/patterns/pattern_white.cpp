#include "pattern_white.h"

#include "../common.h"

void PatternWhite::init() {}

unsigned char PatternWhite::step() {
  unsigned char brightness = map(Hardware.getPot1Value(), 0, POT_1_MAX, 0, 255);

  for (unsigned short i = 0; i < LED_COUNT; i++) {
    leds[i] = CHSV(0, 0, brightness);
  }

  return 20;
}
