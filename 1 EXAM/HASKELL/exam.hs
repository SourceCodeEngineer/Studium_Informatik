-- Question 1
--Task 1 (8 Points)

listShow :: Show a => [a] -> String 
listShow [] = "()"
listShow [x] = "(" ++ show x ++ ")"
listShow l1@(x:xs) = "(" ++ helper l1 ++ ")"

helper :: Show a => [a] -> String
helper [] = ""
helper [x] = (show x)
helper (x:xs) = (show x) ++ " and " ++ helper xs

--Task 2 (8 Points)

data Newlist a = ListConstr [a]

instance Show a => Show (Newlist a) where 
    show (ListConstr []) = ""
    show (ListConstr xs) = tail $ init $ show xs -- wirft die äußersten 2 chars weg (in dem Fall die Klammern bei Listen und die "" Zeichen bei Strings)

--Task 3 (4 Points)

answerTask3 :: Bool
answerTask3 =  False

--Question 2
--Task 1 (9 Points)

rotChar :: Char -> Char 
rotChar c 
    | c == 'Z' = toEnum ((fromEnum c) -27)
    | c < 'Z' && c >= 'A' = toEnum ((fromEnum c) +1)
    | otherwise = c

--Task 2 (6 Points)
nApply :: (a -> a) -> Int -> (a -> a)
nApply f 0 x = x 
nApply f n x = nApply f (n-1) (f x)

--Task 3 (5 Points)
cipher :: Int -> String -> String 
cipher n s = map (nApply rotChar n) s -- map wendet die Funktion (1. Parameter) auf alle Elemente der Liste (2. Parameter)

--Question 3
--Task 1 (7 points)

minBy :: Ord b => (a -> b) -> [a] -> a 
minBy = undefined 

--Task 2 (9 Points)
type Item a = (a, Integer)

selections :: Ord a => [Item a] -> [((a, a, a), Integer)]
selections [] = []
selections [x] = []
selections [] = undefined

--Task 3 (4 Points)

optimalCombination :: Ord a => [Item a] -> (a, a, a)
optimalCombination = undefined 

--Question 4
--Task 1 (4 Points)
testPalindrome :: Eq a => [a] -> Bool 
testPalindrome [] = error "List is emty!"
testPalindrome xs = xs == reverse xs

main :: IO()
main = undefined 