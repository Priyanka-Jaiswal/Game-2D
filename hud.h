#ifndef HUD__H
#define HUD__H
#include <string>
#include <SDL.h>
#include <stdint.h>
#include "clock.h"
#include "ioMod.h"
#include "player.h"
#include "twoWaySprite.h"
class Hud {
public:
	static Hud& getInstance(Player*);
        ~Hud();
        void displayHud() const;
	void displayWin(int) const;
	void displayLost(int) const;
//	void drawGodMode(int x, int y, int w, int h, float percent) const;
private:
       Player* player;       
       const int width;
       const int height;
       int hudx;
       int hudy;
       SDL_Rect hudRect;
       SDL_Renderer* renderer;
       Hud(Player*);
       Hud(const Hud&);
       Hud& operator=(const Hud&);
       const IoMod& io;
       SDL_Color textFontColor;
       int fontSize()const;
};
#endif

