#include <string>
#include <iostream>
#include <ctime>
#include "sound.h"
using std::string;


SDLSound& SDLSound::getInstance(){
  static SDLSound instance;
  return instance;
}

SDLSound::~SDLSound() {
  std::cout << "Cleaning up sounds ..." << std::endl;
  std::clock_t start = std::clock();
  Mix_HaltMusic();
  Mix_FreeMusic(music);
  for (unsigned int i = 0; i < sounds.size(); ++i) {
    Mix_FreeChunk(sounds[i]);
  }
  Mix_CloseAudio();
  std::clock_t duration = std::clock() - start;
  std::cout << "Clean up took " << duration << " ticks\n";
}


SDLSound::SDLSound() : 
  SDLSound("sound/pokemonIntro.wav")
{}

void  SDLSound::update(const char *name){
    music = Mix_LoadMUS(name);
  }

SDLSound::SDLSound(const char *name) : 
  volume(SDL_MIX_MAXVOLUME/4), 
  currentSound(-1), 
  music(NULL),
  audioRate(22050), 
  audioChannels(2), 
  audioBuffers(4096),
  sounds(),
  channels(),
volumeBoost()
{

  if(Mix_OpenAudio(audioRate, MIX_DEFAULT_FORMAT, audioChannels, 
                   audioBuffers)){
    throw string("Unable to open audio!");
  }
  
  music = Mix_LoadMUS(name);
  // Need to install midi to play the following:
  // music = Mix_LoadMUS("sound/ballad2.mid");
  if (!music) throw string("Couldn't load 100Years.ogg : ")+Mix_GetError();

  sounds.push_back( Mix_LoadWAV("sound/shoot.wav") );
  volumeBoost[sounds.size()-1]=-20;
  sounds.push_back( Mix_LoadWAV("sound/explosion.wav") );
  volumeBoost[sounds.size()-1]=-20;
  sounds.push_back( Mix_LoadWAV("sound/helloGameDevelopers.wav") );
  volumeBoost[sounds.size()-1]=80;
  sounds.push_back( Mix_LoadWAV("sound/overAndOut.wav") );
  volumeBoost[sounds.size()-1]=80;
  sounds.push_back( Mix_LoadWAV("sound/oblivionIntro.wav") );
  volumeBoost[sounds.size()-1]=0;
  sounds.push_back( Mix_LoadWAV("sound/pokemonIntro.wav") );
  volumeBoost[sounds.size()-1]=0;
  sounds.push_back( Mix_LoadWAV("sound/shoot.wav") );
  volumeBoost[sounds.size()-1]=0;
  sounds.push_back( Mix_LoadWAV("sound/explosion.wav") );
  volumeBoost[sounds.size()-1]=0;
  sounds.push_back( Mix_LoadWAV("sound/yee.wav") );
  volumeBoost[sounds.size()-1]=0;
  sounds.push_back( Mix_LoadWAV("sound/jurrasicParkTheme.wav") );
  volumeBoost[sounds.size()-1]=0;
  sounds.push_back( Mix_LoadWAV("sound/coin.wav") );
  volumeBoost[sounds.size()-1]=0;
  sounds.push_back( Mix_LoadWAV("sound/explosion.wav") );
  volumeBoost[sounds.size()-1]=-25;
    sounds.push_back( Mix_LoadWAV("sound/explosion.wav") );
  volumeBoost[sounds.size()-1]=-25;
    sounds.push_back( Mix_LoadWAV("sound/explosion.wav") );
  volumeBoost[sounds.size()-1]=-25;
    sounds.push_back( Mix_LoadWAV("sound/explosion.wav") );
  volumeBoost[sounds.size()-1]=-25;
    sounds.push_back( Mix_LoadWAV("sound/explosion.wav") );
  volumeBoost[sounds.size()-1]=-25;
    sounds.push_back( Mix_LoadWAV("sound/explosion.wav") );
  volumeBoost[sounds.size()-1]=-25;
  sounds.push_back( Mix_LoadWAV("sound/finish.wav") );
  volumeBoost[sounds.size()-1]=0;
  for (unsigned int i = 0; i < sounds.size(); ++i) channels.push_back(i);
  std::cout << "Music and Sound is loaded" << std::endl;


}

void SDLSound::toggleMusic() {
  if( Mix_PausedMusic() ) { 
    Mix_ResumeMusic(); 
  } 
  else { 
    Mix_PauseMusic(); 
  } 
}

void SDLSound::operator[](int index) {  
  if (currentSound >= 0) Mix_HaltChannel(currentSound);
  currentSound = index;
  Mix_VolumeChunk(sounds[index], volume+volumeBoost[index]);
  channels[index] = 
     // Mix_PlayChannel(channels[index], sounds[index], 0);
     Mix_PlayChannel(-1, sounds[index], 0);
}

void SDLSound::startMusic() {
  Mix_VolumeMusic(volume);
  Mix_PlayMusic(music, -1);
}

void SDLSound::stopMusic() {
  Mix_HaltMusic();
  Mix_FreeMusic(music);
}

