/*

A: Implement a function that removes duplicates
   (cf ../utils/kata_list.c list_remove_dupes() for singly-linked lists)

B: Implement an alorithm to find a kth to last element (O(1) space, O(N) time)

C: How to delete a node from the middle of the list having only access to that node?

D: Partition a list around a value (pivot) in a part with elements smaller and
   one with elements greater than (or equal to) that value.

E: Implement is_palindrome(list)

F: Given a circular list, return the first node of the circle.

G: a) Given two lists that represent two numbers (e.g. 1->2->3 is 123), implement
      a function that adds two numbers
   b) Variation: lists store the numbers in reverse order: e.g. 3->2->1 is 123).

(H:) 1) implement a singly linked list (cf ../utils/)
     2) implemnet a doubly linked list
     3) implement a list using an array

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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

void int_cpy(void *a, void *b) {
  int tmp, *x, *y;

  if (a == NULL || b == NULL) {
    fprintf(stderr,"ERROR: int_cpy: failed to copy -- both elements must be non-NULL\n");
    return;
  }

  x = (int *) a;
  y = (int *) b;

  tmp = *x;
   *x = *y;
   *y = tmp;
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


// E:

// utils

// reversing a list
// if copy_fn == NULL -> swap pointers, otherwise deep copy
// TODO: test the copy_fn != NULL branch
list_t *list_reverse(list_t *list, void (*print_fn)(void *), int (*compare_fn)(const void *a, const void *b),
                     void (*copy_fn)(void *a, void *b)) {
  list_t *new_list;
  list_elem_t *elem;
  long idx;

  if (list == NULL)
    return NULL;

  if (list->length == 0)
    return list;

  long len = list->length;
  void *values[len];

  new_list = list_create(print_fn, compare_fn);

  elem = list->first;
  idx = 0;
  while (elem) {                // store pointers in a temporary array
    values[idx] = elem->value;
    elem = elem->next;
    ++idx;
  }

  --idx;
  for (idx; idx >= 0; --idx) { // add values to the new list in reverse order

    if (copy_fn == NULL) {
      list_append(new_list, values[idx]); // TODO: check interface for reverse (return new list vs old but reversed ?!)
    }
    else {  // copy_fn allocates new memory and copies the value
        elem = malloc(sizeof(*elem)); // TODO: add error checking
        copy_fn(values[idx]/* from */, elem->value/* to */);
        list_append(new_list, values[idx]);
    }
  }

  return new_list;
}

// assumes list holding elements of the same type
//  (i.e. compare_fn works for values in both lists)
bool list_equal(list_t *list1, list_t *list2) {
  list_elem_t *elem1, *elem2;

  if (!list1 || !list2 || list1->length != list2->length)
    return false;

  elem1 = list1->first;
  elem2 = list2->first;

  while (elem1) {
    if (list1->compare_fn(elem1->value, elem2->value) != 0) {
      return false;
    }
    elem1 = elem1->next;
    elem2 = elem2->next;
  }

  return true;
}

// a function that checks if a list is a palindrome
// i.e. equals to the reverse of the list list
// requires list_equal() -- returns true if two lists are equivalent
//    and list_reverse() -- create a new list which is a reverse copy of the original list
// O(n) time, O(n) space
bool is_palindrome(list_t *list, void (*free_fn)(void *v)) {
  list_t *rev_list;
  bool ret;

  if (list == NULL)
    return false;

  rev_list = list_reverse(list, int_print, int_cmp, NULL);
  ret = list_equal(list, rev_list);
  list_destroy(rev_list, free_fn);

  return ret;
}


