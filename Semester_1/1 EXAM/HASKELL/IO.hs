--IO Function to check for palindroms
main :: IO ()
main = loop 0

loop :: (Show t, Num t) => t -> IO ()
loop n = do
    s <- getLine
    if s == "quit" then putStrLn $ "I detected " ++ show n ++ " palindrome(s)!" else do
        let x = if checkPalindrome s then n+1 else n
        loop x

checkPalindrome :: Eq a => [a] -> Bool
checkPalindrome x = x == reverse x

