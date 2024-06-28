import Data.Char as C
import Data.List as L

type Coord = (Int, Int)
data PartNum = PartNum Coord Int Int deriving (Eq, Show)
data Gear = Gear Coord deriving (Eq, Show)

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

getGears :: [String] -> [Gear]
getGears grid = reverse $ helper grid 0 0 []
   where helper grid x y acc
            | y >= length grid        = acc
            | x >= length (grid !! y) = helper grid 0 (y + 1) acc
            | isGear                  = helper grid (x + 1) y ((Gear (x, y)):acc)
            | otherwise               = helper grid (x + 1) y acc
            where isGear = not (isDigit symbol) && symbol /= '.'
                  symbol = inputChar grid (x, y)

partCoords :: PartNum -> [Coord]
partCoords (PartNum (x, y) len _) = [(x1, y) | x1 <- [x..x+len-1]]

surrounds :: [String] -> Gear -> [Coord]
surrounds grid (Gear (x, y)) =
   [(x1, y1) | x1 <- [x-1..x+1], y1 <- [y-1..y+1], 
               y1 >= 0 && y1 < length grid, x1 >= 0 && x1 < length (grid !! y1),
               y1 /= y || x1 /= x]

gearNums :: [String] -> [PartNum] -> Gear -> [PartNum]
gearNums grid ps g = helper grid ps g []
   where helper _ [] _ acc = acc
         helper grid (p:ps) g acc
            | length inter > 0 = helper grid ps g (p:acc)
            | otherwise        = helper grid ps g acc
            where inter = intersect (partCoords p) (surrounds grid g)

solution :: String -> String
solution x = show $ sum $ map (\[(PartNum _ _ n1), (PartNum _ _ n2)] -> n1 * n2) gears
   where grid = lines x
         gears = filter (\xs -> length xs == 2) (map (gearNums grid (getNums grid)) (getGears grid))

main = do
       file <- readFile "../inputs/2023/day03-input.txt"
       putStrLn $ solution file