// Brian Malloy        Data-Driven Object oriented Game Construction
#include "engine.h"

FrameFactory*  FrameFactory::instance = NULL;
RenderContext* RenderContext::instance = NULL;

int main(int, char*[]) {
   try {

      Menu& menu = Menu::getInstance();
      int restart=1;

      while(restart){

         string s = menu.play();
         Engine engine(s);
         restart = engine.play();
         //menu.fix();
   }


      delete RenderContext::getInstance();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
