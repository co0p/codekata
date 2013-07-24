// tesing the single linked list


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "kata_list.c" // TODO proper makefile

// print an int
void int_print(void *a) {
  int *i = (int *) a;
  (void) printf("%d ", *i);
}

// compare two ints
// returns:  0  if a == b
//          n>0 if a > b
//          n<0 if a < b
int int_cmp(void *a, void *b) {
  int *x, *y;
  assert(a && b);

  x = (int *) a;
  y = (int *) b;

  return (*x - *y);
}

int main(void) {
  list_t *list;
  int *x, *y;
  long ret;

  x = malloc(sizeof(int)); // no error checking done
  y = malloc(sizeof(int));
  *x = 3;
  *y = 5;

  list = list_create(int_print, int_cmp);

  assert(list_length(list) == 0);

  ret  = list_insert(list, (void *) x, 0);
  assert(ret == 1);
  assert(list_length(list)== 1);

  ret = list_prepend(list, (void *) y);
  assert(ret == 1);
  assert(list_length(list)== 2);

  list_print(list, (unsigned int) 1);

  // TODO remove elements from the list or provide freeing function
  list_destroy(list, NULL);

  free(x);
  free(y);
  return EXIT_SUCCESS;
}
