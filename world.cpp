#include <iostream>
#include "world.h"
#include "renderContext.h"

World::World(const std::string& name, int fact) : 
  frame( RenderContext::getInstance()->getFrame(name) ),
  factor(fact),
    worldWidth( Gamedata::getInstance().getXmlInt("world/width") ),
    frameWidth( frame->getWidth() ),
    viewX(0.0), viewY(0.0), 
    view(Viewport::getInstance()) 
{ }

void World::update() {
    // std::cout << view.getX() << std::endl;
    // std::cout << factor << std::endl;
    // std::cout << frameWidth << std::endl;

  viewX = static_cast<int>(view.getX() / factor) % frameWidth;
  viewY = view.getY();

}

void World::draw() const { 
   frame->draw(0,0,-viewX,-viewY);
   frame->draw(0,0,frameWidth-viewX,-viewY);
  // frame->draw(0,0,-Gamedata::getInstance().getXmlInt("world/width"),-Gamedata::getInstance().getXmlInt("world/height"));
  // frame->draw(0,0,Gamedata::getInstance().getXmlInt("world/width"),-Gamedata::getInstance().getXmlInt("world/height"));
}

