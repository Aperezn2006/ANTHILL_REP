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

/**
 * @test Test object set uses
 * @pre Pointer to a valid object
 * @post Output == OK
 */
void test1_object_set_uses();

/**
 * @test Test object set uses with NULL object
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_object_set_uses();

/**
 * @test Test object get uses
 * @pre Pointer to a valid object with uses set
 * @post Output == Number of uses
 */
void test1_object_get_uses();

/**
 * @test Test object get uses with NULL object
 * @pre NULL pointer
 * @post Output == -1
 */
void test2_object_get_uses();

/**
 * @test Test object set turn amplifier
 * @pre Pointer to a valid object
 * @post Output == OK
 */
void test1_object_set_turn_amplifier();

/**
 * @test Test object set turn amplifier with NULL object
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_object_set_turn_amplifier();

/**
 * @test Test object get turn amplifier
 * @pre Pointer to a valid object with turn amplifier set
 * @post Output == Turn amplifier value
 */
void test1_object_get_turn_amplifier();

/**
 * @test Test object get turn amplifier with NULL object
 * @pre NULL pointer
 * @post Output == -1
 */
void test2_object_get_turn_amplifier();

/**
 * @test Test object set dependency
 * @pre Pointer to a valid object
 * @post Output == OK
 */
void test1_object_set_dependency();

/**
 * @test Test object set dependency with NULL object
 * @pre NULL pointer
 * @post Output == ERROR
 */
void test2_object_set_dependency();

/**
 * @test Test object get dependency
 * @pre Pointer to a valid object with dependency set
 * @post Output == Dependency ID
 */
void test1_object_get_dependency();

/**
 * @test Test object get dependency with NULL object
 * @pre NULL pointer
 * @post Output == NO_ID
 */
void test2_object_get_dependency();

#endif