#include "twoWaySprite.h"
#include "gamedata.h"
#include "renderContext.h"

void TwoWaySprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}

TwoWaySprite::TwoWaySprite(const std::string& rightSprite,const std::string& leftSprite) : Drawable(rightSprite, 
         Vector2f(Gamedata::getInstance().getXmlInt(rightSprite+"/startLoc/x"), 
         Gamedata::getInstance().getXmlInt(rightSprite+"/startLoc/y")), 
         Vector2f(Gamedata::getInstance().getXmlInt(rightSprite+"/speedX"),
         Gamedata::getInstance().getXmlInt(rightSprite+"/speedY"))
           ),
  images( RenderContext::getInstance()->getImages(rightSprite) ),

  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(rightSprite+"/frames")),
  frameInterval( Gamedata::getInstance().getXmlInt(rightSprite+"/frameInterval")),
  timeSinceLastFrame( 0 ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  rightsprite(rightSprite),
  leftsprite(leftSprite)
{ }

TwoWaySprite::TwoWaySprite(const TwoWaySprite& s) :
  Drawable(s), 
  images(s.images),
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
rightsprite(s.rightsprite),
leftsprite(s.leftsprite)
  { }

TwoWaySprite& TwoWaySprite::operator=(const TwoWaySprite& s) {
  Drawable::operator=(s);
  images = (s.images);
  currentFrame = (s.currentFrame);
  numberOfFrames = ( s.numberOfFrames );
  frameInterval = ( s.frameInterval );
  timeSinceLastFrame = ( s.timeSinceLastFrame );
  worldWidth = ( s.worldWidth );
  worldHeight = ( s.worldHeight );
  rightsprite=(s.rightsprite);
  leftsprite=(s.leftsprite);
  return *this;
}

void TwoWaySprite::draw() const { 
  images[currentFrame]->draw(getX(), getY(), getScale());
}

void TwoWaySprite::update(Uint32 ticks) { 
  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( getY() < 0) {
    setVelocityY( fabs( getVelocityY() ) );
  }
  if ( getY() > worldHeight-getScaledHeight()) {
    setVelocityY( -fabs( getVelocityY() ) );
  }

  if ( getX() < 0) {
    setVelocityX( fabs( getVelocityX() ) );
    setName(rightsprite);
   Images(RenderContext::getInstance()->getImages(rightsprite));
  }
  if ( getX() > worldWidth-getScaledWidth()) {
    setVelocityX( -fabs( getVelocityX() ) );

    setName(leftsprite);
    Images(RenderContext::getInstance()->getImages(leftsprite));
  }  

}