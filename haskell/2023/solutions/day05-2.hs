data PlantMap = PlantMap Int Int Int deriving (Eq, Show)
data Range = Range Int Int Bool deriving (Eq, Show)
-- Destination Start, Source Start, Source Length

applyMap :: PlantMap -> Range -> [Range]
applyMap (PlantMap ds ss slen) r@(Range rs rlen _)
   | rs < ss && re > se = [Range ds slen True, Range se (re - se) False, Range rs (ss - rs) False]
   | rs >= ss && re <= se = [Range (rs + diff) rlen True]
   | rs >= ss && rs < se && re > se = [Range se (re - se) False, Range (rs + diff) (se - rs) True]
   | rs < ss && re <= se && re >= ss = [Range rs (ss - rs) False, Range ds (re - ss) True]
   | otherwise = [Range rs rlen False]
   where diff = ds - ss
         re = rs + rlen
         se = ss + slen

flatRanges :: [[Range]] -> ([Range], [Range])
flatRanges rrs = (filter notMapped rs, filter hasMapped rs)
   where hasMapped = (\(Range _ _ mapped) -> mapped)
         notMapped = (\(Range _ _ mapped) -> not mapped)
         rs = concat rrs

applyMaps :: [PlantMap] -> [Range] -> [Range]
applyMaps _ [] = []
applyMaps [] rs = rs
applyMaps (pm:pms) rs = let newRs = flatRanges $ map (applyMap pm) rs
   in applyMaps pms (fst newRs) ++ snd newRs

toMap :: String -> PlantMap
toMap s = PlantMap (nums !! 0) (nums !! 1) (nums !! 2)
   where nums = map read (words s)

toRanges :: [String] -> [Range]
toRanges [] = []
toRanges [_] = []
toRanges (x:y:xs) = (Range (read x) (read y) False):(toRanges xs)

getMaps :: [String] -> [[PlantMap]]
getMaps ms = helper maps [] []
   where maps = filter (\x -> length x == 0 || last x /= ':') (drop 2 ms)
         helper [] acc1 acc2 = acc1 ++ [acc2]
         helper (m:ms) acc1 acc2
            | length m == 0 = helper ms (acc1 ++ [acc2]) []
            | otherwise     = helper ms acc1 (acc2 ++ [toMap m])

applyAllMaps :: [Range] -> [[PlantMap]] -> [Range]
applyAllMaps = foldl (flip applyMaps)

solution :: String -> String
solution x = show $ minimum $ map (\(Range ss _ _) -> ss) (applyAllMaps seeds (getMaps l))
    where l = lines x
          seeds = toRanges (tail $ words (l !! 0))

main = do
       file <- readFile "../inputs/2023/day05-input.txt"
       putStrLn $ solution file