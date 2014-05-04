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

// compares two ints
int int_cmp(const void *a, const void *b) {
  int x, y;
  assert(a && b);

  x = *((int *) a);
  y = *((int *) b);

  if (x > y) return  1;
  if (x < y) return -1;
/*(x == y)*/ return  0;
}

int main(void) {
  list_t *list, *list2;
  list_elem_t *elem;
  int *x, *y, *z, *n, *m;
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
  //free(elem->value);   // keep the space for x,y,z,n for re-use later
  free(elem);
  assert(list_length(list) == 2);

  list_print(list, (unsigned int) 10); // 5 124

  elem = list_remove(list, n);
  assert(elem == NULL);

  elem = list_remove(list, z);
  assert(elem != NULL);
  //free(elem->value);
  free(elem);
  assert(list_length(list) == 1);

  list_print(list, (unsigned int) 10); // 5

  elem = list_remove(list, y);
  assert(elem != NULL);
  //free(elem->value);
  free(elem);
  assert(list_length(list) == 0);

  list_print(list, (unsigned int) 10); //

  elem = list_remove(list, y);
  assert(elem == NULL);

  *x = *y = *z = *n = 7;

  list_append(list, z);
  list_prepend(list, x);
  list_append(list, y);
  list_insert(list, n, 0);
  list_remove_dupes(list, n, free); // frees the values
  assert(list_length(list) == 1);
  list_print(list, (unsigned int) 1); // 7

  list_destroy(list, free); // also frees the last element's value

  // test the sorting function: TODO need more testing, asserts etc.
  list2 = list_create(int_print, int_cmp);

  x = malloc(sizeof(int)); // no error checking done
  y = malloc(sizeof(int));
  z = malloc(sizeof(int));
  n = malloc(sizeof(int));
  m = malloc(sizeof(int));

  *x = 891;
  *y = 52;
  *z = 124;
  *n = 234;
  *m = 73;

  list_append(list2, (void *) x);
  list_append(list2, (void *) y);
  list_append(list2, (void *) z);
  list_append(list2, (void *) n);
  list_append(list2, (void *) m);

  list_print(list2, (unsigned int) 10);
  list_sort(list2);                        // FIXME
  list_print(list2, (unsigned int) 10);

  list_destroy(list2, free); // also frees the last element's value

  return EXIT_SUCCESS;
}
