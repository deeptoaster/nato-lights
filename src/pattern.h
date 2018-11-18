#pragma once

class Pattern {
 public:
  virtual void init() {}
  virtual int step() {}
  virtual ~Pattern() {}
};

class Factory{
 public:
  virtual Pattern *getInstance() = 0;
  Factory *next;
  Factory *previous;
};

template<class TPattern>
class PatternFactory : Factory {
  Pattern *getInstance();
  Factory *next;
  Factory *previous;
};

template<class TPattern>
Pattern *PatternFactory<TPattern>::getInstance() {
  return new TPattern();
}
