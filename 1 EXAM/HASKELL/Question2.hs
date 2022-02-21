onlyPunct :: String -> Bool
onlyPunct [] = True
onlyPunct l1@(x:xs)
  | x == '.' || x == '?' || x == ',' || x == '!' = onlyPunct xs 
  | otherwise = False

splitAtColon :: String -> [String]
splitAtColon  xs = case break (==':') xs of 
  (ls, "") -> [ls]
  (ls, x:rs) -> ls : splitAtColon rs

main :: IO ()
main = loop 0

loop :: (Show t, Num t) => t -> IO ()
loop n = do
    s <- getLine
    if s == "" then putStr "" else  do 
        putStrLn $ show (length (splitAtColon s)-1) ++ " punct(s)"
        loop n

helper :: Num p => [a] -> p
helper [] = 0
helper l@(x:xs) = 1 + helper xs

