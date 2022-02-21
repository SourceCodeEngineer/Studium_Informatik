findLastElement :: [a] -> a
findLastElement [] = error "leere Liste!"
findLastElement [x] = x
findLastElement (x:xs) = findLastElement xs

findSecondLast :: [a] -> a
findSecondLast x = findLastElement (init x)

elementAt :: [a] -> Int -> a
elementAt x i =  head $ foldr ($) x $ replicate (i-1) tail

numOfElements :: [a] -> Int
numOfElements = length

myReverse :: [a] -> [a]
myReverse = reverse

isPalindrom :: Eq a => [a] -> Bool
isPalindrom x = reverse x == x

data NestedList a = Elem a | List [NestedList a]
flatten :: NestedList a -> [a]
flatten (Elem x) = [x]
flatten (List x) = concatMap flatten x

compress :: Eq a => [a] -> [a]
compress (x:ys@(y:_))
    | x == y    = compress ys
    | otherwise = x : compress ys
compress ys = ys

pack :: (Eq a) => [a] -> [[a]]
pack [] = []
pack (x:xs) = (x : takeWhile (==x) xs) : pack (dropWhile (==x) xs)

encode :: Eq a => [a] -> [(Int, a)]
encode [] = []
encode (x:xs) = (length $ x : takeWhile (==x) xs, x) : encode (dropWhile (==x) xs)



reverseWords = go ""
    where
        go w "" = w
        go w (' ' : xs) = w ++ " " ++ go "" xs
        go w (x:xs) = go (x : w) xs



seriesSum :: Integer -> String
seriesSum 0 = "0.00"
seriesSum 1 = "1.00"
seriesSum n
  | length (show f) > 4 && show f!!4 >= '5' = take 4 $ show (f + 0.01)
  | otherwise = take 4 $ show f
    where f = (+1) . sum . map (1/) $ take (fromInteger n-1) [4,7..]

friend :: [String] -> [[Char]]
friend [] = []
friend l@(x:xs) = if length x == 4 then x : friend xs else friend xs

--firstNonConsecutive :: (Eq a,Enum a) => [a] -> Maybe a
--firstNonConsecutive [] = Nothing
----firstNonConsecutive l1@(x:y:ys) = if (fromEnum(x)+1) == y then firstNonConsecutive (y:ys) else Just y

squareDigit :: Int -> Int
squareDigit i
    | i < 0 = i
    | otherwise =  h (concatMap (show . (\x -> x*x)) (reverse (digit i)))

h :: String -> Int
h x = read x :: Int

digit :: Integral a => a -> [a]
digit 0 = []
digit i = i `mod` 10 : digit (i `div` 10)

data Membership = Open | Senior deriving (Eq, Show)

openOrSenior :: [[Int]] -> [Membership]
openOrSenior [] = []
openOrSenior ([x, xs]:ys) = if x >= 55 && xs > 7 then Senior : openOrSenior ys else Open : openOrSenior ys

isTriangle :: Int -> Int -> Int -> Bool
isTriangle a b c
  | a <= 0 || b<= 0 || c<=0 = False
  | c >= b && c >= a = c < (a+b)
  | b >= c && b >= a = b < (a+c)
  | a >= b && a >= c = a < (c+b)

countSmileys :: [String] -> Int
countSmileys = foldr ((+) . state1) 0


state1 :: Num p => [Char] -> p
state1 [] = 0
state1 (x:xs)
  | x == ':' || x == ';' = state2 xs
  | otherwise = 0


state2 :: Num p => [Char] -> p
state2 [] = 0
state2 (x:xs)
  | x == '-' || x == '~' = state3 xs
  | otherwise = state3 (x:xs)


state3 :: Num p => [Char] -> p
state3 [] = 0
state3 (x:xs)
  | x == ')' || x == 'D' = 1
  | otherwise = 0

tribonacci :: Num a => (a, a, a) -> Int -> [a]
tribonacci (a, b, c) n = reverse (help (a, b, c) n)

help :: (Eq t, Num t, Num c) => (c, c, c) -> t -> [c]
help (a, b, c) 0 = []
help (a, b, c) 1 = (a+b+c) : []
help (a, b, c) n = (help (a, b, c) (n-1)) ++ help (a, b, c) (n-2)