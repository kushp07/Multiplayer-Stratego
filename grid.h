#ifndef GRID_H
#define GRID_H
#include <iostream>
#include <vector>
#include <cstddef>
#include <string>
#include "cell.h"
#include "data.h"
#include "virus.h"
#include "player.h"
#include "state.h"
//#include "info.h"
#include <memory>
#include "textdisplay.h"
#include "graphicsdisplay.h"

class TextDisplay;
template <typename StateType> class Observer;

class Grid {
  std::vector<std::vector<Cell>> theGrid; 
  TextDisplay *td = nullptr;
  GraphicsDisplay *ob = nullptr;
  int player = 1;
  size_t width = 0;
  size_t height = 0;
  bool graphics = false;

  // Ability methods:
  void linkboost(char link);
  void scan(char link);
  void polarize(char link);
  void firewall(int row, int col);
  void download(char link);
  void wildcard(char newAbility);
  void extrastrength(char link);
  void trap(int row, int col);

 public:
  Grid(bool graphics);
  ~Grid();
  Player *player1;
  Player *player2;
  void setObserver(GraphicsDisplay *ob);
  int whoWon();
  // bool isWinner(); 
  void init(size_t n, vector<string> p1order, vector<string> p2order,
	                  vector<char> p1abilities, vector<char> p2abilities ); // Initialize Grid
  void move(char link, string dir);
  bool invalidMove(string dir, int index, int moves);
  string abilities();
  void ability(size_t which, std::istream &file);
  int getTurn();
  friend std::ostream &operator<<(std::ostream &out, const Grid &g);
};

#endif
