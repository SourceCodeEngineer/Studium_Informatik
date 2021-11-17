-- Exercise 1

data Rat = Rat Integer Integer

normaliseRat :: Rat -> Rat
normaliseRat = undefined

instance Eq Rat where

instance Ord Rat where
          
instance Show Rat where
  show r = undefined
      
instance Num Rat where


-- Exercise 2

data Unit = ML | G | PC deriving Show

data Ingredient 

createIngredient :: String -> Float -> Unit -> Ingredient
createIngredient = undefined -- specify as soon as Ingredient has been defined

instance Show Ingredient where


-- remove the following line, as soon as 
-- you define the class Price
getPrice x = (undefined :: Float)

data Recipe 

createRecipe :: [Ingredient] -> Recipe
createRecipe = undefined -- specify as soon as Recipe has been defined

instance Show Recipe where


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
