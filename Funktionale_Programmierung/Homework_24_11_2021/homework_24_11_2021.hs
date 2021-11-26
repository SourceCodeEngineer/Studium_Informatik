import Data.List {- required to use groupBy -}

-- Exercise 1

--div1 :: Fractional a => a -> a -> a
--div2 :: Fractional a => a -> a
--div3 :: Fractional a => a -> a
--eqTuple :: Eq a => (t -> a) -> (t, t) -> Bool
--eqTuple' :: Eq a => (t -> a) -> (t, t) -> Bool

--

-- Exercise 2
fan :: (a -> Bool) -> [a] -> [[a]]
-- fan p = groupBy (\x y -> p x == p y)
fan b [] = [[]]
fan (b) (x : xs) = if b then x : (fan b xs) else [[]]

splitOnNumbers :: String -> [String]
splitOnNumbers = fan undefined

splitBy :: (a -> Bool) -> [a] -> [[a]]
splitBy p = undefined

-- Exercise 3
dig2intFold :: [Integer] -> Integer
dig2intFold = undefined

suffsFold :: [a] -> [[a]]
suffsFold = undefined

-- Tests
tests = do
  test "2.1a" "[]" (fan undefined [] :: [[Int]])
  test "2.1b" "[[1],[2],[3],[4],[5]]" (fan even [1..5])
  test "2.1c" "[\"T\",\"his is a \",\"T\",\"est\"]" (fan (== 'T') "This is a Test")
  test "2.2 " "[\"8\",\" out of \",\"10\",\" cats\"]" (splitOnNumbers "8 out of 10 cats")
  test "2.3 " "[\"Just\",\"some\",\"lines\"]" (splitBy (== '\n') "Just\nsome\nlines\n")
  test "3.1 " "512" (dig2intFold [2,1,5])
  test "3.2a" "[[1,2],[2],[]]" (suffsFold [1,2])
  test "3.2b" "[\"hello\",\"ello\",\"llo\",\"lo\",\"o\",\"\"]" (suffsFold "hello")

test name e c = do
  putStr ("*** " ++ name ++ ": ")
  if show c == e then putStrLn "OK"
  else putStrLn ("ERROR; expected '" ++ e ++ "', but found '" ++ show c ++ "'")