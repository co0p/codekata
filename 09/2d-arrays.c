#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// utility function for printing the 2d array
void print(int *m, int rows, int cols) {
  int i, j;

  for (i = 0; i < rows; ++i) {
    for (j = 0; j < cols; ++j) {
      printf("%d ", m[i*cols + j]);
    }
    printf("\n");
  }
  printf("\n");
}

// rotate90 -- version using O(N) temporary store
void rotate90(int *m, int N) {
  int tmp[N];
  int i, j = N/2-1, k, l;

  printf("ZOO j = %d\n",j);
  for (i = 0; i < N/2; ++i) {
    l = N - i;                 // sub-row limit
    printf("XOO l = %d\n",l);
    for (k = i; k < l; ++k) {
      tmp[k] = *(m+sizeof(*m)*i+k);
      printf("POO tmp[k] = %d\n",tmp[k]);
    }

  printf("YO\n");
  //print(tmp[0], 1, N);

  printf("YO MAN\n");
    //copy col left to row top

    //copy row bottom to col left

    //copy col right to row bottom

    //copy store to col tight
  }
}

// rot90ip -- in-place version
// TODO

// TODO set_zero_ij
//

enum {ADIM = 2, BDIM, CDIM};

int main(void) {
  int a[][ADIM] = {1,2,3,4};
  int b[][BDIM] = {1,2,3,4,5,6,7,8,9,10};
  int c[][CDIM] = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4};

  print(a[0], ADIM, ADIM);
  rotate90(a[0], ADIM);
  print(a[0], ADIM, ADIM);

  //print(b[0], BDIM, BDIM);
  //rotate90(b[0], BDIM);
  //print(b[0], BDIM, BDIM);

  //print(c[0], CDIM, CDIM);
  //rotate90(c[0], CDIM);
  //print(c[0], CDIM, CDIM);

  return EXIT_SUCCESS;
}
