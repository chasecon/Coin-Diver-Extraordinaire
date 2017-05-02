// Brian Malloy        Data-Driven Object oriented Game Construction
#include "engine.h"

FrameFactory*  FrameFactory::instance = NULL;
RenderContext* RenderContext::instance = NULL;

int main(int, char*[]) {
   try {

      int restart=1;

      while(restart){
         Menu menu;
         string s = menu.play();
         Engine engine(s);
         restart = engine.play();
   }


      delete RenderContext::getInstance();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
