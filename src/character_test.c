#include "character.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character_test.h"
#include "test.h"

#define MAX_TESTS 30

/*gcc -o (name) (.c files) -I. -I/path(change this)*/
/* gcc -o character_test character_test.c character.c -I. -I/(path)*/

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

  if (all || test == 1) test1_character_create();
  if (all || test == 2) test1_character_get_id();
  if (all || test == 3) test2_character_get_id();
  if (all || test == 4) test1_character_set_id();
  if (all || test == 5) test2_character_set_id();
  if (all || test == 6) test1_character_get_name();
  if (all || test == 7) test2_character_get_name();
  if (all || test == 8) test1_character_set_name();
  if (all || test == 9) test2_character_set_name();
  if (all || test == 10) test1_character_get_description();
  if (all || test == 11) test2_character_get_description();
  if (all || test == 12) test1_character_set_description();
  if (all || test == 13) test2_character_set_description();
  if (all || test == 14) test1_character_get_health();
  if (all || test == 15) test2_character_get_health();
  if (all || test == 26) test1_character_set_health();
  if (all || test == 17) test2_character_set_health();
  if (all || test == 18) test1_decrease_health();
  if (all || test == 19) test2_decrease_health();
  if (all || test == 20) test1_character_get_friendly();
  if (all || test == 21) test2_character_get_friendly();
  if (all || test == 22) test1_character_set_friendly();
  if (all || test == 23) test2_character_set_friendly();
  if (all || test == 24) test1_character_get_message();
  if (all || test == 25) test2_character_get_message();
  if (all || test == 26) test1_character_set_message();
  if (all || test == 27) test2_character_set_message();
  if (all || test == 28) test1_character_print();
  if (all || test == 29) test2_character_print();
  if (all || test == 30) test1_character_get_following();
  if (all || test == 31) test2_character_get_following();
  if (all || test == 32) test1_character_set_following();
  if (all || test == 33) test2_character_set_following();

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

/*  Create */
void test1_character_create() {
  Character *character = character_create(10);
  PRINT_TEST_RESULT(character != NULL);
  character_destroy(character);
}

/*  Manejo de id */

void test1_character_get_id() {
  Character *c;
  c = character_create(1);
  character_set_id(c, 1);
  PRINT_TEST_RESULT(character_get_id(c) == 1);
  character_destroy(c);
}

void test2_character_get_id() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_id(c) == NO_ID);
}

void test1_character_set_id() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_id(c, 1) == OK);
  character_destroy(c);
}

void test2_character_set_id() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_id(c, 1) == ERROR);
}

/*  Manejo de name */

void test1_character_get_name() {
  Character *c;
  c = character_create(1);
  character_set_name(c, "adios");
  PRINT_TEST_RESULT(strcmp(character_get_name(c), "adios") == 0);
  character_destroy(c);
}

void test2_character_get_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_name(c) == NULL);
}

void test1_character_set_name() {
  Character *c;
  c = character_create(5);
  PRINT_TEST_RESULT(character_set_name(c, "hola") == OK);
  character_destroy(c);
}

void test2_character_set_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_name(c, "hola") == ERROR);
}

/*  Manejo de gdesc */

void test1_character_get_description() {
  Character *c;
  c = character_create(1);
  character_set_description(c, "adios");
  PRINT_TEST_RESULT(strcmp(character_get_description(c), "adios") == 0);
  character_destroy(c);
}

void test2_character_get_description() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_description(c) == NULL);
}

void test1_character_set_description() {
  Character *c;
  c = character_create(5);
  PRINT_TEST_RESULT(character_set_description(c, "hola") == OK);
  character_destroy(c);
}

void test2_character_set_description() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_description(c, "hola") == ERROR);
}

/*  Manejo de health */

void test1_character_get_health() {
  long health = 2;
  Character *c;
  c = character_create(1);
  printf("%ld %ld\n", character_get_health(c), health);
  character_set_health(c, health);
  printf("%ld %ld\n", character_get_health(c), health);
  PRINT_TEST_RESULT(character_get_health(c) == health);
  character_destroy(c);
}

void test2_character_get_health() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_health(c) == -1);
}

void test1_character_set_health() {
  Character *c;
  c = character_create(5);
  PRINT_TEST_RESULT(character_set_health(c, 2) == OK);
  character_destroy(c);
}

void test2_character_set_health() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_health(c, 2) == ERROR);
}

void test1_decrease_health() {
  Character *c = NULL;
  c = character_create(12);
  character_set_health(c, 100);
  character_decrease_health(c, 10);
  PRINT_TEST_RESULT(character_get_health(c) == 90);
}

void test2_decrease_health() {
  Character *c = NULL;
  c = character_create(12);
  character_set_health(c, 100);
  PRINT_TEST_RESULT(character_decrease_health(c, 0) == ERROR);
}

/*  Manejo de friendly */

void test1_character_get_friendly() {
  Character *c;
  c = character_create(1);
  character_set_friendly(c, TRUE);
  PRINT_TEST_RESULT(character_get_friendly(c) == TRUE);
  character_destroy(c);
}

void test2_character_get_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_friendly(c) == FALSE);
}

void test1_character_set_friendly() {
  Character *c;
  c = character_create(5);
  PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == OK);
  character_destroy(c);
}

void test2_character_set_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == ERROR);
}

/*  Manejo de message */

void test1_character_get_message() {
  Character *c;
  c = character_create(1);
  character_set_message(c, "adios");
  PRINT_TEST_RESULT(strcmp(character_get_message(c), "adios") == 0);
  character_destroy(c);
}

void test2_character_get_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_message(c) == NULL);
}

void test1_character_set_message() {
  Character *c;
  c = character_create(5);
  PRINT_TEST_RESULT(character_set_message(c, "hola") == OK);
  character_destroy(c);
}

void test2_character_set_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_message(c, "hola") == ERROR);
}

/*  Print */
void test1_character_print() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_print(c) == OK);
  character_destroy(c);
}

void test2_character_print() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_print(c) == ERROR);
}

/*  Manejo de following */

void test1_character_get_following() {
  Character *c;
  c = character_create(1);
  character_set_following(c, 42);
  PRINT_TEST_RESULT(character_get_following(c) == 42);
  character_destroy(c);
}

void test2_character_get_following() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_following(c) == NO_ID);
}

void test1_character_set_following() {
  Character *c;
  c = character_create(1);
  PRINT_TEST_RESULT(character_set_following(c, 42) == OK);
  character_destroy(c);
}

void test2_character_set_following() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_following(c, 42) == ERROR);
}