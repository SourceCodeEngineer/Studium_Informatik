--simple Show Instance
data Newlist a = ListConstr [a]

instance Show a => Show (Newlist a) where
    show (ListConstr []) = ""
    show (ListConstr xs) = tail $ init $ show xs

--complex Rational Numbers Instance
data Rat = Rat Integer Integer

normaliseRat :: Rat -> Rat
normaliseRat (Rat a b)
  | a < 0 && b < 0 = Rat (((-1) * a) `div` gcd a b) (((-1) * b) `div` gcd a b)
  | otherwise = Rat (a `div` gcd a b) (b `div` gcd a b)

instance Eq Rat where
  (Rat a1 b1) == (Rat a2 b2) = a3 == a4 && b3 == b4
    where Rat a3 b3 = normaliseRat (Rat a1 b1)
          Rat a4 b4 = normaliseRat (Rat a2 b2)

instance Ord Rat where
  r1 <= r2 = na1 * nb2 <= na2 * nb1 where
    (Rat na1 nb1) = normaliseRat r1
    (Rat na2 nb2) = normaliseRat r2

instance Num Rat where
  (Rat a1 b1) + (Rat a2 b2) = normaliseRat (Rat (a1 * b2 + a2 * b1) (b1 * b2))
  (Rat a1 b1) * (Rat a2 b2) = normaliseRat (Rat (a1 * a2) (b1 * b2))
  abs r
    | r < Rat 0 1 = normaliseRat ((-1) * r)
    | otherwise = normaliseRat r
  signum r = fromInteger (signum na) where Rat na _ = normaliseRat r
  fromInteger a = Rat a 1
  negate (Rat a b) = Rat ((-1) * a) b

instance Show Rat where
  show (Rat a 0) = "can't divide by 0! (" ++ show a ++ "/0)"
  show (Rat a 1) = show a
  show r = let (Rat xa xb) = normaliseRat r in show xa ++ "/" ++ show xb

--simpler Instance
data Unit = ML | G | PC deriving Show

data Ingredient = Ingredient Float Unit String

createIngredient :: String -> Float -> Unit -> Ingredient
createIngredient s f u = Ingredient f u s

instance Show Ingredient where
  show (Ingredient f u s) = show f ++ " " ++ show u ++ " of " ++ s ++ ", cost: " ++ showSign(getPrice (Ingredient f u s)) ++ " EUR"

class Price a where
  getPrice :: a -> Float

instance Price Ingredient where
  getPrice (Ingredient f ML s) = 0.0012 * f
  getPrice (Ingredient f G s) = 0.00095 * f
  getPrice (Ingredient f PC s) = 0.75 * f

instance Price Recipe where
  getPrice Empty = 0
  getPrice (Ingredient1 x xs) = getPrice x + getPrice xs

data Recipe =
  Empty | Ingredient1 Ingredient Recipe

createRecipe :: [Ingredient] -> Recipe
createRecipe = foldr Ingredient1 Empty

instance Show Recipe where
  show recipe = " - " ++ mkstr recipe ++ showSign price ++ " EUR" where
    price = getPrice recipe
    mkstr re = case re of
      Empty -> "Price of the Recipi: "
      Ingredient1 x xs -> show x ++ "\n - " ++ mkstr xs

showSign :: Float -> String
showSign value
  | floor value == ceiling value = show (round value)
  | last value1 == '0' = show (floor value) ++ "." ++ [last (init value1)]
  | otherwise = show (floor value) ++ "." ++ [last (init value1)] ++ [last value1]
  where value1 = "0" ++ show (round (value * 100))
