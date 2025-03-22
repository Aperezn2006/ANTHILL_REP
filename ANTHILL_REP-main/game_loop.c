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

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);
void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log_file);
void game_loop_cleanup(Game *game, Graphic_engine *gengine);
void log_command(FILE *log_file, Command *cmd);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "graphic_engine.h"

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name);
void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log_file);

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

int game_loop_init(Game *game, Graphic_engine **gengine, char *file_name)
{
    if (game_create_from_file(game, file_name) == ERROR)
    {
        fprintf(stderr, "Error al inicializar el juego.\n");
        return 1;
    }

    *gengine = graphic_engine_create();
    if (!*gengine)
    {
        fprintf(stderr, "Error al inicializar el motor gráfico.\n");
        game_destroy(game);
        return 1;
    }

    return 0;
}

void game_loop_run(Game *game, Graphic_engine *gengine, FILE *log_file)
{
    Command *last_cmd;

    if (!gengine)
        return;

    last_cmd = game_get_last_command(game);

    while (command_get_code(last_cmd) != EXIT && game_get_finished(game) == FALSE)
    {
        space_set_discovered(game_get_space(game, game_get_player_location(game)), TRUE);
        graphic_engine_render(gengine, game);
        command_get_user_input(last_cmd);
        game_actions_update(game, last_cmd);

        if (log_file)
        {
            log_command(log_file, last_cmd);
        }

        if (command_get_code(last_cmd) != UNKNOWN && command_get_code(last_cmd) != NO_CMD)
        {
            game_set_turn(game, (game_get_turn(game) + 1) % game_get_num_players(game));
        }

        if (player_get_health(game_get_player(game)) == 0)
        {
            printf("You died!\n >->->- GAME OVER -<-<-<\n");
            game_set_finished(game, TRUE);
        }
    }
}

void game_loop_cleanup(Game *game, Graphic_engine *gengine)
{
    game_destroy(game);
    graphic_engine_destroy(gengine);
}

void log_command(FILE *log_file, Command *cmd)
{
    CommandCode code = command_get_code(cmd);

    fprintf(log_file, "Comando ejecutado: %s, %s, %d\n",
            command_to_str(code),
            command_get_obj(cmd),
            command_get_result(cmd));

    fflush(log_file);
}
