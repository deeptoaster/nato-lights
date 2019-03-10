#include "../pattern.h"

#define TRAINS_ACCELERATION_CHANCE 2
#define TRAINS_COUNT_MAX 12
#define TRAINS_DECELERATION_CHANCE 4
#define TRAINS_SPEED_MAX 6
#define TRAINS_SPEED_CYCLE_COUNT 8

struct train {
  signed char sign : 1;
  signed char acceleration : 2;
  unsigned char speed : 3;
  unsigned short position : 10;
};

class PatternTrains : public Pattern {
 public:
  void init();
  unsigned char step();
 private:
  unsigned char cycle;
  struct train trains[TRAINS_COUNT_MAX];
};
