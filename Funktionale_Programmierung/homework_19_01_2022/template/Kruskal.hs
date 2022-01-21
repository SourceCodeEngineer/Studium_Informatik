import Data.List (sortOn)
import Partition

type Vertex = Int
type Weight = Int
data Edge = Edge Vertex Weight Vertex
  deriving (Show, Eq)
data Graph = Graph [Vertex] [Edge]
  deriving Show

weight :: Edge -> Weight
weight (Edge _ w _) = w

kruskal :: Graph -> [Edge]
kruskal (Graph vs es) = go (discrete vs) (sortOn weight es)
  where go _ [] = []
        go part (e@(Edge u _ v) : es)
          | related u v part = go part es
          | otherwise        = e : go (join u v part) es


-- Tests

testGraph1 :: Graph
testGraph1 = Graph [1..3] [Edge 1 10 2, Edge 2 20 3, Edge 3 30 1]

testResult1 :: [Edge]
testResult1 = [Edge 1 10 2,Edge 2 20 3]


testGraph2 :: Graph
testGraph2 = Graph [1..5] [Edge 1 7 2, Edge 1 3 3, Edge 1 12 4, Edge 2 9 5, Edge 3 8 5, Edge 4 5 5]

testResult2 :: [Edge]
testResult2 = [Edge 1 3 3,Edge 4 5 5,Edge 1 7 2,Edge 3 8 5]


testGraph3 :: Graph
testGraph3 = Graph [1..7] [Edge 1 28 2, Edge 1 10 6, Edge 5 25 6, Edge 5 24 7, Edge 5 22 4, Edge 7 18 4, Edge 2 14 7, Edge 2 16 3, Edge 4 12 3]

testResult3 :: [Edge]
testResult3 = [Edge 1 10 6,Edge 4 12 3,Edge 2 14 7,Edge 2 16 3,Edge 5 22 4,Edge 5 25 6]


runTests = 
  do putStrLn "Testing Kruskal on graphs..."
     if null zs then
       putStrLn "No mistakes found."
     else do
       mapM (\(i, g, corr, res) -> putStrLn $ "Graph " ++ show i ++ " results in edge list \n  " ++ show res ++ "\nbut should be \n  " ++ show corr ++ "\n") zs
       return ()
  where ys = [(testGraph1, testResult1), (testGraph2, testResult2), (testGraph3, testResult3)]
        zs = [(i, g, corr, res) | (i, (g, corr)) <- zip [1..] ys, let res = kruskal g, corr /= res]


