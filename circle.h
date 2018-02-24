#include <string>
#include <iostream>
#include <SDL.h>

class circle {
public:
	circle(SDL_Renderer*, SDL_Point Center,int, SDL_Color color );
	void drawcircle();
        int  getRadius() const;

        

       
private:
	SDL_Renderer* const renderer;
	SDL_Point const Center;
	const int Radius;
	SDL_Color const Color;
};
std::ostream &operator<<(std::ostream& out, const circle& h);

