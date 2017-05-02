#include "player.h"
#include "gamedata.h"
#include "renderContext.h"



Player::Player( const std::string& name) :  
TurningMultiSprite(name),
  xPressed(false),
  yPressed(false),
  initVelocity(getVelocity()),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ) {}

Player::Player( const std::string& name, float vScale) :  
TurningMultiSprite(name,vScale),
  xPressed(false),
  yPressed(false),
  initVelocity(getVelocity()),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ) {}

  Player::Player( const std::string& name, float vScale, float sScale) :  
TurningMultiSprite(name,vScale,sScale),
  xPressed(false),
  yPressed(false),
  initVelocity(getVelocity()),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ) {}

  Player::Player( const std::string& name, int x, int y) :  
TurningMultiSprite(name),
  xPressed(false),
  yPressed(false),
  initVelocity(getVelocity()),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ){setPosition(Vector2f(x,y));}

  Player::Player( const std::string& name, float vScale, float sScale, int x, int y) :  
  TurningMultiSprite(name,vScale,sScale),
  xPressed(false),
  yPressed(false),
  initVelocity(getVelocity()),
  bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ) {setPosition(Vector2f(x,y));}

Player::Player(const Player& s) : 
TurningMultiSprite(s),
  xPressed(s.xPressed),
  yPressed(s.yPressed),
  initVelocity(getVelocity()),
  bulletName( Gamedata::getInstance().getXmlStr(s.getName()+"/bullet") ),
  bullets( bulletName ),
  minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ) {}

void Player::draw() const { 
  frames[currentFrame]->draw(getX(), getY(),getsScale());
  bullets.draw();
}


void Player::stopY(){
  setVelocityY(0.0);
}
void Player::stopX(){
  setVelocityX(0.0);
}

void Player::right(){
xPressed=true;
if(getX()<worldWidth-frameWidth){
  setVelocityX(-initVelocity[0]);
}
}

void Player::left(){
xPressed=true;
if(getX()>0){
  setVelocityX(initVelocity[0]);
}
}

void Player::up(){
yPressed=true;
if(getY() > 100){
  setVelocityY(-initVelocity[1]);
}
}

void Player::down(){

yPressed=true;
/*
if(getY() < worldHeight -frameHeight){
  setVelocityY(initVelocity[1]);
}*/
if(getY() < worldHeight -(getScale()*(getFrame()->getHeight()))){
  setVelocityY(initVelocity[1]);
}
}

void Player::speedUp(){


}
void Player::speedDown(){

  setVelocityY(initVelocity[1]);
  setVelocityX(initVelocity[0]);

}

void Player::shoot() { 
  float x; 
  float y;
  // I'm not adding minSpeed to y velocity:
  Vector2f vNew;
  if(getVelocityX() >= 0 && frames == framesRight){
      x = getX()+(getScale()*getFrame()->getWidth());
      y = getY()+(getScale()*getFrame()->getHeight()/2);
      vNew = Vector2f(minSpeed+getVelocityX(), 0);
    }
    else{ 
      vNew = Vector2f(getVelocityX() -minSpeed , 0);
      x = getX()-15;
      y = getY()+(getScale()*getFrame()->getHeight()/2);
    }
  bullets.shoot( Vector2f(x, y), vNew);
}

bool Player::collidedWith(const Drawable* obj)  {
  return bullets.collidedWith( obj );
}

void Player::update(Uint32 ticks) { 
    if(  !((getVelocityX() == 0) && (  getVelocityY() == 0)) )  {
      advanceFrame(ticks);

    }
    bullets.update(ticks);

if(getVelocityY()==0)
  setY(getY()+1.0);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  //double incrY = getVelocityY() * static_cast<float>(ticks) * 0.001;

  setPosition(getPosition() + incr);

  if ( getY() < 80) {

   stopY();

  }
  
    if ( getY() > worldHeight-(getScale()*(getFrame()->getHeight()))) {
        setY(getY() - incr[1]);
      setY(getY()-1.0);

  }

  if ( getX() < 0) {
    stopX();
  }
  if ( getX() > worldWidth-frameWidth) {
    stopX();
  }   
  if(getVelocityX() < 0){
    if(frames != framesLeft){
      frames = framesLeft;
    }

  }else if (getVelocityX() > 0){
    if(frames != framesRight)
    {
        frames = framesRight;
    }
  }

  if(!xPressed) stopX();
  yPressed=false;
  xPressed=false;


}
