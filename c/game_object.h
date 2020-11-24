#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include <SDL_image.h>

typedef struct {
	int x;
    int y;
    int width;
    int height;
    SDL_Surface *gCurrentFrame;
    SDL_Surface *gAnimationFrames[20];
    //Canons
    // Notoriety
	// TemporaryStatus tempStatuses[MAX_TEMP_STATUSES];
	//TemporaryStatus tempStatuses[10];
} GameObject;

#endif