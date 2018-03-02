#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
#include "twoWaySprite.h"

Engine::~Engine() { 
 for(auto s: sprites) delete s;
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  ground("ground-back", Gamedata::getInstance().getXmlInt("ground-back/factor")),
 road("road-back",Gamedata::getInstance().getXmlInt("road-back/factor")),
 viewport( Viewport::getInstance() ),
	sprites(),
  currentSprite(0),
  makeVideo( false )
{
  sprites.push_back(new TwoWaySprite("SpriteRight","SpriteLeft"));
  int noofbird=Gamedata::getInstance().getXmlInt("bird/noofbird");
  sprites.reserve(noofbird+1);
  for(int i=1;i<noofbird;++i)
  {
  sprites.push_back(new Sprite("bird"));
  }
  Viewport::getInstance().setObjectToTrack(sprites[0]);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  ground.draw();
  road.draw();
 // bird->draw();
 // spinningStar->draw();
 for(auto sprite:sprites)
 {
	         sprite->draw();
 }

  std::stringstream strm;
  strm<<"fps:"<<clock.getFps();
  SDL_Color color={102,0,102,0};
  io.writeText(strm.str(),30,85);
  io.writeText("Priyanka",color,30,400);
  viewport.draw();
  SDL_RenderPresent(renderer);
}

void Engine::update(Uint32 ticks) {
//  bird->update(ticks);
 // spinningStar->update(ticks);
 
 ground.update();
  road.update();
  for(auto sprite:sprites)
  {
	  sprite->update(ticks);
  }
  viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
  ++currentSprite;
  currentSprite=currentSprite%sprites.size();
  Viewport::getInstance().setObjectToTrack(sprites[currentSprite]);
}

void Engine::play() {
  SDL_Event event;
  const Uint8* keystate;
  bool done = false;
  Uint32 ticks = clock.getElapsedTicks();
  FrameGenerator frameGen;

  while ( !done ) {
    // The next loop polls for events, guarding against key bounce:
    while ( SDL_PollEvent(&event) ) {
      keystate = SDL_GetKeyboardState(NULL);
      if (event.type ==  SDL_QUIT) { done = true; break; }
      if(event.type == SDL_KEYDOWN) {
        if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
          done = true;
          break;
        }
        if ( keystate[SDL_SCANCODE_P] ) {
          if ( clock.isPaused() ) clock.unpause();
          else clock.pause();
        }
        if ( keystate[SDL_SCANCODE_T] ) {
          switchSprite();
        }
        if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
          std::cout << "Initiating frame capture" << std::endl;
          makeVideo = true;
        }
        else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
          std::cout << "Terminating frame capture" << std::endl;
          makeVideo = false;
        }
      }
    }

    // In this section of the event loop we allow key bounce:

    ticks = clock.getElapsedTicks();
    if ( ticks > 0 ) {
      clock.incrFrame();
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
