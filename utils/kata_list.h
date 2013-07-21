//
// simle single linked list API
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
  list_elem_t *(*alloc_fn)(void *value);
  void (*free_fn)(list_elem_t *elem);
  void (*print_fn)(list_elem_t *);
  int (*compare_fn)(void *a, void *b); // for sort and search
} list_t;


extern list_t *list_create(alloc_fn, free_fn, print_fn, compare_fn);
extern list_destroy(list_t *l);
extern long kata_list_length(kata_list_t *l);
extern long kata_list_insert(kata_list_t *l, void *value, int order);
extern long kata_list_append(kata_list_t *l, void *value)
extern long kata_list_prepend(kata_list_t *l, void *value);
extern long kata_list_remove(kata_list *l, void *value);
extern long kata_list_remove_dupes(kata_list *l, void *value);
extern kata_list_elem_t *kata_list_search(void *value);
extern long kata_list_sort(kata_list_t *l, int order);
extern void kata_list_print(kata_list_t *l);

#endif /* KATA_LIST_H */
