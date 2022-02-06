-- Question 1 (instance of show class as well as string manipulation)
--Task 1 (8 Points)

listShow :: Show a => [a] -> String
listShow [] = "()"
listShow [x] = "(" ++ show x ++ ")"
listShow l1@(x:xs) = "(" ++ helper l1 ++ ")"

helper :: Show a => [a] -> String
helper [] = ""
helper [x] = show x
helper (x:xs) = show x ++ " and " ++ helper xs

--Task 2 (8 Points)

data Newlist a = ListConstr [a]

instance Show a => Show (Newlist a) where
    show (ListConstr []) = ""
    show (ListConstr xs) = tail $ init $ show xs -- wirft die äußersten 2 chars weg (in dem Fall die Klammern bei Listen und die "" Zeichen bei Strings)

--Task 3 (4 Points)
answerTask3 :: Bool
answerTask3 =  False

--Question 2 (cypher and ceasar algorythm)
--Task 1 (9 Points)

rotChar :: Char -> Char
rotChar c
    | c == 'Z' = toEnum (fromEnum c -27)
    | c < 'Z' && c >= 'A' = toEnum (fromEnum c +1)
    | otherwise = c

--Task 2 (6 Points)
nApply :: (a -> a) -> Int -> (a -> a)
nApply f 0 x = x
nApply f n x = nApply f (n-1) (f x)

--Task 3 (5 Points)
cipher :: Int -> String -> String
cipher n = map (nApply rotChar n) -- map wendet die Funktion (1. Parameter) auf alle Elemente der Liste (2. Parameter)

--Question 3 (lamda functions and list comprehension)
--Task 1 (7 points)
type Item a = (a, Integer)   -- (item identifier, weight)

minList :: Ord b => (a -> b) -> [a] -> a
minList f = foldr1 (\ x m -> if f x <= f m then x else m)

--Task 2 (9 Points)
allTriples :: Ord a => [Item a] -> [((a, a, a), Integer)]
allTriples xs = [((i1, i2, i3), w) | (i1,w1) <- xs, (i2,w2) <- xs, (i3,w3) <- xs, i1 > i2 && i2 > i3,
    let w = w1 + w2 + w3,122 <= w]

--Task 3 (4 Points)
optimalCombination :: Ord a => [Item a] -> (a, a, a)
optimalCombination xs = fst (minList snd (allTriples xs))

--Question 4 (IO)
--Task 1 (4 Points) 
checkPalindrome :: Eq a => [a] -> Bool
checkPalindrome x = x == reverse x

--Task 2 (11 Points) read input from command line and check every line for a palindrome! if the string "quit" is entered, end the programm!
main :: IO ()
main = loop 0

loop :: (Show t, Num t) => t -> IO ()
loop n = do
    s <- getLine
    if s == "quit" then putStrLn $ "I detected " ++ show n ++ " palindrome(s)!" else do
        let x = if checkPalindrome s then n+1 else n
        loop x

longest :: [Char] -> [Char] -> [Char]
longest s1@(x:xs) s2@(y:ys) = (if (x == y) then x : longest xs ys else x : y : longest xs ys)

countChar :: String -> Char -> Int
countChar str char = length $ filter (==char) str

isCaseSensitiveIsogram :: String -> Bool
isCaseSensitiveIsogram str = all (\c -> (countChar str c) <= 1) str

isIsogram :: String -> Bool
isIsogram str = isCaseSensitiveIsogram (map tL str)

tL :: Char -> Char
tL x = if (x >= 'A') && (x <= 'Z') then toEnum(fromEnum x+32) else x
