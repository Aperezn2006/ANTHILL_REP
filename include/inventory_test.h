#ifndef LINK_TEST_H_
#define LINK_TEST_H_

/**
 * @test Test inventory creation
 * @pre Valid size parameter
 * @post Output == Non-NULL pointer
 */
void test1_inventory_create();
/**
 * @test Test inventory creation
 * @pre Invalid size parameter
 * @post Output == NULL pointer
 */
void test2_inventory_create();

/**
 * @test Test inventory destruction
 * @pre Valid inventory pointer
 * @post Output == OK
 */
void test1_inventory_destroy();
/**
 * @test Test inventory destruction
 * @pre NULL inventory pointer
 * @post Output == ERROR
 */
void test2_inventory_destroy();

/**
 * @test Test adding object
 * @pre Valid inventory and object ID
 * @post Output == Ok
 */
void test1_inventory_add_object();
/**
 * @test Test adding object
 * @pre Invalid object ID
 * @post Output == ERROR
 */
void test2_inventory_add_object();

/**
 * @test Test getting object
 * @pre Valid inventory ID
 * @post Output == non-NULL set pointer 
 */
void test1_inventory_get_object();
/**
 * @test Test getting object
 * @pre NULL inventory pointer
 * @post Output == NULL pointer 
 */
void test2_inventory_get_object();

/**
 * @test Test removing object
 * @pre Existing object in inventory
 * @post Output == OK 
 */
void test1_inventory_remove_object();
/**
 * @test Test removing object
 * @pre Non-existing object ID
 * @post Output == ERROR 
 */
void test2_inventory_remove_object();

/**
 * @test Test checking object existence
 * @pre Object exist in inventory
 * @post Output == TRUE 
 */
void test1_inventory_has_object();
/**
 * @test Test checking object existence
 * @pre Object doesn't exist in inventory
 * @post Output == FALSE 
 */
void test2_inventory_has_object();

/**
 * @test Test getting object count
 * @pre Valid inventory pointer
 * @post Output == non-negative count 
 */
void test1_inventory_get_num_objects();
/**
 * @test Test getting object count
 * @pre NULL inventory pointer
 * @post Output == -1 
 */
void test2_inventory_get_num_objects();

/**
 * @test Test getting object by index
 * @pre Valid index
 * @post Output == correct object ID
 */
void test1_inventory_get_object_by_index();
/**
 * @test Test getting object by index
 * @pre Invalid index
 * @post Output == NO_ID
 */
void test2_inventory_get_object_by_index();

/**
 * @test Test getting object by index
 * @pre Object exist in inventory
 * @post Output == valid index
 */
void test1_inventory_get_object_index();
/**
 * @test Test getting object by index
 * @pre Object doesn't exist in inventory
 * @post Output == -1
 */
void test2_inventory_get_object_index();

/**
 * @test Test setting max objects
 * @pre Valid positive size
 * @post Output == OK
 */
void test1_inventory_set_max_objects();
/**
 * @test Test setting max objects
 * @pre Invalid positive size
 * @post Output == ERROR
 */
void test2_inventory_set_max_objects();

/**
 * @test Test printing inventory
 * @pre Valid inventory pointer
 * @post Output == OK
 */
void test1_inventory_print();
/**
 * @test Test printing inventory
 * @pre NULL inventory pointer
 * @post Output == ERROR
 */
void test2_inventory_print();


#endif 

