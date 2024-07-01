data PlantMap = PlantMap Int Int Int deriving (Eq, Show)
-- Destination Start, Source Start, Source Length

applyMaps :: [PlantMap] -> Int -> Int
applyMaps [] n = n
applyMaps ((PlantMap ds ss len):pms) n
   | n >= ss && n < ss + len = n + (ds - ss)
   | otherwise               = applyMaps pms n

toMap :: String -> PlantMap
toMap s = PlantMap (nums !! 0) (nums !! 1) (nums !! 2)
   where nums = map read (words s)

getMaps :: [String] -> [[PlantMap]]
getMaps ms = helper maps [] []
   where maps = filter (\x -> length x == 0 || last x /= ':') (drop 2 ms)
         helper [] acc1 acc2 = acc1 ++ [acc2]
         helper (m:ms) acc1 acc2
            | length m == 0 = helper ms (acc1 ++ [acc2]) []
            | otherwise     = helper ms acc1 (acc2 ++ [toMap m])

applyAllMaps :: Int -> [[PlantMap]] -> Int
applyAllMaps = foldl (flip applyMaps)

solution :: String -> String
solution x = show $ minimum $ map (flip applyAllMaps (getMaps l)) seeds
    where l = lines x
          seeds = map read (tail $ words (l !! 0)) :: [Int]

main = do
       file <- readFile "../inputs/2023/day05-input.txt"
       putStrLn $ solution file