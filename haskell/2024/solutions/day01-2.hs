import Data.List

counts :: [[Int]] -> Int
counts [fir, sec] = sum $ map (\x -> (length $ filter (==x) sec) * x) fir

solution :: String -> Int
solution s = counts $ transpose $ map (map read . words) (lines s)

main = do
       file <- readFile "../inputs/2024/day01-input.txt"
       putStrLn $ show $ solution file