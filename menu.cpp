#include "menu.h"

// Menu& Menu::getInstance(){
//   static Menu menu;
//   return menu;
// }

void Menu::fix(){
          for(auto* s : spritesGood) s->setY(500);
        for(auto* s : spritesBad) s->setY(500);
        for(auto* s : spritesThing) s->setY(500);
}

Menu::~Menu(){
  for(auto it : spritesGood){ delete it; }
  for(auto it : spritesBad){ delete it; }
  for(auto it : spritesThing){ delete it; }
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
  chosenPlayer("diver"),
  spritesGood(),
  spritesBad(),
  spritesThing(),
  chosenPlayerInt(0)
{ 

MenuSprite* player = new MenuSprite("diver",1.0,1.0,0,300);
MenuSprite* villain = new MenuSprite("malloy",1.0,1.0,300,300);
MenuSprite* thing = new MenuSprite("book",1.0,0.15,300,300);
player->setVelocityX(200);
villain->setVelocityX(200);
thing->setVelocityX(200);
MenuSprite* player2 = new MenuSprite("spongebob",1.0,3.0,0,300);
MenuSprite* villain2 = new MenuSprite("bigJelly",1.0,2.5,300,300);
MenuSprite* thing2 = new MenuSprite("book",1.0,0.1,300,300);
player2->setVelocityX(200);
villain2->setVelocityX(200);
thing2->setVelocityX(200);
MenuSprite* player3 = new MenuSprite("yee",1.0,0.3,0,300);
MenuSprite* villain3 = new MenuSprite("flyDino",1.0,1.2,300,300);
MenuSprite* thing3 = new MenuSprite("book",1.0,0.1,300,300);
player3->setVelocityX(200);
villain3->setVelocityX(200);
thing3->setVelocityX(200);


spritesGood.push_back(player);
spritesBad.push_back(villain);
spritesThing.push_back(thing);

spritesGood.push_back(player2);
spritesBad.push_back(villain2);
spritesThing.push_back(thing2);

spritesGood.push_back(player3);
spritesBad.push_back(villain3);
spritesThing.push_back(thing3);
}


void Menu::draw() { 
  Viewport::getInstance().setY(0);
  Viewport::getInstance().setX(0);
  SDL_SetRenderDrawColor(renderer, 0x05,0xff,0xff, 0xff);
  SDL_RenderClear(renderer);
  //for(auto* s : sprites) s->draw();

  spritesGood[chosenPlayerInt]->draw();
  spritesBad[chosenPlayerInt]->draw();
  spritesThing[chosenPlayerInt]->draw();


  	std::stringstream strm;
//    strm << "FPS: " << clock.getFps();
    strm << "Avg FPS: "<<clock.getAvgFps();

  io.writeText(strm.str(), 25, HEIGHT-50,{255, 0, 0, 255 });

  io.writeText("W and S to navigate the menu, ENTER to choose level.", 5, 5,{255, 0, 0, 255 });
  io.writeText("Get points by gathering points and shooting missles, mines, and large fish.", 5, 30,{0, 0, 0, 255 });
  io.writeText("Get 50 points for the enemy to release your C++ book, grab it to win!", 5, 55,{0, 0, 0, 255 });
  io.writeText(Gamedata::getInstance().getXmlStr("screenTitle"), (WIDTH/2)-150,(HEIGHT/4)-50,{255, 0, 0, 255 });
 	io.writeText("---------------------------", (WIDTH/2)-150,(HEIGHT/4)-15,{255, 0, 0, 255 });
  io.writeText("Malloy Diver", (WIDTH/2)-150,(HEIGHT/4)+15,{255, 0, 0, 255 });
  io.writeText("Spongebob Diver", (WIDTH/2)-150,(HEIGHT/4)+45,{255, 0, 0, 255 });
  io.writeText("DinosaurVille (YeeVille) BETA", (WIDTH/2)-150,(HEIGHT/4)+75,{255, 0, 0, 255 });
  io.writeText("*", (WIDTH/2)-160,(HEIGHT/4)+20+choice,{255, 0, 0, 255 });

  io.writeText("Chase Conklin and Stephen Linnell", 25, HEIGHT-25,{0xff, 0, 0, 0});
  //for(auto* s : sprites) s->draw();

    SDL_RenderPresent(renderer);

}

void Menu::levelSwitch(int i){
  if(!i){
if(choice == 0){
  choice=30;
            chosenPlayer="spongebob";
            chosenPlayerInt = (chosenPlayerInt+1)%3;

}else if(choice==30){
            chosenPlayer="yee";
            chosenPlayerInt = (chosenPlayerInt+1)%3;

choice=60;
}else if(choice==60){
choice=0;
              chosenPlayer="diver";
            chosenPlayerInt = (chosenPlayerInt+1)%3;

}
}else{
if(choice == 0){
  choice=60;
            chosenPlayer="yee";
                        chosenPlayerInt = 2;


}else if(choice==30){
            chosenPlayer="diver";
                        chosenPlayerInt = 0;

choice=0;
}else if(choice==60){
choice=30;
              chosenPlayer="spongebob";
                        chosenPlayerInt = 1;

}
}

}

string Menu::play(){



  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
spritesGood[0]->setX(0);
spritesBad[0]->setX(300);
spritesThing[0]->setX(300);

  // SDLSound sound("sound/pokemonIntro.wav");
  SDLSound& sound = SDLSound::getInstance();

sound.startMusic();

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

        for(auto* s : spritesGood) s->update(ticks);
        for(auto* s : spritesBad) s->update(ticks);
        for(auto* s : spritesThing) s->update(ticks);
        // for(auto* s : spritesGood) s->setY(300);
        // for(auto* s : spritesBad) s->setY(300);
        // for(auto* s : spritesThing) s->setY(300);
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
