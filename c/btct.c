#include "sponsor.h"
#include "map.h"
#include "btct.h"

#include <stdio.h>
#include <SDL.h>
#include <emscripten.h>
#include <stdlib.h>

int bQuit = 0;
int frameCount = 0;
int loadedMedia = 0;

SDL_Surface *screen;
SDL_Surface *gSplash;

int main()
{
  printf("hello, world!\n");
  Map testMap;
  mapInit(&testMap);
  mapDebugPrint(&testMap);
  printf("Filling the floor.\n");
  mapFillFloor(&testMap, 2);
  mapDebugPrint(&testMap);
  printf("YEET - Just finished Map Print\n");
  SDL_Init(SDL_INIT_VIDEO);
  screen = SDL_SetVideoMode(480, 270, 32, SDL_SWSURFACE);

  loadedMedia = loadMedia();
  //Load media

  printf("Emscripten main loop should be set next.\n");
  emscripten_set_main_loop(update, 60, 1);
  return 0;
}

void update()
{
  if (bQuit == 1)
  {
    //quit();
  }
  else
  {
    frameCount += 1;
    //drawRandomPixels();
    if (!loadedMedia)
    {
      printf("Failed to load media!\n");
      bQuit = 1;
    }
    else
    {
      drawSplash();
    }
    // printf("Frame Count: %i", frameCount);
  }
}

void handleInput()
{
}

void drawRandomPixels()
{
  if (SDL_MUSTLOCK(screen))
    SDL_LockSurface(screen);

  Uint8 *pixels = screen->pixels;

  for (int i = 0; i < 1048576; i++)
  {
    char randomByte = rand() % 255;
    pixels[i] = randomByte;
  }

  if (SDL_MUSTLOCK(screen))
    SDL_UnlockSurface(screen);

  SDL_Flip(screen);
}

void drawSplash()
{
  /*if (SDL_MUSTLOCK(screen))
    SDL_LockSurface(screen);

  Uint8 *pixels = screen->pixels;

  for (int i = 0; i < 1048576; i++)
  {
    char randomByte = rand() % 255;
    pixels[i] = randomByte;
  }

  if (SDL_MUSTLOCK(screen))
    SDL_UnlockSurface(screen);*/

  //Apply the image
  SDL_BlitSurface(gSplash, NULL, screen, NULL);

  //SDL_Flip(screen);
}

int loadMedia()
{
  //Loading success flag
  int success = 1;

  //Load splash image
  gSplash = SDL_LoadBMP("img/bg_splashes/10_years_too_early.png");
  if (gSplash == NULL)
  {
    printf("Unable to load image %s! SDL Error: %s\n", "img/bg_splashes/10_years_too_early.png", SDL_GetError());
    success = 0;
  }

  return success;
}

void quit()
{
  //Deallocate surface
  SDL_FreeSurface(gSplash);
  gSplash = NULL;

  //Destroy window
  //SDL_DestroyWindow(gWindow);
  //gWindow = NULL;

  //Quit SDL subsystems
  SDL_Quit();
}