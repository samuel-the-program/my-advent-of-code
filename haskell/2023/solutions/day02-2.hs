import Data.List as L

data Color = Red | Green | Blue | NoCol deriving Eq

getColor :: String -> Color
getColor x
   | isInfixOf "red" x   = Red
   | isInfixOf "green" x = Green
   | isInfixOf "blue" x  = Blue
   | otherwise           = NoCol

spanUntil :: Eq a => (a -> Bool) -> [a] -> ([a], [a])
spanUntil p x 
   | snd s == [] = s
   | otherwise   = ((fst s) ++ [(head $ snd s)], tail $ snd s)
   where s = span p x

minGame :: [String] -> Color -> Int
minGame x c = helper x c 0
   where helper [] c acc = acc
         helper [_] c acc = acc
         helper all@(x:y:xs) c acc
            | col == c   = helper xs c (max (read x) acc)
            | otherwise  = helper xs c acc
            where col = getColor y

power :: String -> Int
power x = (minGame game Red) * (minGame game Green) * (minGame game Blue)
   where game = drop 2 (words x)

solution :: String -> String
solution x = show $ sum $ map power (lines x)

main = do
       file <- readFile "../inputs/2023/day02-input.txt"
       putStrLn $ solution file