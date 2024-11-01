import Data.List

data Card = Two | Three | Four | Five | Six | Seven | Eight | Nine | T | J | Q | K | A
   deriving (Eq, Ord, Show)

toCard :: Char -> Card
toCard c = case c of
           '2' -> Two
           '3' -> Three
           '4' -> Four
           '5' -> Five
           '6' -> Six
           '7' -> Seven
           '8' -> Eight
           '9' -> Nine
           'T' -> T
           'J' -> J
           'K' -> K
           'Q' -> Q
           'A' -> A
           _   -> Two

handStrength :: String -> Int
handStrength hand = let handType = reverse $ sort $ map length (group $ sort hand)
                    in case handType of
                       [5]             -> 8
                       [4, 1]          -> 7
                       [3, 2]          -> 6
                       [3, 1, 1]       -> 5
                       [2, 2, 1]       -> 4
                       [2, 1, 1, 1]    -> 3
                       [1, 1, 1, 1, 1] -> 2
                       _               -> 1

compareHand :: String -> String -> Ordering
compareHand hand1 hand2 = if order /= EQ then order else handCheck hand1 hand2 0
   where order = compare (handStrength hand1) (handStrength hand2)
         handCheck h1 h2 i
            | i >= 5    = EQ
            | otherwise = if order /= EQ then order else handCheck h1 h2 (i + 1)
            where order = compare (toCard (h1 !! i)) (toCard (h2 !! i))

readLine :: String -> (String, Int) 
readLine s = let w = words s
             in (w !! 0, read $ w !! 1)

solution :: String -> Int
solution s = let bids = sortBy (\a b -> compareHand (fst a) (fst b)) (map readLine (lines s))
             in sum $ map (\(rank,(_,bid)) -> rank * bid) (zip [1..] bids)

main = do
       file <- readFile "../inputs/2023/day07-input.txt"
       putStrLn $ show $ solution file