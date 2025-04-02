#include "player.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player_test.h"
#include "test.h"

#define MAX_TESTS 30

/*gcc -o (name) (.c files) -I. -I/path(change this)*/
/* gcc -o player_test player_test.c player.c -I. -I/(path)*/

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Player:\n");
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
  if (all || test == 1) test1_player_get_id();
  if (all || test == 1) test2_player_get_id();
  if (all || test == 1) test1_player_set_id();
  if (all || test == 1) test2_player_set_id();
  if (all || test == 1) test1_player_get_location();
  if (all || test == 1) test2_player_get_location();
  if (all || test == 1) test1_player_set_location();
  if (all || test == 1) test2_player_set_location();
  if (all || test == 1) test1_player_get_name();
  if (all || test == 1) test2_player_get_name();
  if (all || test == 1) test1_player_set_name();
  if (all || test == 1) test2_player_set_name();
  if (all || test == 1) test1_player_get_health();
  if (all || test == 1) test2_player_get_health();
  if (all || test == 1) test1_player_set_health();
  if (all || test == 1) test2_player_set_health();
  if (all || test == 1) test1_decrease_health();
  if (all || test == 1) test2_decrease_health();
  if (all || test == 1) test1_player_get_description();
  if (all || test == 1) test2_player_get_description();
  if (all || test == 1) test1_player_set_description();
  if (all || test == 1) test2_player_set_description();
  // TODO -
  if (all || test == 1) test1_player_print();
  if (all || test == 1) test2_player_print();

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

/*  Create */

void test1_player_create() {
  Player *player = player_create(10);
  PRINT_TEST_RESULT(player != NULL);
  player_destroy(player);
}

/*  Manejo de id */

void test1_player_get_id() {
  Player *c;
  c = player_create(1);
  player_set_id(c, 1);
  PRINT_TEST_RESULT(player_get_id(c) == 1);
  player_destroy(c);
}

void test2_player_get_id() {
  Player *c = NULL;
  PRINT_TEST_RESULT(player_get_id(c) == NO_ID);
}

void test1_player_set_id() {
  Player *c;
  c = player_create(1);
  PRINT_TEST_RESULT(player_set_id(c, 1) == OK);
  player_destroy(c);
}

void test2_player_set_id() {
  Player *c = NULL;
  PRINT_TEST_RESULT(player_set_id(c, 1) == ERROR);
}

/* Manejo de player_location */
// TODO -
void test1_player_get_location() {}

void test2_player_get_location() {}

void test1_player_set_location() {}

void test2_player_set_location() {}

/*  Manejo de name */

void test1_player_get_name() {
  Player *c;
  c = player_create(1);
  player_set_name(c, "adios");
  PRINT_TEST_RESULT(strcmp(player_get_name(c), "adios") == 0);
  player_destroy(c);
}

void test2_player_get_name() {
  Player *c = NULL;
  PRINT_TEST_RESULT(player_get_name(c) == NULL);
}

void test1_player_set_name() {
  Player *c;
  c = player_create(5);
  PRINT_TEST_RESULT(player_set_name(c, "hola") == OK);
  player_destroy(c);
}

void test2_player_set_name() {
  Player *c = NULL;
  PRINT_TEST_RESULT(player_set_name(c, "hola") == ERROR);
}

/*  Manejo de health */

void test1_player_get_health() {
  long health = 2;
  Player *c;
  c = player_create(1);
  printf("%ld %ld\n", player_get_health(c), health);
  player_set_health(c, health);
  printf("%ld %ld\n", player_get_health(c), health);
  PRINT_TEST_RESULT(player_get_health(c) == health);
  player_destroy(c);
}

void test2_player_get_health() {
  Player *c = NULL;
  PRINT_TEST_RESULT(player_get_health(c) == -1);
}

void test1_player_set_health() {
  Player *c;
  c = player_create(5);
  PRINT_TEST_RESULT(player_set_health(c, 2) == OK);
  player_destroy(c);
}

void test2_player_set_health() {
  Player *c = NULL;
  PRINT_TEST_RESULT(player_set_health(c, 2) == ERROR);
}

void test1_decrease_health() {
  Player *c = NULL;
  c = player_create(12);
  player_set_health(c, 100);
  player_decrease_health(c, 10);
  PRINT_TEST_RESULT(player_get_health(c) == 90);
}

void test2_decrease_health() {
  Player *c = NULL;
  c = player_create(12);
  player_set_health(c, 100);
  PRINT_TEST_RESULT(player_decrease_health(c, 0) == ERROR);
}

/*  Manejo de gdesc */

void test1_player_get_description() {
  Player *c;
  c = player_create(1);
  player_set_description(c, "adios");
  PRINT_TEST_RESULT(strcmp(player_get_description(c), "adios") == 0);
  player_destroy(c);
}

void test2_player_get_description() {
  Player *c = NULL;
  PRINT_TEST_RESULT(player_get_description(c) == NULL);
}

void test1_player_set_description() {
  Player *c;
  c = player_create(5);
  PRINT_TEST_RESULT(player_set_description(c, "hola") == OK);
  player_destroy(c);
}

void test2_player_set_description() {
  Player *c = NULL;
  PRINT_TEST_RESULT(player_set_description(c, "hola") == ERROR);
}

/*  Manejo de inventory*/

// TODO -

/*  Print */

void test1_player_print() {}

void test2_player_print() {}