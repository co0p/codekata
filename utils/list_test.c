// tesing the single linked list


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "kata_list.c" // TODO proper makefile

// print an int
void int_print(void *a) {
  int *i = (int *) a;
  (void) printf(".8%d ", *i);
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

  list = list_create(int_print, int_cmp);
  printf("list->length = %d\n", list_length(list));
  list_destroy(list, NULL);

  return EXIT_SUCCESS;
}
