#include "inventory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inventory_test.h"
#include "test.h"
#include "set.h"

#define MAX_TEST 30

int main(int argc, char **argv) {
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Link:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TEST) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_FAILURE);
    }
  }

  if (all || test == 1) test1_inventory_create();
  if (all || test == 2) test2_inventory_create();
  
  if (all || test == 3) test1_inventory_destroy();
  if (all || test == 4) test2_inventory_destroy();
  
  if (all || test == 5) test1_inventory_add_object();
  if (all || test == 6) test2_inventory_add_object();
  
  if (all || test == 7) test1_inventory_get_object();
  if (all || test == 8) test2_inventory_get_object();
  
  if (all || test == 9) test1_inventory_remove_object();
  if (all || test == 10) test2_inventory_remove_object();
  
  if (all || test == 11) test1_inventory_has_object();
  if (all || test == 12) test2_inventory_has_object();
  
  if (all || test == 13) test1_inventory_get_num_objects();
  if (all || test == 14) test2_inventory_get_num_objects();
  
  if (all || test == 15) test1_inventory_get_object_by_index();
  if (all || test == 16) test2_inventory_get_object_by_index();
  
  if (all || test == 17) test1_inventory_get_object_index();
  if (all || test == 18) test2_inventory_get_object_index();
  
  if (all || test == 19) test1_inventory_set_max_objects();
  if (all || test == 20) test2_inventory_set_max_objects();
  
  if (all || test == 21) test1_inventory_print();
  if (all || test == 22) test2_inventory_print();
  
  PRINT_PASSED_PERCENTAGE;
  return EXIT_SUCCESS;
}

void test1_inventory_create(){
    Inventory *inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory != NULL);
    inventory_destroy(inventory);
}

void test2_inventory_create(){
    Inventory *inventory = inventory_create(0);
    PRINT_TEST_RESULT(inventory == NULL);
    inventory_destroy(inventory);

}

void test1_inventory_destroy(){
    Inventory *inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_destroy(inventory)==OK);
}
void test2_inventory_destroy(){
    Inventory *inventory = inventory_create(0);
    PRINT_TEST_RESULT(inventory_destroy(inventory)==ERROR);
}

void test1_inventory_add_object(){
    Inventory *inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_add_object(inventory, 1)==OK);
    
}
void test2_inventory_add_object(){
    Inventory *inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_add_object(inventory, NO_ID)==ERROR);
}

void test1_inventory_get_object(){
    Inventory *inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_get_objects(inventory)!=NULL);
}
void test2_inventory_get_object(){
    Inventory *inventory = inventory_create(0);
    PRINT_TEST_RESULT(inventory_get_objects(inventory)==NULL);
}

void test1_inventory_remove_object(){
    Inventory *inventory = inventory_create(1);
    inventory_add_object(inventory, 2);
    PRINT_TEST_RESULT(inventory_remove_object(inventory, 2)==OK);

}
void test2_inventory_remove_object(){
    Inventory *inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_remove_object(inventory, NO_ID)==ERROR);
}

void test1_inventory_has_object(){
    Inventory *inventory = inventory_create(1);
    inventory_add_object(inventory, 1);
    PRINT_TEST_RESULT(inventory_has_object(inventory, 1)==TRUE);
}
void test2_inventory_has_object(){ /**/
    Inventory *inventory = inventory_create(1);
    inventory_remove_object(inventory, 1);
    PRINT_TEST_RESULT(inventory_has_object(inventory, 1)==FALSE);
}

void test1_inventory_get_num_objects(){
    Inventory *inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_get_num_objects(inventory)!=-1);
}
void test2_inventory_get_num_objects(){
    Inventory *inventory = inventory_create(0);
    PRINT_TEST_RESULT(inventory_get_num_objects(inventory)==-1);
}

void test1_inventory_get_object_by_index(){
    Inventory *inventory = inventory_create(1);
    inventory_add_object(inventory, 1);
    PRINT_TEST_RESULT(inventory_get_object_by_index(inventory, 0)==1);
}
void test2_inventory_get_object_by_index(){
    Inventory *inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_get_object_by_index(inventory, -1)==NO_ID);
}

void test1_inventory_get_object_index(){
    Inventory *inventory = inventory_create(1);
    inventory_add_object(inventory, 1);
    PRINT_TEST_RESULT(inventory_get_object_index(inventory, 1)==0);
}
void test2_inventory_get_object_index(){
    Inventory *inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_get_object_index(inventory, NO_ID)==-1);
}

void test1_inventory_set_max_objects(){
    Inventory *inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_set_max_objects(inventory, 1)==OK);
}
void test2_inventory_set_max_objects(){
    Inventory *inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_set_max_objects(inventory, 0)==ERROR);
}

void test1_inventory_print(){
    Inventory *inventory = inventory_create(1);
    PRINT_TEST_RESULT(inventory_print(inventory)==OK);
    inventory_destroy(inventory);
}
void test2_inventory_print(){
    Inventory *inventory = NULL;
    PRINT_TEST_RESULT(inventory_print(inventory)==ERROR);

}