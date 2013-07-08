-- input:  String
-- output: True  if all chars are unique (case-insensitive)
--         False otherwise 

-- test in ghci: $ghci unique.hs
-- unique <String>

import Data.Char

unique :: [Char] -> Bool
unique []  = error "String should be non-empty"
unique [x] = True
unique xs  = length xs == length ys
  where 
    ys = [x | x<-xs, y<-xs, toLower x == toLower y]


