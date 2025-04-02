/**
 * @brief It defines the unit tests for the set module
 *
 * @file set_test.h
 * @version 1.0
 * @date 11-02-2025
 */

#ifndef SET_TEST_H
#define SET_TEST_H

#include "set.h"
#include "test.h"

/**
 * @test Test set creation
 * @pre No parameters
 * @post Non NULL pointer to set
 */
void test1_set_create();

/**
 * @test Test set destruction
 * @pre Pointer to a valid set
 * @post Output == OK
 */
void test1_set_destroy();

/**
 * @test Test set destruction with NULL set
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_set_destroy();

/**
 * @test Test adding an element to the set
 * @pre Valid set and ID
 * @post Output == OK
 */
void test1_set_add();

/**
 * @test Test adding an invalid element to the set
 * @pre Valid set and NO_ID
 * @post Output == ERROR
 */
void test2_set_add();

/**
 * @test Test deleting an element from the set
 * @pre Valid set with an existing ID
 * @post Output == OK
 */
void test1_set_del();

/**
 * @test Test deleting a non-existing element from the set
 * @pre Valid set but ID not present
 * @post Output == ERROR
 */
void test2_set_del();

/**
 * @test Test checking if set contains an element
 * @pre Valid set with an existing ID
 * @post Output == TRUE
 */
void test1_set_has();

/**
 * @test Test checking if set contains a non-existing element
 * @pre Valid set but ID not present
 * @post Output == FALSE
 */
void test2_set_has();

/**
 * @test Test getting the size of the set
 * @pre Valid set with elements
 * @post Output == Correct size
 */
void test1_set_get_size();

/**
 * @test Test getting the size of an empty set
 * @pre Empty set
 * @post Output == 0
 */
void test2_set_get_size();

/**
 * @test Test retrieving an element by index
 * @pre Valid set with elements
 * @post Output == Correct ID
 */
void test1_set_get_n();

/**
 * @test Test retrieving an element by invalid index
 * @pre Valid set but invalid index
 * @post Output == NO_ID
 */
void test2_set_get_n();

#endif /* SET_TEST_H */
