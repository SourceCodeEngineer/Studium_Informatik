type Item a = (a, Integer)

allTriples :: Ord a => [Item a] -> [((a, a, a), Integer)]
allTriples xs = [((i1, i2, i3), w) | (i1,w1) <- xs, (i2,w2) <- xs, (i3,w3) <- xs, i1 > i2 && i2 > i3,
    let w = w1 + w2 + w3,122 <= w]