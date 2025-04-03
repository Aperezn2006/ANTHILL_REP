#ifndef test1_TEST_H
#define test1_TEST_H

#include "player.h"
#include "test.h"

/* Create */
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
/**
 * @test Test player get inventory
 * @pre Pointer to a valid player
 * @post Output == valid inventory
 */
void test1_player_get_inventory();

/**
 * @test Test player get inventory with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_get_inventory();

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

/* Manejo de player_location */
/**
 * @test Test player get location
 * @pre Pointer to a valid player
 * @post Output == valid location
 */
void test1_player_get_location();

/**
 * @test Test player get location with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_get_location();

/**
 * @test Test player set location
 * @pre Pointer to a valid player and a valid location
 * @post Output == OK
 */
void test1_player_set_location();

/**
 * @test Test player set location with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_set_location();

/**
 * @test Test player get object from index
 * @pre Pointer to a valid player and a valid index
 * @post Output == valid object
 */
void test1_player_get_object_from_index();

/**
 * @test Test player get object from index with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_get_object_from_index();

/* Manejo de objects */
/**
 * @test Test player get number of objects
 * @pre Pointer to a valid player
 * @post Output == valid number of objects
 */
void test1_player_get_num_objects();

/**
 * @test Test player get number of objects with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_get_num_objects();

/**
 * @test Test player remove object
 * @pre Pointer to a valid player and a valid object
 * @post Output == OK
 */
void test1_player_remove_object();

/**
 * @test Test player remove object with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_remove_object();

/**
 * @test Test player has object
 * @pre Pointer to a valid player and a valid object
 * @post Output == TRUE or FALSE
 */
void test1_player_has_object();

/**
 * @test Test player has object with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_has_object();

/**
 * @test Test player add object
 * @pre Pointer to a valid player and a valid object
 * @post Output == OK
 */
void test1_player_add_object();

/**
 * @test Test player add object with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_add_object();

/**
 * @test Test player set maximum number of objects
 * @pre Pointer to a valid player and a valid max number
 * @post Output == OK
 */
void test1_player_set_max_objs();

/**
 * @test Test player set maximum number of objects with NULL player
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_player_set_max_objs();

#endif