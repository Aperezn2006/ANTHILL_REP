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
 * @test Test character destruction
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_get_id();

/**
 * @test Test character destruction with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_get_id();

/**
 * @test Test character destruction
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_set_id();

/**
 * @test Test character destruction with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_set_id();

/*  Manejo de name */
/**
 * @test Test character destruction
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_get_name();

/**
 * @test Test character destruction with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_get_name();

/**
 * @test Test character destruction
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_set_name();

/**
 * @test Test character destruction with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_set_name();

/*  Manejo de gdesc */
/**
 * @test Test character destruction
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_get_description();

/**
 * @test Test character destruction with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_get_description();

/**
 * @test Test character destruction
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_set_description();

/**
 * @test Test character destruction with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_set_description();

/*  Manejo de health */
/**
 * @test Test character destruction
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_get_health();

/**
 * @test Test character destruction with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_get_health();

/**
 * @test Test character destruction
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_set_health();

/**
 * @test Test character destruction with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_set_health();

/**
 * @test Test character destruction
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_decrease_health();

/**
 * @test Test character destruction with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_decrease_health();

/*  Manejo de friendly */
/**
 * @test Test character destruction
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_get_friendly();

/**
 * @test Test character destruction with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_get_friendly();

/**
 * @test Test character destruction
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_set_friendly();

/**
 * @test Test character destruction with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_set_friendly();

/*  Manejo de message */
/**
 * @test Test character destruction
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_get_message();

/**
 * @test Test character destruction with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_get_message();

/**
 * @test Test character destruction
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_set_message();

/**
 * @test Test character destruction with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_set_message();

/*  Print */
/**
 * @test Test character destruction
 * @pre Pointer to a valid character
 * @post Output == OK
 */
void test1_character_print();

/**
 * @test Test character destruction with NULL character
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_character_print();

#endif