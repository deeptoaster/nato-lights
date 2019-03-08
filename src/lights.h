#include "pattern.h"

class LightsControl {
 public:
  LightsControl();
  template<class TPattern>
  void addPattern();
  void nextPattern();
  void off();
  void on();
  void previousPattern();
  void step();
 private:
  Pattern *pattern;
  Factory *patternFactory;
  unsigned char steps;
};

template<class TPattern>
void LightsControl::addPattern() {
  Factory *newFactory = (Factory *)new PatternFactory<TPattern>();

  if (!patternFactory) {
    patternFactory = newFactory;
  } else {
    newFactory->previous = patternFactory->previous;
    patternFactory->previous->next = newFactory;
  }

  newFactory->next = patternFactory;
  patternFactory->previous = newFactory;
}
