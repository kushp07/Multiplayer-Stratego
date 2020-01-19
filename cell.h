#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include "link.h"
#include "state.h"
#include "subject.h"
#include "observer.h"
#include "info.h"

// make cell a subject after
class Cell: public Subject<State> {
  const size_t row;
  const size_t col;
  Link *l = nullptr;
  bool server;
  bool player1firewall;
  bool player2firewall;
  bool player1trap;
  bool player2trap;

 public:
  Cell(size_t r, size_t c, bool server = false, bool player1firewall = false, bool player2firewall = false, bool player1trap = false, bool player2trap = false);
  void addLink(Link *l);
  bool isServer();
  void setLink(Link * l);
  Link *getLink() override;
  void setfirewall(int player, bool b);
  bool isfirewall(int player); 
  void settrap(int player, bool b);
  bool istrap(int player);
  //void notify(Subject<Info, State> &whoFrom) override;
  CellInfo2 getInfo2() const override;
};
#endif
