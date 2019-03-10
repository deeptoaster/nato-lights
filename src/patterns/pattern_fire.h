#include "../pattern.h"

#define FIRE_G_R_OFFSET 48
#define FIRE_SCALE_MIN 64
#define FIRE_SCALE_MAX 128
#define FIRE_SPAWN_FREQUENCY 128

class PatternFire : public Pattern {
 public:
  void init();
  unsigned char step();
};
