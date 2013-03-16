/*
name: fizzbuzz.c
author: julian godesa

compile: cc fizzbuzz_julian.c -o fizzbuzz_julian
*/


#include <stdio.h>

void fizzbuzz(int n) {
	if ((n%5 == 0) && (n%3 == 0)) {
		printf("fizzbuzz\n");
	} else if (n%5 == 0) {
		printf("buzz\n");
	} else if (n%3 == 0) {
		printf("fizz\n");
	} else {
		printf("%d\n", n);
	}
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("usage: ./fizzbuzz_julian <n>\n");
		return 0;
	}
	
	int n = atoi(argv[1]);
	int i;
	for (i=1; i<n;i++) {
		fizzbuzz(i);
	}
	
	return 0;	
}
	
	
	
