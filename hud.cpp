#include "hud.h"
#include "ioMod.h"
#include <iostream>
#include <string>
#include <iomanip>
#include "gamedata.h"
#include "renderContext.h"
#include <sstream>
#include"clock.h"
Hud& Hud::getInstance(Player* player){
	 static Hud instance(player);
	 return instance;
}

Hud::~Hud()
{}

Hud::Hud(Player* player):
    player(player),
    width(Gamedata::getInstance().getXmlInt("hud/width")),
    height(Gamedata::getInstance().getXmlInt("hud/height")),
    hudx(Gamedata::getInstance().getXmlInt("hud/start/x")),
    hudy(Gamedata::getInstance().getXmlInt("hud/start/y")),
    hudRect({hudx,hudy,width,height}),
    renderer( RenderContext::getInstance()->getRenderer() ),
    io( IoMod::getInstance() ),
    textFontColor({102,0,102, 255})
{}

int Hud::fontSize()const{
        float fontWidthsize = width * 0.09;
        float fontHeightsize = height * 0.09;
	 if(fontWidthsize < fontHeightsize)
	{
	return (int)fontWidthsize;
	}
        return (int)fontHeightsize;
}

void Hud::displayWin(int) const{
  SDL_Rect RectW = {300,200,310,150};
  SDL_Color Textcolor = {255,0,0,255};
  std::stringstream str1;
  str1 << "You Win!";
  std::stringstream str2;
  str2 << "Your Score: "<<player->getNumEnemiesDestroyed();
  std::stringstream str3;
  str3 << "Game Over Reached Castle";
  std::stringstream str4;
  str4 << "Press R to Restart";
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/4 );
  SDL_RenderFillRect( renderer, &RectW );
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  SDL_RenderDrawRect( renderer, &RectW );
  IoMod::getInstance().writeText(str1.str(), Textcolor,320+5, 200+15);           IoMod::getInstance().writeText(str4.str(), Textcolor,320+5, 240);	        IoMod::getInstance().writeText(str2.str(),  Textcolor,320+5, 260+5);
  IoMod::getInstance().writeText(str3.str(),  Textcolor,320+5, 280+5);

}

void Hud::displayLost(int) const{
 SDL_Rect RectW = {300,330,200,120};
 SDL_Color Textcolor = {255,0,0,255};
 std::stringstream str1;
 str1 << "You Lost!";
 std::stringstream str4;
 str4 << "Your Score: "<<player->getNumEnemiesDestroyed();
 std::stringstream str2;
 str2 << "Game Over";
 std::stringstream str3;
 str3 << "Press R to Restart";
 SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
 SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
 SDL_RenderFillRect( renderer, &RectW );
 SDL_SetRenderDrawColor( renderer, 255, 0, 0, 255 );
 SDL_RenderDrawRect( renderer, &RectW );
 IoMod::getInstance().writeText(str1.str(), Textcolor,320+15, 330+15);           IoMod::getInstance().writeText(str4.str(), Textcolor,320+15, 330+40);          IoMod::getInstance().writeText(str2.str(),  Textcolor,320+15, 330+65);
 IoMod::getInstance().writeText(str3.str(),  Textcolor,302, 330+90);
}



void Hud::displayHud() const {
 int fSize = fontSize();
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255/2 );
  SDL_RenderFillRect( renderer, &hudRect );
  SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
  SDL_RenderDrawRect( renderer, &hudRect);
  IoMod::getInstance().writeText("Menu: ", hudx+15, hudy+20,textFontColor, fSize);
  IoMod::getInstance().writeText("F1 to toggle Help", hudx+15, hudy+50,textFontColor, fSize);
 IoMod::getInstance().writeText(" Player Control : ASDW ", hudx+15, hudy+80,textFontColor, fSize);  
 IoMod::getInstance().writeText("Shoot: Space ", hudx+15, hudy+110,textFontColor, fSize); 
  std::stringstream strm;
  strm << "Bullets in use: " << player->bulletCount();
  IoMod::getInstance().writeText(strm.str(), hudx+15, hudy+170,textFontColor, fSize);
  strm.clear();
  strm.str("");
  strm << "Bullets in pool: " << player->freeCount();
  IoMod::getInstance().writeText(strm.str(), hudx+15, hudy+200, textFontColor, fSize);
  strm.clear();
  strm.str("");
  strm << "Fps: " << Clock::getInstance().getFps();
   IoMod::getInstance().writeText(strm.str(), hudx+15, hudy+230, textFontColor, fSize);
}


