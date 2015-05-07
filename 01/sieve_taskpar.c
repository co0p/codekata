/* KATA01 - sieve of eratosthenes 
*
* compile: gcc -Wall -O2 -fopenmp -lm -o sieve_taskpar sieve_taskpar.c
**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>        /* link with -lm for sqrt() */
#include <time.h>

#include <omp.h>

#define NON_PRIME 0
#define PRIME     1


int main(int argc, char **argv) {
	long n, i, j, sqrLen, cnt = 0;
	int nthreads;
	char *primes;
	//clock_t cl;
	double elapsed = 0.0;
	FILE *out = NULL;
	
	if (argc < 2) {
		printf("usage: %s <n> [<num threads>] [<out-file>]\n", argv[0]);
		return EXIT_FAILURE;
	}
	n = atol(argv[1]); /* get n */
	
	if (argc >= 3) {
	    nthreads = atoi(argv[2]);
	    if (nthreads)
	        omp_set_num_threads(nthreads);
	}
	else {
		#pragma omp parallel
		{
	        nthreads = omp_get_num_threads(); 
	    }
	}
	
	
	if (argc >= 4) {
	    if ((out = fopen(argv[3], "w+")) == NULL) { /* write primes */
            fprintf(stderr, "ERROR:can't open %s for writing\n", argv[2]);
            exit(EXIT_FAILURE);
        }
	}

	if ((primes = (char *) malloc(sizeof(char) * n)) == NULL) {
	    fprintf(stderr, "ERROR: not enough memory (for primes array)\n");
	    exit(EXIT_FAILURE);
	}
		
	primes[0] = primes[1] = NON_PRIME;            /* fill */
	primes[2] = PRIME;
	#pragma omp parallel for
	for (i = 3; i < n; ++i) 
	    primes[i] = (i % 2 == 0) ? NON_PRIME : PRIME;
	    
	sqrLen = (long) sqrt((double) n);   
	//cl = clock();
	elapsed = omp_get_wtime();

	#pragma omp parallel for private(i,j) schedule(dynamic)
	for (i = 3; i <= sqrLen; i+=2) {             /* sieve */
        if (primes[i] == PRIME) {
	        for (j = i*i; j <= n; j += i) {
	            primes[j] = NON_PRIME;
	        }
	    }
	}

	//elapsed = (clock() - cl) / (double) CLOCKS_PER_SEC;
	elapsed = omp_get_wtime() - elapsed;
	  	
	#pragma omp parallel for private(i) shared(cnt)
	for (i = 2; i < n; i++) { 
		if (primes[i] == PRIME) {
			//printf("%ld\n", i);
			if (out != NULL)
			    fprintf(out, "%ld\n", i);
			#pragma omp atomic   
			++cnt; /* how many primes found ? */
		}
	}
	
	printf("Found %ld primes in range [0 .. %ld] in %lf seconds using %d thread%s.\n", 
	       cnt, n, elapsed, nthreads, (nthreads == 1) ? "" : "s");
	
	if (out) 
	    fclose(out);	
	free(primes);
	
	return EXIT_SUCCESS;	
}
