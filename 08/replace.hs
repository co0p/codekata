-- test in ghci
-- works on lists (rather than null-reminated strings here)
-- alternatively could use FFI to call C or use mutable Array of Chars

-- is list of chars to replace
-- s is Char to search for
-- assumes the string is trimmed from trailing spaces
replace20 :: [Char] -> [Char] -> Char -> [Char]
replace20 [] _ _ = []
replace20 (x:xs) r s = transform x ++ replace20 xs r s
  where transform x = if (x == s) then r else [x] 