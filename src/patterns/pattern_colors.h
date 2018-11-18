#include "../pattern.h"

class PatternColors : public Pattern {
 public:
  void init();
  int step();
 private:
  int offset;
};
