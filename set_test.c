/**
 * @brief It tests set module
 *
 * @file set_test.c
 * @author Rubén
 * @version 0.0
 * @date 10-03-2025
 * @copyright GNU Public License
 */
#include "set.h"

#include <stdio.h>
#include <stdlib.h>

#include "set_test.h"
#include "test.h"

#define MAX_TESTS 10

/* gcc -o set_test set_test.c set.c -I. -I/(path)*/

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

  if (all || test == 1) test1_set_create();
  if (all || test == 2) test1_set_add();
  if (all || test == 3) test2_set_add();
  if (all || test == 4) test1_set_del();
  if (all || test == 5) test2_set_del();
  if (all || test == 6) test1_set_has();
  if (all || test == 7) test2_set_has();
  if (all || test == 8) test1_set_get_size();
  if (all || test == 9) test1_set_get_n();
  if (all || test == 10) test2_set_get_n();

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

void test1_set_create() {
  Set *s = set_create();
  PRINT_TEST_RESULT(s != NULL);
  set_destroy(s);
}

void test1_set_add() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_add(s, 69) == OK && set_has(s, 69) == TRUE);
  set_destroy(s);
}

void test2_set_add() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_add(s, 69) == ERROR);
}

void test1_set_del() {
  Set *s = set_create();
  set_add(s, 69);
  PRINT_TEST_RESULT(set_del(s, 69) == OK && set_has(s, 69) == FALSE);
  set_destroy(s);
}

void test2_set_del() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_del(s, 69) == ERROR);
  set_destroy(s);
}

void test1_set_has() {
  Set *s = set_create();
  set_add(s, 200);
  PRINT_TEST_RESULT(set_has(s, 200) == TRUE);
  set_destroy(s);
}

void test2_set_has() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_has(s, 300) == FALSE);
  set_destroy(s);
}

void test1_set_get_size() {
  Set *s = set_create();
  set_add(s, 69);
  set_add(s, 200);
  PRINT_TEST_RESULT(set_get_size(s) == 2);
  set_destroy(s);
}

void test1_set_get_n() {
  Set *s = set_create();
  set_add(s, 69);
  set_add(s, 200);
  PRINT_TEST_RESULT(set_get_n(s, 0) == 69);
  set_destroy(s);
}

void test2_set_get_n() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_get_n(s, 0) == NO_ID);
  set_destroy(s);
}
