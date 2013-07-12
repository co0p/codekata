// replaces ' ' with %20, assumening enough space
// is available and the final length is provided

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void replace(char *str, size_t len) {
  int from_idx, to_idx;

  from_idx = to_idx = len-1;

  while (str[from_idx] == ' ') {
    --from_idx; // set from_idx to last non-space char
  }

  while (from_idx >= 0) {
    while (str[from_idx] != ' ') {
      str[to_idx--] = str[from_idx--];
    }
    if (from_idx >= 0) {
      from_idx--;
      str[to_idx--] = '0';
      str[to_idx--] = '2';
      str[to_idx--] = '%';
    }
  }
}

int main(void) {

  char str1[11], str2[48], str3[7]; // +1 for '\0'
  size_t len1 = 10, len2 = 47, len3 = 6;

  strcpy(str1,"Mr Smith  ");
  strcpy(str2,"The phone is ringing - Oh My God!              ");
  strcpy(str3,"Foobar");

  replace(str3, len3);
  assert(strcmp(str3, "Foobar") == 0);
  replace(str1, len1);
  assert(strcmp(str1, "Mr%20Smith") == 0);
  replace(str2, len2);
  assert(strcmp(str2, "The%20phone%20is%20ringing%20-%20Oh%20My%20God!") == 0);

  return EXIT_SUCCESS;
}
