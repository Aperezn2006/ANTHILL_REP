/**
 * @brief It tests space module
 *
 * @file space_test.c
 * @author Profesores Pprog
 * @version 0.0
 * @date 17-02-2025
 * @copyright GNU Public License
 */

#include "space.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "space_test.h"
#include "test.h"

#define MAX_TESTS 36

/*gcc -o space_test space_test.c space.c set.c -I. -I/(path)*/

/**
 * @brief Main function for SPACE unit tests.
 *
 * You may execute ALL or a SINGLE test
 *   1.- No parameter -> ALL test are executed
 *   2.- A number means a particular test (the one identified by that number)
 *       is executed
 */
int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Space:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)
    test1_space_create();
  if (all || test == 2)
    test2_space_create();
  if (all || test == 3)
    test1_space_set_name();
  if (all || test == 4)
    test2_space_set_name();
  if (all || test == 5)
    test3_space_set_name();

  if (all || test == 6)
    test1_space_set_gdesc();
  if (all || test == 7)
    test2_space_set_gdesc();
  if (all || test == 8)
    test1_space_set_discovered();
  if (all || test == 9)
    test2_space_set_discovered();

  if (all || test == 10)
    test1_space_get_object_from_index();
  if (all || test == 11)
    test2_space_get_object_from_index();
  if (all || test == 12)
    test1_space_get_num_objects();
  if (all || test == 13)
    test2_space_get_num_objects();

  if (all || test == 14)
    test1_space_set_object();
  if (all || test == 15)
    test2_space_set_object();
  if (all || test == 16)
    test1_space_get_id();
  if (all || test == 17)
    test2_space_get_id();
  if (all || test == 18)
    test1_space_get_name();
  if (all || test == 19)
    test2_space_get_name();

  if (all || test == 20)
    test1_space_get_gdesc();
  if (all || test == 21)
    test2_space_get_gdesc();
  if (all || test == 22)
    test1_space_get_discovered();
  if (all || test == 23)
    test2_space_get_discovered();

  if (all || test == 24)
    test1_space_get_character();
  if (all || test == 25)
    test2_space_get_character();
  if (all || test == 26)
    test1_space_set_character();
  if (all || test == 27)
    test2_space_set_character();

  if (all || test == 28)
    test1_space_has_character();
  if (all || test == 29)
    test2_space_has_character();

  if (all || test == 30)
    test1_space_get_i_description();
  if (all || test == 31)
    test2_space_get_i_description();
  if (all || test == 32)

  if (all || test == 34)
    test1_space_multiple_objects();
  if (all || test == 35)
    test2_space_multiple_objects();
  if (all || test == 36)
    test3_space_multiple_objects();

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

void test1_space_create() {
  int result;
  Space *s;
  s = space_create(5);
  result = s != NULL;
  PRINT_TEST_RESULT(result);
  space_destroy(s);
}

void test2_space_create() {
  Space *s;
  s = space_create(4);
  PRINT_TEST_RESULT(space_get_id(s) == 4);
  space_destroy(s);
}

void test1_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, "hola") == OK);
  space_destroy(s);
}

void test2_space_set_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_name(s, "hola") == ERROR);
}

void test3_space_set_name() {
  Space *s;
  s = space_create(5);
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
}

void test1_space_set_gdesc() {
  Space *s;
  char gdesc[5][10] = {"line1", "line2", "line3", "line4", "line5"};

  s = space_create(1);
  PRINT_TEST_RESULT(space_set_description(s, gdesc) == OK);
  space_destroy(s);
}

void test2_space_set_gdesc() {
  char gdesc[5][10] = {"line1", "line2", "line3", "line4", "line5"};

  PRINT_TEST_RESULT(space_set_description(NULL, gdesc) == ERROR);
}

void test1_space_set_discovered() {
  Space *s;
  s = space_create(1);
  PRINT_TEST_RESULT(space_set_discovered(s, TRUE) == OK);
  space_destroy(s);
}

