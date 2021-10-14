-- Aufgabe 1 
-- 1.1 0 :: Bool --> 0 is not a Bool because it is a number!
-- 1.2 head "test" : Char --> Head gives back the first character of a string and "t" is a Char!
-- 1.3 'hello' :: String --> is not a string because of the wrong quotation marks!
-- 1.4 plus1 :: Integer -> Integer --> Not valid, because plus1 does take the input float as well!

--Exercise 3

data Panel =
    Empty
    | PanelForWebsiteWithRetunToPanel
        String Panel--PanelLabel + return to Panel Datatype
        String Panel--PanelLink + return to Panel Datatype
    deriving Show

data PanelTwo =
    Emptytwo
    | PanelWithLimitedItems
        String --Label
        String --Link
    deriving Show 

data FP =
    Temp1
    | FirstpanelFP PanelTwo --You can Create 1 Panel here
    | SecondpanelFP PanelTwo --You can optionally create a second pannel here
    deriving Show 

data OLAT =
    Temp2
    | FirstpanelOLAT PanelTwo --You can Create 1 Panel here
    | SecondpanelOLAT PanelTwo --You can optionally create a second pannel here
    deriving Show

data Website =
    Temp3
    |CreatePanel Panel   --creates a Panel if you wish so
    | Item1 OLAT         --you can create OLAT if you wish so
    | Item2 FP           --you can create FP if you insist
    deriving Show 

data MenuWithThreeFixedElements =
    ConstPanel1
        PanelTwo
        PanelTwo
        PanelTwo
    | AddManyPanels Panel
    deriving Show

data Menu =
    Temp4
    | ManyManyManyPanels Panel