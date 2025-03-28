/**
 * @brief It declares the tests for the space module
 *
 * @file space_test.h
 * @version 0.0
 * @date 17-02-2025
 */

#ifndef SPACE_TEST_H
#define SPACE_TEST_H

/**
 * @test Test space creation
 * @pre Space ID
 * @post Non NULL pointer to space
 */
void test1_space_create();

/**
 * @test Test space creation
 * @pre Space ID
 * @post Space_ID == Supplied Space Id
 */
void test2_space_create();

/**
 * @test Test function for space_name setting
 * @pre String with space name
 * @post Output==OK
 */
void test1_space_set_name();

/**
 * @test Test function for space_name setting
 * @pre pointer to space = NULL
 * @post Output==ERROR
 */
void test2_space_set_name();

/**
 * @test Test space set name
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test3_space_set_name();

/**
 * @test Test space set north
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_space_set_north();

/**
 * @test Test space set north with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_space_set_north();

/**
 * @test Test space set north with invalid id
 * @pre Pointer to a valid space
 * @post Output == ERROR
 */
void test3_space_set_north();

/**
 * @test Test space set north with valid id
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test4_space_set_north();

/**
 * @test Test space set south
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_space_set_south();

/**
 * @test Test space set south with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_space_set_south();

/**
 * @test Test space set south with invalid id
 * @pre Pointer to a valid space
 * @post Output == ERROR
 */
void test3_space_set_south();

/**
 * @test Test space set south with valid id
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test4_space_set_south();

/**
 * @test Test space set east
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_space_set_east();

/**
 * @test Test space set east with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_space_set_east();

/**
 * @test Test space set east with invalid id
 * @pre Pointer to a valid space
 * @post Output == ERROR
 */
void test3_space_set_east();

/**
 * @test Test space set east with valid id
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test4_space_set_east();

/**
 * @test Test space set west
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_space_set_west();

/**
 * @test Test space set west with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_space_set_west();

/**
 * @test Test space set west with invalid id
 * @pre Pointer to a valid space
 * @post Output == ERROR
 */
void test3_space_set_west();

/**
 * @test Test space set west with valid id
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test4_space_set_west();

/**
 * @test Test space set object
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_space_set_object();

/**
 * @test Test space set object with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_space_set_object();

/**
 * @test Test space get id
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_space_get_id();

/**
 * @test Test space get id with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_space_get_id();

/**
 * @test Test space get name
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_space_get_name();

/**
 * @test Test space get name with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_space_get_name();

/**
 * @test Test space get north
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_Game_get_north();

/**
 * @test Test space get north with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_Game_get_north();

/**
 * @test Test space get south
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_Game_get_south();

/**
 * @test Test space get south with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_Game_get_south();

/**
 * @test Test space get east
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_Game_get_east();

/**
 * @test Test space get east with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_Game_get_east();

/**
 * @test Test space get west
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_Game_get_west();

/**
 * @test Test space get west with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_Game_get_west();

/**
 * @test Test space get object
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_space_get_object();

/**
 * @test Test space get object with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_space_get_object();

/**
 * @test Test space get multiple objects
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_space_multiple_objects();

/**
 * @test Test space get multiple objects with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_space_multiple_objects();

/**
 * @test Test space get multiple objects with valid space
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test3_space_multiple_objects();

#endif /* SPACE_TEST_H */
