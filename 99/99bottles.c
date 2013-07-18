#include <stdio.h>
#include <stdlib.h>

#define MAX_BOTTLES 99

// naive version
inline void print_nomore(int i) {
  if (i > 0)  { printf("%d ", i);   return;}
  if (i == 0) { printf("No more "); return;}
    /* i < 0 */ printf("%d ", MAX_BOTTLES);
}

inline void print_bottles(int i) {
  print_nomore(i);
  printf("bottle%s of beer on the wall, ", (i==1) ? "" : "s");
  print_nomore(i);
  printf("bottle%s of beer.\n", (i==1) ? "" : "s");
}

inline void print_wall_bottles(int i) {
  if (i != 0) {
    printf("Take one down and pass it around, ");
  }
  else { /* No beeer!!!  i == 0 */
    printf("Go to the store and buy some more, ");
  }

  print_nomore(i);
  printf("bottle%s of beer on the wall.\n\n",
         (i==1) ? "" : "s");
}



void simple_beer(void) {
  int n;

  for (n = MAX_BOTTLES; n >= 0; --n) {
    print_bottles(n);
    print_wall_bottles(n-1);
  }
}


int main(void) {

  simple_beer();

  return EXIT_SUCCESS;
}
