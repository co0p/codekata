/*

A: Implement a function that removes duplicates
   (cf ../utils/kata_list.c list_remove_dupes() for singly-linked lists)

B: Implement an alorithm to find a kth to last element (O(1) space, O(N) time)

C: How to delete a node from the middle of the list having only access to that node?

D: Partition a list around a value (pivot) in a list with elements smaller and
   one with elements greater than (or equal to) that value.

E: Implement is_palindrome(list)

F: Given a circular list, return the first node of the circle.

 ...

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../utils/kata_list.c"  // FIXME: use a makefile


// utils
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


// B:
list_elem_t *list_kth_to_last(list_t *list, int k) {
  list_elem_t *elem, *runner;
  int i;

  assert(list && k >= 0);

  if (list->length < k)
    return NULL;

  elem = list->first;
  runner = elem;
  i = k;
  while (i--) {
    runner = runner->next; // set the runner k elements apart
  }

  while (runner && runner->next) {
    runner = runner->next;
    elem = elem->next;
  }

  return elem;
}

// C: (user responsible for cleanup)
// move the next to current node and remove (and return) next
// special case: last element (user needs to handle the return NULL)
list_elem_t *remove_from_list(list_elem_t *e) {
  list_elem_t *elem;
  void *tmp;

  assert(e);

  if (e->next == NULL) {
    return NULL; // failed to remove (could also encode this by setting value to NULL)
  }

  elem = e->next;
  tmp = elem->value;
  elem->value = e->value; // swap values (otherwise memory leak)
  e->value = tmp;
  e->next = elem->next;
  // issue: can't update list->length from here

  return elem; // to be freed by the user
}


int main(void) {
  list_t *list;
  int *x,*y,*z,*n,*m;
  list_elem_t *e;

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

  list = list_create(int_print, int_cmp);

  list_append(list, (void *) x);
  list_append(list, (void *) y);
  list_append(list, (void *) z);
  list_append(list, (void *) n);
  list_append(list, (void *) m);

  list_print(list, (unsigned int) 10);

  e = list_kth_to_last(list, 25);
  assert(e == NULL);
  e = list_kth_to_last(list, 2); // 124
  assert(*((int *)e->value) == 124);


  e = remove_from_list(list_search(list, n));
  list->length--;
  free(e->value);
  free(e);

  e = remove_from_list(list_search(list, x));
  list->length--;
  free(e->value);
  free(e);

  list_print(list, (unsigned int) 10);
  list_destroy(list, free);

  return EXIT_SUCCESS;
}
