module Main where

-- A game of Mastermind (http://en.wikipedia.org/wiki/Mastermind_%28board_game%29) 6x4
-- (part of the exercise B at the 2013 Summer School on Applied Functional Programming)

-- run in ghci or compile with: ghc --make -O2 MasterMind.hs
-- TODO: implement computer playing against itself and printing the protocol version

import System.Random  -- for randoms
import System.IO      -- for hFlush
import Data.List      -- for list subtract (\\)
import Data.Char      -- for isSpace

type Row      = [Int]
type Guess    = Row
type Solution = Row

colors = 6
width  = 4


main :: IO()
main =
  do s <- generateSolution 
     loop s 0
  
  
-- generates random solution for given number of colors and width
generateSolution :: IO [Int]
generateSolution =
  do g <- getStdGen
     let rs = take width (randoms g)
     return (map ((+1) . (`mod` colors)) rs)
    

-- loop: a single interaction: reads input and either loops or stops
loop :: Solution -> Int -> IO ()
loop s rounds =
  do g <- input
     case g of
       Nothing -> do 
         putStrLn $ "See you. The secret was " ++ show s ++ ".\n"
         return ()
       Just g' -> 
         do let (b,w,c) = check s g'
            putStr $ report $ (b,w,c)
            if c 
            then do putStrLn $ " You won after " ++ show (rounds+1) ++ " guesses.\n"
                    return ()
            else loop s (rounds + 1)
      
-- number of matching elements of the solution
black :: Solution -> Guess -> Int
black solution guess = length $ filter id $ zipWith (==) solution guess  

-- number of right coloors but in wroing position
white :: Solution -> Guess -> Int                       
white solution guess = length l1 - length (l1 \\ l2) where 
  (l1,l2) = unzip $ filter (\x -> fst x /= snd x) $ zip solution guess 


check :: Solution -> Guess -> (Int, Int, Bool)  -- (black points, white points, all-correct?)   
check solution guess = (numBlack, numWhite, numBlack == width) 
  where numBlack = black solution guess
        numWhite = white solution guess
        
        
-- report: produces the string to be displayed to the player
report :: (Int, Int, Bool) -> String
report (black, white, correct) = str
    where str = (show black ++ " black, " ++ show white ++ " white\n") ++ congrats
          congrats = if correct == True then "\nCongratulations!" else ""


-- read a guess (a line and parse it), assumes a white-space separated 
-- list of numbers within the range [1..colors]
input :: IO (Maybe Guess)
input =
  do putStr "? "
     hFlush stdout                            -- force prompt is printed
     l <- getLine
     let l' = dropWhile isSpace l
     if (not $ null l') && (head l' == 'q') 
     then return Nothing                   -- indicates abort by user 
     else do let g = map readInt (words l)
             case valid g of 
               True ->  return (Just g)
               False -> do putStrLn $ "Please try again. Input should contain " 
                                      ++ show width 
                                      ++ " space-separated integers from the interval [1.." 
                                      ++ show colors ++"].\nType 'q' to quit.\n"
                           input
                       
                           
-- parses an Int from a string or returns -1
readInt :: String -> Int
readInt x = 
  case reads x of
    [(n, "")] -> n
    _         -> -1


-- returns True is a guess is valid, otherwise False
--  1. a guess should contain 'width' values
--  2. a guess' values should be of a valid color from [1..colors]
valid :: Guess -> Bool
valid guess = lg == width && lg == (length $ filter id $ map (\x -> x `elem` [1..colors]) guess)
  where lg = length guess
