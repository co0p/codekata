/*

A: Implement a function that removes duplicates
   (cf ../utils/kata_list.c list_remove_dupes() for singly-linked lists)

B: Implement an alorithm to find a kth to last element (O(1) space, O(N) time)

C: How to delete a node from the middle of the list having only access to that node?

D: Partition a list around a value (pivot) in a part with elements smaller and
   one with elements greater than (or equal to) that value.

E: Implement is_palindrome(list)

F: Given a circular list, return the first node of the circle.

G: Given two lists that represent tow numbers (e.g. 1->2->3 is 123), implement
   a function that adds two numbers (Variation: lists strore number is
   reverse order: e.g. 3->2->1 is 123).

(H:) 1) implement a singly linked list (cf ../utils/)
     2) implemnet a doubly linked list
     3) implement a list using an array

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
// (!) if removing last element need to adjust list->last
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


// D: returns the length of the first part (i.e. number for steps to get to the second
// first part contain elements <x, second part the rest
// -1 indicates error
long list_partition(list_t *list, void *value) {
  list_elem_t *elem, *prev, *tmp;
  long i, idx;

  if (list == NULL || value == NULL) {
    fprintf(stderr, "ERROR: list_partition() -- both elements should be non-NULL\n");
    return -1;
  }

  if ((i = list->length) <= 1) {
    return 0;
  }

  prev = NULL;
  elem = list->first;
  idx = 0;
  while (i-- > 0 /* && elem */) { // >= value; move to the end
    if (list->compare_fn(elem->value, value) == 0 ||
        list->compare_fn(elem->value, value)  > 0) {
        list->last->next = elem; // move to the end
        list->last = elem;
        tmp = elem->next;
        if (prev) {
          prev->next = elem->next;
        }
        else { // no prev -- need to adjust first
          list->first = elem->next;
        }
        elem->next = NULL;
        elem = tmp;
    }
    else {          // < value; keep in place
      prev = elem;
      elem = elem->next;
      ++idx;
    }

  }

  return idx;
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

  assert(list_partition(list, m) == 1);
  list_print(list, (unsigned int) 10);
  assert(list_partition(list, z) == 2);

  list_print(list, (unsigned int) 10);

  e = list_kth_to_last(list, 25);
  assert(e == NULL);
  e = list_kth_to_last(list, 2);
  assert(*((int *)e->value) == 891);


  e = remove_from_list(list_search(list, n));
  if (e == NULL) {  // handle last element
    fprintf(stderr, "WARNING: couldn't remove last element using reference to the element only\n");
    // could call normal remove here ? or use convention to mark is as dummy or overwritable
  }
  list_print(list, (unsigned int) 10);

  e = remove_from_list(list_search(list, y));
  list->length--;
  free(e->value);
  free(e);
  list_print(list, (unsigned int) 10);

  e = remove_from_list(list_search(list, z));
  list->length--;
  free(e->value);
  free(e);
  list_print(list, (unsigned int) 10);

  list_destroy(list, free);

  return EXIT_SUCCESS;
}
