-- run in ghci

-- G: b) 
-- listAdd [3,2,1] [7,8,9,1] -> [0,1,1,2]
-- standing for 123 + 1987 = 2110

listAdd res c [] [] = res
listAdd res c [] (y:ys) = listAdd (res++[s `mod` 10]) newc [] ys 
                            where
                              s = y + c 
                              newc = if s > 10 then 1 else 0
listAdd res c (x:xs) [] = listAdd res c [] (x:xs)
listAdd res c (x:xs) (y:ys) = listAdd (res++[s `mod` 10]) newc xs ys
                            where
                              s = y + x + c 
                              newc = if s > 10 then 1 else 0


