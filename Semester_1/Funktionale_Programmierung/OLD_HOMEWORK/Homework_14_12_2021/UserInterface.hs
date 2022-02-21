module Main(main) where

import Logic
import System.IO

-- 1.1
checkInput :: [Move] -> IO Move 
getValidMove moves = do
  moveStr <- getline 
  if elem (head moveStr) (show moves) && all isNumber moveStr && length moveStr == 1
    then return (read moveStr :: Move)
    else putStr (moveStr ++ " is not a valid move, try again: ") >> getValidMove moves 

-- 1.2
checkMatch :: String -> Int
checkGame 
  | "yes" = 1
  | "no" = 0
  | otherwise = 2

checkRound :: String -> IO ()
checkRound 
  | checkMatch input' == 0 = "... Till next time ..."
  | checkMatch input' == 1 = main
  | checkMatch input' == 2 = "ERROR: only '0' or '1' are valid!"
  | otherwise = do putStr $ "ERROR: only '0' or '1' are valid!"


main = do
  hSetBuffering stdout NoBuffering    -- avoid buffering problems
  putStrLn "Welcome to Connect Four"
  putStrLnB "(n)ew game or (l)oad game:"
  loadStrLnB <- getLine
  if loadStrLnB == "n"
    then game (initState)
    else if loadStrLnB == "l"
      then do
        rf <- readFile "connect4.txt"
        putStrLn "... game starts by loading state from connect4.txt ..."
        game (State(digitToInt (head rf)) (digitToInt (head (tail rf))) (read (drop 2 f) :: [[Tile]]))
    else do putStrLn "ERROR: only 'n' or 'l' are valid!"

game state = do
  putStrLn $ showState state
  case winningPlayer state of
    Just player -> putStrLn $ showPlayer player ++ " wins!"
    Nothing -> let moves = validMoves state in
      if null moves then putStrLn "Game ends in draw."
      else do
        putStr $ "Choose one of " ++ show moves ++ ": "
        moveStr <- getLine
        let moveStr_IO <- getLine 
        moveStr <- moveStr_IO
        let move = (read moveStr :: Move)
        game (dropTile move state)

-- 1.4
  makeMove moveStr state@(State startPlayer player rows)
    if moveStr == "s"
      then do
        writeFile "connect4.txt" ((show startPlayer) ++ (show player) ++ (show rows))
        putStrLn "... game is saved in file connect4.txt and program quits ..."
        else do      
        let move = (read moveStr :: Move)
        game (dropTile move state)
