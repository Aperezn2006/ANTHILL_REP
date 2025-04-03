#include "link.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "link_test.h"
#include "test.h"

#define MAX_TESTS 30

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Link:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_FAILURE);
    }
  }

  if (all || test == 1) test1_link_create();
  if (all || test == 2) test2_link_create();
  if (all || test == 3) test1_link_set_id();
  if (all || test == 4) test2_link_set_id();
  if (all || test == 5) test1_link_get_id();
  if (all || test == 6) test2_link_get_id();
  if (all || test == 7) test1_link_set_name();
  if (all || test == 8) test2_link_set_name();
  if (all || test == 9) test1_link_get_name();
  if (all || test == 10) test2_link_get_name();
  if (all || test == 11) test1_link_set_open();
  if (all || test == 12) test2_link_set_open();
  if (all || test == 13) test1_link_get_open();
  if (all || test == 14) test2_link_get_open();
  if (all || test == 15) test1_link_set_direction();
  if (all || test == 16) test2_link_set_direction();
  if (all || test == 17) test1_link_get_direction();
  if (all || test == 18) test2_link_get_direction();
  if (all || test == 19) test1_link_set_start();
  if (all || test == 20) test2_link_set_start();
  if (all || test == 21) test1_link_get_start();
  if (all || test == 22) test2_link_get_start();
  if (all || test == 23) test1_link_set_end();
  if (all || test == 24) test2_link_set_end();
  if (all || test == 25) test1_link_get_end();
  if (all || test == 26) test2_link_get_end();
  if (all || test == 27) test1_link_print();
  if (all || test == 28) test2_link_print();

  PRINT_PASSED_PERCENTAGE;
  return EXIT_SUCCESS;
}

/*  Create */

void test1_link_create() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link != NULL);
    link_destroy(link);
}

void test2_link_create() {
    Link *link = link_create(NO_ID); 
    PRINT_TEST_RESULT(link == NULL);
}

void test1_link_set_id() {
    Link *link = link_create(1);
    link_set_id(link, 2);
    PRINT_TEST_RESULT(link_get_id(link) == 2);
    link_destroy(link);
}

void test2_link_set_id() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_set_id(link, -1) == ERROR); 
    link_destroy(link);
}

void test1_link_get_id() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_get_id(link) == 1);
    link_destroy(link);
}

void test2_link_get_id() {
    Link *link = NULL;
    PRINT_TEST_RESULT(link_get_id(link) == ERROR); 
}

void test1_link_set_name() {
    Link *link = link_create(1);
    link_set_name(link, "door1");
    PRINT_TEST_RESULT(strcmp(link_get_name(link), "door1") == 0);
    link_destroy(link);
}

void test2_link_set_name() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_set_name(link, NULL) == ERROR);
    link_destroy(link);
}

void test1_link_get_name() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_get_name(link) != NULL);
    link_destroy(link);
}

void test2_link_get_name() {
    Link *link = NULL;
    PRINT_TEST_RESULT(link_get_name(link) == NULL);
}

void test1_link_set_open() {
    Link *link = link_create(1);
    link_set_open(link, TRUE);
    PRINT_TEST_RESULT(link_get_open(link) == TRUE);
    link_destroy(link);
}

void test2_link_set_open() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_set_open(link, 4) == ERROR);
    link_destroy(link);
}

void test1_link_get_open() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_get_open(link) == TRUE || link_get_open(link) == FALSE);
    link_destroy(link);
}

void test2_link_get_open() {
    Link *link = NULL;
    PRINT_TEST_RESULT(link_get_open(link) == WRONG);
}

void test1_link_set_direction() {
    Link *link = link_create(1);
    link_set_direction(link, 0);
    PRINT_TEST_RESULT(link_get_direction(link) == 0);
    link_destroy(link);
}

void test2_link_set_direction() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_set_direction(link, 4) == ERROR);
    link_destroy(link);
}

void test1_link_get_direction() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_get_direction(link) >= 0 || link_get_direction(link) <= 3);
    link_destroy(link);
}

void test2_link_get_direction() {
    Link *link = NULL;
    PRINT_TEST_RESULT((int)link_get_direction(link) == (int)NO_DIR);
}

void test1_link_set_start(){
    Link *link = link_create(1);
    link_set_start(link, 11);
    PRINT_TEST_RESULT(link_get_start(link)==11);
    link_destroy(link);
}

void test2_link_set_start(){
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_set_start(link, -1) == ERROR);
    link_destroy(link);
}

void test1_link_get_start() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_get_start(link) != NO_ID);
    link_destroy(link);
}


void test2_link_get_start(){
    Link *link = NULL;
    PRINT_TEST_RESULT(link_get_start(link) == NO_ID);
}

void test1_link_set_end(){
    Link *link = link_create(1);
    link_set_end(link, 11);
    PRINT_TEST_RESULT(link_get_end(link)==11);
    link_destroy(link);
}

void test2_link_set_end(){
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_set_end(link, -1) == ERROR);
    link_destroy(link);
}

void test1_link_get_end() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_get_end(link)!= -1);
    link_destroy(link);
}


void test2_link_get_end(){
    Link *link = NULL;
    PRINT_TEST_RESULT(link_get_end(link) == NO_ID);
}

void test1_link_print() {
    Link *link = link_create(1);
    PRINT_TEST_RESULT(link_print(link) == OK);
    link_destroy(link);
}

void test2_link_print() {
    Link *link = NULL;
    PRINT_TEST_RESULT(link_print(link) == ERROR);
}
