#ifndef SMARTSPRITE__H
#define SMARTSPRITE__H
#include <iostream>
#include "turningMultiSprite.h"
//#include "ioMod.h"
#include "hud.h"
#include "bulletPool.h"
// SmartSprite is an observer of subject SubjectSprite, which
// in this example is a spinning star.

class SmartSprite : public TurningMultiSprite {
public:
  //SmartSprite(const std::string&, const Vector2f& pos, int w, int h);
  SmartSprite(const std::string&, Hud* h);
  SmartSprite(const std::string&, float vScale, Hud* h);
  SmartSprite(const std::string&, float vScale, float sScale, Hud* h);

  void draw() const;
  void update(Uint32 ticks);
  void goLeft();
  void goRight();
  void goUp();
  void goDown();
  void shoot();
  virtual bool collidedWith(const Drawable*) const;


private:	
  //IOmod& io;	
  Hud* hud;
  SmartSprite(const SmartSprite &);
  SmartSprite& operator=(const SmartSprite &rhs);
  std::string bulletName;
  BulletPool bullets;
    float minSpeed;
};
#endif