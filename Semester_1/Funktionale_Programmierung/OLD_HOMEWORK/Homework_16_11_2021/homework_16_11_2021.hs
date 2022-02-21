-- Exercise 1

data Rat = Rat Integer Integer
--1.1
normaliseRat :: Rat -> Rat
normaliseRat (Rat a b)
  | a < 0 && b < 0 = Rat (((-1) * a) `div` gcd a b) (((-1) * b) `div` gcd a b)
  | otherwise = Rat (a `div` gcd a b) (b `div` gcd a b)

--1.2
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

-- Exercise 2

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

-- Tests

expected e = putStrLn ("expected: " ++ e)
computed c = putStrLn ("computed: " ++ show c)

testRat = do
  expected "True"
  computed (case (normaliseRat (Rat (-1) (-2)), normaliseRat (Rat 2 4)) of
    (Rat n1 d1, Rat n2 d2) -> (n1,d1) == (n2,d2))

  expected "[True,False]"
  computed [Rat 3 5 == Rat (-9) (-15), Rat 3 5 == Rat 5 3]

  expected "[True,False,True]"
  computed [Rat 3 5 < Rat 3 4, Rat 2 4 < Rat 2 4, Rat (-5) 3 < Rat 10 1]

  expected "[3,4/5,-1/2]"
  computed [Rat 3 1, Rat 4 5, Rat 1 (-2)]

  expected "[1/2,7/12,3/4,-1]"
  computed [3 * Rat 1 6, Rat 1 3 + Rat 1 4, abs (Rat (-3) 4), signum (Rat (-3) 4)]


  putStrLn "some simple calculation: compute the sum 1/1 + 1/2 + 1/3 + ... + 1/100, i.e., sum [ Rat 1 n | n <- [1..100] ]"
  expected "14466636279520351160221518043104131447711/2788815009188499086581352357412492142272"
  computed (sum [ Rat 1 n | n <- [1..100] ])

ing1 = createIngredient "Milk" 200 ML
ing2 = createIngredient "Sugar" 200 G
ing3 = createIngredient "Egg" 3 PC
recipe = createRecipe [ing1, ing2, ing3]

testIng = do
  expected "0.19"
  computed (getPrice ing2)
  expected "0.4275"
  computed (getPrice (createIngredient "Test" 450 G))
  expected (show "200.0 ML of Milk, cost: 0.24 EUR")
  computed (show ing1)
  expected (show "3.0 PC of Egg, cost: 2.25 EUR")
  computed (show ing3)

testRecipe = do
  expected "200.0 ML of Milk, cost: 0.24 EUR - 200.0 G of Sugar, cost: 0.19 EUR - 3.0 PC of Egg, cost: 2.25 EUR - Price of the Recipe: 2.68 EUR"
  computed recipe
  expected "2.68"
  computed (getPrice recipe)
