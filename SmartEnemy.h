#ifndef SMARTENEMY_H
#define SMARTENEMY_H


#include "multisprite.h"

class SmartEnemy : public MultiSprite {
	public:
SmartEnemy( const std::string& name, const Vector2f& pos, int w, int h );
SmartEnemy(const SmartEnemy&);
SmartEnemy& operator=(const SmartEnemy&);
  virtual void update(Uint32 ticks);
  virtual void reset();
   void restartGame();
  void setPlayerPos(const Vector2f& p) { playerPos = p; }
  void moveToInitialPosition() { setPosition(initialPosition); }
   void Shot() { ++bulletsHit; }
   bool Dead() { return bulletsToDie == bulletsHit; }
 private:
    enum MODE {NORMAL, FACEPLAYER};
    Vector2f playerPos;
    int playerWidth;
    int playerHeight;
    MODE currentMode;
    float safeDistance;
    int viewWidth;
    int viewHeight;
    int worldWidth;								    int worldHeight;
    int enemyWidth;								    int enemyRange;
   // unsigned int bulletsHit;
  //  Vector2f initialPosition;
  //  Vector2f initialVelocity;
    unsigned int bulletsToDie;
    unsigned int bulletsHit;
   // Vector2f initialPosition;
    Vector2f initialPosition;
    Vector2f initialVelocity;    
    void goUp(Uint32 ticks);							    void goDown(Uint32 ticks);
};
#endif

