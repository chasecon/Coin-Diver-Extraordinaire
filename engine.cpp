#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "engine.h"

#include <random>

class SpriteLess {
public:
  bool operator()(const Drawable* lhs, const Drawable* rhs) const {
    return lhs->getsScale() < rhs->getsScale();
  }
};

Engine::~Engine() { 
  std::cout << "Terminating program" << std::endl;
  for(auto it : sprites){ delete it; }
  for(auto it : spritesBack){ delete it; }
  for(auto it : spritesMiddle){ delete it; }
  for(auto it : spritesFront){ delete it; }
  for(auto it: coins){delete it;}
  for(auto it : spritesExplosion){delete it;}
  for(auto it: enemies){delete it;}
  for(auto it: explodedMines){delete it;}
  delete hud;
  delete book;
  delete dropper;
  delete strategy;
}

Engine::Engine(string choice) :
  rc( RenderContext::getInstance() ),
  io( IOmod::getInstance() ),
  clock( Clock::getInstance() ),
  frameGen( FrameGenerator::getInstance()),
  renderer( rc->getRenderer() ),
  worldC(choice+"Back", Gamedata::getInstance().getXmlInt(choice+"Back/factor") ),
  worldB(choice+"Middle", Gamedata::getInstance().getXmlInt(choice+"Middle/factor") ),
  worldA(choice+"Front", Gamedata::getInstance().getXmlInt(choice+"Front/factor") ),
  viewport( Viewport::getInstance() ),
  sprites(),
  spritesBack(),
  spritesMiddle(),
  spritesFront(),
  spritesExplosion(),
  coins(),
  enemies(),
  explodedMines(),
  currentSprite(-1),
  player(new Player(choice,1.0,0.5,100,500)),
  hud(new Hud("hud")),
  showHud(true),
  hudTicks(0),
  playerType(choice),
  strategy( new PerPixelCollisionStrategy ),
  waitTimer(0),
  mineTimer(0),
  ignore(),
  ignoreCoins(),
  // sound("sound/oblivionIntro.wav")
  sound(SDLSound::getInstance()),
  book(new Sprite("bookWin",1.0,0.5)),
  win(false),
  won(false),
  godMode(false),
  dropper(new CoinDropper("coinDropper"))
{
  string villian="angler";
  string npc1 = "tuna";
  string npc2 = "fish";

  if(choice == "spongebob"){
    player->setsScale(3.0);
    villian="bigJelly";
    npc1="jelly";
    npc2="jelly";
  }else if(choice == "yee"){
      player->setsScale(0.2);
      villian="flyDino";
      npc1="flyDino";
      npc2="flyDino";

  }else if(choice == "diver"){
      player->setsScale(0.5);

  }

  constexpr float u = 0.8f; //Mean size
  constexpr float d = 0.3f; //Std deviation

  std::random_device rd;
  std::mt19937 mt(rd());
  std::normal_distribution<float> dist(u,d);
  unsigned int numB = Gamedata::getInstance().getXmlInt("numBack");
  unsigned int numM = Gamedata::getInstance().getXmlInt("numMiddle");
  unsigned int numF = Gamedata::getInstance().getXmlInt("numFront");

//create seagulls
  for ( unsigned int i = 0; i < numB; ++i ) {
      auto* s = new TurningMultiSprite("seagull");
      float scale = dist(mt);
      while(scale > 0.33f) scale = dist(mt);
      s->setScale(scale);
      spritesBack.push_back(s);
    }
//create middle layer fish
  for ( unsigned int i = 0; i < numM; ++i ) {
    string name = "";
    if(i%2==0){ 
        name = npc1;   
      }
      else{    
        name=npc2;
      }
      auto* s = new TurningMultiSprite(name);

      float scale = dist(mt);
      while((scale < 0.2f) || (scale > 0.5f)) scale = dist(mt);
      s->setScale(scale);
      spritesMiddle.push_back(s);
    }
//create front fish
  for ( unsigned int i = 0; i < numF; ++i ) {
    string name = "";
    if(i%2==0){ 
        name = npc1;   
      }
      else{    
        name=npc2;
      }
      auto* s = new TurningMultiSprite(name);
      float scale = dist(mt);
      while(scale < 0.66f) scale = dist(mt);
      s->setScale(scale);
      if(i==0)s->setsScale(7.0);
      spritesFront.push_back(s);
    }


  std::vector<Drawable*>::iterator ptr = spritesBack.begin();
  sort(ptr, spritesBack.end(), SpriteLess());

  ptr = spritesMiddle.begin();
  sort(ptr, spritesMiddle.end(), SpriteLess());

  ptr = spritesFront.begin();
  sort(ptr, spritesFront.end(), SpriteLess());

  sprites.push_back(player);




  coins.push_back( new StayingMultiSprite("coin",170,900));
  coins.push_back( new StayingMultiSprite("coin",190,900));
  coins.push_back( new StayingMultiSprite("coin",210,900));
  coins.push_back( new StayingMultiSprite("coin",230,900));
  coins.push_back( new StayingMultiSprite("coin",250,900));
  coins.push_back( new StayingMultiSprite("coin",1480,900));
  coins.push_back( new StayingMultiSprite("coin",1500,900));
  coins.push_back( new StayingMultiSprite("coin",1520,900));
  coins.push_back( new StayingMultiSprite("coin",1540,900));
  coins.push_back( new StayingMultiSprite("coin",1560,900));

  //spritesFront.push_back( new TurningMultiSprite(villian,1.0,3.0));
  // spritesFront.push_back( new TurningMultiSprite("missle"));
  // spritesFront.push_back( new TurningMultiSprite("missle"));
  // spritesFront.push_back( new TurningMultiSprite("missle"));
  // spritesFront.push_back( new TurningMultiSprite("missle"));  
  // spritesFront.push_back( new TurningMultiSprite("missle"));
  // spritesFront.push_back( new TurningMultiSprite("missle"));
  // spritesFront.push_back( new TurningMultiSprite("missle"));
  // spritesFront.push_back( new TurningMultiSprite("missle"));  
  // spritesFront.push_back( new TurningMultiSprite("missle"));
  // spritesFront.push_back( new TurningMultiSprite("missle"));
  // spritesFront.push_back( new TurningMultiSprite("missle"));
  // spritesFront.push_back( new TurningMultiSprite("missle"));
  // spritesFront.push_back( new TurningMultiSprite("mine",1.0,0.1));
  // spritesFront.push_back( new TurningMultiSprite("mine",1.0,0.1));
  // spritesFront.push_back( new TurningMultiSprite("mine",1.0,0.1));
  // spritesFront.push_back( new TurningMultiSprite("mine",1.0,0.1));
  // spritesFront.push_back( new TurningMultiSprite("mine",1.0,0.1));
  // spritesFront.push_back( new TurningMultiSprite("mine",1.0,0.1));
  // spritesFront.push_back( new TurningMultiSprite("mine",1.0,0.1));
  // spritesFront.push_back( new TurningMultiSprite("mine",1.0,0.1));
  // spritesFront.push_back( new TurningMultiSprite("mine",1.0,0.1));
  // spritesFront.push_back( new TurningMultiSprite("mine",1.0,0.1));
  //spritesFront.push_back( new SmartSprite("jelly",0.3,1.0,hud));
  enemies.push_back( new SmartSprite("malloyTop",0.3,1.0,hud));
  enemies.push_back( new SmartSprite("mmalloyLeft",0.3,1.0,hud));
  enemies.push_back( new SmartSprite("malloyRight",0.3,1.0,hud));



  switchSprite();
  std::cout << "Loading complete" << std::endl;
}

