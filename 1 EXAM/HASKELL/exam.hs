-- Question 1
--Task 1 (8 Points)

listShow :: Show a => [a] -> String 
listShow [] = "<>"
listShow [x] = "<" ++ show x ++ ">"
listShow l1@(x:xs) = "<" ++ helper l1 ++ ">"

helper :: Show a => [a] -> String
helper [] = ""
helper [x] = (show x)
helper (x:xs) = (show x) ++ " - " ++ helper xs

--Task 2 (8 Points)

data AList a = SomeList [a]

instance Show a => Show (AList a) where 
    show (SomeList []) = ""
    show (SomeList xs) = tail $ init $ show xs -- wirft die äußersten 2 chars weg (in dem Fall die Klammern bei Listen und die "" Zeichen bei Strings)

--Question 2
--Task 1 (9 Points)

rotChar :: Char -> Char 
rotChar c 
    | c == 'Z' = toEnum ((fromEnum c) -27)
    | c < 'Z' && c >= 'A' = toEnum ((fromEnum c) +1)
    | otherwise = c

--Task 2 (6 Points)
nFold :: (a -> a) -> Int -> (a -> a)
nFold f 0 x = x 
nFold f n x = nFold f (n-1) (f x)

--Task 3 (5 Points)
cipher :: Int -> String -> String 
cipher n s = map (nFold rotChar n) s -- map wendet die Funktion (1. Parameter) auf alle Elemente der Liste (2. Parameter)

--Question 3
--Task 1 (7 points)

