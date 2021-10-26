-- Definition of List from lecture
data List = Empty | Cons Integer List deriving Show
-- example list for testing
list = Cons 1 (Cons 7 (Cons 9 (Cons 3 Empty)))
-- example assignment for testing
myAssn = Assign "x" 1 (Assign "x" 2 (Assign "y" 3 EmptyA))

-- Exercise 1

--1 Student "Jane Doe" 243781 True (Teaching Math Physics) --> i
--2 Student "Max Meyer" 221341 False (Teaching CS Math) --> nothing
--3 Student "Mary Smith" 234145 False (Master CS) --> ii

-- Exercise 2
-- disj
disj :: Bool -> Bool -> Bool
disj True True = True
disj _ _ = False

-- sumList
sumList :: List -> Integer
sumList Empty = 0
sumList (Cons x xs) = x + sumList xs

-- double2nd
double2nd :: List -> List
double2nd Empty = Empty -- check if list is completexly empty
double2nd (Cons i Empty) = Cons i Empty -- check if list is only containing one element
double2nd (Cons i (Cons i2 l))= Cons i (Cons (i2 * 2) (double2nd l)) -- recusion step

-- Exercise 3

data Expr = Number Integer
  | Var String
  | Plus Expr Expr
  | Negate Expr
  deriving Show

data Assignment =
  EmptyA
  | Assign String Integer Assignment
  deriving Show

ite :: Bool -> Integer -> Integer -> Integer
ite b x y = if b then x else y

lookupA :: Assignment -> String -> Integer
lookupA (Assign s i recursion) k = ite (s == k) i (lookupA recursion k) --s defined as string, i defined as integer, recursion selfexplaining...
lookupA _ _ = 0 --Emty List

eval :: Assignment -> Expr -> Integer
eval assign expr = 0

helperFun :: Expr -> Integer
helperFun = lookupA
-- search element from expression with lookupA
-- make expr recursive
-- combine those 2

-- Exercise 3.4

{- You may (and will have to) extend this datatype in order to incorporate the "let" construct. -}
data Expr' = Number' Integer
  | Var' String
  | Plus' Expr' Expr'
  | Negate' Expr'
  deriving Show

eval' :: Assignment -> Expr' -> Integer
eval' assn e = undefined


-- the following tests can be used by you, once you have implemented your functions,
-- for testing, just invoke testX in ghci
testSum = putStrLn ("expected: 20\ncomputed: " ++ show (sumList list))
testDouble = putStrLn ("expected: Cons 1 (Cons 14 (Cons 9 (Cons 6 Empty)))\ncomputed: " ++ show (double2nd list))
testLookupA = putStrLn ("expected: 1 3 0\ncomputed: " ++ show (lookupA myAssn "x") ++ " " ++ show (lookupA myAssn "y") ++ " " ++ show (lookupA myAssn "z"))
testEval = putStrLn ("expected: 42\ncomputed: " ++ show (eval myAssn (Plus (Negate (Var "y")) (Number 45))))
