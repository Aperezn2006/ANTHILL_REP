#include "object.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "object_test.h"
#include "test.h"

#define MAX_TESTS 21

/*gcc -o (name) (.c files) -I. -I/path(ohange this)*/
/* gcc -o object_test object_test.c object.c -I. -I/(path)*/

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Set:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\t", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1) test1_object_create();
  if (all || test == 2) test1_object_set_id();
  if (all || test == 3) test2_object_set_id();
  if (all || test == 4) test1_object_get_id();
  if (all || test == 5) test2_object_get_id();
  if (all || test == 6) test1_object_set_name();
  if (all || test == 7) test2_object_set_name();
  if (all || test == 8) test1_object_get_name();
  if (all || test == 9) test2_object_get_name();
  if (all || test == 11) test1_object_set_desc();
  if (all || test == 12) test2_object_set_desc();
  if (all || test == 13) test1_object_get_desc();
  if (all || test == 14) test2_object_get_desc();
  if (all || test == 15) test1_object_set_inspected();
  if (all || test == 16) test2_object_set_inspected();
  if (all || test == 17) test1_object_get_inspected();
  if (all || test == 18) test2_object_get_inspected();
  if (all || test == 19) test1_object_print();
  if (all || test == 20) test2_object_print();
  if (all || test == 21) test1_object_set_uses();
  if (all || test == 22) test2_object_set_uses();
  if (all || test == 23) test1_object_get_uses();
  if (all || test == 24) test2_object_get_uses();
  if (all || test == 25) test1_object_set_turn_amplifier();
  if (all || test == 26) test2_object_set_turn_amplifier();
  if (all || test == 27) test1_object_get_turn_amplifier();
  if (all || test == 28) test2_object_get_turn_amplifier();
  if (all || test == 29) test1_object_set_dependency();
  if (all || test == 30) test2_object_set_dependency();
  if (all || test == 31) test1_object_get_dependency();
  if (all || test == 32) test2_object_get_dependency();

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

/*Create*/
void test1_object_create() {
  Object *object = object_create(10, 1);
  PRINT_TEST_RESULT(object != NULL);
  object_destroy(object);
}

/*Management of id*/
void test1_object_set_id() {
  Object *o;
  o = object_create(1, 1);
  PRINT_TEST_RESULT(object_set_id(o, 1) == OK);
  object_destroy(o);
}

void test2_object_set_id() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_id(o, 1) == ERROR);
}

void test1_object_get_id() {
  Object *o;
  o = object_create(1, 1);
  object_set_id(o, 1);
  PRINT_TEST_RESULT(object_get_id(o) == 1);
  object_destroy(o);
}

void test2_object_get_id() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_id(o) == NO_ID);
}

/*Management of name*/
void test1_object_set_name() {
  Object *o;
  o = object_create(5, 2);
  PRINT_TEST_RESULT(object_set_name(o, "hola") == OK);
  object_destroy(o);
}

void test2_object_set_name() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_name(o, "hola") == ERROR);
}

void test1_object_get_name() {
  Object *o;
  o = object_create(1, 1);
  object_set_name(o, "adios");
  PRINT_TEST_RESULT(strcmp(object_get_name(o), "adios") == 0);
  object_destroy(o);
}

void test2_object_get_name() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_name(o) == NULL);
}

/*Management of desc*/
void test1_object_set_desc() {
  Object *o;
  o = object_create(5, 1);
  PRINT_TEST_RESULT(object_set_desc(o, "hola") == OK);
  object_destroy(o);
}

void test2_object_set_desc() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_desc(o, "hola") == ERROR);
}

void test1_object_get_desc() {
  Object *o;
  o = object_create(1, 1);
  object_set_desc(o, "adios");
  PRINT_TEST_RESULT(strcmp(object_get_desc(o), "adios") == 0);
  object_destroy(o);
}

void test2_object_get_desc() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_desc(o) == NULL);
}

/*Management of inspected*/
void test1_object_set_inspected() {
  Object *o;
  o = object_create(5, 1);
  PRINT_TEST_RESULT(object_set_inspected(o, TRUE) == OK);
  object_destroy(o);
}

void test2_object_set_inspected() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_inspected(o, TRUE) == ERROR);
}

void test1_object_get_inspected() {
  Object *o;
  o = object_create(1, 1);
  object_set_inspected(o, TRUE);
  PRINT_TEST_RESULT(object_get_inspected(o) == TRUE);
  object_destroy(o);
}

void test2_object_get_inspected() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_inspected(o) == FALSE);
}

/*Print*/
void test1_object_print() {
  Object *o = object_create(1, 1);
  PRINT_TEST_RESULT(object_print(o) == OK);
  object_destroy(o);
}

void test2_object_print() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_print(o) == ERROR);
}

/* Management of uses */
void test1_object_set_uses() {
  Object *o = object_create(1, 1);
  PRINT_TEST_RESULT(object_set_uses(o, 5) == OK);
  object_destroy(o);
}

void test2_object_set_uses() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_uses(o, 5) == ERROR);
}

void test1_object_get_uses() {
  Object *o = object_create(1, 1);
  object_set_uses(o, 5);
  PRINT_TEST_RESULT(object_get_uses(o) == 5);
  object_destroy(o);
}

void test2_object_get_uses() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_uses(o) == -1);
}

/* Management of turn amplifier */
void test1_object_set_turn_amplifier() {
  Object *o = object_create(1, 1);
  PRINT_TEST_RESULT(object_set_turn_amplifier(o, 3) == OK);
  object_destroy(o);
}

void test2_object_set_turn_amplifier() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_turn_amplifier(o, 3) == ERROR);
}

void test1_object_get_turn_amplifier() {
  Object *o = object_create(1, 1);
  object_set_turn_amplifier(o, 3);
  PRINT_TEST_RESULT(object_get_turn_amplifier(o) == 3);
  object_destroy(o);
}

void test2_object_get_turn_amplifier() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_turn_amplifier(o) == 0);
}

/* Management of dependencies */
void test1_object_set_dependency() {
  Object *o = object_create(1, 1);
  PRINT_TEST_RESULT(object_set_dependency(o, 42) == OK);
  object_destroy(o);
}

void test2_object_set_dependency() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_dependency(o, 42) == ERROR);
}

void test1_object_get_dependency() {
  Object *o = object_create(1, 1);
  object_set_dependency(o, 42);
  PRINT_TEST_RESULT(object_get_dependency(o) == 42);
  object_destroy(o);
}

void test2_object_get_dependency() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_dependency(o) == NO_ID);
}