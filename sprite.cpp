#include <cmath>
#include "sprite.h"
#include "gamedata.h"
#include "renderContext.h"

Sprite::Sprite(const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedY")),
           1.0 
           ),
  frame( RenderContext::getInstance()->getFrame(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight())
{ }

Sprite::Sprite(const std::string& name, const double vs, const double ss) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedY")),
           vs,
           ss 
           ),
  frame( RenderContext::getInstance()->getFrame(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight())
{ }

Sprite::Sprite(const std::string& name, const Frame* f,const double vs, const double ss) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedY")),
           vs,
           ss 
           ),
  frame( f ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight())
{ }
Sprite::Sprite(const std::string& name,const double vs, const double ss, float x, float y) :
  Drawable(name,
           Vector2f(x,y), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedY")),
           vs,
           ss 
           ),
  frame( RenderContext::getInstance()->getFrame(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight())
{ }


Sprite::Sprite(const Drawable* d,const Drawable* dd) :
  Drawable(d->getName(),
           d->getPosition(), 
           d->getVelocity(),
           dd->getvScale(),
           dd->getsScale() 
           ),
  frame( d->getFrame() ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight())
{ }

Sprite::Sprite(const std::string& name, const Frame* f) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"), 
                    Gamedata::getInstance().getXmlInt(name+"/speedY")),
           1.0 
           ),
  frame( f ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(f->getWidth()),
  frameHeight(f->getHeight())
{ }

Sprite::Sprite(const Sprite& s) :
  Drawable(s), 
  frame(s.frame),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight())
{ }

Sprite& Sprite::operator=(const Sprite& rhs) {
  Drawable::operator=( rhs );
  frame = rhs.frame;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  return *this;
}

void Sprite::draw() const { 
  frame->draw(getX(), getY(),getsScale()); 
}

void Sprite::update(Uint32 ticks) { 
// if(getName()=="mineDrop"){
// setVelocityY(200);
// setScale(0.15);
// }

  //std::cout <<getName()<<", "<<getsScale()<<std::endl;
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  // if ( getY() < 0) {
  //   setVelocityY( std::abs( getVelocityY() ) );
  // }
  // if ( getY() > worldHeight-frameHeight) {
  //   setVelocityY( -std::abs( getVelocityY() ) );
  // }

  if ( getX() < 0) {
    setVelocityX( std::abs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-frameWidth) {
    setVelocityX( -std::abs( getVelocityX() ) );
  }  
}
