#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "SmartEnemy.h"
#include "hud.h"
#include "Castle.h"
class Player;
class CollisionStrategy;
class Engine {
public:
  Engine ();
  ~Engine ();
  void play();
 Engine(const Engine&)=delete;
 Engine& operator=(const Engine&)=delete;
void restart();
private:
  const RenderContext* rc;
  const IoMod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  unsigned int hudTime;
  World ground;
  World road;
  Viewport& viewport;
  Player* player;
  Castle* castle;
  std::vector<Drawable*> sprites;
  std::vector<SmartEnemy* > enemies;
  std::vector<CollisionStrategy*> strategies;
  int currentSprite;
  int currentStrategy;
  int count;
  bool collision;
 
  bool showHud;

  Hud& hud;

  bool makeVideo;

  void draw() const;
  void update(Uint32);
 
  void printScales() const;
  void checkForCollisions();
};

