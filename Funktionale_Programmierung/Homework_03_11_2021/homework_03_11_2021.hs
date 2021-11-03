ite :: Bool -> a -> a -> a
ite True x y = x
ite False x y = y

-- Exercise 1.1
mergeLists = undefined

-- Exercise 1.2
calculateAge :: (Int, Int, Int) -> Int
calculateAge (d2, m2, y2)
   | 11 > m2 = 2021 - y2
   | 11 == m2 && 10 >= d2 = 2021 - y2
   | otherwise = 2021 - y2 - 1


-- Exercise 1.3
convertDatesToAges :: [(String, (Int, Int, Int))] ->  [(String, Int)]
convertDatesToAges [(s, (i1, i2, i3))] = [(s, calculateAge(i1, i2, i3))]
convertDatesToAges [] = []

-- Exercise 1.4
getOtherPairValue :: a
getOtherPairValue = undefined

-- Exercise 2.3
fstList :: [(a, b)] -> [a]
fstList = undefined

-- Exercise 2.4
lengthSumMax :: Num a => [a] -> (Int, a, a)
lengthSumMax = undefined

-- Tests
testMergeLists = do
  expected "[(1,'a'),(2,'b'),(3,'c')]"
  computed (mergeLists [1,2,3,4] ['a','b','c'] :: [(Int, Char)])
testCalculateAge = do
  expected "0"
  computed (calculateAge (10, 11, 2021))
  expected "20"
  computed (calculateAge (12, 12, 2000))
testFstList = do
  expected "[1,2,3]"
  computed (fstList [(1,'a'),(2,'b'),(3,'c')])
  expected "[\"hello\"]"
  computed (fstList [("hello","world")])
  expected "[]"
  computed (fstList [] :: [Integer])
testLengthSumMax = do
  expected "(0,0,0)"
  computed (lengthSumMax [])
  expected "(5,3,2)"
  computed (lengthSumMax [0,1,0,2,0])

expected e = putStrLn ("expected: " ++ e)
computed c = putStrLn ("computed: " ++ show c)