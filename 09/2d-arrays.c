#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

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
  int i, k, x, y, tmp, lim, offset;

  for (i = 0; i < N/2; ++i) {  // starting with the outermost layer (continue for each layer until went for half of the diagonal)
      lim = N - i - 1;         // inner layers get smaller
      for (k = i; k < lim; ++k) {
          offset = k - i;
          tmp = m[i*N+k];                                // tmp    = top
          m[i*N+k] = m[(lim-offset)*N + i];              // top    = left
          m[(lim-offset)*N + i] = m[lim*N+lim-offset];   // left   = bottom
          m[lim*N+lim-offset] = m[k*N+lim];              // bottom = right
          m[k*N+lim] = tmp;                              // right  = bottom
          //printf("[%d][%d]\n", i,k);
      }
  }
}


// function that sets row i and col j if Mij = 0
// update happens in-place
// TODO: use a bit vector instead of the bool array
void set_zero_rc(int *m, int rows, int cols) {
   //bool row_markers[rows];  // would work with C99
   bool *row_markers, *col_markers;
   int i, j;

   if ((row_markers = malloc(rows*sizeof(*row_markers))) == NULL) {
     fprintf(stderr, "FATAL ERROR: out of memory in set_zero_rc()\n");
     exit(EXIT_FAILURE);
   }

    if ((col_markers = malloc(cols*sizeof(*col_markers))) == NULL) {
     fprintf(stderr, "FATAL ERROR: out of memory in set_zero_rc()\n");
     free(row_markers);
     exit(EXIT_FAILURE);
   }

   memset(row_markers, false, rows);
   memset(col_markers, false, cols);

   for (i = 0; i < rows; ++i) {
     for (j = 0; j < cols; ++j) {
       if (m[i*rows+j] == 0) {
         row_markers[i] = true;    // remember which rows and cols to zero out
         col_markers[j] = true;
       }
     }
   }

   for (i = 0; i < rows; ++i) {
     for (j = 0; j < cols; ++j) {
       if (row_markers[i] == true || col_markers[j] == true) {
         m[i*rows+j] = 0;
       }
     }
   }

   free(row_markers);
   free(col_markers);
}



enum {ADIM = 2, BDIM, CDIM, DDIM};

int main(void) {
  int a[ADIM*ADIM] = {1,2,3,4};
  int b[BDIM*BDIM] = {1,2,3,4,5,6,7,8,9};
  int c[CDIM*CDIM] = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4};
  int d[DDIM*DDIM] = {1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5};
  int z[DDIM*DDIM] = {1,1,1,1,1,2,0,2,2,2,3,3,3,3,3,4,4,4,0,4,5,5,5,5,5};

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

  print(c, CDIM, CDIM);
  rotate90(c, CDIM);
  print(c, CDIM, CDIM);
  rotate90(c, CDIM);
  print(c, CDIM, CDIM);
  rotate90(c, CDIM);
  print(c, CDIM, CDIM);
  rotate90(c, CDIM);
  print(c, CDIM, CDIM);

  print(d, DDIM, DDIM);
  rotate90(d, DDIM);
  print(d, DDIM, DDIM);
  rotate90(d, DDIM);
  print(d, DDIM, DDIM);
  rotate90(d, DDIM);
  print(d, DDIM, DDIM);
  rotate90(d, DDIM);
  print(d, DDIM, DDIM);

  print(z, DDIM, DDIM);
  set_zero_rc(z, DDIM, DDIM);
  print(z, DDIM, DDIM);

  return EXIT_SUCCESS;
}
