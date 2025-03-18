/**
 * @brief It defines common types for the whole project
 *
 * @file types.h
 * @author Profesores PPROG, Rubén, Ana
 * @version 2
 * @date 01-03-2025
 * @copyright GNU Public License
 */

#ifndef TYPES_H
#define TYPES_H

#define WORD_SIZE 1000
#define NO_ID -1

#define MAX_SPACES 100
#define MAX_OBJECTS 100
#define MAX_CHARACTERS 100

#define PLAYER_HEALTH 5
#define CHARACTER_HEALTH 10

#define PLAYER_ID -200
#define BOX_WIDTH 19

typedef long Id;

typedef enum { FALSE, TRUE } Bool;

typedef enum { ERROR, OK } Status;

typedef enum { N, S, E, W } Direction;

#endif