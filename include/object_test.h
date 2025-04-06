#ifndef test1_TEST_H
#define test1_TEST_H

#include "object.h"
#include "test.h"

/*Create*/
/**
 * @test Test object creation
 * @pre No parameters
 * @post Non NULL pointer to object
 */
void test1_object_create();

/*Management of id*/
/**
 * @test Test object set id
 * @pre Pointer to a valid object
 * @post Output == OK
 */
void test1_object_set_id();

/**
 * @test Test object set id with NULL object
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_object_set_id();

/**
 * @test Test object get id
 * @pre Pointer to a valid object
 * @post Output == 1
 */
void test1_object_get_id();

/**
 * @test Test object get id with NULL object
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_object_get_id();

/*Management of name*/
/**
 * @test Test object set name
 * @pre Pointer to a valid object
 * @post Output == OK
 */
void test1_object_set_name();

/**
 * @test Test object set name with NULL object
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_object_set_name();

/**
 * @test Test object get name
 * @pre Pointer to a valid object
 * @post Output == OK
 */
void test1_object_get_name();

/**
 * @test Test object get name with NULL object
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_object_get_name();

/*Management of desc*/
/**
 * @test Test object set description
 * @pre Pointer to a valid object
 * @post Output == OK
 */
void test1_object_set_desc();

/**
 * @test Test object set description with NULL object
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_object_set_desc();

/**
 * @test Test object get description
 * @pre Pointer to a valid object
 * @post Output == OK
 */
void test1_object_get_desc();

/**
 * @test Test object get description with NULL object
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_object_get_desc();

/*Management of inspected*/
/**
 * @test Test object set friendly
 * @pre Pointer to a valid object
 * @post Output == OK
 */
void test1_object_set_inspected();

/**
 * @test Test object set inspected with NULL object
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_object_set_inspected();

/**
 * @test Test object get inspected
 * @pre Pointer to a valid object
 * @post Output == OK
 */
void test1_object_get_inspected();

/**
 * @test Test object get inspected with NULL object
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_object_get_inspected();

/*Print*/
/**
 * @test Test object print
 * @pre Pointer to a valid object
 * @post Output == OK
 */
void test1_object_print();

/**
 * @test Test object print with NULL object
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_object_print();

#endif