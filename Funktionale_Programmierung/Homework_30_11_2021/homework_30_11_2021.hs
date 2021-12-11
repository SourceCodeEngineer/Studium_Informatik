import Data.Char -- useful for Caesar exercise
import Data.Ratio -- for Bernoulli exercise
import Data.List -- for the tests


{- Caesar cipher-}
shift :: Int -> Char -> Char
shift n c
  | isLower c = chr $ ((ord c - ord 'a' + n) `mod` 26) + ord 'a'
  | otherwise = c

encode :: Int -> String -> String
encode n = map (shift n)

freqList = [8.2, 1.5, 2.8, 4.3, 13, 2.2, 2, 6.1, 7, 0.15, 0.77, 4, 2.4, 6.7,
            7.5, 1.9, 0.095, 6, 6.3, 9.1, 2.8, 0.98, 2.4, 0.15, 2, 0.074]

count :: Char -> String -> Int
count c str = length $ filter (== c) str

percent :: Int -> Int -> Float
percent x y =   100 * ( a / b )
  where a = fromIntegral x :: Float
        b = fromIntegral y :: Float

freqs :: String -> [Float]
--reusing count for number of occurences (char -> string -> int)
freqs s = helperf (helperc s ['a'..'z']) (length s)

--using last char of the alphabet and match it to the string, then returns it to a list
helperc :: String -> [Char] -> [Int]
helperc s = map (`count` s)

--takes the return list from helperc and the len of the string
helperf :: [Int] -> Int -> [Float]
helperf is i3 = map (`percent` i3) is

chisqr :: [Float] -> [Float] -> Float
chisqr [] _ = 0
chisqr _ [] = 0
chisqr (x:xs) (y:ys) = (((x-y) * (x-y)) / y) + chisqr xs ys

rotate :: Int -> [a] -> [a]
rotate i [] = []
rotate i p@(x:xs) = taker p i ++ dropper p i

dropper :: [a] -> Int -> [a]
dropper [] _ = []
dropper p i = if length p == i then p else dropper (init p) i

taker :: [a] -> Int -> [a]
taker p i = if length p < i then p else taker (tail p) i

positions :: Eq a => a -> [a] -> [Int]
positions _ [] = []
positions x p@(y:ys) = undefined 

crack :: String -> String
crack s = undefined

encString = "rkcuovv sc pex"

{--Bernoulli numbers--}

fact :: Integer -> Integer
fact = undefined

binom :: Integer -> Integer -> Integer
binom = undefined

bernoulli :: Integer -> Rational
bernoulli = undefined

bernoullis :: Integer -> [Rational]
bernoullis = undefined

check1 :: Integer -> Bool
check1 = undefined

check2 :: Integer -> Bool
check2 = undefined

{-- Tests  --}

-- The following should print the first eight rows of Pascal's triangle - try it out!
pascalTriangle = putStrLn $ unlines $ map (\n -> spaces ((m - n) * 2) ++ (intercalate " " $ map (pad 3 . show . binom n) [0..n])) [0..m]
  where m = 8
        spaces n = replicate (fromIntegral n) ' '
        pad n s = let l = length s in if l < n then s ++ spaces (n - l) else s

tests = do
  test "1.1  " "\"mjwj nx fs jcfruqj.\"" (encode 5 "here is an example.")
  test "1.2a " "2" (count 'e' "example")
  test "1.2a'" "33.333336" (percent 1 3)
  test "1.2b " "[10.0,20.0,30.000002,40.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0]" (freqs "abbcccdddd")
  test "1.2c " "25.0" (chisqr [50,50,0] [40,40,20])
  test "1.2d " "[4,5,1,2,3]" (rotate 3 [1,2,3,4,5])
  test "1.2d'" "[0,2,3]" (positions 3 [3,1,3,3])
  test "1.3  " "\"test\"" (crack (encode 10 "test"))
  test "2.1a " "[1,1,2,6,24,120]" (map fact [0..5])
  test "2.1b " "[1,5,10,10,5,1]" [binom 5 k | k <- [0..5]]
  test "2.2  " "[1 % 1,(-1) % 2,1 % 6,0 % 1,(-1) % 30,0 % 1,1 % 42]" (map bernoulli [0..6])
  test "2.3  " "[1 % 1,(-1) % 2,1 % 6,0 % 1,(-1) % 30,0 % 1,1 % 42]" (bernoullis 6)
  test "2.4a " "True" (check1 10)
  test "2.4b " "True" (check2 10)

test name e c = do
  putStr ("*** " ++ name ++ ": ")
  if show c == e then putStrLn "OK"
  else putStrLn ("ERROR; expected '" ++ e ++ "', but found '" ++ show c ++ "'")