void test2_space_set_discovered() {
  PRINT_TEST_RESULT(space_set_discovered(NULL, TRUE) == ERROR);
}

void test1_space_set_object() {
  Space *s;
  s = space_create(1);
  PRINT_TEST_RESULT(space_add_object(s, TRUE) == OK);
  space_destroy(s);
}

void test2_space_set_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_object(s, TRUE) == ERROR);
}

void test1_space_get_name() {
  Space *s;
  s = space_create(1);
  space_set_name(s, "adios");
  PRINT_TEST_RESULT(strcmp(space_get_name(s), "adios") == 0);
  space_destroy(s);
}

void test2_space_get_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

void test1_space_get_object_from_index() {
  Space *s = space_create(1);
  space_add_object(s, 100);
  PRINT_TEST_RESULT(space_get_object_from_index(s, 0) == 100);
  space_destroy(s);
}

void test2_space_get_object_from_index() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_object_from_index(s, 0) == NO_ID);
}

void test1_space_get_gdesc() {
  Space *s;

  s = space_create(1);

  PRINT_TEST_RESULT(space_get_description(s) != NULL);

  space_destroy(s);
}

void test2_space_get_gdesc() {
  Space *s = NULL;

  PRINT_TEST_RESULT(space_get_description(s) == NULL);

  space_destroy(s);
}

void test1_space_get_discovered() {
  Space *s;
  s = space_create(1);
  space_set_discovered(s, TRUE);

  PRINT_TEST_RESULT(space_get_discovered(s) == TRUE);

  space_destroy(s);
}

void test2_space_get_discovered() {
  PRINT_TEST_RESULT(space_get_discovered(NULL) == WRONG);
}

void test1_space_get_id() {
  Space *s;
  s = space_create(25);
  PRINT_TEST_RESULT(space_get_id(s) == 25);
  space_destroy(s);
}

void test2_space_get_id() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

void test1_space_get_num_objects() {
  Space *s = space_create(1);
  space_add_object(s, 100);
  space_add_object(s, 200);
  PRINT_TEST_RESULT(space_get_num_objects(s) == 2);
  space_destroy(s);
}

void test2_space_get_num_objects() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_num_objects(s) == 0);
}

void test1_space_get_character() {
  Space *s = space_create(1);
  space_set_character(s, 42);
  PRINT_TEST_RESULT(space_get_character(s) == 42);
  space_destroy(s);
}

void test2_space_get_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_character(s) == NO_ID);
}

void test1_space_set_character() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_set_character(s, 42) == OK);
  space_destroy(s);
}

void test2_space_set_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_character(s, 42) == ERROR);
}

void test1_space_has_character() {
  Space *s = space_create(1);
  space_set_character(s, 42);
  PRINT_TEST_RESULT(space_has_character(s, 42) == TRUE);
  space_destroy(s);
}

void test2_space_has_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_has_character(s, 42) == WRONG);
}

void test1_space_get_i_description() {
  Space *s = space_create(1);
  
  PRINT_TEST_RESULT(space_get_i_description(s, 0) != NULL);
  space_destroy(s);
}

void test2_space_get_i_description() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_i_description(s, 0) == NULL);
}


void test1_space_multiple_objects() {
  Space *s = space_create(1);
  space_add_object(s, 100);
  space_add_object(s, 200);
  PRINT_TEST_RESULT(space_has_object(s, 100) == TRUE &&
                    space_has_object(s, 200) == TRUE);
  space_destroy(s);
}

void test2_space_multiple_objects() {
  Space *s = space_create(1);
  space_add_object(s, 100);
  space_add_object(s, 200);
  space_remove_object(s, 100);
  PRINT_TEST_RESULT(space_has_object(s, 100) == FALSE &&
                    space_has_object(s, 200) == TRUE);
  space_destroy(s);
}

void test3_space_multiple_objects() {
  Space *s = space_create(1);
  space_add_object(s, 100);
  space_add_object(s, 200);
  space_add_object(s, 300);
  PRINT_TEST_RESULT(space_get_num_objects(s) == 3);
  space_destroy(s);
}