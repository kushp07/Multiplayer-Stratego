#ifndef STATE_H
#define STATE_H

enum class StateType { Cell, Player };
//enum class ObjectType { Cell, Player };

struct State {
  StateType statetype;  // See above
  //ObjectType objecttype;
};

#endif
