#include "../pattern.h"

class PatternFire : public Pattern {
 public:
  void init();
  int step();
 private:
  int i;
  int j;
  int scale;
};
