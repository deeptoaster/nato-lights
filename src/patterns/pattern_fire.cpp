#include "pattern_fire.h"

#include "../common.h"

void PatternFire::init() {
  for (i = 0; i < LED_COUNT; i++) {
    leds[i].r = random8(128, 256);
    leds[i].g = (leds[i].r - 48) / 2;
    leds[i].b = 0;
  }
}

int PatternFire::step() {
  scale = map(Hardware.getPot1Value(), 0, POT_1_MAX, 0, random(64, 128));

  for (i = 0; i < LED_COUNT; i++) {
    j = random(2) ? LED_COUNT - i - 1 : i;
    leds[j].r = qadd8((leds[(j - 2 + LED_COUNT) % LED_COUNT].r + leds[(j - 1 + LED_COUNT) % LED_COUNT].r * 2 + leds[j].r + leds[(j + 1) % LED_COUNT].r * 2 + leds[(j + 2) % LED_COUNT].r) * 4 / 29, scale / 64);

    if (!random(128)) {
      leds[j].r = qadd8(leds[j].r, scale);
    }

    leds[j].g = qsub8(leds[j].r, 48) / 2;
  }

  return 5;
}
