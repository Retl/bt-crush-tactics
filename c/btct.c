#include "sponsor.h"
#include "map.h"
#include "btct.h"
#include "bitmap_font.h"

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
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
SDL_Surface *gCursor;
SDL_Surface *gFont;

SDL_Rect rect = {0, 0, 100, 100};

void update()
{
  if (bQuit == 1)
  {
    //quit();
  }
  else
  {
    frameCount += 1;
    printf("Frame Count: %i\r\n", frameCount);
    //drawRandomPixels();
    if (!loadedMedia)
    {
      printf("Failed to load media!\r\n");
      bQuit = 1;
    }
    else
    {
      handleInput();
      drawSplash();
      drawGameObjects();
    }
    // printf("Frame Count: %i", frameCount);
  }
}

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

    printf("Emscripten main loop should be set next.\n");
    emscripten_set_main_loop(update, 0, 0);
    printf("Emscripten main loop should have been set before this.\n");

    SDL_CreateWindowAndRenderer(480, 270, 0, &gWindow, &gRenderer); // For 8x8 text characters, this is 60 x 33.75 = 1980
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

  //Load media
  loadedMedia = loadMedia();
  printf("loadMedia: %i\n", loadedMedia);

  // Init Gamepad
  // https://davidgow.net/handmadepenguin/ch6.html

  return 0;
}

void handleInput()
{
}

void drawGameObjects()
{
  // Keep this reference on string concatenation and copying on speed-dial. You'll need it a lot. http://www.cplusplus.com/reference/cstring/strncat/ 
  
  char displayStringAdvancing[3000] = ""; // We're going to use strncat to populate this.
  // char testString[300] = "This is a test.\nIs it working?\nOh, it works!\n@@NICE@@\nBut can it handle line-breaks...\n!\"#$\%&'()*+,-./\n0123456789:;<=>?\n@ABCDEFGHIJKLMNO\nPQRSTUVWXYZ[\\]^_\n`abcdefghijklmno\npqrstuvwxyz{|}~";
  // char testString[300] = " !\"#$\%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
  char testString[3000] = "As you make your way down the corridor, your foot loses grip.\nSuddenly you're tumbling- then rolling- down and down \ninto a dark abyss.\n \nAs you spiral down the incline, you feel the walls pull in \naround you until you're passing through \nwhat feels like a small tube. \n \nTHUMP! Ouch!\n \nYou stand and dust yourself. The room is dark. \nYour aura produces enough light \nto see a few feet in front of you and nothing more. \nThe path to the east seems short. Probably a wall? \nThere seems to be a corridor \nleading into more darkness to your left.\nThe platform beneath you \nmakes a gentle ceramic clink when kicked.\nSeems like it could move with some extra force.\nAbove you is the way you came. You can't go that way.\n \nSmall mechanical whirs from the darkness \nsuggest robots are nearby.\nNothing you haven't dealt with before...\nbut it's hard to fight what you can't see.\n \nExits: \nEast: (Too Dark To See)\nWest: (Too Dark To See)\nUp: Spiral Tumbler.\nDown: Rotating Barrier\n \n<10/14 HP - 069 C - 100/100 EN - (D.Boost) [Agile]>\n \n                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        ";

  int currentRow = 0;
  int currentCol = 0;

  // This is the part that was yanked from the SDL1.2 sample I think?
  if (SDL_MUSTLOCK(gScreenSurface))
    SDL_LockSurface(gScreenSurface);

  // BlitSurface is software based rendering and slow. When we RenderCopy to the renderer that is hardware accelerated and much faster.
  // https://wiki.libsdl.org/SDL_BlitSurface
  //SDL_BlitSurface(gSplash, NULL, gScreenSurface, NULL);
  //SDL_FillRect(gScreenSurface, (&rect), SDL_MapRGB(gScreenSurface->format, 0xAA, 0xAA, 0xAA));

  SDL_Texture *fontTexture = SDL_CreateTextureFromSurface(gRenderer, gFont);
  SDL_UpdateWindowSurface(gWindow); // Delete this??

  //SDL_Texture *screenTexture = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);

  SDL_RenderClear(gRenderer); // Comment this out if you want the backdrop to show.

  char delim[10] = "\n";
  char *ptr = strtok(strncat(displayStringAdvancing, testString, (frameCount % strlen(testString))), delim);

  while (ptr != NULL)
  {
    for (int i = 0; i < strlen(ptr); i++)
    {

      SDL_Rect destination = {currentCol * 8, currentRow * 8, 8, 8};
      SDL_Rect srcRect = getBitmapFontRectFromCharacter(ptr[i]);
      SDL_RenderCopy(gRenderer, fontTexture, &srcRect, &destination);

      //printf("Character srcRect: %c - (%i, %i, %i, %i)\n", testString[i], srcRect.x, srcRect.y, srcRect.w, srcRect.h);

      currentCol += 1;
    }
    currentCol = 0;
    currentRow += 1;
    //printf("'%s'\n", ptr);
    ptr = strtok(NULL, delim);
  }
  SDL_RenderPresent(gRenderer);

  SDL_DestroyTexture(fontTexture);
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

  // This is the part that was yanked from the SDL1.2 sample I think?
  if (SDL_MUSTLOCK(gScreenSurface))
    SDL_LockSurface(gScreenSurface);

  // BlitSurface is software based rendering and slow. When we RenderCopy to the renderer that is hardware accelerated and much faster.
  // https://wiki.libsdl.org/SDL_BlitSurface
  SDL_BlitSurface(gSplash, NULL, gScreenSurface, NULL);
  //SDL_FillRect(gScreenSurface, (&rect), SDL_MapRGB(gScreenSurface->format, 0xAA, 0xAA, 0xAA));
  SDL_UpdateWindowSurface(gWindow); // Delete this??

  SDL_Texture *screenTexture = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);

  SDL_RenderClear(gRenderer);
  // https://wiki.libsdl.org/SDL_RenderCopy
  SDL_RenderCopy(gRenderer, screenTexture, NULL, NULL);
  SDL_RenderPresent(gRenderer);

  SDL_DestroyTexture(screenTexture);

  //SDL_Flip(gScreenSurface);
}

