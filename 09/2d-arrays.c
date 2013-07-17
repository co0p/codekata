#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// using 1d array as approx 2d array

// utility function for printing the 2d array
void print(int *m, int rows, int cols) {
  int i, j;

  for (i = 0; i < rows; ++i) {
    for (j = 0; j < cols; ++j) {
      printf("%d ", m[i*cols+j]);
    }
    printf("\n");
  }
  printf("\n");
}

// rotate90 -- version swapping elemnt by element
// moving fro moutside layers to the inside
void rotate90(int *m, int N) {
  int i, j = N/2-1, k, x, y, tmp, lim;

  for (i = 0; i < N/2; ++i) {  // starting with the outermost layer (continue for each layer until went for half of the diagonal)
      lim = N - i - 1;         // inner layers get smaller
      for (k = i; k < lim; ++k) {
          tmp = m[i*N+k];                        // tmp    = top
          m[i*N+k] = m[(lim-k-i)*N + i];         // top    = left
          m[(lim-k-i)*N + i] = m[lim*N+lim-k-i]; // left   = bottom
          m[lim*N+lim-k-i] = m[k*N+lim];         // bottom = right
          m[k*N+lim] = tmp;                      // right  = bottom
          //printf("[%d][%d]\n", i,k);
      }
  }
}



enum {ADIM = 2, BDIM, CDIM};

int main(void) {
  int a[ADIM*ADIM] = {1,2,3,4};
  int b[BDIM*BDIM] = {1,2,3,4,5,6,7,8,9};
  int c[CDIM*CDIM] = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4};

  print(a, ADIM, ADIM); // rotate four time should be the same as original
  rotate90(a, ADIM);
  print(a, ADIM, ADIM);
  rotate90(a, ADIM);
  print(a, ADIM, ADIM);
  rotate90(a, ADIM);
  print(a, ADIM, ADIM);
  rotate90(a, ADIM);
  print(a, ADIM, ADIM);

  print(b, BDIM, BDIM);
  rotate90(b, BDIM);
  print(b, BDIM, BDIM);
  rotate90(b, BDIM);
  print(b, BDIM, BDIM);
  rotate90(b, BDIM);
  print(b, BDIM, BDIM);
  rotate90(b, BDIM);
  print(b, BDIM, BDIM);

#if 0
  print(c, CDIM, CDIM); // FIXME: something messed up for more than one layer
  rotate90(c, CDIM);
  print(c, CDIM, CDIM);
  rotate90(c, CDIM);
  print(c, CDIM, CDIM);
  rotate90(c, CDIM);
  print(c, CDIM, CDIM);
  rotate90(c, CDIM);
  print(c, CDIM, CDIM);
#endif
  return EXIT_SUCCESS;
}
