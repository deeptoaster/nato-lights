#include "../pattern.h"

#define COLORS_SPEED_MAX (LED_COUNT / 16)

class PatternColors : public Pattern {
 public:
  void init();
  unsigned char step();
 private:
  unsigned short i;
  unsigned short offset;
};
