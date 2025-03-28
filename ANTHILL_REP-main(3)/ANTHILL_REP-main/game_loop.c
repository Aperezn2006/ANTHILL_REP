/**
 * @brief It defines the game loop
 *
 * @file game_loop.c
 * @author Profesores PPROG, Rubén, Ana
 * @version 1
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "game.h"
#include "game_actions.h"
#include "game_reader.h"
#include "graphic_engine2.h"
#include "player.h"
#include "input.h" // Include keyboard input system
#define MOVE_STEP 2  // Reduce this for finer movement
#define SCREEN_WIDTH  800   // Change based on your window size
#define SCREEN_HEIGHT 600
#define TILE_SIZE     10    // Scaling factor
#define PLAYER_WIDTH  50    // Ant width in pixels
#define PLAYER_HEIGHT 50    // Ant height in pixels



int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);
void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log_file);
void game_loop_cleanup(Game *game, Graphic_engine *gengine);
void log_command(FILE *log_file, Command *cmd);

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name)
{
    if (game_create_from_file(game, file_name) == ERROR)
    {
        fprintf(stderr, "Error while initializing game.\n");
        return 1;
    }

    if ((*gengine = graphic_engine_create()) == NULL)
    {
        fprintf(stderr, "Error while initializing graphic engine.\n");
        game_destroy(game);
        return 1;
    }

    return 0;
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine)
{
    game_destroy(game);
    graphic_engine_destroy(gengine);
}

int main(int argc, char *argv[])
{
    Game *game;
    Graphic_engine *gengine;
    FILE *log_file = NULL;
    char *game_data_file = NULL;

    if (argc < 2)
    {
        fprintf(stderr, "Uso: %s <game_data_file> [-l log_file]\n", argv[0]);
        return 1;
    }

    game_data_file = argv[1];

    if (argc == 4 && strcmp(argv[2], "-l") == 0)
    {
        log_file = fopen(argv[3], "w");
        if (!log_file)
        {
            fprintf(stderr, "Error: No se pudo abrir el archivo de log %s\n", argv[3]);
            return 1;
        }
    }

    game = game_init();
    if (!game)
    {
        fprintf(stderr, "Error: No se pudo crear el juego\n");
        if (log_file)
            fclose(log_file);
        return 1;
    }

    if (game_loop_init(game, &gengine, game_data_file) != 0)
    {
        game_destroy(game);
        if (log_file)
            fclose(log_file);
        return 1;
    }

    game_loop_run(game, gengine, log_file);
    game_loop_cleanup(game, gengine);

    if (log_file)
        fclose(log_file);

    return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log_file) {
    if (!gengine) return;

    while (!game_get_finished(game)) {
        input_update();  
        game_update_player_position(game);  // Move player with bounds check
        graphic_engine_render(gengine, game);  

        if (game_input.escape == KS_PRESSED) {
            game_set_finished(game, TRUE);
            break;
        }

        SDL_Delay(16);  
    }
}

