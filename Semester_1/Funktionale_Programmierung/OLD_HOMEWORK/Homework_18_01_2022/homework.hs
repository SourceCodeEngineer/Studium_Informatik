import Data.Char -- useful for Exercise 1

-- Exercise 1

stringToUpperTail :: String -> String
stringToUpperTail cs = aux [] cs where
  aux acc []  = acc
  aux acc (c:cs) = let accN = acc ++ [toUpper c] in seq accN (aux accN cs)

stringToUpperGuarded :: String -> String
stringToUpperGuarded = map toUpper

-- Exercise 2
type Graph a = [(a, a)]
type RootedGraph a = (a, Graph a)
data Tree a = Node a [Tree a] deriving (Eq, Show)

graphFigure1 :: RootedGraph Int
graphFigure1 = (1, [(1,1), (1,2), (1,3), (1,4), (2,1), (3,1), (4,1)])

unwind :: Eq a => RootedGraph a -> Tree a
unwind (root, graph) = Node root [unwind (succ, graph) | (pred, succ) <- graph, pred == root]

prune :: Int -> Tree a -> Tree a
prune n (Node root children) = Node root (help n children) where
  help 0 _ = []
  help _ [] = []
  help n children = map (prune (n-1)) children

narrow :: Int -> Tree a -> Tree a
narrow n (Node root children) = Node root (help n children) where
  help _ [] = []
  help n children = take n (map (narrow n) children)

mults :: Tree Integer
mults = let multnumber x = Node x (map (\n -> multnumber (x*n)) [2..]) in multnumber 1

-- Tests
firsts :: Tree a -> [a]
firsts (Node x []) = [x]
firsts (Node x (t:_)) = x : firsts t

tests = do
  test "to-upper-tail" "\"HELLO\"" (stringToUpperTail "Hello")
  test "to-upper-guarded" "\"WORLD!\"" (stringToUpperGuarded "World!")
  test "narrow" "Node 1 [Node 2 []]" (narrow 1 $ Node 1 [Node 2 [], Node 3 []])
  test "prune+unwind" "Node 1 [Node 1 [Node 1 [],Node 2 [],Node 3 [],Node 4 []],Node 2 [Node 1 []],Node 3 [Node 1 []],Node 4 [Node 1 []]]" (prune 2 $ unwind graphFigure1)
  test "prune+unwind" "Node 1 []" (prune 0 $ unwind graphFigure1)
  test "mults" "[1,2,4,8,16,32,64,128,256,512]" (take 10 $ firsts $ mults)

test name e c = do
  putStr ("*** " ++ name ++ ": ")
  if show c == e then putStrLn "OK"
  else putStrLn ("ERROR; expected '" ++ e ++ "', but found '" ++ show c ++ "'")