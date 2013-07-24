#include <stdio.h>
#include <stdlib.h>

#include "kata_list.h"

#if 0
typedef struct list_elem {
  struct list_elem *next;
  void *value;
} list_elem_t;


typedef struct list {
  struct list_elem *first;
  struct list_elem *last;
  long length;
  void (*print_fn)(list_elem_t *);
  int (*compare_fn)(void *a, void *b); // for sort and search
} list_t;
#endif

list_t * list_create(void (*print)(void *), int (*compare)(void *a, void *b)) {
  list_t *new_list;

  assert(print && compare);

  if ((new_list = malloc(sizeof(list_t))) == NULL) {
    fprintf(stderr, "FATAL ERROR: out of memory in list_create()\n");
    exit(EXIT_FAILURE);
  }

  new_list->first = NULL;
  new_list->last  = NULL;
  new_list->length = 0L;
  new_list->print_fn   = print;
  new_list->compare_fn = compare;

  return new_list;
}


void list_destroy(list_t *list, void (*destroy_elem_fn)(list_elem_t *)) {

  if (list->length > 0 && destroy_elem_fn == NULL) {
    fprintf(stderr, "ERROR: no function for freeing elements provided while trying to destroy a non-empty list\n");
    return;
  }

  while (list->length > 0) {
    destroy_elem_fn(list_remove(list, list->first->value));
  }

  free(list);
}


inline long list_length(list_t *list) {
  return list->length;
}


// returns th eindex of the element in the list
// order can be 0 -> no order (use append)
//              1 -> ascending, before a value that is larger    TODO
//             -1 -> descending, befaore a value that is smaller TODO
long list_insert(list_t *list, void *value, int order) {
  if (order == 0) {
    return list_append(list, value);
  }
  else {
      fprintf(stderr,"ERROR: list_insert(): order != 0, not im plemented yet\n");
      exit(EXIT_FAILURE);
  }
}


// (!) the user is responsible for freeing memory once no longer needed
// usually returned by remove or pass destroy-elem-fn to list_destroy()
long list_append(list_t *list, void *value) {
  long idx = 1;
  list_elem_t *new_elem, *elem_ptr;

  assert(list != NULL);

  if ((new_elem = malloc(sizeof(list_elem_t))) == NULL) {
    fprintf(stderr, "FATAL ERROR: list_appen(): out of space\n");
    exit(EXIT_FAILURE);
  }

  new_elem->next  = NULL;
  new_elem->value = value;

  elem_ptr = list->first;
  while (elem_ptr != NULL) {
    elem_ptr = elem_ptr->next;
    ++idx;
  }

  if (elem_ptr == NULL) {          // append new element
    list->first = new_elem;
  }
  else {
    elem_ptr->next = new_elem;
  }
  list->last  = new_elem;
  list->length++;

  return idx; // starting with 1 (not 0, as for array indices)
}


long list_prepend(list_t *list, void *value) {
  list_elem_t *new_elem;

  assert(list != NULL);

  if ((new_elem = malloc(sizeof(list_elem_t))) == NULL) {
    fprintf(stderr, "FATAL ERROR: list_appen(): out of space\n");
    exit(EXIT_FAILURE);
  }

  new_elem->next  = list->first;
  new_elem->value = value;
  list->first = new_elem;

  if (list->last == NULL) {
    list->last = new_elem;
  }

  list->length++;

  return 1;
}


list_elem_t *list_remove(list_t *list, void *value) {
  fprintf(stderr,"ERROR: list_remove() not im plemented yet\n");
  exit(EXIT_FAILURE);
  // search for value and remove
}


long list_remove_dupes(list_t *l, void *value) {
  fprintf(stderr,"ERROR: list_remove_dupes() not im plemented yet\n");
  exit(EXIT_FAILURE);
}
 // TODO: need a function as argument to remove values


list_elem_t *list_search(void *value) {
  fprintf(stderr,"ERROR: list_search() not im plemented yet\n");
  exit(EXIT_FAILURE);
}


long list_sort(list_t *l, int order) {
  fprintf(stderr,"ERROR: list_sort() not im plemented yet\n");
  exit(EXIT_FAILURE);
}

// print \n after every cols elements
void list_print(list_t *list, unsigned int cols) {
  list_elem_t *tmp;
  unsigned int cnt;

  assert(list != NULL && cols > 0);

  cnt = cols;
  tmp = list->first;
  while (tmp) {
    if (tmp->value != NULL )
      list->print_fn(tmp->value);
    else
      printf("NULL ");

    if (cnt-- == 0)
      printf("\n");
    tmp = tmp->next;
  }
}

