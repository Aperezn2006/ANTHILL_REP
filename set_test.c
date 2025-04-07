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

  if (all || test == 3) test1_set_destroy();
  if (all || test == 4) test2_set_destroy();
   
  if (all || test == 5) test1_set_add_id();
  if (all || test == 6) test2_set_add_id();

  if (all || test == 7) test1_set_remove_id();
  if (all || test == 8) test2_set_remove_id();

  if (all || test == 9) test1_set_has_id();
  if (all || test == 10) test2_set_has_id();

  if (all || test == 11) test1_set_get_num_ids();
  if (all || test == 12) test2_set_get_num_ids();
  
  if (all || test == 13) test1_set_get_id_from_index();
  if (all || test == 14) test2_set_get_id_from_index();

  if(all || test == 15) test1_set_print();
  if(all || test == 16) test1_set_print();

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

void test1_set_create() {
  Set *s = set_create();
  PRINT_TEST_RESULT(s != NULL);
  set_destroy(s);
}

void test2_set_create() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_get_num_ids(s) == 0);
  set_destroy(s);
}

void test1_set_destroy(){
  Set *set = set_create();
  PRINT_TEST_RESULT(set_destroy(set)==OK);
}

void test2_set_destroy(){
  Set *set = NULL;
  PRINT_TEST_RESULT(set_destroy(set)==ERROR);
}

void test1_set_add_id() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_add_id(s, 69) == OK && set_has_id(s, 69) == TRUE);
  set_destroy(s);
}

void test2_set_add_id() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_add_id(s, 69) == ERROR);
}

void test1_set_remove_id() {
  Set *s = set_create();
  set_add_id(s, 69);
  PRINT_TEST_RESULT(set_remove_id(s, 69) == OK && set_has_id(s, 69) == FALSE);
  set_destroy(s);
}

void test2_set_remove_id() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_remove_id(s, 69) == ERROR);
  set_destroy(s);
}

void test1_set_has_id() {
  Set *s = set_create();
  set_add_id(s, 200);
  PRINT_TEST_RESULT(set_has_id(s, 200) == TRUE);
  set_destroy(s);
}

void test2_set_has_id() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_has_id(s, 300) == FALSE);
  set_destroy(s);
}

void test1_set_get_num_ids() {
  Set *s = set_create();
  set_add_id(s, 69);
  set_add_id(s, 200);
  PRINT_TEST_RESULT(set_get_num_ids(s) == 2);
  set_destroy(s);
}


void test2_set_get_num_ids() {
  Set *s = NULL;
  PRINT_TEST_RESULT(set_get_num_ids(s) == 0);
  set_destroy(s);
}

void test1_set_get_id_from_index() {
  Set *s = set_create();
  set_add_id(s, 69);
  set_add_id(s, 200);
  PRINT_TEST_RESULT(set_get_id_from_index(s, 0) == 69);
  set_destroy(s);
}

void test2_set_get_id_from_index() {
  Set *s = set_create();
  PRINT_TEST_RESULT(set_get_id_from_index(s, 0) == NO_ID);
  set_destroy(s);
}

void test1_set_print(){
  Set *set = set_create();
  PRINT_TEST_RESULT(set_print(set)==OK);
  set_destroy(set);
}

void test2_set_print(){
  Set *set = NULL;
  PRINT_TEST_RESULT(set_print(set)==ERROR);
}