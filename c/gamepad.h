#ifndef GAMEPAD_H
#define GAMEPAD_H

// Gamepad State
typedef struct {
	int connected;
    int dirHeldUp;
    int dirHeldDown;
    int dirHeldRight;
    int dirHeldLeft;
    int btnHeldSouth;
    int btnHeldEast;
    int stickHorizontal;
    int stickVertical;
} GamepadStatus;

GamepadStatus* get_gamepad_status();

int mascot_init_gamepad();
void mascot_cleanup_gamepad();
void mascot_update_input_state();
void mascot_check_connections_gamepad();
void mascot_clear_gamepad_status();
void mascot_update_gamepad_status();

#endif