#include <stdio.h>
#include "game.h"

void update_game(Game *game){
    Character *character = game_get_character(game, 31);
    Id open_link = 123;


    if(character_get_health(character) == 0){
        game_set_link_open(game, open_link, S);
    }
}