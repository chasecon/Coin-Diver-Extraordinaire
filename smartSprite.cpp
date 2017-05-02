#include <cmath>
#include "viewport.h"
#include "smartSprite.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}


  SmartSprite::SmartSprite(const std::string& name, Hud* h) : TurningMultiSprite(name),hud(h),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ) {}

  SmartSprite::SmartSprite(const std::string& name, float vScale, Hud* h) : TurningMultiSprite(name,vScale),hud(h),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ){}

  SmartSprite::SmartSprite(const std::string& name, float vScale, float sScale, Hud* h) : TurningMultiSprite(name,vScale,sScale),hud(h),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ){

    if(name == "malloyTop"){
      setY(70);
      setX(100);
    }else if(name == "mmalloyLeft"){
      setY(300);
      setX(0);
    }
        if(name == "malloyRight"){
      setY(400);
      setX(2800);
    }
    if(name == "coinBag"){
      setX(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"));
      setY(Gamedata::getInstance().getXmlInt(name+"/startLoc/y"));

    }


  }


void SmartSprite::shoot() { 

  if(getName()=="malloyTop" || getName()=="coinBag"){
  float x; 
  float y;
  // I'm not adding minSpeed to y velocity:
  Vector2f vNew;
  if(getVelocityX() >= 0 && frames == framesRight){
      x = getX()+(getScale()*getFrame()->getWidth());
      y = getY()+(getScale()*getFrame()->getHeight()/2);
      vNew = Vector2f(0, 200);
    }
    else{ 
      vNew = Vector2f(0,200);
      x = getX()-15;
      y = getY()+(getScale()*getFrame()->getHeight()/2);
    }
  bullets.shoot( Vector2f(x, y), vNew);
}else if(getName()=="mmalloyLeft"){
    float x; 
  float y;
  // I'm not adding minSpeed to y velocity:
  Vector2f vNew;
  if(getVelocityX() >= 0 && frames == framesRight){
      x = getX()+(getScale()*getFrame()->getWidth());
      y = getY()-30+(getScale()*getFrame()->getHeight()/2);
      vNew = Vector2f(200, 0);
    }
    else{ 
      vNew = Vector2f(200,0);
      x = getX()-15;
      y = getY()+(getScale()*getFrame()->getHeight()/2);
    }
  bullets.shoot( Vector2f(x, y), vNew);
}else if(getName() == "malloyRight"){
    float x; 
  float y;
  // I'm not adding minSpeed to y velocity:
  Vector2f vNew;
  if(getVelocityX() >= 0 && frames == framesRight){
      x = getX()+(getScale()*getFrame()->getWidth());
      y = getY()-30+(getScale()*getFrame()->getHeight()/2);
      vNew = Vector2f(-200, 0);
    }
    else{ 
      vNew = Vector2f(-200,0);
      x = getX()-15;
      y = getY()+(getScale()*getFrame()->getHeight()/2);
    }
  bullets.shoot( Vector2f(x, y), vNew);
}



}

bool SmartSprite::collidedWith( Drawable* obj)  {
  return bullets.collidedWith( obj );
}
bool SmartSprite::collidedWith( BulletPool* bulls)  {
  return bullets.collidedWith( bulls );
}


void SmartSprite::goLeft()  { 
  if (getX() > 0) setVelocityX( -fabs(getVelocityX()) ); 
}
void SmartSprite::goRight() { setVelocityX( fabs(getVelocityX()) ); }
void SmartSprite::goUp()    { setVelocityY( -fabs(getVelocityY()) ); }
void SmartSprite::goDown()  { setVelocityY( fabs(getVelocityY()) ); }

void SmartSprite::draw() const {
  TurningMultiSprite::draw();

    bullets.draw();

}

void SmartSprite::update(Uint32 ticks) {
  TurningMultiSprite::update(ticks);
      bullets.update(ticks);

  float x= getX()+getFrame()->getWidth()/2;
  float y= getY()+getFrame()->getHeight()/2;
 
  float ex= hud->getPlayerX()+hud->getPlayerW()/2;
  float ey= hud->getPlayerY()+hud->getPlayerH()/2;
    
if(getName()=="coinBag"){


      if ( std::abs(x-ex)<10){

      }else {
      if ( x > ex ) {
        goRight();
      }else if ( x < ex ) {
        goLeft(); 
      }     
      }
      if ( y > ey ) goDown();
      if ( y < ey ) goUp();

          if ( getX() < 0) {
      setX( 2000  );
    }
    if ( getX() > worldWidth-frameWidth) {
      setX(0 );
    }  

}else{
      if ( std::abs(x-ex)<10){

      }else {
      if ( x > ex ) {
        goLeft();
      }else if ( x < ex ) {
        goRight(); 
      }     
      }
      if ( y > ey ) goUp();
      if ( y < ey ) goDown();
    }
  
}


