import System.IO
-- Exercise 1

dividesRange :: Integer -> Integer -> Integer -> Bool
dividesRange number rstart rend = go rstart where
  go x
    | x > rend = False
    | otherwise = number `rem` x == 0 || go (x+1)

prime :: Integer -> Bool
prime k = not(dividesRange k 2 (sqrtInt k))

generatePrime :: Integer -> Integer
generatePrime l = primemin (10^l-1)

primemin :: Integer -> Integer
primemin x = if prime x then x else primemin (x+1)

sqrtInt :: Integer -> Integer
sqrtInt n = bbin 0 (n+1)
    where bbin a b | a + 1 == b = a
                   | otherwise = if m*m > n
                                 then bbin a m
                                 else bbin m b
                               where m = (a + b) `div` 2

getallprimesfromto :: Integer -> [Integer]
getallprimesfromto 0 = []
getallprimesfromto end = if prime end then end : getallprimesfromto (end-1) else getallprimesfromto (end-1)

checkifprimesaredevidedbylist :: Integer -> [Integer] -> Bool
checkifprimesaredevidedbylist _ [] = True
checkifprimesaredevidedbylist i (x:xs)= i `mod` x /= 0 && checkifprimesaredevidedbylist i xs

{-
generatePrime l = if prime ((10^l-1)+1) then l+1 else helper (10^(l-1))

helper :: Integer -> Integer
helper x = if prime (x+1) then x+1 else helper (x+2)

helper1 :: Integer -> Integer
helper1 = sqrtInt

sqrtInt :: Integer -> Integer
sqrtInt n = aux n
  where
    aux x
      | x *x  > n = aux (x - 1)
      | otherwise = x

-}
-- Exercise 2

heron :: Double -> [Double]
heron 0 = [0.0]
heron 1 = [1.0]
heron l = (1/2 * (heron (l-1) + (l / heron (l-1))))


-- Exercise 3
fib :: Integer -> Integer
fib 0 = 1
fib 1 = 1
fib n = fib (n - 1) + fib (n - 2)

fib' :: Integer -> Integer
fib' 0 = 0
fib' 1 = 1
fib' 2 = 1
fib' n = if even n then 2 * fib'  (div n 2 +1) - fib' (div n 2) * fib' (div n 2) else fib' (2 * div n 2)^2 + fib' (div n 2 +1)^2

fibFast :: Integer -> Integer
fibFast n = undefined

fibFastAux :: Integer -> [(Integer, Integer)] -> (Integer, [(Integer, Integer)])
fibFastAux = undefined


-- Tests
testDividesRange = do
  expected "True"
  computed (dividesRange 629 15 25)
  expected "False"
  computed (dividesRange 1009 30 500)
testPrime = do
  expected "[2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97]"
  computed (filter prime [0..100])
testGeneratePrime = do
  expected "[1009,100003,10000019]"
  computed (map generatePrime [4,6,8])
testHeron = do
  expected "[0.0]"
  computed (heron 0)
  expected "[1.0]"
  computed (heron 1)
  expected "[2.0,1.5,1.4166666666666665,1.4142156862745097,1.4142135623746899,1.414213562373095]"
  computed (heron 2)

expected e = putStrLn ("expected: " ++ e)
computed c = putStrLn ("computed: " ++ show c)


testFibGen :: String -> (Integer -> Integer) -> IO ()
testFibGen s f = mapM_ test (zip [0..] xs)
  where xs = [0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765]
        test (n, m) =
           do putStr ("Testing " ++ s ++ " " ++ show n ++ " == " ++ show m ++ "... ")
              hFlush stdout
              let m' = f n
              if m' == m then
                putStrLn "OK"
              else
                putStrLn ("WRONG (got " ++ show m' ++ ")")

testFib = testFibGen "fib" fib
testFib' = testFibGen "fib'" fib'
testFibFast = testFibGen "fibFast" fibFast