#ifndef PLAYER__H
#define PLAYER__H

#include <string>
#include <list>
#include <cmath>
#include "twoWaySprite.h"
#include "SmartEnemy.h"
#include "bulletpool.h"

//class ExplodingSprite;
class Player : public TwoWaySprite {
	public:
	enum Facing { LEFT, RIGHT };
        Player(const std::string&,const std::string&,const std::string&);
        Player(const Player&);
        Player& operator=(const Player&);
        virtual void draw() const;     
        void collided() { collision = true; }
        void missed() { collision = false; }
	void reset();
        void right();
        void left();
        void up();
	void down();
	void shoot();
        unsigned int bulletCount() const { return bullets.bulletCount();}
        unsigned int freeCount() const { return bullets.freeCount();}
         void update(Uint32 ticks);
         void attach(SmartEnemy* o ) { observers.push_back(o); }
         void detach( SmartEnemy* o );
         void destroy(SmartEnemy*);
	 void incrementEnemiesDestroyed() { enemiesDestroyed++; }
         void stop();
	 int getNumEnemiesDestroyed() const { return enemiesDestroyed; }
         void toggleGodMode() { godMode = !godMode; }
	 bool isInvincible() { return godMode; } 
         void restartGame();
	 bool hasReachedCastle() { return reachedCastle; }
	 virtual int getTotalLives() const { return initialLives;}
//	 bool explode();
    	private:
         bool collision;
	 Facing facing;
         Vector2f initialVelocity;
	// ExplodingSprite* explosion;
	 std::list<SmartEnemy*> observers;
	 std::string bulletName;
	 float bulletInterval;
	 float timeSinceLastBullet;
	 float minBulletSpeed;
	 Vector2f rightOffset;
         Vector2f leftOffset;
//	 int initialLives;
/*`	 int initialHealth;
	 int currentLives;
	 int currentHealth;*/
         BulletPool bullets;
	 int enemiesDestroyed;
         bool godMode;
	 bool reachedCastle;

};
#endif


