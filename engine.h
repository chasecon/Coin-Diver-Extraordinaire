#ifndef ENGINE__H
#define ENGINE__H

#include <vector>
#include <SDL.h>
//#include "ioMod.h"
//#include "renderContext.h"
//#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "player.h"
#include "hud.h"
#include "frameGenerator.h"
#include "sprite.h"
#include "multisprite.h"
#include "runningSprite.h"
#include "gamedata.h"
#include "turningMultiSprite.h"
#include "runningTurningMultiSprite.h"
#include "stayingMultiSprite.h"
#include "player.h"
#include "menu.h"
#include "explodingSprite.h"
#include "collisionStrategy.h"
#include <map>
#include "smartSprite.h"
class Engine {
public:
  Engine (string choice);
  ~Engine ();
  int play();
  void switchSprite();

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;
  FrameGenerator& frameGen;

  SDL_Renderer * const renderer;
  World worldC;
  World worldB;
  World worldA;
  Viewport& viewport;

  std::vector<Drawable*> sprites;
  std::vector<Drawable*> spritesBack;
  std::vector<Drawable*> spritesMiddle;
  std::vector<Drawable*> spritesFront;
  std::vector<Drawable*> spritesExplosion;

  int currentSprite;
  //bool makeVideo;

  void draw() const;
  void update(Uint32);
  Player* player;
  Hud* hud;
  bool showHud;
  int hudTicks;
  string playerType;
    CollisionStrategy* strategy;
    int waitTimer;
    std::map<int,int> ignore;

  Engine(const Engine&)=delete;
  Engine& operator=(const Engine&)=delete;
    void checkForCollisions();

};
#endif