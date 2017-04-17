#include "menu.h"


Menu& Menu::getInstance(){
  static Menu menu;
  return menu;
}

Menu::~Menu(){

}

Menu::Menu() :
  clock( Clock::getInstance() ),
  frameGen( FrameGenerator::getInstance()),
  io( IOmod::getInstance() ),
  rc( RenderContext::getInstance() ),
  renderer(rc->getRenderer()),
  WIDTH( Gamedata::getInstance().getXmlInt("view/width") ),
  HEIGHT( Gamedata::getInstance().getXmlInt("view/height") ),
  choice(0),
  chosenPlayer("diver")
{ }


void Menu::draw() { 
    SDL_SetRenderDrawColor(renderer, 0x05,0xff,0xff, 0xff);
    SDL_RenderClear(renderer);


  	std::stringstream strm;
//    strm << "FPS: " << clock.getFps();
    strm << "Avg FPS: "<<clock.getAvgFps();

  io.writeText(strm.str(), 25, HEIGHT-50,{255, 0, 0, 255 });

  io.writeText("W,A,S,D to choose settings", 5, 5,{255, 0, 0, 255 });
  io.writeText(Gamedata::getInstance().getXmlStr("screenTitle"), (WIDTH/2)-150,(HEIGHT/2)-50,{255, 0, 0, 255 });
 	io.writeText("---------------------------", (WIDTH/2)-150,(HEIGHT/2)-15,{255, 0, 0, 255 });
  io.writeText("Malloy Diver", (WIDTH/2)-150,(HEIGHT/2)+15,{255, 0, 0, 255 });
  io.writeText("Spongebob Diver", (WIDTH/2)-150,(HEIGHT/2)+45,{255, 0, 0, 255 });
  io.writeText("DinosaurVille (YeeVille)", (WIDTH/2)-150,(HEIGHT/2)+75,{255, 0, 0, 255 });
  io.writeText("*", (WIDTH/2)-160,(HEIGHT/2)+20+choice,{255, 0, 0, 255 });

  io.writeText("Chase Conklin", 25, HEIGHT-25,{0xff, 0, 0, 0});

    SDL_RenderPresent(renderer);

}

void Menu::levelSwitch(int i){
  if(!i){
if(choice == 0){
  choice=30;
            chosenPlayer="spongebob";

}else if(choice==30){
            chosenPlayer="yee";

choice=60;
}else if(choice==60){
choice=0;
              chosenPlayer="diver";

}
}else{
if(choice == 0){
  choice=60;
            chosenPlayer="spongebob";

}else if(choice==30){
            chosenPlayer="yee";

choice=0;
}else if(choice==60){
choice=30;
              chosenPlayer="diver";

}
}

}

string Menu::play(){



  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();

  while ( !done ) {
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }

      if(event.type == SDL_KEYDOWN) 
      {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q] || keystate[SDL_SCANCODE_RETURN]) 
        {
          done = true;
          break;
        }
        
         
          if (keystate[SDL_SCANCODE_F4] && !frameGen.getBool()) 
          {
            std::cout << "Initiating frame capture" << std::endl;
            frameGen.setBool(true);
          }else if (keystate[SDL_SCANCODE_F4] && frameGen.getBool()) 
          {
            std::cout << "Terminating frame capture" << std::endl;
            frameGen.setBool(false);
          }




        if( (keystate[SDL_SCANCODE_W] && keystate[SDL_SCANCODE_S]) || (!keystate[SDL_SCANCODE_W] && !keystate[SDL_SCANCODE_S])){
// do nothing here
        }else if(keystate[SDL_SCANCODE_W]){
//move menu up
            levelSwitch(1);
        }else if(keystate[SDL_SCANCODE_S]){
//move menu down
            levelSwitch(0);
        }

        if( (keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_D]) || (!keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_D])){
//do nothing
        }else if(keystate[SDL_SCANCODE_A]){
//menu left?
        }else if(keystate[SDL_SCANCODE_D]){
//menu right?       
 }
      }


}
   ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {


      clock.incrFrame();
      draw();
      //update(ticks);
      if ( frameGen.getBool()) {
        frameGen.makeFrame();
      }
    }
  }

          choice=0;
string temp=chosenPlayer;
chosenPlayer="diver";
return temp;

}



// void Hud::update(Uint32 ticks) { 
// 	if(ticks==0){
// 		std::cout<<"should never get here" <<std::endl;
// 	}

// }
