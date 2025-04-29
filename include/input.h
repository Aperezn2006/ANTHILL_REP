#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>
#include "game.h"
#include "types.h"  

/* Key states */
typedef enum {
  KS_UNPRESSED = 0,  
  KS_PRESSED,        
  KS_HELD            
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
  Key_State jump;
  Key_State use;      /* Added use key */
  Key_State open;     /* Added open key */
  Bool is_selecting_drop;
  Key_State inventory_toggle;
  Key_State inventory_up;
  Key_State inventory_down;
  Key_State inventory_confirm;
  Key_State inventory_cancel;
} Game_Input;

/* Global input state */
extern Game_Input game_input;

/* Functions */
void input_update(Game *game);

#endif /* INPUT_H */

