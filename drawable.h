#ifndef DRAWABLE__H
#define DRAWABLE__H
#include <SDL.h>
#include <iostream>
#include <string>
#include "vector2f.h"
#include "frame.h"
// Drawable is an Abstract Base Class (ABC) that
// specifies the methods that derived classes may
// and must have.
class Drawable {
public:
  Drawable(const std::string& n, const Vector2f& pos, const Vector2f& vel, const float vs, const float ss): 
    name(n), position(pos), velocity(vel), vScale(vs),sScale(ss) {}
    Drawable(const std::string& n, const Vector2f& pos, const Vector2f& vel, const float s): 
    name(n), position(pos), velocity(vel), vScale(s),sScale(s) {}

  Drawable(const Drawable& s) : 
    name(s.name), position(s.position), velocity(s.velocity), vScale(s.vScale), sScale(s.sScale)
    { }

  virtual ~Drawable() {}

  virtual void draw() const = 0;
  virtual void update(Uint32 ticks) = 0;

  const std::string& getName() const { return name; }
  void setName(const std::string& n) { name = n;    }

  virtual const Frame* getFrame() const = 0;

  float getX() const  { return position[0]; }
  void  setX(float x) { position[0] = x;    }

  float getY() const  { return position[1]; }
  void  setY(float y) { position[1] = y;    }

  float getVelocityX() const   { return velocity[0]; }
  void  setVelocityX(float vx) { velocity[0] = vx;   }
  float getVelocityY() const   { return velocity[1]; }
  void  setVelocityY(float vy) { velocity[1] = vy;   }

  const Vector2f& getVelocity() const    { return velocity; }
  void  setVelocity(const Vector2f& vel) { velocity = vel;  }
  const Vector2f& getPosition() const    { return position; }
  void  setPosition(const Vector2f& pos) { position = pos;  }
    inline float getvScale()const{ return vScale; }
  void  setvScale(float s){ vScale = s; }
    inline float getsScale()const{ return sScale; }
    inline float getScale()const{ return sScale; }
  void  setsScale(float s){ sScale = s; }
  void  setScale(float s){ vScale = sScale = s; }

private:
  std::string name;
  Vector2f position;
  Vector2f velocity;
  float vScale;
  float sScale;
};
#endif
