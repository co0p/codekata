//
// simle single linked list API
// (!) user is responsible for allocating and freeing the values
//
#ifndef KATA_LIST_H
#define KATA_LIST_H


typedef struct list_elem {
  struct list_elem *next;
  void *value;
} list_elem_t;


typedef struct list {
  struct list_elem *first;
  struct list_elem *last;
  long length;
  void (*print_fn)(void *value);
  int (*compare_fn)(const void *a, const void *b); // for sort and search
} list_t;


extern list_t * list_create(void (*print_fn)(void *), int (*compare_fn)(const void *a, const void *b));
extern void list_destroy(list_t *l, void (*destroy_elem_fn)(void *value));
extern long list_length(list_t *l);
extern long list_insert(list_t *l, void *value, int order);
extern long list_append(list_t *l, void *value);
extern long list_prepend(list_t *l, void *value);
extern list_elem_t *list_remove(list_t *l, void *value);
extern long list_remove_dupes(list_t *l, void *value, void (*destroy_elem_fn)(void *value));
extern list_elem_t *list_search(list_t *l, void *value);
extern long list_sort(list_t *l); // control order via the compare function
extern void list_print(list_t *l, unsigned int cols);

#endif /* KATA_LIST_H */
