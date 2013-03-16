-- KATA04 - reverse the word order in a string
-- Haskell (sequential version)

-- compile: ghc -O2 --make reverse_jev_hs.hs
--     run: ./reverse_jeve_hs <sentence>

-- TODO: add argument check for a nice usage message
 
import System(getArgs)

stringListToString :: [[Char]] -> [Char] -> [Char]
stringListToString [] _ = []
stringListToString (x:xs) separator | null xs   = x
                                    | otherwise = x ++ separator ++ stringListToString xs separator

main = do  
           args <- getArgs      
           let separator = " "
               result = stringListToString (reverse args) separator
           print result