void Engine::checkForCollisions() {
  std::vector<Drawable*>::const_iterator it = spritesFront.begin();
  Drawable* player = sprites[0];

  int counter=0;



  while ( it != spritesFront.end() ) {
    if(!ignore[counter] && dynamic_cast<Player*>(player)->collidedWith(*it)){
        ignore[counter]=1;
        const Sprite s(spritesFront[counter],spritesFront[counter]);

        Drawable* boom = new ExplodingSprite(s);
        delete spritesFront[counter];

        spritesFront[counter] = boom;
        srand (time(NULL));

        sound[11+(rand()%5)];
    }
    if ( strategy->execute(*player, **it) ) {

      if(!ignore[counter] && (hud->getHealth()>0) ){

        srand (time(NULL));
        sound[11+(rand()%5)];

        hud->setHealth(hud->getHealth()-10) ;
        showHud=true;
        ignore[counter]=1;
        const Sprite s(spritesFront[counter],spritesFront[counter]);

        Drawable* boom = new ExplodingSprite(s);
        delete spritesFront[counter];

        spritesFront[counter] = boom;

        if(hud->getHealth()==0){
          sound[3];
          hud->setLives(hud->getLives()-1);
          const Sprite s(sprites[0],sprites[0]);

          Drawable* boom = new ExplodingSprite(s);

          spritesExplosion.push_back(boom);
          waitTimer=1;


        }
      }
    }
    ++it;
    counter++;
  }
counter=0;
//check all coins
it = coins.begin();

  while ( it != coins.end() ) {

    if ( strategy->execute(*player, **it) ) {

      if(!ignoreCoins[counter] && (hud->getHealth()>0) ){

        sound[10];
        hud->setScore(hud->getScore()+1);
        showHud=true;
        ignoreCoins[counter]=1;
        const Sprite s(coins[counter],coins[counter]);

        Drawable* boom = new ExplodingSprite(s);
        delete coins[counter];

        coins[counter] = boom;
      }

    }
    ++it;
    counter++;
  }
//check enemie mines dropped if they hit the player
for(auto e: enemies){
  if(dynamic_cast<SmartSprite*>(e)->collidedWith(player)){
    sound[11+(rand()%5)];
    hud->setHealth(hud->getHealth()-10);
    showHud=true;
  }
  
  if(dynamic_cast<SmartSprite*>(e)->collidedWith(static_cast<Player*>(player)->getBullets())){
    sound[11+(rand()%5)];
    hud->setScore(hud->getScore()+1);
    showHud=true;
  }
}
if(win){
  if(strategy->execute(*player, *book)){
    ExplodingSprite *e = new ExplodingSprite(*book);
    delete book;
    book = e;
    win = false; 
    won = true;
  }
}


}

