/*
name: reverse_julian.c
author: julian godesa

description:
reverse the words in a given string. For example
"kate has cat" becomes "cat has kate".

challenge:
Use only one char as a temp storage place.

compile: cc reverse_julian.c -o reverse_julian
test: cc reverse_julian.c -o reverse_julian -DTEST
*/

/* testing */
#include "../minunit/minunit.h"
static char * all_tests();

/* main program */
#include <string.h>
#include <stdio.h>

#define MAX_STRING_LENGTH 65535

void flip(char*, int, int);
void reverse(char*, int, int);
void wordReverse(char*, int, int);



/*------------------------------------------------------------------------------
main
------------------------------------------------------------------------------*/

/* reverse the arguments 'word-by-word' */
int main(int argc, char **argv) {
	
#ifdef TEST
	char *result = all_tests();
	if (result != 0) printf("%s\n", result); 
	else printf("ALL TESTS PASSED\n");
	return result != 0;
#endif
	
	if (argc < 3) {
		printf("usage: ./reverse_julian <string of words>\n");
		return 0;
	}
	
	/* convert arguments to a single string */
	char str[MAX_STRING_LENGTH];
	int i;
	for (i=1; i<argc; i++) {
		strcat(str, *(argv+i));
		if (i < argc-1) strcat(str, " ");
	}
	
	/* reverse the words */
	wordReverse(str, 0, strlen(str)-1);
	printf("%s\n", str);
	
	return 0;
}



/*------------------------------------------------------------------------------
functions
------------------------------------------------------------------------------*/

/* flips chars src with dest */
void flip(char *str, int src, int dest) {
	// printf("flip: %d <-> %d\n", src, dest);
	
	char tmp = str[dest];
	str[dest] = str[src];
	str[src] = tmp; 
}

/* reverses the chars in string */
void reverse(char *str, int begin, int end) {
	//printf("reverse: %d ... %d\n", begin, end);
	if (end < begin) return;
	
	int middle = (begin + end) / 2;
	int i,j;
	for (i=begin, j=0; i<middle+1; i++, j++) {
		flip(str, i, end-j);
	}
}

/* reverses the words */ 
void wordReverse(char *str, int begin, int end) {
	
	/* 1. reverse complete string without '\0' */
	reverse(str, 0, strlen(str)-1);
	
	/* 2. reverse each word seperated by ws */
	int wBegin = 0;
	int i;
	for (i=0; i<strlen(str)+1; i++) { // count '\0' as well
		if (str[i] == ' ' || str[i] == '\0') {
			reverse(str, wBegin, i-1); // ommit space
			wBegin = i+1;
		}
	}
}


/*------------------------------------------------------------------------------
tests
------------------------------------------------------------------------------*/
static char * test_flip() {
	char str[] = "abc";
	
	/* flip in place */
	flip(str, 0, 0);
	mu_assert("error, flip inplace", str[0] == 'a');
	mu_assert("error, flip inplace", str[1] == 'b');
	mu_assert("error, flip inplace", str[2] == 'c');
	
	/* flip two chars */
	flip(str, 0, 1);
	mu_assert("error, flip", str[0] == 'b');
	mu_assert("error, flip", str[1] == 'a');
	mu_assert("error, flip", str[2] == 'c');
	
	return 0;
}

#include <string.h>
static char * test_reverse() {
	char str1[] = "";
	reverse(str1, 0, strlen(str1)-1);
	mu_assert("error, reverse empty word", strcmp(str1, "") == 0);
	
	char str2[] = "a";
	reverse(str2, 0, strlen(str2)-1);
	mu_assert("error, reverse word single char", strcmp(str2, "a") == 0);
	
	char str3[] = "abc";
	reverse(str3, 0, strlen(str3)-1);
	mu_assert("error, reverse word", strcmp(str3, "cba") == 0);
	
	char str4[] = "abc def";
	reverse(str4, 0, strlen(str4)-1);
	mu_assert("error, reverse two words", strcmp(str4, "fed cba") == 0);
	
	char str5[] = "abcd";
	reverse(str5, 0, 2);
	mu_assert("error, reverse beginning", strcmp(str5, "cbad") == 0);
	
	char str6[] = "abcd";
	reverse(str6, 1, 2);
	mu_assert("error, reverse middle", strcmp(str6, "acbd") == 0);

	char str7[] = "abcd";
	reverse(str7, 2, strlen(str7)-1);
	mu_assert("error, reverse end", strcmp(str7, "abdc") == 0);
	
	return 0;
}


static char * all_tests() {
	mu_run_test(test_flip);
	mu_run_test(test_reverse);
	return 0;
}
