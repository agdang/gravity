#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* window = SDL_CreateWindow("Untitled SDL Application", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

  bool running = true;

  float gravity = .7f;

  int input[2];

  SDL_Rect player = { 100, 480-64, 32, 32 };
  SDL_Rect floor = { 0, 480-32, 640, 32 };

  bool jumping = false;

  float yvel;

  while(running)
  {
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
      switch(event.type)
      {
        case SDL_QUIT:
          running = false;
          break;
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym)
          {
            case SDLK_LEFT:
              input[0] = 1;
              break;
            case SDLK_RIGHT:
              input[1] = 1;
              break;
            case SDLK_SPACE:
              if (jumping == false)
              {
                jumping = true;
                yvel = 15.f;
              }
              break;
          }
          break;
          case SDL_KEYUP:
            switch(event.key.keysym.sym)
            {
              case SDLK_LEFT:
                input[0] = 0;
                break;
              case SDLK_RIGHT:
                input[1] = 0;
                break;
            }
            break;
      }
    }

    if (input[0] == 1)
      player.x -= 5;
    if (input[1] == 1)
      player.x += 5;

    if (jumping == true)
    {
      player.y -= yvel;
      yvel -= gravity;
    }

    if (player.y >= floor.y-32)
    {
      jumping = false;
      player.y = floor.y-32;
    }


    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &floor);

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &player);

    SDL_RenderPresent(renderer);

    SDL_Delay(10);
  }


  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
