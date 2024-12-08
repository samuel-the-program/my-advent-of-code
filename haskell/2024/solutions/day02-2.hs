steady :: (Int, Int) -> Bool
steady (x, y) = let dist = abs (x - y) in dist >= 1 && dist <= 3

isSafe :: [Int] -> Bool
isSafe xs = let pairs = (zip xs (tail xs)) 
                dirs = (map (\(x,y) -> x < y) pairs) in
    all steady pairs && all (== head dirs) dirs

canSafe :: [Int] -> Bool
canSafe xs = any id (map isSafe ([a ++ drop 1 b | n <- [0..length xs], let (a, b) = splitAt n xs]))

solution :: [String] -> Int
solution s = length $ filter id (map canSafe (map (map read . words) s))

main = do
       file <- readFile "../inputs/2024/day02-input.txt"
       putStrLn $ show $ solution $ lines file