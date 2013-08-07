-- open in ghci
-- http://www.haskell.org/haskellwiki/99_questions/1_to_10
-- (solutions available there too)

-- 1: get last element of the list
-- Prelude: last
-- list!!(length list-1)
-- head $ drop (length list-1) list

mylast :: [a] -> a
mylast []   = error "empty list"
mylast (x:xs) = if null xs then x
                else mylast xs

-- or:
-- foldr1 (const id)
--
-- foldr1 (flip const)
--
-- head . reverse
--
-- foldl1 (curry snd)


-- 2: get second to last element of a list

sndToLast :: [a] -> a
sndToLast []   = error "empty list"
sndToLast [x]   = error "only one elemnt in the list"
sndToLast (x:y:xs) = if null xs then x
                     else sndToLast (y:xs)

--or:
-- last . init
-- head . tail . reverse
-- reverse list !! 1


-- 3: find the k-th element of the list (first element's index is 1)


myElemAt :: [a] -> Integer -> a
myElemAt [] _     = error "list too short"
myElemAt (x:_) 1  = x
myElemAt (x:xs) n
  | n < 1     = error "index out of bounds"
  | otherwise = myElemAt xs (n-1)

-- or:
-- myElemAt list i = list !! (i-1) 
--
-- flip $ (last .) . take . (+ 1)  [point free]

-- 4: find the number of elements in the list
-- Prelude: length

myLen :: [a] -> Integer
myLen [] = 0
myLen (x:xs) = 1 + myLen xs

myLen' = foldl (const . (+1)) 0


-- 5: reverse a list
myRev :: [a] -> [a]
myRev [] = []
myRev (x:xs) = myRev xs ++ [x] -- naive O(n*n)

-- or:
-- foldl (flip (:)) []
--
-- reverse list = reverse' list []
--  where
--    reverse' [] reversed     = reversed                  -- using an accumulator, O(n)
--    reverse' (x:xs) reversed = reverse' xs (x:reversed)  -- avoids some intermediate data st


-- 6: function that checks if a list is a palindrome
isPalin :: Eq a => [a] -> Bool
isPalin [] = True
isPalin [_] = True
isPalin (x:xs) = (x == last xs) && (isPalin $ init xs)
             

-- or:
-- xs == reverse xs
--
-- palindrome' xs = and $ zipWith (==) xs (reverse xs)


-- 7: Flatten a nested list structure
--  We have to define a new data type, 
--  because lists in Haskell are homogeneous.

data NestedList a = Elem a | List [NestedList a]

myFlatten :: NestedList a -> [a]
myFlatten (Elem x) = [x]
myFlatten (List (x:xs)) = myFlatten x ++ myFlatten (List xs) 
myFlatten (List []) = []

-- or (from solutions page):
-- flatten3 (Elem x ) = [x]
-- flatten3 (List xs) =  foldr (++) [] $ map flatten3 xs



-- 8: Eliminate consecutive duplicates of list elements
--    If a list contains repeated elements they should be replaced 
--    with a single copy of the element. The order of the elements should not be changed.
myCompress :: Eq a => [a] -> [a]
myCompress [] = []
myCompress (x:xs) = [x] ++ myCompress' x xs

myCompress' :: Eq a => a -> [a] -> [a]
myCompress' x [] = []
myCompress' y (x:xs) = if y == x then myCompress' x xs
                       else [x] ++ myCompress' x xs
-- or:
-- compress []     = []
-- compress (x:xs) = x : (compress $ dropWhile (== x) xs)
--
-- compress xs = map head $ group xs
--
-- another idea: fromSet $ toSet xs



-- 9: Pack consecutive duplicates of list elements into sublists. 
--    If a list contains repeated elements they should be placed in separate sublists.




-- 10: Run-length encoding of a list. Use the result of problem P09 
--     to implement the so-called run-length encoding data compression method. 
--     Consecutive duplicates of elements are encoded as lists (N E) 
--     where N is the number of duplicates of the element E.



