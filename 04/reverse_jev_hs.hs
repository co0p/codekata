-- KATA04 - reverse the word order in a string
-- Haskell (sequential version)

-- compile: ghc -O2 --make reverse_jev_hs.hs
--     run: ./reverse_jev_hs <sentence>

import System.Environment(getArgs)
import Data.List

stringListToString :: [[Char]] -> [Char] -> [Char]
stringListToString [] _ = []
stringListToString (x:xs) separator | null xs   = x
                                    | otherwise = x ++ separator ++ stringListToString xs separator

main = do  
         args <- getArgs      
         if null args
           then error "usage: ./reverse_jev_hs <sentence>"
           else do
                  let 
                    --separator = " "
                    --result = stringListToString (reverse args) separator
                    result = concat $ intersperse " " $ reverse args
                  print result
