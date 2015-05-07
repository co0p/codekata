--
-- KATA 02: FizzBuzz
--
-- compile: ghc -O2 --make fizzbuzz.hs
--     run: ./fizzbuzz <n> with n > 0
 
import System.Environment(getArgs)

fizzbuzz :: Int -> String
fizzbuzz x | x `mod` 3 == 0 = "fizz"
           | x `mod` 5 == 0 = "buzz"
           | (x `mod` 3 == 0) && (x `mod` 5 == 0) = "fizzbuzz"
           | otherwise = show x
           
main = do 
         args <- getArgs
          -- TODO: add check:if null args 
          --   then return error "usage: ./fizzbuzz <n>" 
          --   else do
         let
           n   = read (args!!0) :: Int   -- parse an integer
           fbs = map fizzbuzz [1..n-1]
         putStr $ unlines fbs 
