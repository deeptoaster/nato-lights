#include "pattern_trains.h"

#include "../common.h"

void PatternTrains::init() {
  for (unsigned short i = 0; i < TRAINS_COUNT_MAX; i++) {
    trains[i].sign = random8(2);
    trains[i].acceleration = random8(2) ? -2 : 1;
    trains[i].speed = random8(0, TRAINS_SPEED_MAX);
    trains[i].position = map((i & 0b0001) << 3 | (i & 0b0010) << 1 | (i & 0b0100) >> 1 | (i & 0b1000) >> 3, 0, TRAINS_COUNT_MAX + 1, 0, LED_COUNT + 1);
  }

  cycle = 0;
}

unsigned char PatternTrains::step() {
  unsigned char count = map(Hardware.getPot1Value(), 0, POT_1_MAX + 1, 1, TRAINS_COUNT_MAX + 1);

  for (unsigned short i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB::Black;
  }

  for (unsigned short i = 0; i < count; i++) {
    for (unsigned char j = 0; j <= trains[i].speed * 4; j++) {
      unsigned short k = ((signed short)trains[i].position - j * (trains[i].sign ? -1 : 1) + LED_COUNT) % LED_COUNT;
      leds[k] += CHSV(map(i, 0, TRAINS_COUNT_MAX, 0, 255), 255, map(j, 0, trains[i].speed * 4, 255, 0));
      leds[k].r /= 2;
      leds[k].g /= 2;
      leds[k].b /= 2;
    }

    trains[i].position = (trains[i].position + trains[i].speed * (trains[i].sign ? -1 : 1) + LED_COUNT) % LED_COUNT;

    if (!cycle) {
      trains[i].speed -= trains[i].acceleration;

      if (!trains[i].speed) {
        trains[i].acceleration = !random8(0, TRAINS_ACCELERATION_CHANCE) ? -2 : 0;
      } else if (trains[i].speed >= TRAINS_SPEED_MAX) {
        trains[i].acceleration = !random8(0, TRAINS_DECELERATION_CHANCE);
      }
    }
  }

  cycle = (cycle - 1 + TRAINS_SPEED_CYCLE_COUNT) % TRAINS_SPEED_CYCLE_COUNT;
  return 5;
}
