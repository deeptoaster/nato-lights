#include "lights.h"

#include "common.h"

LightsControl::LightsControl() {
  patternFactory = NULL;
  pattern = NULL;
  steps = 0;
}

void LightsControl::nextPattern() {
  if (patternFactory) {
    if (!pattern) {
      on();
    } else {
      patternFactory = patternFactory->next;

#ifdef DEBUG
      Serial.print("[Lights] Next pattern: ");
      Serial.println((int)patternFactory);
#endif

      off();
    }
  }
}

void LightsControl::off() {
#ifdef DEBUG
  Serial.println("[Lights] Turning off.");
#endif

  delete pattern;
  pattern = NULL;
  steps = 0;

  for (unsigned short i = 0; i < LED_COUNT; i++) {
    leds[i] = CRGB::Black;
  }
}

void LightsControl::on() {
#ifdef DEBUG
  Serial.println("[Lights] Turning on.");
#endif

  pattern = patternFactory->getInstance();
  pattern->init();
}

void LightsControl::previousPattern() {
  if (patternFactory) {
    if (!pattern) {
      on();
    } else {
      patternFactory = patternFactory->previous;

#ifdef DEBUG
      Serial.print("[Lights] Previous pattern: ");
      Serial.println((int)patternFactory);
#endif

      off();
    }
  }
}

void LightsControl::step() {
  if (pattern) {
    if (!steps) {
      steps = pattern->step();
    }

    steps--;
  }
}
