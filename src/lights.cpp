#include "lights.h"

#include <FastLED.h>

Lights::Lights() {
  patternFactory = NULL;
  pattern = NULL;
  steps = 0;
}

void Lights::nextPattern() {
  if (patternFactory) {
    if (!pattern) {
      on();
    } else {
      patternFactory = patternFactory->next;
      off();
    }
  }
}

void Lights::off() {
  delete pattern;
  pattern = NULL;
  steps = 0;
}

void Lights::on() {
  pattern = patternFactory->getInstance();
  pattern->init();
}

void Lights::previousPattern() {
  if (patternFactory) {
    if (!pattern) {
      on();
    } else {
      patternFactory = patternFactory->previous;
      off();
    }
  }
}

void Lights::step() {
  if (pattern) {
    if (!steps) {
      steps = pattern->step();
    }

    steps--;
  }
}
