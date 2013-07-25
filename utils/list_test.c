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
  list_elem_t *elem;
  int *x, *y, *z, *n;
  long ret;

  x = malloc(sizeof(int)); // no error checking done
  y = malloc(sizeof(int));
  z = malloc(sizeof(int));
  n = malloc(sizeof(int));

  *x = 3;
  *y = 5;
  *z = 124;
  *n = 1234;

  list = list_create(int_print, int_cmp);

  assert(list_length(list) == 0);

  ret  = list_insert(list, (void *) x, 0);
  assert(ret == 1);
  assert(list_length(list) == 1);

  ret = list_prepend(list, (void *) y);
  assert(ret == 1);
  assert(list_length(list) == 2);

  ret = list_append(list, (void *) z);
  assert(ret == 3);
  assert(list_length(list) == 3);

  list_print(list, (unsigned int) 10);  // 5 3 124

  elem = list_remove(list, x);
  assert(elem != NULL);
  free(elem->value);
  free(elem);
  assert(list_length(list) == 2);

  list_print(list, (unsigned int) 10); // 5 124

  elem = list_remove(list, n);
  assert(elem == NULL);

  elem = list_remove(list, z);
  assert(elem != NULL);
  free(elem->value);
  free(elem);
  assert(list_length(list) == 1);

  list_print(list, (unsigned int) 10); // 5 TODO: fix the output

  elem = list_remove(list, y);
  assert(elem != NULL);
  free(elem->value);
  free(elem);
  assert(list_length(list) == 0);

  list_print(list, (unsigned int) 10); //

  elem = list_remove(list, y);
  assert(elem == NULL);

  // TODO remove elements from the list or provide freeing function
  list_destroy(list, free);

  free(x);
  free(y);
  free(z);

  return EXIT_SUCCESS;
}
