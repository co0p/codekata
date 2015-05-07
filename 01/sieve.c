/* KATA01 - sieve of eratosthenes 
*
* compile: gcc -Wall -fopenmp -o sieve sieve.c
* 
* check out sieve_taskpar for a faster version
**/

#include <stdio.h>
#include <stdlib.h>

#include <omp.h>

#define MARKED 0



int main(int argc, char **argv) {
	int n, i, j, prime;
	int *primes;
	double elapsed = 0.0;
    
	/* get n */
	if (argc < 2) {
		printf("usage: %s <n> [<outfile>]\n", argv[0]);
		return 0;
	}
	n = atoi(argv[1]);
	primes = (int*)malloc(sizeof(int) * n);
	
	elapsed = omp_get_wtime();
    
	/* fill */
	#pragma omp parallel for
	for (i=0; i<n; i++) primes[i] = i+2;
	
	/* sieve */
	for (i=0; i<n; i++) {
		if (primes[i] == MARKED) continue; 
		else prime = primes[i];
		
		#pragma omp parallel for
		for (j=i+1; j<n; j++) {
			if (primes[j] % prime == 0) {
				primes[j] = MARKED;
			}
		}
	}
	
	elapsed = omp_get_wtime() - elapsed;
    
	fprintf(stderr, "Found primes in range [0 .. %d] in %lf seconds.\n",  n, elapsed);
           
	/* write primes */
	FILE *out = NULL;
	if (argc > 2) out = fopen(argv[2], "w+");
	
	for (i=0;i<n; i++) { 
		if (primes[i] == 0) continue; 
		else {
			 if (out == NULL) printf("%d\n", primes[i]);
			 else fprintf(out, "%d\n", primes[i]);
		}
	}
	if (out != NULL) fclose(out);
	
	free(primes);
	return 0;	
}
