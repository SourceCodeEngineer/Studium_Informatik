module Partition (Partition, toLists, pretty, discrete, representative, related, join) where

import Prelude hiding (lookup)
import Data.List (sort, intercalate)
import Control.Monad (mapM)

newtype Partition a = Partition () -- change this

-- insert Eq instance declaration here

-- returns a list of the groups of a partition
toLists :: Ord a => Partition a -> [[a]]
toLists = undefined

pretty :: (Show a, Ord a) => Partition a -> String
pretty = braces . intercalate ", " . map (braces . intercalate ", " . map show) . sort . map sort . toLists
  where braces s = "{" ++ s ++ "}"


-- The discrete partition in which no two elements are related.
discrete :: Ord a => [a] -> Partition a
discrete = undefined

-- Returns the canonical representative for the given element's group.
representative :: Ord a => a -> Partition a -> a
representative = undefined

-- Determines whether two elements are related
related :: Ord a => a -> a -> Partition a -> Bool
related = undefined

-- makes two elements related, i.e. joins their groupes
join :: Ord a => a -> a -> Partition a -> Partition a
join  = undefined


-- Testing functions

-- auxiliary function, ignore this
testRelatedAux part xs =
  do putStrLn "Testing 'related' function on test partition..."
     if null ys then
       putStrLn "No errors found."
     else do
       mapM (\(i, j, b, b') -> putStrLn $ "Wrong result: " ++ show i ++ " and " ++ show j ++ " should" ++ notStr b ++ " be related, but your " ++
         "implementation claims they are" ++ notStr b' ++ ".") ys
       return ()
  where ys = [(i, j, b, b') | (i, j, b) <- xs, let b' = related i j part, b /= b']
        notStr b = if b then "" else " not"
        


-- The following are tests that you can run to check whether your implementation does the right thing

-- should return True
testEquality1 = join 1 2 (discrete [1..5]) == join 2 1 (discrete [1..5])
  
-- should return True
testEquality2 = join 3 4 (join 1 2 (discrete [1..5])) == join 1 2 (join 3 4 (discrete [1..5]))

-- This should be the partition {{1, 3, 4}, {2, 5}, {6}, {7}} (check by hand)
testPartition = join 1 3 $ join 2 5 $ join 1 4 $ discrete [1..7]

-- This tests your 'representative function' on the testPartition
testRepresentative =
  do bs <- mapM test (toLists testPartition)
     if and bs then putStrLn "All okay!" else putStrLn "Some errors were found."
  where err s = putStrLn ("Wrong result: " ++ s) >> return False
        test zs
          | any (`notElem` zs) rs = err $ "representative of " ++ show (head (filter (`notElem` zs) rs)) ++ " should be one of " ++ show zs
          | any (/= head rs) rs = err $ "representatives of " ++ show zs ++ " are " ++ show rs ++ " (should all be the same)"
          | otherwise = putStrLn ("Testing representatives of " ++ show zs ++ "... " ++ show rs) >> return True
          where rs = map (\i -> representative i testPartition) zs

-- This tests your 'related function' on a discrete partition
testRelated1 = testRelatedAux (discrete [1..5]) [(i, j, i == j) | i <- [1..5], j <- [1..5]]

-- This tests your 'related function' on the test partition
testRelated2 = testRelatedAux testPartition
  [(1,1,True),(1,2,False),(1,3,True),(1,4,True),(1,5,False),(1,6,False),(1,7,False),(2,1,False),(2,2,True),(2,3,False),
   (2,4,False),(2,5,True),(2,6,False),(2,7,False),(3,1,True),(3,2,False),(3,3,True),(3,4,True),(3,5,False),(3,6,False),
   (3,7,False),(4,1,True),(4,2,False),(4,3,True),(4,4,True),(4,5,False),(4,6,False),(4,7,False),(5,1,False),(5,2,True),
   (5,3,False),(5,4,False),(5,5,True),(5,6,False),(5,7,False),(6,1,False),(6,2,False),(6,3,False),(6,4,False),(6,5,False),
   (6,6,True),(6,7,False),(7,1,False),(7,2,False),(7,3,False),(7,4,False),(7,5,False),(7,6,False),(7,7,True)]

