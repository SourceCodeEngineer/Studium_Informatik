-- Exercise 1
merge :: Ord a => [a] -> [a] -> [a]
merge = undefined

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

