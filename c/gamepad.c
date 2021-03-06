#include <SDL.h>
#include <stdio.h>
#include "gamepad.h"
#include "btct.h"

// Gamepad State. Find some way to wrap this up and pass it around?
//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;

//Game Controller 1 handler
SDL_Joystick *gGameController = NULL;
SDL_Event e;

double joystickAngle = 0;
int gamepad_quit = 0;

int xDir = 0;
int yDir = 0;

GamepadStatus gamepadStatus;

// End of Gamepad State or something.

GamepadStatus* get_gamepad_status() 
{
    return &gamepadStatus;
}

int get_gamepad_quit() 
{
    return gamepad_quit;
}

int mascot_init_gamepad()
{
    int success = 1;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = 0;
    }
    mascot_check_connections_gamepad();

    return success;
}

void mascot_cleanup_gamepad()
{
    //Close game controller
    SDL_JoystickClose(gGameController);
    gGameController = NULL;
}

void mascot_update_input_state()
{
    while (SDL_PollEvent(&e) != 0)
    {
        //User requests quit
        if (e.type == SDL_QUIT)
        {
            gamepad_quit = 1;
        }
        else if (e.type == SDL_JOYDEVICEADDED) 
        {
            mascot_check_connections_gamepad();
        }
        else if (e.type == SDL_JOYAXISMOTION)
        {
            //Motion on controller 0
            if (e.jaxis.which == 0)
            {
                //X axis motion
                if (e.jaxis.axis == 0)
                {
                    //Left of dead zone
                    if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
                    {
                        xDir = -1;
                    }
                    //Right of dead zone
                    else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
                    {
                        xDir = 1;
                    }
                    else
                    {
                        xDir = 0;
                    }
                    gamepadStatus.stickHorizontal = xDir;
                }
                //Y axis motion
                else if (e.jaxis.axis == 1)
                {
                    //Below of dead zone
                    if (e.jaxis.value < -JOYSTICK_DEAD_ZONE)
                    {
                        yDir = -1;
                    }
                    //Above of dead zone
                    else if (e.jaxis.value > JOYSTICK_DEAD_ZONE)
                    {
                        yDir = 1;
                    }
                    else
                    {
                        yDir = 0;
                    }
                    gamepadStatus.stickVertical = yDir;
                }
            }

            // printf("Updated Thumbstick Position: (%d, %d)\n",xDir, yDir);
            setJoystickTilt(xDir, yDir);
        }
        else if (e.type == SDL_JOYBUTTONUP)
        {
            printf("Button released: %i\n", e.jbutton.button);
        }
        else if (e.type == SDL_JOYBUTTONDOWN)
        {
            printf("Button pressed: %i\n", e.jbutton.button);
        }

        //Calculate angle
        joystickAngle = atan2((double)yDir, (double)xDir) * (180.0 / M_PI);

        //Correct angle
        if (xDir == 0 && yDir == 0)
        {
            joystickAngle = 0;
        }
    }
}

void mascot_check_connections_gamepad()
{
    printf("Checking gamepad connections.\n");
    //Check for joysticks
    if (SDL_NumJoysticks() < 1)
    {
        printf("Warning: No joysticks connected!\n");
    }
    else
    {
        //Load joystick
        gGameController = SDL_JoystickOpen(0);
        if (gGameController == NULL)
        {
            printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
        }
    }
}

void mascot_clear_gamepad_status(GamepadStatus* gs)
{
    gs->connected = 0;
    gs->dirHeldUp = 0;
    gs->dirHeldDown = 0;
    gs->dirHeldLeft = 0;
    gs->dirHeldRight = 0;
    gs->btnHeldSouth = 0;
    gs->btnHeldEast = 0;
}

void mascot_update_gamepad_status(GamepadStatus* gs)
{
    if (gs->dirHeldUp > 0) {gs->dirHeldUp += 1;}
    if (gs->dirHeldDown > 0) {gs->dirHeldDown += 1;}
    if (gs->dirHeldLeft > 0) {gs->dirHeldLeft += 1;}
    if (gs->dirHeldRight > 0) {gs->dirHeldRight += 1;}
    if (gs->btnHeldSouth > 0) {gs->btnHeldSouth += 1;}
    if (gs->btnHeldEast > 0) {gs->btnHeldEast += 1;}
}