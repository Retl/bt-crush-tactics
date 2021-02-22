#include "game_object.h"
#include "gamepad.h"
//#include "btct.h"

const int MAX_SUBPIXEL_SPEED = 256;
const int MIN_SUBPIXEL_SPEED = 0;

GamepadStatus* go_gamepad_status = NULL;

SDL_Surface *gGODefaultSprite;

void go_init_default_sprite (SDL_Surface *gNewDefaultSprite) 
{
    gGODefaultSprite = gNewDefaultSprite;
} 

void go_do_nothing (void* game_object) 
{
    return;
} 

void go_set_position (void* game_object, int xPosition, int yPosition) 
{
    GameObject* go = (GameObject*)game_object;
    go->x = xPosition;
    go->y = yPosition;
    return;
} 

void go_draw_default (void* game_object, SDL_Renderer *gRenderer) 
{
    GameObject* go = (GameObject*)game_object;
    if (go->gCurrentFrame > 0) 
    {
        SDL_Texture *textureCurrentFrame = SDL_CreateTextureFromSurface(gRenderer, go->gCurrentFrame);
        
        SDL_Rect destination = {(go->x - go->xOrigin), (go->y - go->yOrigin), go->gCurrentFrame->w, go->gCurrentFrame->h};
        SDL_Rect srcRect = {0, 0, go->gCurrentFrame->w, go->gCurrentFrame->h};
        SDL_RenderCopy(gRenderer, textureCurrentFrame, &srcRect, &destination);

        SDL_DestroyTexture(textureCurrentFrame);
    }

    go->gCurrentFrame = gGODefaultSprite;
}

void go_step_player_combat_generic (void* game_object) 
{
    GameObject* go = (GameObject*)game_object;
    go_gamepad_status = get_gamepad_status();
    if (go_gamepad_status->stickHorizontal > 0) 
    {
        go->xSpeed = 4;
        go->xSpeedSub = 0;
    }
    if (go_gamepad_status->stickHorizontal < 0) 
    {
        go->xSpeed = -4;
        go->xSpeedSub = 0;
    }
    if (go_gamepad_status->stickHorizontal == 0) 
    {
        go->xSpeed = 0;
        go->xSpeedSub = 0;
    }

    if (go_gamepad_status->stickVertical > 0) 
    {
        go->ySpeed = 4;
        go->ySpeedSub = 0;
    }
    if (go_gamepad_status->stickVertical < 0) 
    {
        go->ySpeed = -4;
        go->ySpeedSub = 0;
    }
    if (go_gamepad_status->stickVertical == 0) 
    {
        go->ySpeed = 0;
        go->ySpeedSub = 0;
    }

    go->xSub += go->xSpeedSub;
    go->ySub += go->ySpeedSub;

    go->x += go->xSpeed;
    go->y += go->ySpeed;
    
    while (go->xSub > MAX_SUBPIXEL_SPEED) { go->xSub -= MAX_SUBPIXEL_SPEED; go->x += 1;} 
    while (go->xSub < MIN_SUBPIXEL_SPEED) { go->xSub += MAX_SUBPIXEL_SPEED; go->x -= 1;} 
    while (go->ySub > MAX_SUBPIXEL_SPEED) { go->ySub -= MAX_SUBPIXEL_SPEED; go->y += 1;} 
    while (go->ySub < MIN_SUBPIXEL_SPEED) { go->ySub += MAX_SUBPIXEL_SPEED; go->y -= 1;} 
}

void go_init (GameObject* game_object) 
{
    GameObject* go = (GameObject*)game_object;
    go->x = 0;
    go->y = 0;
    go->xSub = 0;
    go->ySub = 0;
    go->xOrigin = 0;
    go->yOrigin = 0;

    go->xSpeed = 0;
    go->ySpeed = 0;
    go->xSpeedSub = 0;
    go->ySpeedSub = 0;

    go->xAccel = 0;
    go->yAccel = 0;
    go->xAccelSub = 0;
    go->yAccelSub = 0;

    go->fun_step = &go_do_nothing;
    go->fun_pre_step = &go_do_nothing;
    go->fun_post_step = &go_do_nothing;
    go->fun_draw = &go_draw_default;
;

    go->gCurrentFrame = gGODefaultSprite;
}