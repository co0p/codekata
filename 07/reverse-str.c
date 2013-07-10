/* reverses a \0-terminated string in-place */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

inline void reverse_str(char *str) {
  register int i, j;
  size_t len = strlen(str);
  char tmp;

  for (i = 0, j = len-1; i < j; ++i,--j) {
       tmp = str[i]; // swap
    str[i] = str[j];
    str[j] = tmp;
  }
}

int main(void) {
  char x = 'a', y = 'b';
  char str[32];

  strcpy(str,"foobar");

  reverse_str(str);
  assert(strcmp(str,"raboof") == 0);
  reverse_str(str);
  assert(strcmp(str,"foobar") == 0);

  return EXIT_SUCCESS;
}
