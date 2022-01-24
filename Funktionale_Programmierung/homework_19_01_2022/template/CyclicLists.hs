import Data.List

-- Exercise 1
merge :: Ord a => [a] -> [a] -> [a]
merge [] [] = []
merge [] y = y
merge x [] = x
merge g1@(x:xs) g2@(y:ys)
  | x > y = y : merge g1 ys
  | x < y = x : merge g2 xs
  | x == y = x : merge xs ys
  | otherwise = error "ERROR"

sNumbers :: [Integer]
sNumbers = 1 : merge t (merge s e) where
  t = map (3*) sNumbers
  s = map (7*) sNumbers
  e = map (11*) sNumbers

sNum :: Int -> Integer
sNum i = let 
  isS 1 = True 
  isS x 
    | mod x 3 == 0 = isS (div x 3)
    | mod x 7 == 0 = isS (div x 7)
    | mod x 11 == 0 = isS (div x 11)
    | otherwise = False 
  nextNum x = if isS x then x else nextNum (x+1)
  numRec 0 x = x
  numRec n x = numRec (n-1) (nextNum (x+1))
  in numRec i 1


-- Tests

tests = do
  test "merge" "[1,18,19,150,200,300,301]" (merge [1,18,200,300,301] [19,150,200,300,301])
  test "sNumbers" "[1,3,7,9,11,21,27,33,49,63,77,81,99,121,147,189,231,243,297,343]" (take 20 sNumbers)
  test "sNum" "[1,3,7,9,11,21,27,33,49,63,77,81,99,121,147,189,231,243,297,343]" (map sNum [0..19])

test name e c = do
  putStr ("*** " ++ name ++ ": ")
  if show c == e then putStrLn "OK"
  else putStrLn ("ERROR; expected '" ++ e ++ "', but found '" ++ show c ++ "'")

