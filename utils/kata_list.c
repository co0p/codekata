#include <stdio.h>
#include <stdlib.h>

#include "kata_list.h"


list_t * list_create(void (*print)(void *), int (*compare)(const void *a, const void *b)) {
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


void list_destroy(list_t *list, void (*destroy_elem_fn)(void *v)) {
  list_elem_t *elem;

  if (list->length > 0 && destroy_elem_fn == NULL) {
    fprintf(stderr, "WARNING: values not freed as no destroy_elem_fn() provided for a non-empty list\n");
    //return; // user is responsible to free values (or to use automatic vars)
  }

  while (list->length > 0) {
    elem = list_remove(list, list->first->value);
    if (elem != NULL && destroy_elem_fn != NULL) {
      destroy_elem_fn(elem->value);
    }
    free(elem);
  }

  free(list);
}


inline long list_length(list_t *list) {
  return list->length;
}


// returns th eindex of the element in the list
// order can be 0 -> no order (use append)
//              1 -> ascending, before a value that is larger    TODO
//             -1 -> descending, before a value that is smaller TODO
long list_insert(list_t *list, void *value, int order) {
  if (order == 0) {      // no order
    return list_append(list, value);
  }
  else if (order > 0) {  // ascending
      fprintf(stderr,"ERROR: list_insert(): order != 0, not im plemented yet\n");
      exit(EXIT_FAILURE);
  }
  else /* order < 0 */ { // descending
      fprintf(stderr,"ERROR: list_insert(): order != 0, not im plemented yet\n");
      exit(EXIT_FAILURE);
  }
}

// adds a new element at the end of the list
// (!) the user is responsible for freeing memory once no longer needed
// usually returned by remove or pass destroy_elem_fn to list_destroy()
long list_append(list_t *list, void *value) {
  list_elem_t *new_elem;

  assert(list != NULL);

  if ((new_elem = malloc(sizeof(list_elem_t))) == NULL) {
    fprintf(stderr, "FATAL ERROR: list_append(): out of space\n");
    exit(EXIT_FAILURE);
  }

  new_elem->next  = NULL;
  new_elem->value = value;

  if (list->length > 0) {
    list->last->next = new_elem;
  }
  else {
    list->first = new_elem;
  }

  list->last = new_elem;
  list->length++;

  return list->length; // starting with 1 (not 0, as for array indices)
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
  list_elem_t *tmp, *prev;

  assert(list != NULL);

  prev = NULL;
  tmp = list->first;
  while (tmp) {
    if (list->compare_fn(tmp->value, value) == 0) {
      if (prev == NULL) {        // deleting the first element
        list->first = tmp->next; // aka list->first->next
        if (list->length == 1) {  // if it is also the last element
          list->last = NULL;
        }
      }
      else if (tmp->next == NULL) {  // deleting the last element
        list->last = prev;
        prev->next = NULL;
      }
      else {  // somewhere in the middle
        prev->next = tmp->next;
      }

      list->length--; // adjust length in any case

      return tmp; // (!) user is responsible for freeing memory TODO: maybe pass a flag and a free_fn for convenience ?
    }
    prev = tmp;
    tmp = tmp->next;
  }

  return NULL;     // no element with value 'value' found
}

// returns the number of duplicates removed
long list_remove_dupes(list_t *list, void *value, void (*destroy_elem_fn)(void *value)) {
  long cnt = 0;
  list_elem_t *elem, *tmp, *prev;

  elem = list_search(list, value);
  if (elem == NULL) {
    return 0;
  }

  prev = elem;
  elem = elem->next;
  while (elem != NULL) {
    tmp = elem->next;
    if (list->compare_fn(elem->value, value) == 0) {
      destroy_elem_fn(elem->value);
      free(elem);
      prev->next = tmp;
      if (tmp == NULL) {
        list->last = prev;
      }
      list->length--;
      ++cnt;
    }
    elem = tmp;
  }

  return cnt;
}


list_elem_t *list_search(list_t *list, void *value) {
  list_elem_t *tmp;

  assert(list != NULL);

  tmp = list->first;
  while (tmp) {
    if (list->compare_fn(tmp->value, value) == 0) {
      return tmp;
    }
    tmp = tmp->next;
  }
  return NULL;
}


// (!) FIXME FIXME FIXME
long list_sort(list_t *list) {

  if (list == NULL)
    return -1;

  long i, idx, len = list->length;
  void *values[len];
  list_elem_t *elem;

  idx  = 0;
  elem = list->first;
  while (elem) {                    // have the pointers in an array
    values[idx] = elem->value;
    elem = elem->next;
    ++idx;
  }

  for (i = 0; i < len; ++i) {
    printf("%d ", *((int *) values[i]));
  }
  printf("\n");

  qsort(values, sizeof(values)/sizeof(*values), sizeof(*values), list->compare_fn); // sort the array, use compare_fn to control order

  for (i = 0; i < len; ++i) {
    printf("%d ", *((int *) values[i]));
  }
  printf("\n");

  idx  = 0;
  elem = list->first;
  while (elem) {      // copy pointer back to the list
    elem->value = values[idx];
    elem = elem->next;
    ++idx;
  }

  return 1;
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

    if (--cnt == 0) {
      printf("\n");
      cnt = cols;
    }
    tmp = tmp->next;
  }
  printf("\n");
}

