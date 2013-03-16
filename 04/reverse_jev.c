/*
 KATA: reverse word order in a string in-place (may use a temp char)
 
 eb120@hw.ac.uk 6/10/12
 - reading string re-used from julian godesa's version
 - idea: reverse string, then reverse single words
 
 TODO: 
 - add some defensive programming 
   - Q? spec does not say whether final string needs trimming leading spaces
 
 compile:
 gcc -Wall -pedantic -DNDEBUG -O2 -o reverse_jev reverse_jev.c
 
 testing:
 gcc -O2 -o reverse_jev reverse_jev.c -DTEST && ./reverse_jev
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

/* testing */
#ifdef TEST
	#include "../minunit/minunit.h"
	static char * all_tests();
#endif

#define MAX_STRING_LENGTH 65535  /* XXX: a bit excessive */
#define EOS '\0'

#define SWAP(x,y) { char temp = *(y); *(y) = *(x); *(x) = temp; }

#define REVERSE_STRING(s,begin,end) do { int a = begin, b = end; \
                                        assert(("REVERSE_STRING: begin must be smaller than end.\n", a <= b)); \
	                                    while (a <= b) {	 	 \
	                                        SWAP(s+a, s+b);	     \
	                                        ++a;				 \
	                                        --b;				 \
	                                }							 \
	                              } while(0)					 \
	                                
/* takes a pointer to the string in which word order is reversed in-place 
   ~O(3N) - get length, reverse string, reverse each word
 */
void reverse_in_place(char *str) {
	int i = 0, j = strlen(str)-1, x, y; /** str[strlen] == '\0' */
	
	REVERSE_STRING(str,i,j);

    i = j = 0;                 /** i point to the beginning of a word */
   
    while (true) { 
        while (!isalnum(*(str+i))) { /** trim whitespaces */
	        ++i;
	    }
	    
		j = i;
        while (isalnum(*(str+j))) { /** move j to the end of the word */
	        ++j;
	    }
	    --j;                        /** point to the last letter */
	    
	    x = i;
	    y = j;
	    REVERSE_STRING(str,x,y);
	    
        i = j + 1;
        if (str[i] == EOS) {
		    return;           /* done */
		}
        
        while (!isalnum(str[i])) { /** skip to the beginning of the next word */
		    ++i;
		}
		j = i;   
    }
}

int main(int argc, char *argv[]) {
	
	
#ifdef TEST
	char *result = all_tests();
	if (result != 0) printf("%s\n", result); 
	else printf("ALL TESTS PASSED\n");
	return result != 0;
#endif	
	
    char str[MAX_STRING_LENGTH];
	int i;
	
	if (argc < 3) {
		printf("usage: ./reverse_jev <string of words>\n");
		return 0;
	}
	
	/* convert arguments to a single string */
	for (i = 1; i < argc; i++) {
		strcat(str, *(argv+i));
		strcat(str, " ");
	}
    str[strlen(str)-1] = EOS;
    
	printf("given:'%s'\n", str);

	reverse_in_place(str);
	
	printf("reversed:'%s'\n", str);
	
    return EXIT_SUCCESS;
}



/*------------------------------------------------------------------------------
tests for jevs solution
------------------------------------------------------------------------------*/
#ifdef TEST
	static char * test_flip() {
		char str[] = "abc";
		
		/* flip in place */
		SWAP(&str[0], &str[0]);
		mu_assert("error, flip inplace", str[0] == 'a');
		mu_assert("error, flip inplace", str[1] == 'b');
		mu_assert("error, flip inplace", str[2] == 'c');
		
		/* flip two chars */
		SWAP(&str[0], &str[1]);
		mu_assert("error, flip", str[0] == 'b');
		mu_assert("error, flip", str[1] == 'a');
		mu_assert("error, flip", str[2] == 'c');
		
		return 0;
	}
	
	static char * test_reverse() {
		char str1[] = "";
		REVERSE_STRING(str1, 0, 0);
		mu_assert("error, reverse empty word", strcmp(str1, "") == 0);
		
		char str2[] = "a";
		REVERSE_STRING(str2, 0, 0);
		mu_assert("error, reverse word single char", strcmp(str2, "a") == 0);
		
		char str3[] = "abc";
		REVERSE_STRING(str3, 0, 2);
		mu_assert("error, reverse word", strcmp(str3, "cba") == 0);
		
		char str4[] = "abc def";
		REVERSE_STRING(str4, 0, 6);
		mu_assert("error, reverse two words", strcmp(str4, "fed cba") == 0);
		
		char str5[] = "abcd";
		REVERSE_STRING(str5, 0, 2);
		mu_assert("error, reverse beginning", strcmp(str5, "cbad") == 0);
		
		char str6[] = "abcd";
		REVERSE_STRING(str6, 1, 2);
		mu_assert("error, reverse middle", strcmp(str6, "acbd") == 0);
	
		char str7[] = "abcd";
		REVERSE_STRING(str7, 2, 3);
		mu_assert("error, reverse end", strcmp(str7, "abdc") == 0);
		
		return 0;
	}
	
	
	static char * all_tests() {
		mu_run_test(test_flip);
		mu_run_test(test_reverse);
		return 0;
	}


#endif
