# settings #####################################################################

CC = gcc
CFLAGS = -Wall -O2 -fopenmp
LDFLAGS =

GHC=ghc
GHCFLAGS= -O2 --make

# major targets ################################################################

all: sieve sieve_taskpar test_primes sieve_isprime sieve_hs

clean:
	rm -f sieve
	rm -f sieve_taskpar
	rm -f test_primes
	rm -f sieve_isprime
	rm -f sieve_hs
	rm -f *.o
	rm -f test

clobber: clean


# minor targets ################################################################

sieve_taskpar: sieve_taskpar.c
	$(CC) $(CFLAGS) sieve_taskpar.c -o sieve_taskpar -lm

test_primes: test_primes.c
	$(CC) $(CFLAGS) test_primes.c -o test -lm
	
sieve: sieve.c 
	$(CC) $(CFLAGS) sieve.c -o sieve $(LDFLAGS)
	
sieve_isprime: sieve_isprime.c 
	$(CC) $(CFLAGS) sieve_isprime.c -o sieve_isprime $(LDFLAGS) -lm

sieve_hs: sieve.hs
	$(GHC) $(GHCFLAGS) -o sieve_hs sieve.hs

