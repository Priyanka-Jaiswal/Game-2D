#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "circle.h"
#include "frameGenerator.h"

const std::string NAME="pjaiswa";
const int WIDTH = 820;
const int HEIGHT = 640;


int main (void) {

	SDL_Renderer *renderer;
	SDL_Window   *window;

 	SDL_Init(SDL_INIT_VIDEO);
   SDL_CreateWindowAndRenderer(WIDTH,HEIGHT,0,&window,&renderer);
   SDL_SetWindowTitle(window,"Bus_Scenery");

 SDL_SetRenderDrawColor(renderer,135,206,235,255);
 SDL_RenderClear(renderer);

SDL_Rect Road={0,355,825,200};
SDL_SetRenderDrawColor(renderer,128,128,128,0);
SDL_RenderFillRect(renderer,&Road);

SDL_Rect Bus={255,180,470,200};
SDL_SetRenderDrawColor(renderer,255,255,153,0);
SDL_RenderFillRect(renderer,&Bus);

SDL_Rect Zebra1={0,420,120,20};
SDL_SetRenderDrawColor(renderer,255,255,255,0);
SDL_RenderFillRect(renderer,&Zebra1);

SDL_Rect Zebra2={160,420,150,20};
SDL_SetRenderDrawColor(renderer,255,255,255,0);
SDL_RenderFillRect(renderer,&Zebra2);

SDL_Rect Zebra3={355,420,150,20};
SDL_SetRenderDrawColor(renderer,255,255,255,0);
SDL_RenderFillRect(renderer,&Zebra3);


SDL_Rect Zebra4={550,420,150,20};
SDL_SetRenderDrawColor(renderer,255,255,255,0);
SDL_RenderFillRect(renderer,&Zebra4);


SDL_Rect Zebra5={745,420,150,20};
SDL_SetRenderDrawColor(renderer,255,255,255,0);
SDL_RenderFillRect(renderer,&Zebra5);

SDL_Rect Windows={255,190,110,80};
SDL_SetRenderDrawColor(renderer,224,224,224,0);
SDL_RenderFillRect(renderer,&Windows);

SDL_Rect Pattern1={255,180,470,5};
SDL_SetRenderDrawColor(renderer,204,102,0,0);
SDL_RenderFillRect(renderer,&Pattern1);


SDL_Rect Pattern2={255,270,470,5};
SDL_SetRenderDrawColor(renderer,204,102,0,0);
SDL_RenderFillRect(renderer,&Pattern2);

SDL_Rect Pattern3={255,280,470,5};
SDL_SetRenderDrawColor(renderer,204,102,0,0);
SDL_RenderFillRect(renderer,&Pattern3);

SDL_Rect Windows2={375,190,80,60};
SDL_SetRenderDrawColor(renderer,224,224,224,0);
SDL_RenderFillRect(renderer,&Windows2);

SDL_Rect Windows3={475,190,80,60};
SDL_SetRenderDrawColor(renderer,224,224,224,5);
SDL_RenderFillRect(renderer,&Windows3);

SDL_Rect Windows4={575,190,80,60};
SDL_SetRenderDrawColor(renderer,224,224,224,5);
SDL_RenderFillRect(renderer,&Windows4);

SDL_Rect Windows5={675,190,50,60};
SDL_SetRenderDrawColor(renderer,224,224,224,5);
SDL_RenderFillRect(renderer,&Windows5);


SDL_Point center1={325,380};
SDL_Color color1={96,96,96,255};
circle outerwheel1(renderer,center1,50,color1);
outerwheel1.drawcircle();
std::cout<<outerwheel1;

SDL_Point center3={655,380};
SDL_Color color3={96,96,96,255};
circle outerwheel2(renderer,center3,50,color3);
outerwheel2.drawcircle();
std::cout<<outerwheel2;

SDL_Point center2={325,380};
SDL_Color color2={32,32,32,255};
circle innerwheel1(renderer,center2,35,color2);
innerwheel1.drawcircle();
std::cout<<innerwheel1;

SDL_Point center4={655,380};
SDL_Color color4={32,32,32,255};
circle innerwheel2 (renderer,center4,35,color4);
innerwheel2.drawcircle();
std::cout<<innerwheel2;

SDL_Point center5={132,500};
SDL_Color color5={255,231,186,255};
circle circle5(renderer,center5,30,color5);
circle5.drawcircle();

SDL_Rect Grass={0,550,825,400};
SDL_SetRenderDrawColor(renderer,0,128,0,0);
SDL_RenderFillRect(renderer,&Grass);

SDL_SetRenderDrawColor(renderer,0,0,0,0);
SDL_RenderDrawLine(renderer,135,530,135,600);

SDL_SetRenderDrawColor(renderer,0,0,0,0);
SDL_RenderDrawLine(renderer,135,600,100,630);

SDL_SetRenderDrawColor(renderer,0,0,0,0);
SDL_RenderDrawLine(renderer,135,600,150,635);

SDL_SetRenderDrawColor(renderer,0,0,0,0);
SDL_RenderDrawLine(renderer,135,570,160,560);


SDL_Rect Stopsign1={150,180,15,175};
SDL_SetRenderDrawColor(renderer,32,32,32,0);
SDL_RenderFillRect(renderer,&Stopsign1);

SDL_Point center6={160,175};
SDL_Color color6={255,0,0,255};
circle circle6(renderer,center6,50,color6);
circle6.drawcircle();

SDL_Point center7={160,175};
SDL_Color color7={255,255,255,255};
circle circle7(renderer,center7,35,color7);
circle7.drawcircle();

SDL_Rect Stopsign2={100,165,120,19};
SDL_SetRenderDrawColor(renderer,32,32,32,0);
SDL_RenderFillRect(renderer,&Stopsign2);

  SDL_RenderPresent(renderer);

  FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, 
    NAME);
  frameGen.makeFrame();

  SDL_Event event;
  const Uint8* keystate;
  while ( true ) {
    keystate = SDL_GetKeyboardState(0);
    if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        break;
      }
    }
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;
}
