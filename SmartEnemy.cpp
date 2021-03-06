#include "SmartEnemy.h"
#include "gamedata.h"


SmartEnemy::SmartEnemy( const std::string& name, const Vector2f& pos, int w, int h ) :
     MultiSprite(name),
     playerPos(pos),
     playerWidth(w),
     playerHeight(h),
     currentMode(NORMAL),
    safeDistance(Gamedata::getInstance().getXmlFloat(name+"/safeDistance")),        viewWidth(Gamedata::getInstance().getXmlFloat("view/width")),
    viewHeight(Gamedata::getInstance().getXmlFloat("view/height")),
    worldWidth(Gamedata::getInstance().getXmlFloat("world/width")),
    worldHeight(Gamedata::getInstance().getXmlFloat("world/height")),
    enemyWidth(Gamedata::getInstance().getXmlFloat(name+"/imageWidth")),
    enemyRange(Gamedata::getInstance().getXmlFloat("view/enemyRange")),
    bulletsToDie(Gamedata::getInstance().getXmlFloat(name+"/bulletsToDie")),
    bulletsHit(0),
    initialPosition(Vector2f(rand()%(worldWidth-viewWidth)+viewWidth,
    rand()%(viewHeight-enemyRange)+1)),
   initialVelocity(getVelocity())
{
	  setPosition(initialPosition);
}

SmartEnemy::SmartEnemy(const SmartEnemy& s) :
  MultiSprite(s),
  playerPos(s.playerPos),
  playerWidth(s.playerWidth),
  playerHeight(s.playerHeight),
  currentMode(s.currentMode),
  safeDistance(s.safeDistance),
 viewWidth(s.viewWidth),
 viewHeight(s.viewHeight),
worldWidth(s.worldWidth),
 worldHeight(s.worldHeight),
 enemyWidth(s.enemyWidth),
 enemyRange(s.enemyRange),
 bulletsToDie(s.bulletsToDie),
 bulletsHit(s.bulletsHit),
 initialPosition(s.initialPosition),
 initialVelocity(s.initialVelocity)

{ }

SmartEnemy& SmartEnemy::operator=(const SmartEnemy& s) {
 MultiSprite::operator=(s);
 playerPos = s.playerPos;
 playerWidth = s.playerWidth;
 playerHeight = s.playerHeight;
 currentMode = s.currentMode;
 safeDistance = s.safeDistance;
 viewWidth = s.viewWidth;
 viewHeight = s.viewHeight;
 worldWidth = s.worldWidth;
 worldHeight = s.worldHeight;
 enemyWidth = s.enemyWidth;
 enemyRange = s.enemyRange;
 bulletsToDie = s.bulletsToDie;
 bulletsHit = s.bulletsHit;
 initialPosition = s.initialPosition;
 initialVelocity=s.initialVelocity;
 return *this;
}


void SmartEnemy::restartGame() {
 MultiSprite::restartGame();
 currentMode=NORMAL;
 bulletsHit=0;
 setPosition(Vector2f(rand()%(worldWidth-viewWidth)+viewWidth, rand()%(viewHeight-enemyRange)+1));
   setVelocity(initialVelocity);
 }



void SmartEnemy::goUp(Uint32 ticks) {
	  float incr = getVelocityY() * static_cast<float>(ticks) * 0.001;
	    setY( getY()-incr );
}

void SmartEnemy::goDown(Uint32 ticks) {
	  float incr = getVelocityY() * static_cast<float>(ticks) * 0.001;
	    setY( getY()+incr );
}

void SmartEnemy::reset() {
    setPosition(Vector2f(worldWidth + enemyWidth + 1000, 1000));
    if ( explosionDone() ) {
    MultiSprite::reset();
    bulletsHit = 0;
    setX(worldWidth + enemyWidth + rand()%(500));
    setY(rand()%(viewHeight-enemyRange+1));
  }
}


void SmartEnemy::update(Uint32 ticks) {
 MultiSprite::update(ticks);
 advanceFrame(ticks);
 Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
 Vector2f currentPos = getPosition();
 setX(currentPos[0]+incr[0]);
 if ( getX() < -(enemyWidth) ) {
 setX(worldWidth + enemyWidth + 500);
 setY(rand()%(viewHeight-enemyRange+1));
 }

float x= getX()+getImage()->getWidth()/2;
float y= getY()+getImage()->getHeight()/2;
float px= playerPos[0]+playerWidth/2;
float py= playerPos[1]+playerHeight/2;
float distanceToEnemy = std::abs(x-px);
 if  ( currentMode == NORMAL ) {
  if(distanceToEnemy < safeDistance) currentMode = FACEPLAYER;
 }
 else if  ( currentMode == FACEPLAYER ) {
 if(distanceToEnemy > safeDistance) currentMode=NORMAL;
 else if (x > 0 && y > 0 && x < worldWidth && y < worldHeight) {
  if ( y < py ) goDown(ticks);
  if ( y > py ) goUp(ticks);
  }
 }
}






