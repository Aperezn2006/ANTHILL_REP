#ifndef LINK_TEST_H_
#define LINK_TEST_H_

/* Manejo de creación de enlace */
/**
 * @test Test link con un id valido
 * @pre ID
 * @post devuelve un puntero valido
 */
void test1_link_create();

/**
 * @test Test link con id invalido
 * @pre NULL ID
 * @post debe devolver NULL
 */
void test2_link_create();

/* Manejo de ID */
/**
 * @test Test con link id valido
 * @pre Pointer to a valid link
 * @post el id que devuelve es igual al que puesto
 */
void test1_link_set_id();

/**
 * @test Test con ID invalido
 * @pre link creado correctamente, pero id erroneo
 * @post devuelve ERROR
 */
void test2_link_set_id();

/**
 * @test Test con ID valido
 * @pre Puntero valido
 * @post resultado valido
 */
void test1_link_get_id();

/**
 * @test Test con NULL id
 * @pre NULL link puntero
 * @post ERROR returned
 */
void test2_link_get_id();

/* Manejo de nombre */
/**
 * @test Test con valido id
 * @pre valido puntero link y nombre
 * @post strcmp(link_get_name(), "door1") == 0
 */
void test1_link_set_name();

/**
 * @test Test con nombre NULL
 * @pre Puntero valido, nombre NULL
 * @post devuelve ERROR
 */
void test2_link_set_name();

/**
 * @test Test con link valido
 * @pre Puntero valido, y nombre
 * @post Devuelve lo que sea menos NULL
 */
void test1_link_get_name();

/**
 * @test Test con puntero NULL
 * @pre NULL link puntero
 * @post Ndevuelve NULL
 */
void test2_link_get_name();

/* Manejo de estado de apertura */
/**
 * @test Test con el status OPEN
 * @pre Puntero valido
 * @post link_get_open() == TRUE
 */
void test1_link_set_open();

/**
 * @test Test con valor Bool erroneo
 * @pre Puntero valido, pero mal el valor del Bool
 * @post ERROR devuelto
 */
void test2_link_set_open();

/**
 * @test Test con todo valido
 * @pre Puntero valido
 * @post link_get_open() == TRUE o FALSE
 */
void test1_link_get_open();

/**
 * @test Test con link NULL
 * @pre NULL link puntero
 * @post ERROR returned
 */
void test2_link_get_open();

/* Manejo de dirección */
/**
 * @test Test link valido
 * @pre Puntero valido, direccion valida
 * @post link_get_direction() == dierccion asiganda (0-3)
 */
void test1_link_set_direction();

/**
 * @test Test link invalido
 * @pre Puntero valido, direccion invalida (mas de 3 o menos de 0)
 * @post ERROR devuelve
 */
void test2_link_set_direction();

/**
 * @test Test link valido
 * @pre Puntero valido
 * @post link_get_direction() == valida direccion (0-3)
 */
void test1_link_get_direction();

/**
 * @test Test link NULL
 * @pre NULL link puntero
 * @post ERROR devuelve
 */
void test2_link_get_direction();

/* Manejo de espacio inicial */
/**
 * @test Test valido todo
 * @pre Puntero valido, id start valido
 * @post link_get_start() == start  ID asignado
 */
void test1_link_set_start();

/**
 * @test Test link invalido
 * @pre Puntero valido, invalido el id start
 * @post ERROR devuelve
 */
void test2_link_set_start();

/**
 * @test Test con id valido
 * @pre Todo valido
 * @post link_get_start() == valido start id
 */
void test1_link_get_start();

/**
 * @test Test con link NULL
 * @pre NULL link puntero
 * @post ERROR devuelve
 */
void test2_link_get_start();

/* Manejo de espacio final */
/**
 * @test Test todo valido
 * @pre Puntero valido, id end valido
 * @post link_get_end() == end ID set
 */
void test1_link_set_end();

/**
 * @test Test id invalido
 * @pre Puntero invalido
 * @post ERROR devuelve
 */
void test2_link_set_end();

/**
 * @test Test todo valido
 * @pre Puntero valido
 * @post link_get_end() == valido end id
 */
void test1_link_get_end();

/**
 * @test Test con NULL link
 * @pre NULL link puntero
 * @post ERROR devuelve
 */
void test2_link_get_end();

/* Impresión de enlace */
/**
 * @test Test con link valido
 * @pre Puntero valido
 * @post link_print() == OK
 */
void test1_link_print();

/**
 * @test Test con NULL link
 * @pre NULL link puntero
 * @post link_print() == ERROR
 */
void test2_link_print();

#endif /* LINK_TEST_H_ */
