import Data.List as L

-- T = total time, H = held time, D = total distance, R = record distance
-- H^2 - TH + R < 0
-- (T +/- sqrt(T^2 - 4*R))/2

winWays :: [Int] -> Int
winWays info = floor ((t + disc) / 2) - ceiling ((t - disc) / 2) + 1
   where t = fromIntegral (info !! 0) :: Double
         r = fromIntegral (info !! 1)
         disc = sqrt (t^2 - 4*r)

solution :: String -> String
solution x = show $ product $ map winWays (transpose $ (map (map read . drop 1 . words) (lines x) :: [[Int]]))

main = do
       file <- readFile "../inputs/2023/day06-input.txt"
       putStrLn $ solution file