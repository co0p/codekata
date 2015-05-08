/* 
   KATA02: FizzBuzz  (check out README for details)

   filename: fb_no_ifs.c     -- uses no conditionals / branches
     author: eb120@hw.ac.uk
       date: 08/05/2015
   
    compile: gcc -Wall -pedantic -O2 -std=c99 -o fb_no_ifs fb_no_ifs.c
        run: ./fb_no_ifs <upper bound> 
*/

#include <stdio.h>
#include <stdlib.h>

#define CURR_SZ      32
#define FB_CYCLE_LEN 15

static char *fizzbuzz[FB_CYCLE_LEN]; /* indirections to strings */
static char *f  = "fizz";
static char *b  = "buzz";  
static char *fb = "fizzbuzz";
static char  current[CURR_SZ];  /* current string representation */ 
// TODO add const

void fb_init() {
  fizzbuzz[0]  = fizzbuzz[1]  = fizzbuzz[3]  = fizzbuzz[6]  = 
  fizzbuzz[7]  = fizzbuzz[10] = fizzbuzz[12] = fizzbuzz[13] = current; 	
  fizzbuzz[2]  = fizzbuzz[5]  = fizzbuzz[8]  = fizzbuzz[11] = f; 
  fizzbuzz[4]  = fizzbuzz[9]  = b;
  fizzbuzz[14] = fb;
}


int main(int argc, char **argv) {
	int i,n;
	
	if (argc < 2) {
		fprintf(stderr, "usage: ./fb_no_ifs <upper_bound>\n");
		return EXIT_FAILURE;
	}
	
	n = atoi(argv[1]);

    fb_init();
    	
	for (i = 1; i < n; ++i) {
		snprintf(current, CURR_SZ, "%d", i); /* store string representation in current */ 
		printf("%s\n", fizzbuzz[(i-1)%FB_CYCLE_LEN]);
	}
	
	return EXIT_SUCCESS;	
}
