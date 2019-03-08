#include "src/common.h"
#include "src/lights.h"
#include "src/pattern.h"
#include "src/patterns/pattern_colors.h"
#include "src/patterns/pattern_fire.h"

unsigned long debounce;
CRGB leds[LED_BUFFER_SIZE];
LightsControl Lights;
HardwareControl Hardware;

void show(unsigned char strip, unsigned short offset, unsigned short count) {
  for (short i = LED_COUNT - 1; i >= offset + count; i--) {
    leds[i + LED_BUFFER_PADDING] = leds[i];
  }

  for (short i = count - 1; i >= 0; i--) {
    for (unsigned char j = 0; j < LED_DUPLICATION; j++) {
      leds[i * LED_DUPLICATION + j + offset] = leds[i + offset];
    }
  }

  FastLED[strip].showLeds();

  for (unsigned short i = 0; i < count; i++) {
    leds[i + offset] = leds[i * LED_DUPLICATION + offset];
  }

  for (unsigned short i = offset + count; i < LED_COUNT; i++) {
    leds[i] = leds[i + LED_BUFFER_PADDING];
  }
}

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif

  FastLED.addLeds<LED_TYPE, LED_PIN_1>(leds, LED_OFFSET_1, LED_COUNT_1 * LED_DUPLICATION);
  FastLED.addLeds<LED_TYPE, LED_PIN_2>(leds, LED_OFFSET_2, LED_COUNT_2 * LED_DUPLICATION);
  FastLED.addLeds<LED_TYPE, LED_PIN_3>(leds, LED_OFFSET_3, LED_COUNT_3 * LED_DUPLICATION);
  Lights = LightsControl();
  Lights.addPattern<PatternColors>();
  Lights.addPattern<PatternFire>();
  Hardware = HardwareControl();
}

void loop() {
  Lights.step();
  show(0, LED_OFFSET_1, LED_COUNT_1);
  show(1, LED_OFFSET_2, LED_COUNT_2);
  show(2, LED_OFFSET_3, LED_COUNT_3);
  delay(1);

  if (Hardware.getNextButtonPressed()) {
    Lights.nextPattern();
  }
}
