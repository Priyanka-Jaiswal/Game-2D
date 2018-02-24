#include <iostream>
#include <sstream>
#include <iomanip>
#include<sys/stat.h>
#include "circle.h"

circle::
circle(SDL_Renderer* renderer, SDL_Point center,  int radius, SDL_Color color) :
	renderer(renderer),
	Center(center),
	Radius(radius),
	Color(color)
{}

void circle::drawcircle(){
  SDL_SetRenderDrawColor(renderer,Color.r,Color.g, Color.b,Color.a);
  for (int w = 0; w < Radius * 2; w++) {
    for (int h = 0; h < Radius * 2; h++) {
      int dx = Radius - w; //horizontal offset
      int dy = Radius - h; //vertical offset
      if ((dx*dx + dy*dy) <= (Radius * Radius)) {
        SDL_RenderDrawPoint(renderer,Center.x+dx ,Center.y+dy);
      }
    }
  }
}


int circle::getRadius() const
{
	return Radius;
}

	
std::ostream& operator<<(std::ostream& out, const circle& h) {
  return out <<"Drawing wheel with radius "<<h.getRadius()<<std::endl;
}
