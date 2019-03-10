#include "pattern_fire.h"

#include "../common.h"

void PatternFire::init() {
  for (unsigned short i = 0; i < LED_COUNT; i++) {
    leds[i].r = random8(FIRE_SCALE_MIN * 2, FIRE_SCALE_MAX * 2);
    leds[i].g = (leds[i].r - FIRE_G_R_OFFSET) / 2;
    leds[i].b = 0;
  }
}

unsigned char PatternFire::step() {
  unsigned char scale = map(Hardware.getPot1Value(), 0, POT_1_MAX, 0, random8(FIRE_SCALE_MIN, FIRE_SCALE_MAX));

  for (unsigned short i = 0; i < LED_COUNT; i++) {
    unsigned short j = random8(2) ? LED_COUNT - i - 1 : i;
    leds[j].r = qadd8((leds[(j - 2 + LED_COUNT) % LED_COUNT].r + leds[(j - 1 + LED_COUNT) % LED_COUNT].r * 2 + leds[j].r + leds[(j + 1) % LED_COUNT].r * 2 + leds[(j + 2) % LED_COUNT].r) * 4 / 29, scale / FIRE_SCALE_MIN);

    if (!random8(FIRE_SPAWN_FREQUENCY)) {
      leds[j].r = qadd8(leds[j].r, scale);
    }

    leds[j].g = qsub8(leds[j].r, FIRE_G_R_OFFSET) / 2;
  }

  return 5;
}
