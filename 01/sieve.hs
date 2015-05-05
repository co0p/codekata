-- KATA01 - sieve of eratosthenes 
-- Haskell (sequential version)

-- adapted from G. Hutton - Programmin in Haskell p. 134
-- prints prime numbers smaller than the specified number n

-- compile: ghc -O2 --make sieve.hs
--     run: ./sieve <n>
 
import System.Environment(getArgs)

-- the way lazyness is used make this version sequential,
-- which requires a from scratch re-write to parallelise it
-- but it illustrated the use of infinite data-structures and
-- list comprehension syntax

primes :: [Int]
primes = sieve [2..]

sieve :: [Int] -> [Int]
sieve (p:xs) = p : sieve [x | x <- xs, x `mod` p /= 0]

main = do  
           args <- getArgs
           let
             n = read (args!!0) :: Int   -- parse an integer
             p = takeWhile (< n) primes
           print p 
