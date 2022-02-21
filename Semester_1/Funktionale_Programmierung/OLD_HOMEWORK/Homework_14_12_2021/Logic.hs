module Logic(State, Move, Player,
  initState, showPlayer, showState,
  winningPlayer, validMoves, dropTile) where


type Tile   = Int   -- 0, 1, or 2
type Player = Int   -- 1 and 2
type Move   = Int   -- column number
data State = State Player [[Tile]]  -- list of rows

empty :: Tile
empty = 0

numRows, numCols :: Int
numRows = 6
numCols = 7

startPlayer :: Player
startPlayer = 1

initState :: State
initState = State startPlayer 
  (replicate numRows (replicate numCols empty))

validMoves :: State -> [Move]
validMoves (State _ rows) =
  map fst . filter ((== empty) . snd) . zip [0 .. numCols - 1] $ head rows

showPlayer :: Player -> String
showPlayer 1 = "X"
showPlayer 2 = "O"

showTile :: Tile -> Char
showTile t = if t == empty then '.' else head $ showPlayer t

showState :: State -> String
showState (State player rows) = unlines $
    map (head . show) [0 .. numCols - 1] :
    map (map showTile) rows
     ++ ["\nPlayer " ++ showPlayer player ++ " to go"]

otherPlayer :: Player -> Player
otherPlayer = (3 -)

dropTile :: Move -> State -> State
dropTile col (State player rows) = State
  (otherPlayer player) 
  (reverse $ dropAux $ reverse rows)
    where
      dropAux (row : rows) =
        case splitAt col row of
         (first, t : last) ->
           if t == empty 
             then (first ++ player : last) : rows
             else row : dropAux rows

winningRow :: Player -> [Tile] -> Bool
winningRow player [] = False
winningRow player row = take 4 row == replicate 4 player
  || winningRow player (tail row)

-- 1.3 
winningDiagonals :: Player -> [[Tile]] -> Bool
winningDiagonals player field = checkRow 0
  where 
    checkRow row = (row <= numRows - 4) && (checkCol row 0 || checkRow (row + 1))
    checkCol row col = (col <= numCols - 4) && ((checkAux row col (col+) || checkAux row col (numCols - 1 - col - )) || checkCol row (col+1))
    checkAux row col colPred = [(field !! nr) !! j | x <- [0..3], let nr = numRows - 1 - row - x, let j = colPred x] == replicate 4 player
transpose ([] : _) = []
transpose xs = map head xs : transpose (map tail xs)

winningPlayer :: State -> Maybe Player
winningPlayer (State player rows) =
  let prevPlayer = otherPlayer player
      longRows = rows ++ transpose rows -- ++ diags rows
    in if any (winningRow prevPlayer) longRows || winningDiagonals prevPlayer rows
      then Just prevPlayer
      else Nothing