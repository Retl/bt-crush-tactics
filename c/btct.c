#include "sponsor.h"
#include "map.h"
#include "btct.h"

#include <stdio.h>
#include <SDL.h>
#include <emscripten.h>
#include <stdlib.h>

int bQuit = 0;
int success = 1;
int frameCount = 0;
int loadedMedia = 0;

SDL_Renderer *gRenderer = NULL;
SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface;
SDL_Surface *gSplash;

SDL_Rect rect = {0, 0, 100, 100};

int main()
{
  Map testMap;
  mapInit(&testMap);
  mapDebugPrint(&testMap);
  printf("Filling the floor.\n");
  mapFillFloor(&testMap, 2);
  mapDebugPrint(&testMap);
  printf("YEET - Just finished Map Print\n");
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = 0;
  }
  else
  {
    //Create window
    //gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    //gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 480, 270, SDL_WINDOW_SHOWN );
    SDL_CreateWindowAndRenderer(480, 270, 0, &gWindow, &gRenderer);
    printf("Created window...?.");
    if (gWindow == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = 0;
    }
    else
    {
      //Get window surface
      //gScreenSurface = SDL_GetWindowSurface( gWindow );
      //printf( "Got window surface.");

      gScreenSurface = SDL_CreateRGBSurface(0, 480, 270, 32, 0, 0, 0, 0);
    }
  }

  //gScreenSurface = SDL_SetVideoMode(480, 270, 32, SDL_SWSURFACE);

  loadedMedia = loadMedia();
  printf("loadMedia: %i\n", loadedMedia);
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
      //printf("Lol deleteme later - Actually, the draw should follow immediately after this.\n");
      drawSplash();
      //drawRandomPixels();
    }
    // printf("Frame Count: %i", frameCount);
  }
}

void handleInput()
{
}

void drawRandomPixelsOld()
{
  if (SDL_MUSTLOCK(gScreenSurface))
    SDL_LockSurface(gScreenSurface);

  Uint8 *pixels = gScreenSurface->pixels;

  for (int i = 0; i < 1048576; i++)
  {
    char randomByte = rand() % 255;
    pixels[i] = randomByte;
  }

  if (SDL_MUSTLOCK(gScreenSurface))
    SDL_UnlockSurface(gScreenSurface);

  //SDL_Flip(gScreenSurface);
}

void drawRandomPixels()
{
  if (SDL_MUSTLOCK(gScreenSurface))
    SDL_LockSurface(gScreenSurface);
  Uint8 *pixels = gScreenSurface->pixels;
  for (int i = 0; i < 1048576; i++)
  {
    char randomByte = rand() % 255;
    pixels[i] = randomByte;
  }

  printf("BBB\n");
  //SDL_FillRect(gScreenSurface, (&rect), SDL_MapRGB(gScreenSurface->format, 0xFF, 0xFF, 0xFF));
  //SDL_BlitSurface(gSplash, NULL, gScreenSurface, NULL);

  if (SDL_MUSTLOCK(gScreenSurface))
    SDL_UnlockSurface(gScreenSurface);

  SDL_Texture *screenTexture = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);
  printf("CCC\n");
  SDL_RenderClear(gRenderer);
  SDL_RenderCopy(gRenderer, screenTexture, NULL, NULL);
  SDL_RenderPresent(gRenderer);

  SDL_DestroyTexture(screenTexture);
  printf("Drawing random pixels.\n");
}

void drawSplash()
{
  /*if (SDL_MUSTLOCK(gScreenSurface))
    SDL_LockSurface(gScreenSurface);

  Uint8 *pixels = gScreenSurface->pixels;

  for (int i = 0; i < 1048576; i++)
  {
    char randomByte = rand() % 255;
    pixels[i] = randomByte;
  }

  if (SDL_MUSTLOCK(gScreenSurface))
    SDL_UnlockSurface(gScreenSurface);*/

  //Apply the image
  //printf("Drawing splash...!\n");

  // This is the part that was yanked from the SDL1.2 sample I think?
  if (SDL_MUSTLOCK(gScreenSurface)) SDL_LockSurface(gScreenSurface);

  SDL_BlitSurface(gSplash, NULL, gScreenSurface, NULL);
  //SDL_FillRect(gScreenSurface, (&rect), SDL_MapRGB(gScreenSurface->format, 0xAA, 0xAA, 0xAA));
  SDL_UpdateWindowSurface( gWindow ); // Delete this??
  

  SDL_Texture *screenTexture = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);

  SDL_RenderClear(gRenderer);
  SDL_RenderCopy(gRenderer, screenTexture, NULL, NULL);
  SDL_RenderPresent(gRenderer);

  SDL_DestroyTexture(screenTexture);

  //SDL_Flip(gScreenSurface);
}

int loadMedia()
{
  //Loading success flag
  int success = 1;

  //Load splash image
  //gSplash = SDL_LoadBMP("img/bg_splashes/10_years_too_early.bmp");
  gSplash = SDL_LoadBMP("img/temp/mock-vitals.bmp");
  if (gSplash == NULL)
  {
    printf("Unable to load image %s! SDL Error: %s\n", "img/bg_splashes/10_years_too_early.bmp", SDL_GetError());
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

/*

*/