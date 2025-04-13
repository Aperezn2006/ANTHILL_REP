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

/**
 * @test Test space set graphic description
 * @pre Pointer to a valid space and valid gdesc
 * @post Output == OK
 */
void test1_space_set_gdesc();

/**
 * @test Test space set graphic description with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_space_set_gdesc();

/**
 * @test Test space set discovered
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_space_set_discovered();

/**
 * @test Test space set discovered with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_space_set_discovered();

/**
 * @test Test space get graphic description
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_space_get_gdesc();

/**
 * @test Test space get graphic description with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_space_get_gdesc();

/**
 * @test Test space get discovered
 * @pre Pointer to a valid space
 * @post Output == OK
 */
void test1_space_get_discovered();

/**
 * @test Test space get discovered with NULL space
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_space_get_discovered();

/**
 * @test Test space get object from index
 * @pre Pointer to a valid space and a valid index
 * @post Output == Valid object ID
 */
void test1_space_get_object_from_index();

/**
 * @test Test space get object from index with NULL space
 * @pre NULL pointer and/or invalid index
 * @post Output == NO_ID
 */
void test2_space_get_object_from_index();

/**
 * @test Test space get number of objects
 * @pre Pointer to a valid space
 * @post Output == Number of objects in the space
 */
void test1_space_get_num_objects();

/**
 * @test Test space get number of objects with NULL space
 * @pre NULL pointer
 * @post Output == 0
 */
void test2_space_get_num_objects();

/**
 * @test Test space get character
 * @pre Pointer to a valid space
 * @post Output == Valid character ID
 */
void test1_space_get_character();

/**
 * @test Test space get character with NULL space
 * @pre NULL pointer
 * @post Output == NO_ID
 */
void test2_space_get_character();

/**
 * @test Test space set character
 * @pre Pointer to a valid space and a valid character ID
 * @post Output == OK
 */
void test1_space_set_character();

/**
 * @test Test space set character with NULL space
 * @pre NULL pointer or invalid character ID
 * @post Output == ERROR
 */
void test2_space_set_character();

/**
 * @test Test space has character
 * @pre Pointer to a valid space and a valid character ID
 * @post Output == TRUE if the character exists, FALSE otherwise
 */
void test1_space_has_character();

/**
 * @test Test space has character with NULL space
 * @pre NULL pointer
 * @post Output == WRONG
 */
void test2_space_has_character();

/**
 * @test Test space get individual graphic description
 * @pre Pointer to a valid space and a valid index
 * @post Output == Valid graphic description string
 */
void test1_space_get_i_dynamic_description();

/**
 * @test Test space get individual graphic description with NULL space
 * @pre NULL pointer or invalid index
 * @post Output == NULL
 */
void test2_space_get_i_dynamic_description();

#endif /* SPACE_TEST_H */