void Engine::draw() const {
  worldC.draw();
  for(auto* s : spritesBack) s->draw();

  worldB.draw();
    for(auto* s : spritesMiddle) s->draw();

  worldA.draw();
  for(auto* s : spritesFront) s->draw();
  for(auto* s : coins) s->draw();
  for(auto* s : enemies) s->draw();
  for(auto *s : explodedMines)s->draw();
  io.writeText(Gamedata::getInstance().getXmlStr("name"), 0, Gamedata::getInstance().getXmlInt("view/height")-30,{255, 255, 0, 255 });

  io.writeText(Gamedata::getInstance().getXmlStr("screenTitle"), 15,0);


if(hud->getHealth()>0){
  for(auto* s : sprites) s->draw();
}

  for(auto* s : spritesExplosion) s->draw();



  if(showHud){
    hud->draw();
  }
  if(win || won)
    book->draw();
  
  if(godMode){
      std::stringstream ss;
      ss<<"God Mode ON";
      io.writeText(ss.str(), Gamedata::getInstance().getXmlInt("view/width")-170, 0,{255, 100, 0, 255});
     
  }
  if(win && !won){
      std::stringstream ss;
      ss<<"Go collect the book at the end!";
      io.writeText(ss.str(), Gamedata::getInstance().getXmlInt("view/width")/2, Gamedata::getInstance().getXmlInt("view/height")/2,{255, 0, 0, 255});
     
  }


  if(won){
      std::stringstream ss;
      ss<<"You Win!";
      io.writeText(ss.str(), Gamedata::getInstance().getXmlInt("view/width")/2, Gamedata::getInstance().getXmlInt("view/height")/2,{255, 0, 0, 255});
      hud->setHealth(9999);
  }
  viewport.draw();

  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
  for(auto* s : sprites) s->update(ticks);
    hud->setPlayerX(sprites[0]->getX());
    hud->setPlayerY(sprites[0]->getY());
    hud->setPlayerH(sprites[0]->getFrame()->getHeight());
    hud->setPlayerW(sprites[0]->getFrame()->getWidth());

  for(auto* s : spritesExplosion) s->update(ticks);
  for(auto* s : spritesBack) s->update(ticks);
  for(auto* s : spritesMiddle) s->update(ticks);
  for(auto* s : spritesFront) s->update(ticks);
  for(auto* s : coins) s->update(ticks);
  for(auto* s : enemies) s->update(ticks);
  for(auto* s : explodedMines) s->update(ticks);
  if(win || won)
    book->update(ticks);

  worldC.update();
  worldB.update();
  worldA.update();
  dropper->update(ticks);
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  currentSprite++;
  currentSprite = currentSprite % sprites.size();
  Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
}



