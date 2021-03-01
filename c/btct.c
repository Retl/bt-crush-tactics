#include "sponsor.h"
#include "map.h"
#include "btct.h"
#include "bitmap_font.h"
#include "gamepad.h"
#include "game_object.h"

#include <stdio.h>
#include <stdlib.h>

// For Sleeping: 
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

// For Emscripten only: 
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

int bQuit = 0;
int success = 1;
int frameCount = 0;
int loadedMedia = 0;

int mascot_first_joystick_silt_horizontal = 0;
int mascot_first_joystick_silt_vertical = 0;

Map testMap;

SDL_Renderer *gRenderer = NULL;
SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface;
SDL_Surface *gSplash;
SDL_Surface *gCursor;
SDL_Surface *gFont;
SDL_Surface *gDefaultSprite;

GamepadStatus* btct_gamepad_status;

SDL_Rect rect = {0, 0, 100, 100};

GameObject game_objects[1];

void update()
{
  printf("Update called.\r\n");
  if (bQuit == 1)
  {
    //quit();
  }
  else
  {
    frameCount += 1;
    //printf("Frame Count: %i\r\n", frameCount);
    if (!loadedMedia)
    {
      printf("Failed to load media!\r\n");
      bQuit = 1;
    }
    else
    {
      handleInput();
      for (int goNum = 0; goNum < 1; goNum++) 
      {
        game_objects[goNum].fun_step(&(game_objects[goNum]));
      }
      drawSplash();
      drawGameObjects();
    }
    // printf("Frame Count: %i", frameCount);
  }
}

int main()
{
  mapInit(&testMap, 100, 100);
  mapSetSGRumbleRamble(&testMap);
  printf("\nBEEP\n");
  mapDebugPrint(&testMap);
  printf("\nBEEP-BOOP\n");
  printf("Filling the floor.\r\n");
  mapFillFloor(&testMap, 2);
  mapDebugPrint(&testMap);
  printf("Finished Second Map Debug Print.\r\n\r\n");

  go_init(&(game_objects[0]));
  go_set_position(&(game_objects[0]), 256, 256);
  (game_objects[0]).fun_step = &go_step_player_combat_generic;

  printf("YEET - Just finished Map Print\r\n");
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\r\n", SDL_GetError());
    success = 0;
  }
  else
  {
    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(update, 0, 0);
    #endif

    // SDL_CreateWindowAndRenderer(480, 270, 0, &gWindow, &gRenderer); // For 8x8 text characters, this is 60 x 33.75 = 1980
    SDL_CreateWindowAndRenderer(1080, 720, 0, &gWindow, &gRenderer); // For 8x8 text characters, 480x270px is 60 x 33.75 = 1980
    printf("Created window...?.\r\n");
    if (gWindow == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\r\n", SDL_GetError());
      success = 0;
    }
    else
    {
      // This this ScreenSurface was a different size than the WindowRenderer, I got a huge zoomed in render. Experiment with it later.
      gScreenSurface = SDL_CreateRGBSurface(0, 1080, 720, 32, 0, 0, 0, 0); // Resolution of this surface gets set here.
    }
  }

  //Load media
  loadedMedia = loadMedia();
  printf("loadMedia: %i\r\n", loadedMedia);

  // Init Gamepad
  // https://davidgow.net/handmadepenguin/ch6.html
  mascot_init_gamepad();

printf("About to check for Windows \r\n");
  #ifdef _WIN32
  while (bQuit == 0) 
    {
      printf("Hi Windows\r\n");
      update();
      Sleep(1.0 / 60.0);
    }
  #endif
  return 0;
}

void handleInput()
{
  mascot_update_input_state();
}

void setJoystickTilt(int x, int y)
{
  mascot_first_joystick_silt_horizontal = x;
  mascot_first_joystick_silt_vertical = y;
}

