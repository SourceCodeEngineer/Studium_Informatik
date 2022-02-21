
insDescending :: Ord a => [a] -> a -> Maybe [a]
insDescending [] y = Just [y]
insDescending l@(x:xs) y = if x `elem` l then Nothing else Just (quicksort1(y : l))

quicksort1 :: (Ord a) => [a] -> [a]
quicksort1 [] = []
quicksort1 (x:xs) =
  let smallerSorted = quicksort1 [a | a <- xs, a <= x]
      biggerSorted = quicksort1 [a | a <- xs, a > x]
  in  smallerSorted ++ [x] ++ biggerSorted

grabEither :: [Bool] -> [a] -> [b] -> [Either a b]
grabEither [] _ _ = []
grabEither [a] [b] [c] = if a then [Left b] else [Right c]
grabEither x [] l@_ = grabEither (tail x) [] (tail l)
grabEither x l@_ [] = grabEither (tail x) (tail l) []
grabEither l@(x:xs) m@(a:as) n@(b:bs)
  | null l = []
  | x = Left a : grabEither (xs) (as) bs
  | not x = Right b : grabEither (xs) as (bs)
  | x && null m = grabEither xs [] bs
  | not x && null m = grabEither xs as []
  | otherwise = []



applyNtimes :: (Num n, Ord n) => n -> (a -> a) -> a -> a
applyNtimes 1 f x = f x
applyNtimes n f x = f (applyNtimes (n-1) f x)

combine :: Eq a => [(a, b)] -> [(a, [b])]
combine [] = []
combine l@(x:xs) = undefined

pyramid :: [a] -> [[a]]
pyramid [] = []
pyramid [x] = [[x]]
pyramid (x:xs) = [x:pyramid | pyramid <- pyramid xs] ++ pyramid xs