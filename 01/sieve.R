# run like this: R -f unique.R --args 100

sieve <- function(n) {
   n <- as.integer(n)
   # initialize primes array with true (except for primes[1])
   primes <- rep(TRUE, n)
   primes[1] <- FALSE
   # initalize last prime to first prime, 2
   last.prime <- 2L

   # loop till sqrt(n), since we will mark the multiples of last.prime
   for(i in last.prime:floor(sqrt(n))) {
      # mark all multiples of the current prime as not primes
      primes[seq.int(2L*last.prime, n, last.prime)] <- FALSE
      # reassign last prime to first value from primes vector that is TRUE
      last.prime <- last.prime + min(which(primes[(last.prime+1):n]))
   }
   # return only indices where values are TRUE
   which(primes)
}
 
time <- system.time(res <- sieve(commandArgs(trailingOnly = TRUE)))
cat(paste0("Found ",length(res)," primes in ",time[[3]],"s.\n"))
