import Data.List {- required to use groupBy -}
import GHC.Unicode (isDigit)

-- Exercise 1

--div1 :: Fractional a => a -> a -> a
--div2 :: Fractional a => a -> a
--div3 :: Fractional a => a -> a
--eqTuple :: Eq a => (t -> a) -> (t, t) -> Bool
--eqTuple' :: Eq a => (t -> a) -> (t, t) -> Bool

--

-- Exercise 2
fan :: (a -> Bool) -> [a] -> [[a]]
fan _ [] = []
fan _ [x] = [[x]]
fan p (x : y : xs)
  | p x == p y = (takeWhile p [x] ++ takeWhile p [y]) : fan p xs
  | (p x /= p y) && p x = takeWhile p [x]: fan p xs
  | (p x /= p y) && p y = takeWhile p [y]: fan p xs
  | otherwise = []

splitOnNumbers :: String -> [String]
splitOnNumbers = fan isDigit

splitBy :: (a -> Bool) -> [a] -> [[a]]
splitBy f lst = x (fan f lst) where
  x (y:ys) = if f (head y) then x ys else y : x ys
  x [] = []

-- Exercise 3
dig2intFold :: [Integer] -> Integer
dig2intFold = foldr (\x y -> x + 10 * y) 0

suffsFold :: [a] -> [[a]]
suffsFold = foldr (\x l@(y : _) -> (x : y) : l) [[]]

-- Tests
tests = do
  test "2.1a" "[]" (fan undefined [] :: [[Int]])
  test "2.1b" "[[1],[2],[3],[4],[5]]" (fan even [1 .. 5])
  test "2.1c" "[\"T\",\"his is a \",\"T\",\"est\"]" (fan (== 'T') "This is a Test")
  test "2.2 " "[\"8\",\" out of \",\"10\",\" cats\"]" (splitOnNumbers "8 out of 10 cats")
  test "2.3 " "[\"Just\",\"some\",\"lines\"]" (splitBy (== '\n') "Just\nsome\nlines\n")
  test "3.1 " "512" (dig2intFold [2, 1, 5])
  test "3.2a" "[[1,2],[2],[]]" (suffsFold [1, 2])
  test "3.2b" "[\"hello\",\"ello\",\"llo\",\"lo\",\"o\",\"\"]" (suffsFold "hello")

test name e c = do
  putStr ("*** " ++ name ++ ": ")
  if show c == e
    then putStrLn "OK"
    else putStrLn ("ERROR; expected '" ++ e ++ "', but found '" ++ show c ++ "'")