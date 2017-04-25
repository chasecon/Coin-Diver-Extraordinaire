#include "menuSprite.h"
#include "gamedata.h"
#include "renderContext.h"


MenuSprite::MenuSprite( const std::string& name) :
  TurningMultiSprite(name)
{ 
  setVelocityY(0.0);
}

MenuSprite::MenuSprite( const std::string& name, float vScale) :
  TurningMultiSprite(name,vScale)
{ 
    setVelocityY(0.0);

  }

MenuSprite::MenuSprite( const std::string& name, float vScale, float sScale) :
  TurningMultiSprite(name, vScale,sScale)
{ 
    setVelocityY(0.0);

  }

  MenuSprite::MenuSprite( const std::string& name, float vScale, float sScale, float x, float y) :
  TurningMultiSprite(name, vScale,sScale)
{ 
    setVelocityY(0.0);
    setX(x);
    setY(y);

  }

MenuSprite::MenuSprite(const TurningMultiSprite& s) :
  TurningMultiSprite(s)
  {   
    setVelocityY(0.0);
  }

void MenuSprite::draw() const { 
  // frames[currentFrame]->draw(getX(), getY(),getsScale());
               // std::cout << getName() << " y is: "<<getY()<<std::endl;

  frames[currentFrame]->draw(getX(), getY() ,getsScale());
}



void MenuSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getvScale()*getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);


    // if ( getY() < 0) {
    //   setVelocityY( fabs( getVelocityY() ) );
    // }
    // if ( getY() > worldHeight-frameHeight) {
    //   setVelocityY( -fabs( getVelocityY() ) );
    // }

    if ( getX() < 0) {
      setVelocityX( fabs( getVelocityX() ) );
    }
    if ( getX() > Gamedata::getInstance().getXmlInt("view/width")-(getsScale()*(getFrame()->getWidth()))) {
      setX(-(getsScale()*(getFrame()->getWidth())) );
    }  

  if(getVelocityX() < 0){
    if(frames != framesLeft){
      frames = framesLeft;
    }

  }else{
    if(frames != framesRight)
    {
        frames = framesRight;
    }
  }

}
