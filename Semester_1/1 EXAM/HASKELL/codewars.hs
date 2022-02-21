{-digit :: Char -> Char -> Char -> Integer -> String
digit x y z k =
  [[x], [x, x], [x, x, x], [x, y], [y], [y, x], [y, x, x], [y, x, x, x], [x, z]] !!
  (fromInteger k - 1)
 
solution :: Integer -> String
solution 0 = ""
solution x
  | x < 0 = error "Negative roman numeral"
solution x
  | x >= 1000 = 'M' : solution (x - 1000)
solution x
  | x >= 100 = digit 'C' 'D' 'M' q ++ solution r
  where
    (q, r) = x `divMod` 100
solution x
  | x >= 10 = digit 'X' 'L' 'C' q ++ solution r
  where
    (q, r) = x `divMod` 10
solution x = digit 'I' 'V' 'X' x-}

--
--calculate with Functions
op :: (Int -> Int -> Int) -> ((Int -> Int) -> Int) -> Int -> Int
op = flip (.) flip $ flip (.) ($ id)
plus :: ((Int -> Int) -> Int) -> Int -> Int
plus      = op (+)
minus :: ((Int -> Int) -> Int) -> Int -> Int
minus     = op (-)
times :: ((Int -> Int) -> Int) -> Int -> Int
times     = op (*)
dividedBy :: ((Int -> Int) -> Int) -> Int -> Int
dividedBy = op div

num :: Int -> (Int -> Int) -> Int
num   = flip ($)
zero :: (Int -> Int) -> Int
zero  = num 0
one :: (Int -> Int) -> Int
one   = num 1
two :: (Int -> Int) -> Int
two   = num 2
three :: (Int -> Int) -> Int
three = num 3
four :: (Int -> Int) -> Int
four  = num 4
five :: (Int -> Int) -> Int
five  = num 5
six :: (Int -> Int) -> Int
six   = num 6
seven :: (Int -> Int) -> Int
seven = num 7
eight :: (Int -> Int) -> Int
eight = num 8
nine :: (Int -> Int) -> Int
nine  = num 9

--
{-
solution :: [Integer] -> String
solution [] = ""
solution (x:xs) = ""
solution (x:y:xs) = "_"

countBits :: Int -> Int
countBits 0 = 0
countBits x = helper x 0

helper :: Int -> Int -> Int
helper 0 y = y
helper x y = if even x then 0 + helper (x `div` 2) y else 1 + helper (x `div` 2) y
-}


moveZeros :: [Int] -> [Int]
moveZeros [] = []
moveZeros l1@(x:xs) = removeElements l1 0 ++ createList (countOccurences 0 l1)

removeElements :: [Int] -> Int -> [Int]
removeElements xs x = filter (/= x) xs

countOccurences :: Eq a => a -> [a] -> Int
countOccurences x = length . filter (x==)

createList :: Int -> [Int]
createList 0 = []
createList x = 0 : createList (x-1)