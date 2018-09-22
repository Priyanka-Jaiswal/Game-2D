#include "twoWaySprite.h"
#include "gamedata.h"
#include "renderContext.h"
#include "explodingSprite.h"

void TwoWaySprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
        if (timeSinceLastFrame > frameInterval) {
        currentFrame = (currentFrame+1) % numberOfFrames;
        timeSinceLastFrame = 0;
      }
}


TwoWaySprite::~TwoWaySprite( ) { if (explosion) delete explosion; }

TwoWaySprite::TwoWaySprite(const std::string& rightSprite,const std::string& leftSprite) : Drawable(rightSprite, 
         Vector2f(Gamedata::getInstance().getXmlInt(rightSprite+"/startLoc/x"), 
         Gamedata::getInstance().getXmlInt(rightSprite+"/startLoc/y")), 
         Vector2f(Gamedata::getInstance().getXmlInt(rightSprite+"/speedX"),
         Gamedata::getInstance().getXmlInt(rightSprite+"/speedY"))
           ),
  images( RenderContext::getInstance()->getImages(rightSprite) ),
  explosion(nullptr),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(rightSprite+"/frames")),
  frameInterval( Gamedata::getInstance().getXmlInt(rightSprite+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  rightsprite(rightSprite),
  leftsprite(leftSprite),
 initialLives(3),
 currentLives(3)
{ }

TwoWaySprite::TwoWaySprite(const TwoWaySprite& s) :
  Drawable(s), 
  images(s.images),
  explosion(s.explosion),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
rightsprite(s.rightsprite),
leftsprite(s.leftsprite),
initialLives(s.initialLives),
currentLives(s.currentLives)
  { }

TwoWaySprite& TwoWaySprite::operator=(const TwoWaySprite& s) {
  Drawable::operator=(s);
  images = (s.images);
  explosion = s.explosion;
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  rightsprite=(s.rightsprite);
  leftsprite=(s.leftsprite);
  initialLives=(s.initialLives);
  currentLives=(s.currentLives);
  return *this;
}

void TwoWaySprite::restartGame(){
 explosion=NULL;
 initialLives=3;
 /* setPosition(Vector2f(Gamedata::getInstance().getXmlInt(rightsprite+"/startLoc/x"),
			   Gamedata::getInstance().getXmlInt(rightsprite+"/startLoc/y")));*/
 }



void TwoWaySprite::draw() const { 
	if(explosion) explosion->draw();
	else  images[currentFrame]->draw(getX(), getY(), getScale());
}

void TwoWaySprite::explode() {
if ( !explosion ) {
  Vector2f velocity(100, 100);
  Sprite sprite(getName(), getPosition(), velocity, images[currentFrame]);
  explosion = new ExplodingSprite(sprite);
  initialLives--;
  }
}

void TwoWaySprite::reset() {
	    delete explosion;
	        explosion = NULL;
}

bool TwoWaySprite::explosionDone() {
	  return explosion && explosion->chunkCount() == 0;
}

void TwoWaySprite::update(Uint32 ticks) {
  if(explosion) {
  explosion->update(ticks);
  this->reset();
  return;
  }
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);
}
 
