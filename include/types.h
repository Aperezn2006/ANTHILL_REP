/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG,Beatriz, Arturo, Rubén, Ana
 * @version 1
 * @date 11-02-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define NO_ID -1
#define NO_DIR -1

#define MAX_SPACES 100
#define MAX_OBJECTS 100
#define MAX_CHARACTERS 100
#define MAX_LINK 100
#define MAX_PLAYERS 10
#define MAX_TEAMS 16

#define MAX_MESSAGE 100
#define MAX_IMAGE 100

#define PLAYER_HEALTH 5
#define CHARACTER_HEALTH 10

#define BOX_WIDTH 19

typedef long Id;

typedef enum { FALSE, TRUE, WRONG } Bool;

typedef enum { ERROR, OK } Status;

typedef enum { N, S, E, W, U, D } Direction;

typedef enum { SPACE, PLAYER, OBJECT, CHARACTER, LINK, UNSIGNED } Id_Type;

/*SDL*/
#define SDL_SCREEN_ZOOM 2
#define SDL_TILE_SIZE (10 * SDL_SCREEN_ZOOM)

#define SDL_MAP_HEIGHT (128 * 3 * SDL_SCREEN_ZOOM)
#define SDL_INFO_HEIGHT (100 * SDL_SCREEN_ZOOM)

#define SDL_WINDOW_WIDTH (256 * 3 * SDL_SCREEN_ZOOM)
#define SDL_WINDOW_HEIGHT (SDL_MAP_HEIGHT + SDL_INFO_HEIGHT)

#define SDL_MAP_BORDER (20 * SDL_SCREEN_ZOOM)
#define SDL_WALL_HEIGHT (80 * SDL_SCREEN_ZOOM)

#define SDL_LINK_HW (80 * SDL_SCREEN_ZOOM)
#define SDL_PLAYER_HW (70 * SDL_SCREEN_ZOOM)
#define SDL_CHARACTER_HW (70 * SDL_SCREEN_ZOOM)
#define SDL_OBJECT_HW (40 * SDL_SCREEN_ZOOM)

#endif