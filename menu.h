#ifndef MENU__H
#define MENU__H
// #include <string>
// #include <vector>
// #include <cmath>
// #include "drawable.h"
// #include "renderContext.h"
// #include "clock.h"
// #include "ioMod.h"
// #include <sstream>
#include "engine.h"

class Menu {
public:
	// static Menu& getInstance();
	~Menu();
	Menu();

	void fix();
	virtual void draw();
	//virtual void update(Uint32 ticks);
	virtual string play();
	void levelSwitch(int i);
protected:
	Clock& clock;
	FrameGenerator& frameGen;
	const IOmod& io;
	const RenderContext* rc;
	SDL_Renderer * const renderer;
	Menu(const Menu&);
	Menu& operator=(const Menu&);
	int WIDTH;
	int HEIGHT;
	int choice;
	string chosenPlayer;
	  std::vector<Drawable*> spritesGood;
	  std::vector<Drawable*> spritesBad;
	  std::vector<Drawable*> spritesThing;
	  int chosenPlayerInt;


};
#endif
