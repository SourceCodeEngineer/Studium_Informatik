-- String to Lower
{-# OPTIONS_GHC -Wno-unrecognised-pragmas #-}
{-# HLINT ignore "Use isAsciiUpper" #-}
stringToLower :: String -> String
stringToLower [] = ""
stringToLower (x:xs) = if fromEnum x >= 65 && fromEnum x <= 90
                        then toEnum (fromEnum x + 32) : stringToLower xs
                        else x : stringToLower xs

-- String to Upper
stringToUpper :: String -> String
stringToUpper [] = ""
stringToUpper (x:xs) = if fromEnum x >= 97 && fromEnum x <= 122
                        then toEnum (fromEnum x - 32) : stringToUpper xs
                        else x : stringToUpper xs

-- Char to Lower
charToLower :: Char -> Char
charToLower x = if fromEnum x >= 65 && fromEnum x <= 90
                        then toEnum (fromEnum x + 32)
                        else x

-- Char to Upper
charToUpper :: Char -> Char
charToUpper x = if fromEnum x >= 97 && fromEnum x <= 122
                        then toEnum (fromEnum x - 32)
                        else x

-- Char replacement in String
charReplaceString :: String -> String
charReplaceString [] = ""
charReplaceString (x:xs) = if x == 'x' then "y" ++ charReplaceString xs else x : charReplaceString xs

-- x last elements of list
xLastElementsOfList :: [a] -> Int -> [a]
xLastElementsOfList [] _ =  []
xLastElementsOfList l n = applyNtimes (length l - n) tail l

-- apply Function n times
applyNtimes :: (Num n, Ord n) => n -> (a -> a) -> a -> a
applyNtimes 1 f x = f x
applyNtimes n f x = f (applyNtimes (n-1) f x)

-- Quicksort Sortier Algorythmus
quicksort1 :: (Ord a) => [a] -> [a]
quicksort1 [] = []
quicksort1 (x:xs) =
  let smallerSorted = quicksort1 [a | a <- xs, a <= x]
      biggerSorted = quicksort1 [a | a <- xs, a > x]
  in  smallerSorted ++ [x] ++ biggerSorted

-- Isogramm
isIsogram :: String -> Bool
isIsogram str = isCaseSensitiveIsogram (map tL str)

isCaseSensitiveIsogram :: String -> Bool
isCaseSensitiveIsogram str = all (\c -> countChar str c <= 1) str

tL :: Char -> Char
tL x = if (x >= 'A') && (x <= 'Z') then toEnum(fromEnum x+32) else x

countChar :: String -> Char -> Int
countChar str char = length $ filter (==char) str

-- Floating Point rounding to 2 dezimals
showSign :: Float -> String
showSign value
  | floor value == ceiling value = show (round value)
  | last value1 == '0' = show (floor value) ++ "." ++ [last (init value1)]
  | otherwise = show (floor value) ++ "." ++ [last (init value1)] ++ [last value1]
  where value1 = "0" ++ show (round (value * 100))

-- String to Double
stringToDouble :: String -> Double
stringToDouble x = read x :: Double

-- String to Integer
stringToInt :: String -> Int
stringToInt x = read x :: Int

-- String to Int list
toDigit :: Integral a => a -> [a]
toDigit 0 = [0]
toDigit n = aux n where
 aux n
  | n/=0 = aux (div n 10) ++ [mod n 10]
  | otherwise = []

-- Roman Numeral
numerals :: [(String, Integer)]
numerals = zip ["M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" ]
               [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]

solution :: Integer -> String
solution 0 = ""
solution n = k ++ solution (n - v)
             where (k, v) = head $ filter ((<=n).snd) numerals

-- search substring in string
contains :: Eq a => [a] -> [a] -> Bool
contains q str = aux q str where
 aux [] _ = True
 aux _ [] = False
 aux (x:xs) (y:ys)
  | x == y = aux xs ys
  | otherwise = aux q ys

-- substring removal from string
removeFirst :: [Char] -> [Char] -> [Char]
removeFirst q str = aux q str "" where
 aux [] ys buf= ys
 aux xs [] buf= []
 aux (x:xs) (y:ys) buf
  | x == y = aux xs ys (buf++[y])
  | not (null buf) = buf ++ aux q  (y:ys) ""
  | otherwise = aux q ys ""