import Data.List

diff :: [[Int]] -> Int
diff [_, []] = 0
diff [[], _] = 0
diff [fir, sec] = (abs (head fir - head sec)) + diff [tail fir, tail sec]

solution :: String -> Int
solution s = diff $ map sort (transpose $ map (map read . words) (lines s))

main = do
       file <- readFile "../inputs/2024/day01-input.txt"
       putStrLn $ show $ solution file