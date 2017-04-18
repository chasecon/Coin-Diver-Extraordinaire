#include <cmath>
#include "viewport.h"
#include "smartSprite.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}

// SmartSprite::SmartSprite(const std::string& name, 
//                          const Vector2f& pos, int w, int h) :
//  TurningMultiSprite(name, pos, 
//    Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"), 
//             Gamedata::getInstance().getXmlInt(name+"/speedY"))
//  ), 
//  io(IOManager::getInstance())
// { }
//, io( IOManager::getInstance() )
  SmartSprite::SmartSprite(const std::string& name, Hud* h) : TurningMultiSprite(name),hud(h) {}

  SmartSprite::SmartSprite(const std::string& name, float vScale, Hud* h) : TurningMultiSprite(name,vScale),hud(h){}

  SmartSprite::SmartSprite(const std::string& name, float vScale, float sScale, Hud* h) : TurningMultiSprite(name,vScale,sScale),hud(h){}


void SmartSprite::goLeft()  { 
  if (getX() > 0) setVelocityX( -fabs(getVelocityX()) ); 
}
void SmartSprite::goRight() { setVelocityX( fabs(getVelocityX()) ); }
void SmartSprite::goUp()    { setVelocityY( -fabs(getVelocityY()) ); }
void SmartSprite::goDown()  { setVelocityY( fabs(getVelocityY()) ); }

void SmartSprite::draw() const {
  TurningMultiSprite::draw();
  // int x = 10+ X() - Viewport::getInstance().X();
  // int y = 10+ Y() - Viewport::getInstance().Y();
  // std::stringstream strm;
  // strm << currentMode;
  // io.printMessageBlackAt( strm.str(), x, y); 
}

void SmartSprite::update(Uint32 ticks) {
  TurningMultiSprite::update(ticks);
  float x= getX()+getFrame()->getWidth()/2;
  float y= getY()+getFrame()->getHeight()/2;
  // float ex= playerPos[0]+playerWidth/2;
  // float ey= playerPos[1]+playerHeight/2;  
  float ex= hud->getPlayerX()+hud->getPlayerW()/2;
  float ey= hud->getPlayerY()+hud->getPlayerH()/2;
  //float distanceToEnemy = ::distance( x, y, ex, ey );

      if ( x > ex ) goLeft();
      if ( x < ex ) goRight();
      if ( y > ey ) goUp();
      if ( y < ey ) goDown();
    
  
}

