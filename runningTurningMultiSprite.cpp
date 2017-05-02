#include "runningTurningMultiSprite.h"
#include "gamedata.h"
#include "renderContext.h"

RunningTurningMultiSprite::RunningTurningMultiSprite( const std::string& name) :  
TurningMultiSprite(name) {}


RunningTurningMultiSprite::RunningTurningMultiSprite( const std::string& name, const float vscale, const float sscale) :  
TurningMultiSprite(name,vscale,sscale) {}

RunningTurningMultiSprite::RunningTurningMultiSprite(const RunningTurningMultiSprite& s) : 
TurningMultiSprite(s){}

void RunningTurningMultiSprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  float incr = getvScale() * getVelocityX() * static_cast<float>(ticks) * 0.001;
  setX(getX() + incr);

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
  }
  if ( getX() > worldWidth-frameWidth) {
    setVelocityX( -fabs( getVelocityX() ) );
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
