import Text.Read.Lex (Number)
-- Exercise 1

suffixes :: [a] -> [[a]]
suffixes [] = [[]]
suffixes l@(_:t) = l : suffixes t

prefixes :: [a] -> [[a]]
prefixes [] = [[]]
prefixes l@x = l : prefixes (init x)

menu :: Char -> [a] -> Either String [[a]]
menu 'p' l = Right (prefixes l)
menu 's' l = Right (suffixes l)
menu x _ = Left ("(" ++ show x ++ ")" ++ "is not supported, use (p)refix or (s)uffix")


-- Exercise 2
data Expr change these variables = 
  Number Integer
  | Addition Expr Expr
  | Times Expr Expr
  deriving Show

-- replace dummy expressions by real expressions in comments below as soon as datatype Expr has been defined
expr1 = undefined
expr2 = undefined
expr3 = undefined

-- expr1 = Times (Plus (Number (5.2 :: Double)) (Number 4)) (Number 2)
-- expr2 = Plus (Number (2 :: Int)) (Times (Number 3) (Number 4))
-- expr3 = Times (Number "hello") (Number "world")

numbers :: a        -- change the type
numbers = undefined -- and the definition

eval :: a        -- change the type
eval = undefined -- and the definition

exprToString :: a        -- change the type
exprToString = undefined -- and the definition


-- Tests: Un-comment the desired test (and :reload) after you provided a corresponding solution.
testSuffixes = "Expected [[1,2,3],[2,3],[3],[]]; suffixes [1,2,3] returned " ++ show (suffixes [1,2,3] :: [[Int]])
testPrefixes = "Expected [[1,2,3],[1,2],[1],[]]; prefixes [1,2,3] returned " ++ show (prefixes [1,2,3] :: [[Int]])
testMenuP = "Expected Right [[1,2],[1],[]]; menu 'p' [1,2] returned " ++ show (menu 'p' [1,2] :: Either String [[Int]])
testMenuS = "Expected Right [[1,2],[2],[]]; menu 's' [1,2] returned " ++ show (menu 's' [1,2] :: Either String [[Int]])
testMenuC = "Expected Left \"(d) is not supported, use (p)refix or (s)uffix\"; menu 'd' [1,2] returned " ++ show (menu 'd' [1,2] :: Either String [[Int]])
testMenu = putStr (testMenuP ++ "\n" ++ testMenuS ++ "\n" ++ testMenuC ++ "\n")

testEval1 = "Expected 18.4; eval expr1 returned " ++ show (eval expr1 :: Double)
testEval2 = "Expected 14; eval expr2 returned " ++ show (eval expr2 :: Int)
testEval = putStr (testEval1 ++ "\n" ++ testEval2 ++ "\n")

testExprToString1 = "Expected \"(5.2 + 4.0) * 2.0\"; exprToString expr1 returned " ++ exprToString expr1
testExprToString2 = "Expected \"2 + 3 * 4\"; exprToString expr2 returned " ++ exprToString expr2
testExprToString3 = "Expected \"\\\"hello\\\" * \\\"world\\\"\"; exprToString expr3 returned " ++ exprToString expr3
testExprToString = putStr (testExprToString1 ++ "\n" ++ testExprToString2 ++ "\n" ++ testExprToString3 ++ "\n")