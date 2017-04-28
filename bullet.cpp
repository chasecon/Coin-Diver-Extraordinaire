#include <iostream>
#include <cmath>
#include "bullet.h"
#include "collisionStrategy.h"

void Bullet::update(Uint32 ticks) { 
  Vector2f pos = getPosition();
  Sprite::update(ticks);
  //std::cout<<getVelocityY()<<std::endl;
  distance += ( hypot(getX()-pos[0], getY()-pos[1]) );
  if (distance > maxDistance) tooFar = true;

}