void drawGameObjects()
{
  // Keep this reference on string concatenation and copying on speed-dial. You'll need it a lot. http://www.cplusplus.com/reference/cstring/strncat/

  char displayStringAdvancing[3000] = ""; // We're going to use strncat to populate this.
  // char roomDescString[300] = "This is a test.\nIs it working?\nOh, it works!\n@@NICE@@\nBut can it handle line-breaks...\n!\"#$\%&'()*+,-./\n0123456789:;<=>?\n@ABCDEFGHIJKLMNO\nPQRSTUVWXYZ[\\]^_\n`abcdefghijklmno\npqrstuvwxyz{|}~";
  // char roomDescString[300] = " !\"#$\%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~";
  char roomDescString[3000] = "As you make your way down the corridor, your foot loses grip.\nSuddenly you're tumbling- then rolling- down and down \ninto a dark abyss.\n \nAs you spiral down the incline, you feel the walls pull in \naround you until you're passing through \nwhat feels like a small tube. \n \nTHUMP! Ouch!\n \nYou stand and dust yourself. The room is dark. \nYour aura produces enough light \nto see a few feet in front of you and nothing more. \nThe path to the east seems short. Probably a wall? \nThere seems to be a corridor \nleading into more darkness to your left.\nThe platform beneath you \nmakes a gentle ceramic clink when kicked.\nSeems like it could move with some extra force.\nAbove you is the way you came. You can't go that way.\n \nSmall mechanical whirs from the darkness \nsuggest robots are nearby.\nNothing you haven't dealt with before...\nbut it's hard to fight what you can't see.\n \nExits: \nEast: (Too Dark To See)\nWest: (Too Dark To See)\nUp: Spiral Tumbler.\nDown: Rotating Barrier\n \n<10/14 HP - 069 C - 100/100 EN - (D.Boost) [Agile]>\n \n                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        ";
  char debugNoteString[3000] = "";
  char roomTextConcatenated[10000] = "";
  char mockPrompt[500] = "<NB BITTY (Leader) 2 / 7 * - 100 / 100 mp - 15 / 20 mv - 34 c - 20 pop>\n"
                          "<H4X 3 / 6 * - 4 / 34 mp - 15 / 20 mv - 400 c - 33 pop>\n"
                          "Objective: Locate and visit the Crush Queens arena.\n"
                          "Objective: Reach 100 total popularity before Day 30.\n \n"
                          "<Cassie (Leader) 2 / 6 * - - / - mp - 48 / 50 mv - 256 c - 70 pop>\n";
  char mockHazardDetails[500] = "Mrs. Zhlayer \n0/14 * - 100 / 100 mp \nAction: Laser Recharge \nPosture: Standing \nDistance: 512 px \n\nTitle: Combat Tutor \nCanon: Mascots Aplenty! \n  Sub-Canon: - \nNotoriety: 4444 \nPopularity: -";
  
  btct_gamepad_status = get_gamepad_status();
  sprintf(&debugNoteString, "Gamepad Stick Status: (%d, %d) : (%d, %d) - \n", mascot_first_joystick_silt_horizontal, mascot_first_joystick_silt_vertical, 
    btct_gamepad_status->stickHorizontal, btct_gamepad_status->stickVertical);

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

  //SDL_RenderClear(gRenderer); // Comment this out if you want the backdrop to show.

  // strtok basically means it's looking for that delimiter as a tokenizer, to split things into substrings.
  // We need thsoe substrings in the loop to know what row to draw the text on.
  char delim[10] = "\n";
  char *ptr = strtok(strncat(displayStringAdvancing, roomDescString, (frameCount % strlen(roomDescString))), delim);
  // char *ptrDebugGamepad = strtok(debugNoteString, delim);
  char *ptrDebugGamepad = debugNoteString;

  // These are mostly here so I can draw some mockup stuff.
  char *ptrStrPositionLeft = "640px";
  char *ptrStrPositionRight = "960px";
  char *ptrTIME = "^  v  YOU  128 256 384 512 640 768";

  //drawTextWithBitmapFont(0, 0, ptr, delim, gRenderer, fontTexture);

  // This is mostly here for debugging purpose to draw the gamepad status. Remove or make it a toggle option.
  drawTextWithBitmapFont(560, 400, strtok(ptrDebugGamepad, delim), delim, gRenderer, fontTexture);

  // Actually drawing that mockup stuff.
  drawTextWithBitmapFont(560, 432, ptrStrPositionLeft, delim, gRenderer, fontTexture);
  drawTextWithBitmapFont(560, 464, ptrStrPositionRight, delim, gRenderer, fontTexture);
  drawTextWithBitmapFont(560, 496, ptrTIME, delim, gRenderer, fontTexture);

  drawTextWithBitmapFont(12, 12, strtok("Time [==========--------------------------------------------------]", delim), delim, gRenderer, fontTexture);
  drawTextWithBitmapFont(12, 24, strtok(mockPrompt, delim), delim, gRenderer, fontTexture);
  
  drawTextWithBitmapFont(12, 428, strtok(mockHazardDetails, delim), delim, gRenderer, fontTexture);

  strncat(roomTextConcatenated, testMap.displayName, strlen(testMap.displayName));
  strncat(roomTextConcatenated, testMap.textDesc, strlen(testMap.textDesc));
  strncat(roomTextConcatenated, testMap.textExits, strlen(testMap.textExits));
  strncat(roomTextConcatenated, testMap.textContent, strlen(testMap.textContent));
  drawTextWithBitmapFont(12, 290, strtok(roomTextConcatenated, delim), delim, gRenderer, fontTexture);
  //drawTextWithBitmapFont(560, 328, "This\nIs\nA\nTest", delim, gRenderer, fontTexture);


  for (int goNum = 0; goNum < 1; goNum++) 
  {
    game_objects[goNum].fun_draw(&(game_objects[goNum]), gRenderer);
  }

  SDL_RenderPresent(gRenderer);

  SDL_DestroyTexture(fontTexture);
}

