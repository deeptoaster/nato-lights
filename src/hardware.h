#include "pattern.h"

class HardwareControl {
 public:
  HardwareControl();
  bool getNextButtonPressed();
  unsigned short getPot1Value();
  unsigned short getPot2Value();
 private:
  unsigned char nextButtonState;
  unsigned char nextButtonStateDebounced;
  unsigned long debounce;
};
