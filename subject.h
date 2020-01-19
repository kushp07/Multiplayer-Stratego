#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <iostream>
#include "info.h"
using namespace std;
class Link;

template <typename StateType> class Observer;

template <typename StateType> class Subject {
  std::vector<Observer<StateType>*> observers;
  StateType state;
 protected:
  void setState(StateType newS);
 public:
  void attach(Observer<StateType> *o);  
  void notifyObservers(bool empty);
  StateType getState() const;
  virtual Link* getLink();
  virtual PlayerInfo getInfo() const;
  virtual CellInfo2 getInfo2() const;
};


template <typename StateType>
void Subject<StateType>::attach(Observer<StateType> *o) {
  observers.emplace_back(o);
}

template <typename StateType>
void Subject<StateType>::notifyObservers(bool empty) {
  for (auto &ob : observers) {
	  ob->notify(*this, empty);
  }
}

template <typename StateType>
void Subject<StateType>::setState(StateType newS) { state = newS; }

template <typename StateType>
StateType Subject<StateType>::getState() const { return state; }

template <typename StateType>
Link * Subject<StateType>::getLink() {return nullptr; }

template <typename StateType>
CellInfo2 Subject<StateType>::getInfo2() const{
  return CellInfo2();
}

template <typename StateType>
PlayerInfo Subject<StateType>::getInfo() const {
	vector<string> v;
  vector<char> a;
	return PlayerInfo(0,0,a,v,0,nullptr);
}

#endif
