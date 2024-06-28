import Data.List as L

data Color = Red | Green | Blue | NoCol deriving Eq

getId :: String -> Int
getId s = read $ init $ words s !! 1

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

checkGame :: ([String] -> Bool) -> [String] -> Bool
checkGame f [] = True
checkGame f x
   | not (f $ first)     = False
   | otherwise           = checkGame f (snd split)
   where split = spanUntil (\x -> last x /= ';') x
         first = fst split

validRound :: [String] -> Bool
validRound [] = True
validRound [_] = True
validRound (x:y:xs)
   | col == Red && num > 12   = False
   | col == Green && num > 13 = False
   | col == Blue && num > 14  = False
   | otherwise                = validRound xs
   where col = getColor y
         num = read x :: Int

gameValue :: String -> Int
gameValue x = if checkGame validRound game
              then getId x
              else 0
              where game = drop 2 (words x)

solution :: String -> String
solution x = show $ sum $ map gameValue (lines x)

main = do
       file <- readFile "../inputs/2023/day02-input.txt"
       putStrLn $ solution file