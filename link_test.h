#ifndef LINK_TEST_H_
#define LINK_TEST_H_

/* Manejo de creación de enlace */
/**
 * @test Test link creation with a valid ID
 * @pre Valid ID
 * @post Non-null link pointer
 */
void test1_link_create();

/**
 * @test Test link creation with an invalid ID
 * @pre NULL ID
 * @post Null link pointer
 */
void test2_link_create();

/* Manejo de ID */
/**
 * @test Test setting a valid link ID
 * @pre Pointer to a valid link
 * @post link_get_id() == 2
 */
void test1_link_set_id();

/**
 * @test Test setting an invalid link ID
 * @pre Pointer to a valid link, invalid ID
 * @post ERROR returned
 */
void test2_link_set_id();

/**
 * @test Test getting ID from a valid link
 * @pre Pointer to a valid link
 * @post link_get_id() == 1
 */
void test1_link_get_id();

/**
 * @test Test getting ID from a NULL link
 * @pre NULL link pointer
 * @post ERROR returned
 */
void test2_link_get_id();

/* Manejo de nombre */
/**
 * @test Test setting a valid link name
 * @pre Pointer to a valid link, valid name
 * @post strcmp(link_get_name(), "door1") == 0
 */
void test1_link_set_name();

/**
 * @test Test setting a NULL name
 * @pre Pointer to a valid link, NULL name
 * @post ERROR returned
 */
void test2_link_set_name();

/**
 * @test Test getting name from a valid link
 * @pre Pointer to a valid link with assigned name
 * @post Non-null name
 */
void test1_link_get_name();

/**
 * @test Test getting name from a NULL link
 * @pre NULL link pointer
 * @post NULL name
 */
void test2_link_get_name();

/* Manejo de estado de apertura */
/**
 * @test Test setting open status to TRUE
 * @pre Pointer to a valid link
 * @post link_get_open() == TRUE
 */
void test1_link_set_open();

/**
 * @test Test setting an invalid open status
 * @pre Pointer to a valid link, invalid open status
 * @post ERROR returned
 */
void test2_link_set_open();

/**
 * @test Test getting a valid open status
 * @pre Pointer to a valid link
 * @post link_get_open() == TRUE or FALSE
 */
void test1_link_get_open();

/**
 * @test Test getting open status from a NULL link
 * @pre NULL link pointer
 * @post ERROR returned
 */
void test2_link_get_open();

/* Manejo de dirección */
/**
 * @test Test setting a valid link direction
 * @pre Pointer to a valid link, valid direction (0-3)
 * @post link_get_direction() == direction set
 */
void test1_link_set_direction();

/**
 * @test Test setting an invalid link direction
 * @pre Pointer to a valid link, invalid direction (>3)
 * @post ERROR returned
 */
void test2_link_set_direction();

/**
 * @test Test getting a valid link direction
 * @pre Pointer to a valid link with a set direction
 * @post link_get_direction() == valid direction (0-3)
 */
void test1_link_get_direction();

/**
 * @test Test getting direction from a NULL link
 * @pre NULL link pointer
 * @post ERROR returned
 */
void test2_link_get_direction();

/* Manejo de espacio inicial */
/**
 * @test Test setting a valid start space for a link
 * @pre Pointer to a valid link, valid start space ID
 * @post link_get_start() == start space ID set
 */
void test1_link_set_start();

/**
 * @test Test setting an invalid start space
 * @pre Pointer to a valid link, invalid start space
 * @post ERROR returned
 */
void test2_link_set_start();

/**
 * @test Test getting a valid start space
 * @pre Pointer to a valid link with assigned start space
 * @post link_get_start() == valid start space
 */
void test1_link_get_start();

/**
 * @test Test getting start space from a NULL link
 * @pre NULL link pointer
 * @post ERROR returned
 */
void test2_link_get_start();

/* Manejo de espacio final */
/**
 * @test Test setting a valid end space for a link
 * @pre Pointer to a valid link, valid end space ID
 * @post link_get_end() == end space ID set
 */
void test1_link_set_end();

/**
 * @test Test setting an invalid end space
 * @pre Pointer to a valid link, invalid end space
 * @post ERROR returned
 */
void test2_link_set_end();

/**
 * @test Test getting a valid end space
 * @pre Pointer to a valid link with assigned end space
 * @post link_get_end() == valid end space
 */
void test1_link_get_end();

/**
 * @test Test getting end space from a NULL link
 * @pre NULL link pointer
 * @post ERROR returned
 */
void test2_link_get_end();

/* Impresión de enlace */
/**
 * @test Test printing a valid link
 * @pre Pointer to a valid link
 * @post link_print() == OK
 */
void test1_link_print();

/**
 * @test Test printing a NULL link
 * @pre NULL link pointer
 * @post link_print() == ERROR
 */
void test2_link_print();

#endif /* LINK_TEST_H_ */
