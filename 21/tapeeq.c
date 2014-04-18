// codility.com LESSON 1 -- Time Complexity
//                TASK 1 -- TapeEquilibrium
//
// find minimal absolute difference of sums of two partitions of a given array of elements
// given a P, find min |(A[0] + ... + A[P-1]) - (A[P] + ... + A[N-1])|
// with elements from range [-1000..1000], and N from [2..100000]
// (expected O(N) solution for both time and space)
//

#include <limits.h> // for LONG_MAX
#include <stdlib.h> // for labs()

#define MAX_N 100000  // N is in range [2..100000]

// O(2*N) runtime , O(N) space
int solution(int A[], int N) {
    long B[MAX_N]; // store cumul sum
    long min_diff = LONG_MAX;
    long diff;
    int i;
    
    B[0] = A[0]; 
    for (i = 1; i < N; ++i) {
        B[i] = B[i-1] + A[i];  // intermediate sum
    }

    for (i = 0; i < N-1; ++i) {
        diff = labs(B[i] - (B[N-1] - B[i]));
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    return min_diff;
}

// O(N*N) algo for comparison
int solution2(int A[], int N) {
    int p, j;
    long min_diff_prev = LONG_MAX;
    long min_diff_idx = 0;
    long sum1, sum2;
    
    for (p = 1; p < N; ++p) {
        sum1 = 0, sum2 = 0;
        //printf("mindiff %ld, ", min_diff_prev);
        for (j = 0; j < p; ++j) {  // first half
            sum1 += A[j];
        }
        for (j = p; j < N; ++j) {  // second half
            sum2 += A[j];
        }
        //printf("curdiff %ld, ", labs(sum1-sum2));
        if (labs(sum1-sum2) < min_diff_prev) {
            min_diff_prev = labs(sum1-sum2);
            min_diff_idx = p;
        }
        //printf("idx %ld\n", min_diff_idx);
    }
    
    return min_diff_prev;
}
