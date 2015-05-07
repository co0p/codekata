#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define true 1
#define false 0

#warning "FIXME: the output is currently incorrect"

/* 
* returns 1 if candidate is prime, 0 otherwise 
*/
int isPrime(long candidate) {
	
    if(candidate < 2) return false;
    if(candidate == 2 || candidate == 3) return true;
    if(candidate%2 == 0 || candidate%3 == 0) return false;
    
    long sqrtN = (long) sqrt(candidate)+1;
    long i;
    
    
	/*
	* PLEASE OPTIMIZE HERE 
	*/
	
    for(i = 6L; i <= sqrtN; i += 6) {
        if (candidate%(i-1) == 0 || candidate%(i+1) == 0) {
        	return false;
        }
    }
    return true;
}
	


int main(int argc, char **argv) {
	
	if (argc < 2) {
		printf("usage: %s <n> [</path/to/file>]\n", argv[0]);
		return 0;
	}

	/* find primes up to max */
	long max = atol(argv[1]);
	long *primes = (long*) malloc(sizeof(long) * max);
	
	
	/*
	* PLEASE OPTIMIZE HERE 
	*/
	
	/* go through numbers and check if it is prime */
	long index = 0;
	long i;
	#pragma omp parallel for
	for (i=3; i<max; i++) {
		if (isPrime(i) == true) {
			index++;
			primes[index] = i; 
		}
	}
	
	/* print */
	FILE *out = NULL;
	if (argc > 2) out = fopen(argv[2], "w+");
	for (i=0;i<max; i++) { 
		if (primes[i] == 0) continue; 
		else {
			 if (out == NULL) printf("%ld\n", primes[i]);
			 else fprintf(out, "%ld\n", primes[i]);
		}
	}
	if (out != NULL) fclose(out);
	free(primes);
	
	return 0;
}
