#include "hud.h"


Hud::~Hud(){

}

Hud::Hud(const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(0,0), 1.0
           ),
  clock( Clock::getInstance() ),
  io( IOmod::getInstance() ),
  rc( RenderContext::getInstance() ),
  width(Gamedata::getInstance().getXmlInt(name+"/width")),
  height(Gamedata::getInstance().getXmlInt(name+"/height")),
  hudRect({(int)getX(),(int)getY(),width,height}),
  renderer(rc->getRenderer()),
  playerHealth(100),
  playerLives(10),
  playerX(0.0),
  playerY(0.0),
  playerH(0),
  playerW(0)
{ }

Hud::Hud(const Hud& s) :
  Drawable(s), 
    clock( Clock::getInstance() ),
    io( IOmod::getInstance() ),
    rc( RenderContext::getInstance() ),
	width( s.width ),
	height( s.height ),
	hudRect({(int)getX(),(int)getY(),width,height}),
    renderer(rc->getRenderer()),
    playerHealth(100),
    playerLives(10)
  { }

void Hud::draw() const { 

    SDL_SetRenderDrawColor( renderer, 208, 209, 210, 255 );
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
    SDL_RenderFillRect( renderer, &hudRect );
    SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
    SDL_RenderDrawRect( renderer, &hudRect );

  	std::stringstream strm;
    std::stringstream strm2;
    std::stringstream strm3;    
    std::stringstream strm4;
    std::stringstream strm5;
    strm << "FPS: " << clock.getFps();

    strm2 << "Avg FPS: "<<clock.getAvgFps();
              // std::cout << strm2.str()<<std::endl;

    strm3 << "Seconds: "<<clock.getSeconds();

    strm4 << "Lives: "<<getLives();

    strm5 << "Health: "<<getHealth();
 	io.writeText(strm.str(), hudRect.x+5, hudRect.y+65,{255, 0, 0, 255 });
  io.writeText(strm2.str(), hudRect.x+5, hudRect.y+95,{255, 0, 0, 255 });
  io.writeText("W,A,S,D to move", hudRect.x+5, hudRect.y+5,{255, 0, 0, 255 });
  io.writeText(strm3.str(), hudRect.x+5, hudRect.y+125,{255, 0, 0, 255 });
  io.writeText(strm4.str(), hudRect.x+5, hudRect.y+155,{255, 0, 0, 255 });
  io.writeText(strm5.str(), hudRect.x+5, hudRect.y+185,{255, 0, 0, 255 });

  	//io.writeText("Chase Conklin", 350, 40,{0xff, 0, 0, 0});
  	io.writeText(Gamedata::getInstance().getXmlStr("username"), hudRect.x+5,hudRect.y+35,{255, 0, 0, 255 });
  	//io.writeText(Gamedata::getInstance().getXmlStr("screenTitle"), hudRect.x+5,hudRect.y+5);


}



void Hud::update(Uint32 ticks) { 
	if(ticks==0){
		std::cout<<"should never get here" <<std::endl;
	}

}
