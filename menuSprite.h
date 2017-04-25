#ifndef MENUSPRITE__H
#define MENUSPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"
#include "sprite.h"
#include "turningMultiSprite.h"

class MenuSprite : public TurningMultiSprite {
public:
  MenuSprite(const std::string&);
  MenuSprite(const std::string&, float vScale);
  MenuSprite(const std::string&, float vScale, float sScale);
  MenuSprite(const std::string&, float vScale, float sScale, float x, float y);
  MenuSprite(const TurningMultiSprite&);

  virtual void draw() const;
  virtual void update(Uint32 ticks);


protected:
  


};
#endif
