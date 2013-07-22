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


long list_insert(list_t *l, void *value, int order) {
  fprintf(stderr,"ERROR: () not im plemented yet\n");
  exit(EXIT_FAILURE);
}

long list_append(list_t *l, void *value) {
  fprintf(stderr,"ERROR: () not im plemented yet\n");
  exit(EXIT_FAILURE);
}

long list_prepend(list_t *l, void *value) {
  fprintf(stderr,"ERROR: () not im plemented yet\n");
  exit(EXIT_FAILURE);
}

list_elem_t *list_remove(list_t *l, void *value) {
  fprintf(stderr,"ERROR: () not im plemented yet\n");
  exit(EXIT_FAILURE);
}

long list_remove_dupes(list_t *l, void *value) {
  fprintf(stderr,"ERROR: () not im plemented yet\n");
  exit(EXIT_FAILURE);
}
 // TODO: need a function as argument to remove values

list_elem_t *list_search(void *value) {
  fprintf(stderr,"ERROR: () not im plemented yet\n");
  exit(EXIT_FAILURE);
}

long list_sort(list_t *l, int order) {
  fprintf(stderr,"ERROR: () not im plemented yet\n");
  exit(EXIT_FAILURE);
}

void list_print(list_t *l) {
  fprintf(stderr,"ERROR: () not im plemented yet\n");
  exit(EXIT_FAILURE);
}