void drawTextWithBitmapFont(int offsetX, int offsetY, char *ptr, char *delim, SDL_Renderer *gRenderer, SDL_Texture *fontTexture)
{
  int currentRow = 0;
  int currentCol = 0;
  // For each substring the tokenizer has split for us...
  while (ptr != NULL)
  {
    // For each character in the current substring...
    for (int i = 0; i < strlen(ptr); i++)
    {

      // We're assuming your texture is from the renderer.
      // The destination and source are for positioning the individual bitmap font characters.
      SDL_Rect destination = {(currentCol * getBitmapFontCharacterWidth()) + offsetX, (currentRow * getBitmapFontCharacterHeight()) + offsetY, getBitmapFontCharacterWidth(), getBitmapFontCharacterHeight()};
      SDL_Rect srcRect = getBitmapFontRectFromCharacter(ptr[i]);
      SDL_RenderCopy(gRenderer, fontTexture, &srcRect, &destination);

      //printf("Character srcRect: %c - (%i, %i, %i, %i)\n", roomDescString[i], srcRect.x, srcRect.y, srcRect.w, srcRect.h);

      currentCol += 1;
    }
    currentCol = 0;
    currentRow += 1;
    //printf("'%s'\n", ptr);
    ptr = strtok(NULL, delim);
  }
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

  ///gSplash = IMG_Load("img/temp/mock-vitals.bmp");
  gSplash = IMG_Load("img/bg_splashes/map_panels.png");
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

  /*gFont = IMG_Load("img/font_fp.png");
  if (gFont == NULL)
  {
    printf("Unable to load image %s! SDL Error: %s\n", "img/font_fp.png", SDL_GetError());
    success = 0;
  }*/

  gFont = IMG_Load("img/font_fixedsys10x20.png");
  if (gFont == NULL)
  {
    printf("Unable to load image %s! SDL Error: %s\n", "img/font_fixedsys10x20.png", SDL_GetError());
    success = 0;
  }

  gDefaultSprite = IMG_Load("img/temp/unset_sprite.png");
  if (gDefaultSprite == NULL)
  {
    printf("Unable to load image %s! SDL Error: %s\n", "img/temp/unset_sprite.png", SDL_GetError());
    success = 0;
  }
  else 
  {
    go_init_default_sprite(gDefaultSprite);
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

  mascot_cleanup_gamepad();
  //Quit SDL subsystems
  SDL_Quit();
}

int WinMain() 
{
    return main();
}

int DllMain()  // reserved
{
  main();
  return;
}

/*

*/