// G: b)
// assumes int-valued list
list_t* int_list_add(list_t *k, list_t *l) {
  list_t *sum_list;
  list_elem_t *ek, *el;
  int carry = 0, vk, vl, sum, *tmp_val;

  assert(k && l);

  sum_list = list_create(int_print, int_cmp);

  ek = k->first;
  el = l->first;
  while (ek || el) {
      tmp_val = malloc(sizeof(int)); // TODO add error checking
      vk = ek ? *((int *)(ek->value)) : 0;
      vl = el ? *((int *)(el->value)) : 0;
      sum = vk + vl + carry;
      *tmp_val = sum;
      list_append(sum_list, (void *) tmp_val); // user needs to free the memory later on
      carry = sum > 9 ? 1 : 0;
      ek = ek ? ek->next : NULL;
      el = el ? el->next : NULL;
  }
  if (carry = 1) {
    tmp_val = malloc(sizeof(int));
    *tmp_val = 1;
    list_append(sum_list, (void *) tmp_val);
  }

  return sum_list;
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

  printf("\n=================================\n\n");

  int a1 = 23, a2 = 42, a3 = 33,
      b1 = 23, b2 = 42, b3 = 33,
      c1 = 123, c2 = 99, c3 = 10,
      d1 = 10, d2 = 99, d3 = 123,
      p1 = 12, p2 = 34, p3 = 34, p4 = 12;

  list_t *list1, *list2, *list3, *list4, *plndrm,
         *rev_list2, *revrev_list2,  *rev_list3;

  list1 = list_create(int_print, int_cmp);
  list2 = list_create(int_print, int_cmp);
  list3 = list_create(int_print, int_cmp);
  list4 = list_create(int_print, int_cmp);
  plndrm = list_create(int_print, int_cmp);

  list_append(list1, (void *) &a1);
  list_append(list1, (void *) &a2);
  list_append(list1, (void *) &a3);
  list_print(list1, (unsigned int) 10);

  list_append(list2, (void *) &b1);
  list_append(list2, (void *) &b2);
  list_append(list2, (void *) &b3);
  list_print(list2, (unsigned int) 10);

  list_append(list3, (void *) &c1);
  list_append(list3, (void *) &c2);
  list_print(list3, (unsigned int) 10);

  list_append(list4, (void *) &d1);
  list_append(list4, (void *) &d2);
  list_append(list4, (void *) &d3);
  list_print(list4, (unsigned int) 10);

  list_append(plndrm, (void *) &p1);
  list_append(plndrm, (void *) &p2);
  list_append(plndrm, (void *) &p3);
  list_append(plndrm, (void *) &p4);
  list_print(plndrm, (unsigned int) 10);

  assert(list_equal(list1, NULL) == false);  // testing list_equal()
  assert(list_equal(NULL, list1) == false);
  assert(list_equal(list1, list1) == true);  // list is equal to itself
  assert(list_equal(list1, list3) == false); // two lists of unequal size are unequal
  assert(list_equal(list1, list2) == true);
  list_append(list3, (void *) &c3);
  assert(list_equal(list1, list3) == false); // now same size but unequal elements

  // testing list_reverse() (w/o and  [TODO] w copy_fn)
  rev_list2 = list_reverse(list2, list2->print_fn, list2->compare_fn, NULL);
  rev_list3 = list_reverse(list3, list3->print_fn, list3->compare_fn, NULL);
  revrev_list2 = list_reverse(rev_list2, rev_list2->print_fn, rev_list2->compare_fn, NULL);
  assert(list_equal(list4, rev_list3));
  assert(list_equal(list2, revrev_list2));

  // testing is_palindrome()
  assert(is_palindrome(NULL, NULL) == false);
  assert(is_palindrome(list1, NULL) == false);
  assert(is_palindrome(plndrm, NULL) == true);

  list_destroy(list1, NULL);
  list_destroy(list2, NULL);
  list_destroy(list3, NULL);
  list_destroy(list4, NULL);
  list_destroy(rev_list2, NULL);
  list_destroy(rev_list3, NULL);
  list_destroy(revrev_list2, NULL);
  list_destroy(plndrm, NULL);

  printf("\n=================================\n\n");

  // TODO: test G b): int_list_add(list_t *k, list_t *l)

  return EXIT_SUCCESS;
}
