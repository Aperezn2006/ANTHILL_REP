#ifndef test1_TEST_H
#define test1_TEST_H

#include "player.h"
#include "test.h"

/*  Create */
/**
 * @test Test player creation
 * @pre No parameters
 * @post Non NULL pointer to player
 */
void test1_player_create();

/* Manejo de id */
/**
 * @test Test player get id
 * @pre Pointer to a valid player
 * @post Output == 1
 */
void test1_player_get_id();

/**
 * @test Test player get id with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_get_id();

/**
 * @test Test player set id
 * @pre Pointer to a valid player
 * @post Output == OK
 */
void test1_player_set_id();

/**
 * @test Test player set id with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_set_id();

/* Manejo de player_location */
// TODO -
void test1_player_get_location();

void test2_player_get_location();

void test1_player_set_location();

void test2_player_set_location();

/* Manejo de name */
/**
 * @test Test player get name
 * @pre Pointer to a valid player
 * @post Output == OK
 */
void test1_player_get_name();

/**
 * @test Test player get name with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_get_name();

/**
 * @test Test player set name
 * @pre Pointer to a valid player
 * @post Output == OK
 */
void test1_player_set_name();

/**
 * @test Test player set name with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_set_name();

/* Manejo de health */
/**
 * @test Test player get health
 * @pre Pointer to a valid player
 * @post Output == OK
 */
void test1_player_get_health();

/**
 * @test Test player get health with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_get_health();

/**
 * @test Test player set health
 * @pre Pointer to a valid player
 * @post Output == OK
 */
void test1_player_set_health();

/**
 * @test Test player set health with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_set_health();

/**
 * @test Test player decrease health
 * @pre Pointer to a valid player
 * @post Output == OK
 */
void test1_decrease_health();

/**
 * @test Test player decrease health with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_decrease_health();

/* Manejo de gdesc */
/**
 * @test Test player get description
 * @pre Pointer to a valid player
 * @post Output == OK
 */
void test1_player_get_description();

/**
 * @test Test player get description with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_get_description();

/**
 * @test Test player set description
 * @pre Pointer to a valid player
 * @post Output == OK
 */
void test1_player_set_description();

/**
 * @test Test player set description with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_set_description();

/* Manejo de inventory */
// TODO -

/* Print */
/**
 * @test Test player print
 * @pre Pointer to a valid player
 * @post Output == OK
 */
void test1_player_print();

/**
 * @test Test player print with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_print();

#endif