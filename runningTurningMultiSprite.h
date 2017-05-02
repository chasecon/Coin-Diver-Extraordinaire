#ifndef RUNNINGTURNINGMULTISPRITE__H
#define RUNNINGTURNINGMULTISPRITE__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"
#include "turningMultiSprite.h"

class RunningTurningMultiSprite : public TurningMultiSprite {
public:
  RunningTurningMultiSprite(const std::string&);
  RunningTurningMultiSprite(const RunningTurningMultiSprite&);
  RunningTurningMultiSprite( const std::string& name, const float vscale, const float sscale); 

  virtual void update(Uint32 ticks);

protected:

};
#endif
