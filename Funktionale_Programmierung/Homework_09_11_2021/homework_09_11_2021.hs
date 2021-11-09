import System.IO


-- Exercise 1

dividesRange :: Integer -> Integer -> Integer -> Bool
dividesRange = undefined
  
prime :: Integer -> Bool
prime = undefined

generatePrime :: Integer -> Integer
generatePrime = undefined
     
sqrtInt :: Integer -> Integer
sqrtInt = undefined


-- Exercise 2

heron :: Double -> [Double]
heron x = undefined


-- Exercise 3

fib :: Integer -> Integer
fib n = undefined

fib' :: Integer -> Integer
fib' n = undefined

fibFast :: Integer -> Integer
fibFast n = undefined


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