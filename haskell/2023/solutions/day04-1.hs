import Data.List as L

cardValue :: String -> Int
cardValue x = let cards = drop 10 x
                  s = splitAt 30 cards
                  ints = intersect (words $ fst s) (words $ tail $ snd $ s)
              in if length ints == 0 then 0 else 2^(length ints - 1)

solution :: String -> String
solution x = show $ sum $ map cardValue (lines x)

main = do
       file <- readFile "../inputs/2023/day04-input.txt"
       putStrLn $ solution file