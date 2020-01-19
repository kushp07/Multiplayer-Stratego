#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include <string>
#include "observer.h"
#include "subject.h"
#include "state.h"
#include "info.h"
#include "display.h"
using namespace std;

class TextDisplay: public gameDisplay {
 public:
  TextDisplay(int n);

  void notify(Subject<State> &whoNotified, bool empty) override;

  friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
#endif
