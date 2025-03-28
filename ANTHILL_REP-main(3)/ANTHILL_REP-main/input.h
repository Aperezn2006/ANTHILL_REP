#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "types.h"  // Assuming you have a types.h for enums

/* Key states */
typedef enum {
    KS_UNPRESSED = 0,  // Key is not pressed
    KS_PRESSED,        // Key was just pressed
    KS_HELD            // Key is being held
} Key_State;

/* Structure to store input states */
typedef struct {
    Key_State left;
    Key_State right;
    Key_State up;
    Key_State down;
    Key_State attack;
    Key_State take;
    Key_State drop;
    Key_State inspect;
    Key_State escape;
} Game_Input;

/* Global input state */
extern Game_Input game_input;

/* Functions */
void input_update();

#endif /* INPUT_H */
