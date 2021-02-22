#ifndef BTCT_H
#define BTCT_H

#include <SDL.h>
#include <SDL_image.h>
#include "map.h"

int main();
void update();
void handleInput();

void setJoystickTilt(int x, int y);

void drawTextWithBitmapFont(int offsetX, int offsetY, char *ptr, char *delim, SDL_Renderer *gRenderer, SDL_Texture *fontTexture);
void drawRandomPixels();
void drawRandomPixelsOld();
void drawSplash();
void drawSplashOld();
void drawGameObjects();
void drawRenderScreen();
void blit(SDL_Texture* SrcBmp, SDL_Renderer* DstBmp, int SourceX, int SourceY, int DestX, int DestY, int Width, int Height);
void initTestRoomScenario();

int loadMedia();
void quit();

#endif