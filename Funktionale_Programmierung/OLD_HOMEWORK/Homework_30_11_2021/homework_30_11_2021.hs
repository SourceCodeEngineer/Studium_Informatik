import Data.Char -- useful for Caesar exercise
import Data.Ratio -- for Bernoulli exercise
import Data.List -- for the tests
import Data.Ord
import System.Environment


{- Caesar cipher-}
shift :: Int -> Char -> Char
shift n c
  | isLower c = chr $ ((ord c - ord 'a' + n) `mod` 26) + ord 'a'
  | otherwise = c

encode :: Int -> String -> String
encode n cs = [ shift n c | c <- cs ]

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
chisqr os es = sum [((o-e)^2)/e | (o,e) <- zip os es]

rotate :: Int -> [a] -> [a]
rotate n xs = drop n xs ++ take n xs

positions :: Eq a => a -> [a] -> [Int]
positions x xs = [ i' | (x', i') <- zip xs [0..n], x==x' ]
                 where n = length xs - 1

crack :: String -> String
crack cs = encode (factor*(-1)) cs
           where factor = head (positions (minimum chitab) chitab)
                 chitab = [ chisqr (rotate n freqlist') freqList | n <- [0..25] ]
                 freqlist' = freqs cs


encString = "rkcuovv sc pex" --actually it is a very clean language so yes I agree.

{--Bernoulli numbers--}

fact :: Integer -> Integer
fact i = product [1..i]

binom :: Integer -> Integer -> Integer
binom n k = fact n `div` (fact k * fact (n-k))

bernoulli :: Integer -> Rational
bernoulli 0 = 1
bernoulli n = sum [
    toRational(binom n k) * bernoulli k / toRational(k - n - 1)
    | k <- [0..(n-1)]
  ]

bernoullis :: Integer -> [Rational]
bernoullis n = map bernoulli [0..n]

check1 :: Integer -> Bool
check1 i = helperc1' (helperc1 [1 .. i]) == (0 % 1)

helperc1 :: [Integer] -> [Integer] --only odd integers!
helperc1 [] = []
helperc1 (x:xs) = if odd x && x >= 3 then x : helperc1 xs else helperc1 xs

helperc1' :: [Integer] -> Rational
helperc1' = foldr ((+) . bernoulli) 0

check2 :: Integer -> Bool --reverse to bool 
check2 i = (summod4 (helperposmod4 [2 .. i]) < 0) && summod4 (helperposmod2 [2 .. i]) > 0

helperposmod4 :: [Integer] -> [Integer] --only even numbers mod 4
helperposmod4 [] = []
helperposmod4 (x:xs) = if even x && ((x `mod` 4) == 0) then x : helperposmod4 xs else helperposmod4 xs

summod4 :: [Integer] -> Rational
summod4 = foldr ((+) . bernoulli) 0

helperposmod2 :: [Integer] -> [Integer] --even numbers not mod 4
helperposmod2 [] = []
helperposmod2 (x:xs) = if even x && (x `mod` 4) /= 0then x : helperposmod4 xs else helperposmod4 xs

{-- Tests  --}

-- The following should print the first eight rows of Pascal's triangle - try it out!
pascalTriangle :: IO ()
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
