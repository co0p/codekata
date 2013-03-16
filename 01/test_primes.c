#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CHARS 256

#define true 1
#define false 0

/* 
* returns 1 if candidate is prime, 0 otherwise 
*/
int isPrime(long candidate) {
	
    if(candidate < 2) return false;
    if(candidate == 2 || candidate == 3) return true;
    if(candidate%2 == 0 || candidate%3 == 0) return false;
    
    long sqrtN = (long) sqrt(candidate)+1;
    long i;
    for(i = 6L; i <= sqrtN; i += 6) {
        if (candidate%(i-1) == 0 || candidate%(i+1) == 0) {
        	printf("candidate: '%ld' is divisible by '%ld' or '%ld'\n", candidate, i-1,i+1);
        	return false;
        }
    }
    return true;
}
	


int main(int argc, char **argv) {
	
	if (argc < 2) {
		printf("usage: %s </path/to/file>\n", argv[0]);
		return 0;
	}

	/* open file */
	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("couldn't open file for reading\n, abort.");
		return 0;
	}
	
	/* check line by line */
	int nonPrimeFound = false;
	char line[MAX_CHARS];
	long candidate;
	while (fgets(line, sizeof line, fp) != NULL) {
		candidate = atol(line);
		if (isPrime(candidate) == false) {
			nonPrimeFound = true;
			break;
		}
	}
	
	/* tell user about findings */
	if (nonPrimeFound == false) {
		printf("all good.\n");
	}
	
	return 0;
}
