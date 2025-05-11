#ifndef test1_TEST_H
#define test1_TEST_H

#include "character.h"
#include "test.h"

/*  Create */
/**
 * @test Test character creation
 * @pre No parameters
 * @post Non NULL pointer to character
 */
void test1_character_create();

/*  Manejo de id */
/**
 * @test Test character get id
 * @pre Pointer to a valid character
 * @post Output == 1
 */
void test1_character_get_id();

/**
 * @test Test character get id with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_get_id();

/**
 * @test Test character set id
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_set_id();

/**
 * @test Test character set id with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_set_id();

/*  Manejo de name */
/**
 * @test Test character get name
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_get_name();

/**
 * @test Test character get name with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_get_name();

/**
 * @test Test character set name
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_set_name();

/**
 * @test Test character set name with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_set_name();

/*  Manejo de gdesc */
/**
 * @test Test character get description
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_get_description();

/**
 * @test Test character get description with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_get_description();

/**
 * @test Test character set description
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_set_description();

/**
 * @test Test character set description with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_set_description();

/*  Manejo de health */
/**
 * @test Test character get health
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_get_health();

/**
 * @test Test character get health with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_get_health();

/**
 * @test Test character set health
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_set_health();

/**
 * @test Test character set health with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_set_health();

/**
 * @test Test character decrease health
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_decrease_health();

/**
 * @test Test character decrease health with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_decrease_health();

/*  Manejo de friendly */
/**
 * @test Test character get friendly
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_get_friendly();

/**
 * @test Test character get friendly with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_get_friendly();

/**
 * @test Test character set friendly
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_set_friendly();

/**
 * @test Test character set friendly with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_set_friendly();

/*  Manejo de message */
/**
 * @test Test character get message
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_get_message();

/**
 * @test Test character get message with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_get_message();

/**
 * @test Test character set message
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_set_message();

/**
 * @test Test character set message with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_set_message();

/*  Print */
/**
 * @test Test character print
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_print();

/**
 * @test Test character print with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_print();

/*Manejo de following*/
/**
 * @test Test character get following
 * @pre Pointer to a valid character with a following ID set
 * @post Output == ID of the following character
 */
void test1_character_get_following();

/**
 * @test Test character get following with NULL character
 * @pre NULL pointer
 * @post Output == NO_ID
 */
void test2_character_get_following();

/**
 * @test Test character set following
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_set_following();

/**
 * @test Test character set following with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_set_following();
#endif