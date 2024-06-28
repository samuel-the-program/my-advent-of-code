import Data.Char as C

type Coord = (Int, Int)
data PartNum = PartNum Coord Int Int deriving (Eq, Show)

inputChar :: [String] -> Coord -> Char
inputChar grid (x, y) = (grid !! y) !! x

partNums = []
getNums :: [String] -> [PartNum]
getNums grid = reverse $ helper grid 0 0 []
   where helper grid x y acc
            | y >= length grid        = acc
            | x >= length (grid !! y) = helper grid 0 (y + 1) acc
            | len > 0        = helper grid (x + len) y ((PartNum (x, y) len (read taken)):acc)
            | otherwise      = helper grid (x + 1) y acc
            where taken = takeWhile isDigit (drop x (grid !! y))
                  len = length taken

surrounds :: [String] -> PartNum -> [Char]
surrounds grid (PartNum (x, y) len _) =
   [inputChar grid (x1, y1) | x1 <- [x-1..x+len], y1 <- [y-1..y+1], 
               y1 >= 0 && y1 < length grid, x1 >= 0 && x1 < length (grid !! y1),
               y1 /= y || x1 < x || x1 >= x + len]

isPartNum :: [String] -> PartNum -> Bool
isPartNum grid p = any (/='.') (surrounds grid p)

solution :: String -> String
solution x = show $ sum $ map (\(PartNum (_,_) _ n) -> n)$ filter (isPartNum grid) (getNums grid)
   where grid = lines x

main = do
       file <- readFile "../inputs/2023/day03-input.txt"
       putStrLn $ solution file