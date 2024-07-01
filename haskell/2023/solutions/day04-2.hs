import Data.List as L

cardValue :: String -> Int
cardValue x = let cards = drop 10 x
                  s = splitAt 30 cards
              in length $ intersect (words $ fst s) (words $ tail $ snd $ s)

addInRange :: [Int] -> Int -> Int -> Int -> [Int]
addInRange xs start len amt = (take start xs) ++ (helper (drop start xs) len amt)
   where helper [] _ _ = []
         helper xs 0 _ = xs
         helper (x:xs) len amt = (x + amt) : (helper xs (len - 1) amt)

cardAmounts :: [String] -> [Int]
cardAmounts cards = helper cards (replicate (length cards) 1) 0
   where helper [] amts _ = amts
         helper (c:cs) amts i 
            | i >= length amts = amts
            | otherwise = helper cs (addInRange amts (i + 1) (cardValue c) (amts !! i)) (i + 1)

solution :: String -> String
solution = show . sum . cardAmounts . lines

main = do
       file <- readFile "../inputs/2023/day04-input.txt"
       putStrLn $ solution file