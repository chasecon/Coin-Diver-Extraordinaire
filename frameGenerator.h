#include <string>
#include <SDL.h>

class FrameGenerator {
public:
  static FrameGenerator& getInstance();
  void makeFrame();
  unsigned int getFrameCount() const { return frameCount; }
  bool getBool() const {return makeVideo;}
  void setBool(bool b)  {makeVideo=b;}
private:

  FrameGenerator();
  SDL_Renderer* const rend;
  SDL_Window* const window;
  const int WIDTH;
  const int HEIGHT;
  const std::string USERNAME;
  const int MAX_FRAMES;
  int frameCount;
  bool makeVideo;
  FrameGenerator(const FrameGenerator&);
  FrameGenerator& operator=(const FrameGenerator&);
};
