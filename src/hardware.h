#include "pattern.h"

class HardwareControl {
 public:
  HardwareControl();
  bool getNextButtonPressed();
  int getPot1Value();
  int getPot2Value();
 private:
  int nextButtonState;
  int nextButtonStateDebounced;
  unsigned long debounce;
};
