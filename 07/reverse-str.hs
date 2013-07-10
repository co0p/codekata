-- reverse a string (could just use the library function)
-- test in ghci
-- space: create a new string and some intermediate structures
-- time: O(n*n) ?

reverseString :: [Char] -> [Char]
reverseString []     = []
reverseString (x:xs) = reverseString xs ++ [x]


reverseGen1 = foldr (\a b -> b ++ [a]) [] 

reverseGen2 = foldl (flip (:)) []
