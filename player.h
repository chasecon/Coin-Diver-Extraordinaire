#ifndef PLAYER__H
#define PLAYER__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"
#include "turningMultiSprite.h"

class Player : public TurningMultiSprite {
public:
  Player(const std::string&);
  Player(const Player&);
  Player(const std::string&,float vScale);
  Player(const std::string&,float vScale, float sScale);
  Player(const std::string&,int x, int y);
  Player( const std::string& name, float vScale, float sScale, int x, int y); 

  //virtual void draw() const;
    virtual void draw() const;

  virtual void update(Uint32 ticks);
  /*virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
*/
  void stopX();
  void stopY();
  void right();
  void left();
  void up();
  void down();
  void speedUp();
  void speedDown();

protected:

  bool xPressed;
  bool yPressed;
  Vector2f initVelocity;

  /*
  std::vector<Frame *> frames;
  const std::vector<Frame *> framesRight;
  const std::vector<Frame *> framesLeft;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int worldWidth;
  int worldHeight;
  int frameWidth;
  int frameHeight;
*/
  //void advanceFrame(Uint32 ticks);
};
#endif
