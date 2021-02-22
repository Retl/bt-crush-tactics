#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include <SDL_image.h>

typedef struct {
	int x;
    int y;
    int xSub;
    int ySub;
    int xOrigin;
    int yOrigin;

    int xSpeed;
    int ySpeed;
    int xSpeedSub;
    int ySpeedSub;

    int xAccel;
    int yAccel;
    int xAccelSub;
    int yAccelSub;

    int width;
    int height;

    SDL_Surface *gCurrentFrame;
    SDL_Surface *gAnimationFrames[20];

    void (*fun_step)(void*);
    void (*fun_pre_step)(void*);
    void (*fun_post_step)(void*);

    void (*fun_draw)(void*, SDL_Renderer*);

    //Canons
    // Notoriety
	// TemporaryStatus tempStatuses[MAX_TEMP_STATUSES];
	//TemporaryStatus tempStatuses[10];
} GameObject;

void go_init_default_sprite (SDL_Surface *gNewDefaultSprite);
void go_do_nothing (void* game_object);
void go_set_position (void* game_object, int xPosition, int yPosition);
void go_draw_default (void* game_object, SDL_Renderer *gRenderer);
void go_step_player_combat_generic (void* game_object);
void go_init (GameObject* game_object);

#endif