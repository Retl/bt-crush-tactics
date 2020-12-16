#ifndef BTCT_H
#define BTCT_H

#include <SDL.h>
#include <SDL_image.h>

int main();
void update();
void handleInput();

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