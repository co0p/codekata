/*
   name: fizzbuzz_jev.c
 author: jev.belikov@gmail.com
   date: 06/10/12
   
compile: gcc -Wall -pedantic -O2 -std=c99 -o fizzbuzz_jev fizzbuzz_jev.c
    run: ./fizbuzz_jev <uppder bound>

 This is the infamous 'FizzBuzz' Kata.
 Check out README for details.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* static void fizzbuzz(int n) */
#define FIZZBUZZ(n) {                                              \
    int print_as_num = 1; /* if non-zero print as string */        \
                                                                   \
    if ((n)%3 == 0) {                                              \
        (void) printf("fizz");                                     \
        print_as_num = false;                                      \
    }                                                              \
                                                                   \
    if ((n)%5 == 0) {                                              \
		(void) printf("buzz");                                     \
		print_as_num = false;                                      \
    }                                                              \
                                                                   \
    if (true == print_as_num) {                                    \
	    printf("%d", (n));                                         \
	}	                                                           \
	                                                               \
    printf("\n");                                                  \
}                                                                  \


int main(int argc, char **argv) {
	int i,n;
	
	if (argc < 2) {
		fprintf(stderr, "usage: ./fizzbuzz_jev <upper_bound>\n");
		return EXIT_FAILURE;
	}
	
	n = atoi(argv[1]);
	
	for (i = 1; i < n; ++i) {
		FIZZBUZZ(i);
	}
	
	return EXIT_SUCCESS;	
}
