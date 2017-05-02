#ifndef HUD__H
#define HUD__H
#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"
#include "renderContext.h"
#include "clock.h"
#include "ioMod.h"
#include <sstream>


class Hud : public Drawable {
public:
  Hud(const std::string&);
  // Hud(const Hud&);
  ~Hud();
  Hud& operator=(const Hud&);


  virtual void draw() const;

  virtual void update(Uint32 ticks);
  const Frame* getFrame() const{return NULL;};

  int getScore() const{return score;}
  void setScore(int s) { score=s;}
  int getLives() const{return playerLives;}
  int getHealth() const{return playerHealth;}
  void setLives(int lives) { playerLives=lives;}
  void setHealth(int health) { playerHealth=health;}
  float getPlayerX(){return playerX;}
  float getPlayerY(){return playerY;}
  int getPlayerH(){return playerH;}
  int getPlayerW(){return playerW;}
  void setPlayerX(float x){playerX=x;}
  void setPlayerY(float y){playerY=y;}
  void setPlayerH(int h){playerH=h;}
  void setPlayerW(int w){playerW=w;}
protected:
Clock& clock;
Hud(const Hud&);
const IOmod& io;
const RenderContext* rc;


int width;
int height;
SDL_Rect hudRect;
SDL_Renderer * const renderer;
int playerHealth;
int playerLives;
float playerX;
float playerY;
int playerH;
int playerW;
int score;

};
#endif
