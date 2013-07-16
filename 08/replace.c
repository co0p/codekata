#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

// replaces ' ' with %20, assumening enough space
// is available and the final length is provided
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

#define MAX_STR 128
// compresses e.g. abbccccddd to a1b2c4d3
// return original string if new string wouldn't be shorter
// the user is responsible for freeing the strings
// O(n) time, O(n) space
char *compress(char* str) {
  int i, j, cnt;
  size_t len = strlen(str), cnt_len;
  char *new_str, cnt_str[MAX_STR];

  if ((new_str = malloc(len+1)) == NULL) {
    fprintf(stderr, "FATAL ERROR: Out of memory in compress()\n");
    exit(EXIT_FAILURE);
  }

  i = j = 0;
  while (i < len) {           // for each character in the original string

    new_str[j++] = str[i++];
    cnt = 1;

    while (str[i] == str[i-1]) {   // for each substring of identical chars
      ++cnt;
      ++i;
    }
    snprintf(cnt_str, MAX_STR, "%d", cnt);
    cnt_len = strlen(cnt_str);
    if (j + cnt_len >= len) {      // original is shorter, return it
      free(new_str);
      return str;
    }
    strncpy(new_str+j,cnt_str,cnt_len+1);
    j += cnt_len;
  }

  return new_str;
}


// returns true if str2 is substring of str1 , false otherwise
bool is_substr(const char *str1, const char *str2) {
  return (strstr(str1, str2) != NULL);
}

// returns true if str1 is ratation of str2
bool is_rotation(char *str1, const char *str2) {
  char *newstr;
  size_t len;
  int i;
  bool ret = false;

  if ((len = strlen(str1)) != strlen(str2)) {
    return false;
  }

  if((newstr = malloc(2*len+1)) == NULL) {
    fprintf(stderr, "FATAL ERROR: Out of memory in is_rotation()\n");
    exit(EXIT_FAILURE);
  }

  strcpy(newstr, str1);
  strcpy(newstr+len, str1);

  ret = is_substr((const char *) newstr, (const char *) str2);

  free(newstr);
  return ret;
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

  assert(strcmp(compress("abbccccddd"),"a1b2c4d3")==0);
  assert(strcmp(compress("aabbccdde"), "aabbccdde") == 0);
  assert(strcmp(compress("aabbccddee"), "aabbccddee") == 0);

  assert(is_rotation("rotation", "foobar") == false);
  assert(is_rotation("","") == true);
  assert(is_rotation("foobar", "foobaz") == false);
  assert(is_rotation("foobar", "barfoo") == true);

  return EXIT_SUCCESS;
}
