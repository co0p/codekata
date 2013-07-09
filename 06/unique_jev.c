/*
 * different approaches to check whether string is made of unique characters
 * (!) assumes ASCII characters and \0-terminated strings
 *     empty string is deemed consisting of unique chars
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


/* naive version - compare all to all -- O(n*n) */
bool unique_one(char *str) {
  int i, j;
  size_t len = strlen(str);

  for (i = 0; i < len; ++i) {
    for (j = 0; j < len; ++j) {
      if (i != j && str[i] == str[j]) {
        return false;
      }
    }
  }

  return true;
}


/* slightly improved -- using some symmetry */
bool unique_two(char *str) {
  int i, j;
  size_t len = strlen(str);

  for (i = 0; i < len; ++i) {
    for (j = i+1; j < len; ++j) {
      if (str[i] == str[j]) {
        return false;
      }
    }
  }
  return true;
}

/* utility function that compares two characters
 * returns zero if equal
 */
 int chrcmp(const void *a, const void *b){
    char *ca, *cb;
    ca = (char *) a;
    cb = (char *) b;

    if (*ca == *cb) return  0;
    if (*ca < *cb)  return -1;
    if (*ca > *cb)  return  1;
 }


#define MARKERS_SIZE 256
/* use a bool array of flags, O(n) algo with O(1) space
 * space use could be further reduced to 1/8 by using a bit vector
 */
bool unique_three(char *str) {
  bool markers[MARKERS_SIZE];
  int i;
  size_t len = strlen(str);

  if (len > MARKERS_SIZE) { // larger than alphabet
    return false;
  }

  memset(markers, false,  MARKERS_SIZE*sizeof(markers[0]));

  for (i = 0; i < len; ++i) {
    if (markers[str[i]]) {
      return false;
    }
    markers[str[i]] = true;
  }

  return true;
}


/*
 * another solution could be to sort the string in O(n log n) and then test in O(n)
 * (may need an extra O(n) copy to ensure the string is on the heap, i.e. non-const)
 */


int main(int argc, char *argv[]) {

  char *empty      = "";
  char *unique     = "uniq";
  char *non_unique = "non_unique";

  assert(unique_one(empty)      == true);
  assert(unique_one(unique)     == true);
  assert(unique_one(non_unique) == false);

  assert(unique_two(empty)      == true);
  assert(unique_two(unique)     == true);
  assert(unique_two(non_unique) == false);

  assert(unique_three(empty)      == true);
  assert(unique_three(unique)     == true);
  assert(unique_three(non_unique) == false);

  return EXIT_SUCCESS;
}