int Engine::play() {
sound.update("sound/oblivionIntro.wav");
sound.startMusic();
            sound[2];

  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  while ( !done ) {
    if(hud->getScore() >=5 && !won)
      win = true;
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }

      if(event.type == SDL_KEYDOWN) 
      {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) 
        {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) 
        {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }          
                  
          if ( keystate[SDL_SCANCODE_R] ) {

            return 1;
          }
          if ( keystate[SDL_SCANCODE_G] ) {
              if(!godMode){
                hud->setHealth(99999);
                godMode = true;
              }
              else{
                hud->setHealth(100);
                godMode = false;
              }
          }

          if ( keystate[SDL_SCANCODE_SPACE] ) {
              player->shoot();
              sound[0];
          }
          
          if ( keystate[SDL_SCANCODE_T] ) 
          {
            switchSprite();
          }
          if (keystate[SDL_SCANCODE_F4] && !frameGen.getBool()) 
          {
            std::cout << "Initiating frame capture" << std::endl;
            //makeVideo = true;
            frameGen.setBool(true);
          }else if (keystate[SDL_SCANCODE_F4] && frameGen.getBool()) 
          {
            std::cout << "Terminating frame capture" << std::endl;
            //makeVideo = false;
            frameGen.setBool(false);

          }
      }


}
    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {

        if(waitTimer >0){
          waitTimer++;
          if(waitTimer == 200){
            waitTimer = 0;
            hud->setHealth(100);
            sound[2];

          }
        }

        if(mineTimer >=0){
          mineTimer++;
          if(mineTimer == 100){
            mineTimer = 0;
            //enemy drop mine
            enemies[0]->shoot();
            enemies[1]->shoot();
            enemies[2]->shoot();
          }
          // if(mineTimer == 125){
          //   //enemy drop mine
          //   enemies[1]->shoot();
          //   enemies[2]->shoot();
          // }
        }

        if(showHud){
          hudTicks++;
          if(hudTicks == 200){
            hudTicks = 0;
            showHud=false;
          }
        }

        if (keystate[SDL_SCANCODE_F1]) {
          showHud = true;
          hudTicks=0;
        }

        if (keystate[SDL_SCANCODE_LSHIFT] || keystate[SDL_SCANCODE_RSHIFT]) {
          //PLAYER SPEED DOUBLE ?
        }
if(hud->getHealth()>0){

        if( (keystate[SDL_SCANCODE_W] && keystate[SDL_SCANCODE_S]) || (!keystate[SDL_SCANCODE_W] && !keystate[SDL_SCANCODE_S])){
          player->stopY();

        }else if(keystate[SDL_SCANCODE_W]){
          player->up();

        }else if(keystate[SDL_SCANCODE_S]){
          player->down();
        }

        if( (keystate[SDL_SCANCODE_A] && keystate[SDL_SCANCODE_D]) || (!keystate[SDL_SCANCODE_A] && !keystate[SDL_SCANCODE_D])){
          player->stopX();

        }else if(keystate[SDL_SCANCODE_A]){
          player->left();

        }else if(keystate[SDL_SCANCODE_D]){
          player->right();
        }
}
      clock.incrFrame();
      draw();
      update(ticks);
      checkForCollisions();
      if(frameGen.getBool()){
        frameGen.makeFrame();
      
      }
    }
  }
  return 0;
}