void drawSplashOld()
{

  // This is the part that was yanked from the SDL1.2 sample I think?
  if (SDL_MUSTLOCK(gScreenSurface))
    SDL_LockSurface(gScreenSurface);

  SDL_BlitSurface(gSplash, NULL, gScreenSurface, NULL);
  //SDL_FillRect(gScreenSurface, (&rect), SDL_MapRGB(gScreenSurface->format, 0xAA, 0xAA, 0xAA));
  SDL_UpdateWindowSurface(gWindow); // Delete this??

  SDL_Texture *screenTexture = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);

  SDL_RenderClear(gRenderer);
  SDL_RenderCopy(gRenderer, screenTexture, NULL, NULL);
  SDL_RenderPresent(gRenderer);

  SDL_DestroyTexture(screenTexture);

  //SDL_Flip(gScreenSurface);
}

void drawRenderScreen()
{

  // This is the part that was yanked from the SDL1.2 sample I think?
  if (SDL_MUSTLOCK(gScreenSurface))
    SDL_LockSurface(gScreenSurface);

  //SDL_BlitSurface(gSplash, NULL, gScreenSurface, NULL);
  SDL_UpdateWindowSurface(gWindow); // Delete this??

  SDL_Texture *screenTexture = SDL_CreateTextureFromSurface(gRenderer, gScreenSurface);

  SDL_RenderClear(gRenderer);

  // SDL_RenderCopy(gRenderer, screenTexture, NULL, NULL);
  /*
  For the current Scene,
  Draw the background object to the renderer.
  Then get the Game Objects list. For every Game Object in the current room, get their current sprite and draw it to the renderer.
  The Bitmap Font object might have some special behavior for its game object or something?
  */

  // As a temporary placeholder, we're going to draw the placeholder image and the cursor and move the cursor around a bit.
  SDL_RenderCopy(gRenderer, screenTexture, NULL, NULL);
  SDL_RenderCopy(gRenderer, screenTexture, NULL, NULL);

  SDL_RenderPresent(gRenderer);

  SDL_DestroyTexture(screenTexture);
}

void blit(SDL_Texture *SrcBmp, SDL_Renderer *DstBmp, int SourceX, int SourceY, int DestX, int DestY, int Width, int Height)
{
  SDL_Rect Src = {SourceX, SourceY, Width, Height};
  SDL_Rect Dst = {DestX, DestY, Width, Height};
  SDL_RenderCopy(DstBmp, SrcBmp, &Src, &Dst);
}

int loadMedia()
{
  //Loading success flag
  int success = 1;

  //Load splash image
  //gSplash = SDL_LoadBMP("img/bg_splashes/10_years_too_early.bmp");
  //gSplash = SDL_LoadBMP("img/temp/mock-vitals.bmp");
  gSplash = IMG_Load("img/temp/mock-vitals.bmp");
  if (gSplash == NULL)
  {
    printf("Unable to load image %s! SDL Error: %s\n", "img/bg_splashes/10_years_too_early.bmp", SDL_GetError());
    success = 0;
  }

  gCursor = IMG_Load("img/temp/MockCidle-32x32.png");
  if (gCursor == NULL)
  {
    printf("Unable to load image %s! SDL Error: %s\n", "img/bg_splashes/10_years_too_early.bmp", SDL_GetError());
    success = 0;
  }

  gFont = IMG_Load("img/font_fp.png");
  if (gFont == NULL)
  {
    printf("Unable to load image %s! SDL Error: %s\n", "img/font_fp.png", SDL_GetError());
    success = 0;
  }

  return success;
}

void initTestRoomScenario()
{
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