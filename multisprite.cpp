#include "multisprite.h"
#include "gamedata.h"
#include "renderContext.h"
#include "explodingSprite.h"
void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
        currentFrame = (currentFrame+1) % numberOfFrames;
        timeSinceLastFrame = 0;
   }
}

MultiSprite::~MultiSprite( ) { if (explosion) delete explosion; }

MultiSprite::MultiSprite( const std::string& name) :
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  images( RenderContext::getInstance()->getImages(name) ),
  explosion(nullptr),
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
  /* initialPosition(Vector2f(rand()%(worldWidth-viewWidth)+viewWidth,
			   rand()%(viewHeight-enemyRange)+1)),
	  initialVelocity(getVelocity()),*/
{ }

MultiSprite::MultiSprite( const std::string& name, const Vector2f& position, const Vector2f& velocity ) :
     Drawable(name, position, velocity),
     images( RenderContext::getInstance()->getImages(name) ),
     explosion(nullptr),
    currentFrame(0),
    numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
   timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
 worldHeight(Gamedata::getInstance().getXmlInt("world/height"))
/* initialPosition(Vector2f(rand()%(worldWidth-viewWidth)+viewWidth,
  rand()%(viewHeight-enemyRange)+1)),
   initialVelocity(getVelocity()),*/

{ }


MultiSprite::MultiSprite(const MultiSprite& s) :
  Drawable(s), 
  images(s.images),
  explosion(s.explosion),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight )
//  initialPosition(s.initialPosition),
//  initialVelocity(s.initialVelocity),

  { }

MultiSprite& MultiSprite::operator=(const MultiSprite& s) {
  Drawable::operator=(s);
  images = (s.images);
  explosion = s.explosion;
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
 // initialPosition = s.initialPosition;
 // initialVelocity = s.initialVelocity;
  return *this;
}

void MultiSprite::restartGame(){
explosion=NULL;
/*setPosition(Vector2f(rand()%(worldWidth-viewWidth)+viewWidth, rand()%(viewHeight-enemyRange)+1));
  setVelocity(initialVelocity);*/
}


void MultiSprite::draw() const { 
        if ( explosion ) explosion->draw();
	else images[currentFrame]->draw(getX(), getY(), getScale());
}

void MultiSprite::explode() {
	  if ( !explosion ) {
          Vector2f velocity(100, 100);
 Sprite sprite(getName(), getPosition(), velocity, images[currentFrame]);
   explosion = new ExplodingSprite(sprite);
 }
}

void MultiSprite::reset() {
	   delete explosion;
           explosion = NULL;
}

bool MultiSprite::explosionDone() {
    return explosion && explosion->chunkCount() == 0;
}

void MultiSprite::update(Uint32 ticks) { 
	 if ( explosion ) {
	explosion->update(ticks);
	this->reset();
	return;
 }
}
         

