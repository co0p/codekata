-- open in ghci
-- http://www.haskell.org/haskellwiki/99_questions/
-- (solutions available there too)

import Data.List

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
--    (cf group from Data.List)
myPack :: Eq a => [a] -> [[a]]
myPack [] = []
myPack xs = (takeWhile (== x) xs) : (myPack $ dropWhile (==x) xs)
            where x = head xs

-- alternative: use an accumulator
-- or (Import List for group):
-- encode xs = map (\x -> (length x,head x)) (group xs)
-- 
-- [(length x, head x) | x <- group xs]
--
-- encode xs = (enc . pack) xs
--	where enc = foldr (\x acc -> (length x, head x) : acc) []


-- 10: Run-length encoding of a list. Use the result of problem P09 
--     to implement the so-called run-length encoding data compression method. 
--     Consecutive duplicates of elements are encoded as a list of tuples (N,E) 
--     where N is the number of duplicates of the element E.
myRunLenEnc :: Eq a => [a] -> [(Int,a)]
myRunLenEnc xs = zip (map length pxs) (map head pxs)
                 where pxs = myPack xs
-- or:
-- pack (x:xs) = let (first,rest) = span (==x) xs
--               in (x:first) : pack rest
-- pack []     = []


-- 11-10 section:

-- Modify the result of problem 10 in such a way that if an element has no duplicates 
-- it is simply copied into the result list. Only elements with duplicates are transferred as (N E) lists.
data Multiple a = Multiple Int a
                | Single a
  deriving Show

myRunLenEnc' :: Eq a => [a] -> [Multiple a]
myRunLenEnc' xs = mOs $ zip (map length pxs) (map head pxs)
                  where pxs = myPack xs
                        mOs :: Eq a => [(Int,a)] -> [Multiple a]
                        mOs [] =  []
                        mOs xs = map (\x -> if fst x > 1 then Multiple (fst x) (snd x) else Single (snd x)) xs

-- alternatively re-use 10:
-- map helper . sol10
-- where helper (1,x) = Single x
--       helper (n,x) = Multiple n x


-- Given a run-length code list generated as specified in problem 11. Construct its uncompressed version
myRunLenDec' :: [Multiple a] -> [a]
myRunLenDec' [] = []
myRunLenDec' xs = concat (map fromMult xs)   -- or: concatMap fromMult
  where
    fromMult x =
      case x of
        (Single a)     -> [a]
        (Multiple n a) -> replicate n a


fromMultiple :: Multiple a -> (Int,a)
fromMultiple (Single x)     = (1,x)
fromMultiple (Multiple n x) = (n,x)

toMultiple :: Int -> a -> Multiple a 
toMultiple n x
  | n > 1  = Multiple n x
  | n == 1 = Single x
  | otherwise = error "n should be > 0 in toMultiple()"


-- 13: enc direct, don't create lists with multiples
myEncDirect :: Eq a => [a] -> [Multiple a]
myEncDirect xs = med xs []
  where med [] acc = reverse acc
        med (x:xs) [] = med xs [(Single x)]
        med (x:xs) (a:as) 
          | x == a'   = med xs ((toMultiple (n'+1) a') : as)
          | otherwise = med xs ((Single x) : a : as)
            where (n',a') = fromMultiple a
                      
-- 14: duplicate all elements of a list
duplicate :: [a] -> [a]
duplicate xs = dup 2 xs
  where dup n xs = concatMap (replicate n) (xs)

-- or: d = x:x:d xs



