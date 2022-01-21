import Data.List

-- Exercise 1
merge :: Ord a => [a] -> [a] -> [a]
merge x y = sort (combine x y)

combine :: Ord a => [a] -> [a] -> [a]
combine x y
  | null x && not (null y) = y
  | null y && not (null x) = x
  | null x && null y = []
  | elem (head x) (tail x) || elem (head x) (tail y) = combine (tail x) y
  | elem (head y) (tail x) || elem (head y) (tail y) = combine x (tail y)
  | head x == head y = head x : combine (tail x) (tail y)
  | otherwise = head x : head y : combine (tail x) (tail y)

sNumbers :: [Integer]
sNumbers = undefined

sNum :: Int -> Integer
sNum = undefined


-- Tests

tests = do
  test "merge" "[1,18,19,150,200,300,301]" (merge [1,18,200,300,301] [19,150,200,300,301])
  test "sNumbers" "[1,3,7,9,11,21,27,33,49,63,77,81,99,121,147,189,231,243,297,343]" (take 20 sNumbers)
  test "sNum" "[1,3,7,9,11,21,27,33,49,63,77,81,99,121,147,189,231,243,297,343]" (map sNum [0..19])

test name e c = do
  putStr ("*** " ++ name ++ ": ")
  if show c == e then putStrLn "OK"
  else putStrLn ("ERROR; expected '" ++ e ++ "', but found '" ++ show c ++ "'")

