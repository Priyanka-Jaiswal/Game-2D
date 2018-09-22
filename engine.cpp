#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "multisprite.h"
#include "gamedata.h"
#include "SmartEnemy.h"
#include "engine.h"
#include "frameGenerator.h"
#include "twoWaySprite.h"
#include "player.h"
#include "collisonStrategy.h"


Engine::~Engine() {
 delete player;
 delete castle;
 for(Drawable* sprite: sprites){ 
	 delete sprite;
 }
 for ( Drawable* enemy : enemies ) {
	 delete enemy;
 }
 for( CollisionStrategy* strategy:strategies)
 {
	 delete strategy;
 }
  std::cout << "Terminating program" << std::endl;
}

Engine::Engine() :
  rc( RenderContext::getInstance() ),
  io( IoMod::getInstance() ),
  clock( Clock::getInstance() ),
  renderer( rc->getRenderer() ),
  hudTime(Gamedata::getInstance().getXmlInt("hud/time")),
  ground("ground-back", Gamedata::getInstance().getXmlInt("ground-back/factor")),
 road("road-back",Gamedata::getInstance().getXmlInt("road-back/factor")),
 viewport( Viewport::getInstance() ),
 player(new Player("SpriteRight","SpriteLeft","Bullet")),
 castle(new Castle("Castle")),
 sprites(),
 enemies(),
 strategies(),
 currentSprite(0),
 currentStrategy(0),
 count(0),
 collision(),
 showHud(false),
 hud(Hud::getInstance(player)),
 makeVideo( false )
{
  
int SmartEnemyCount = Gamedata::getInstance().getXmlInt("SmartEnemy/count");
enemies.reserve(SmartEnemyCount);
     Vector2f pos = player->getPosition();
     int w = player->getScaledWidth();
     int h = player->getScaledHeight();
      for(int index=0; index < SmartEnemyCount; index++)
      {
      enemies.push_back(new SmartEnemy("SmartEnemy", pos, w, h));
      }
      for(unsigned long index=0; index < enemies.size(); index++) {
      player->attach(static_cast<SmartEnemy*> (enemies[index]) );
 }
      strategies.push_back( new PerPixelCollisionStrategy );

  Viewport::getInstance().setObjectToTrack(player);
  std::cout << "Loading complete" << std::endl;
}

void Engine::draw() const {
  ground.draw();
  road.draw();
  player->draw();
  castle->draw();
  SDL_Color color={102,0,102,0};
  io.writeText("Priyanka",color,30,420);
  for(const Drawable* sprite:sprites){
	  sprite->draw();
}
  for ( const Drawable* enemy : enemies ) {
    enemy->draw();
   }

 if(clock.getSeconds() < hudTime || showHud) {
  hud.displayHud();
  }
if ( player->isInvincible() ){
IoMod::getInstance().writeText("GOD MODE", color,610,420);
}

if(player->getTotalLives()>0){
std::stringstream str3;
str3 << "Life Remaining "<<player->getTotalLives();
io.writeText(str3.str(),color,350,420);
}

if (player->hasReachedCastle()) {
   hud.displayWin(count);
   clock.pause();

}
else if(player->getTotalLives()<=0){
	hud.displayLost(count);
	clock.pause();
}

  viewport.draw();
  SDL_RenderPresent(renderer);
}


void Engine::checkForCollisions() {
  collision = false;
   for ( const Drawable* d : sprites ) {	   
   if ( strategies[currentStrategy]->execute(*player, *d) ) {
    collision = true;    
        }
      }
   for ( Drawable* e : enemies ) {
   SmartEnemy* enemy = static_cast<SmartEnemy*>(e);
    if ( strategies[currentStrategy]->execute(*player, *e) ) {
    collision = true;
    enemy->explode();
     if (player->isInvincible()) {
	 player->incrementEnemiesDestroyed();
     } else{
      player->explode();
    }}
 else
 {
  player->destroy(enemy);
 }
} if ( collision ) {
player->collided();
 }
 else {
  player->missed();
  collision = false;
 }
}


void Engine::update(Uint32 ticks) {
 checkForCollisions();
 ground.update();
 road.update();
 player->update(ticks);
 castle->update(ticks);
 for(Drawable* sprite:sprites)
  {
	  sprite->update(ticks);
  }

  for(Drawable* enemy : enemies) {
    enemy->update(ticks);
  }
  viewport.update(); // always update viewport last
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
	if ( keystate[SDL_SCANCODE_R] ) {
		if(clock.isPaused()) clock.unpause();
		player->restartGame();
		for(Drawable* enemy : enemies) {
	 static_cast<SmartEnemy*>(enemy)->restartGame();
	 }		
	}
        if ( keystate[SDL_SCANCODE_G] ) {
          player->toggleGodMode();
   }
         if ( keystate[SDL_SCANCODE_SPACE] ) {
         player->shoot();
	 }
       if ( keystate[SDL_SCANCODE_F1] && !showHud ) {
	    showHud=true;
       }
       else if ( keystate[SDL_SCANCODE_F1] && showHud ) {
	    showHud=false;
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
    if (keystate[SDL_SCANCODE_A]) {
      player->left();
       }
    if (keystate[SDL_SCANCODE_D]) {
     player->right();
     }
    if (keystate[SDL_SCANCODE_W]) {
    player->up();
     }
    if (keystate[SDL_SCANCODE_S]) {
      player->down();
    }
      draw();
      update(ticks);
      if ( makeVideo ) {
        frameGen.makeFrame();
      }
    }
  }
}
