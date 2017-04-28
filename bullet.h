#ifndef BULLET__H
#define BULLET__H

#include <iostream>
#include "sprite.h"
#include "gamedata.h"

class Bullet : public Sprite {
public:
  explicit Bullet(const string& name) :
    Sprite(name), 
    distance(0), 
    maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")), 
    tooFar(false) 
  { 
if(name=="mineDrop"){
  setScale(0.1);
}

  }

  explicit Bullet(const string& name,double scale) :
  Sprite(name,scale,scale), 
  distance(0), 
  maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")), 
  tooFar(false) 
  { 

if(name=="mineDrop"){
  setScale(0.1);
}
  }
  virtual void update(Uint32 ticks);
  bool goneTooFar() const { return tooFar; }
  void reset() {
    tooFar = false;
    distance = 0;
  }

private:
  float distance;
  float maxDistance;
  bool tooFar;
};
#endif
