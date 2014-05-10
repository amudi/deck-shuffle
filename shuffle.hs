import System.Environment
import Control.Monad.IO.Class (liftIO)

main :: IO ()
main = do
    args <- getArgs
    let decksize = read $ head args
    if null args || (decksize <= 0) then
        error "usage: shuffle <count>\n\ncount is size of deck (positive integer)"
    else liftIO $ print $ roundsuntilsame $ createdeck decksize

createdeck :: Int -> [Int]
createdeck n = [1..n]

oneround :: [Int] -> [Int]
oneround (x : y : xs) = oneround (xs ++ [y]) ++ [x]
oneround [x] = [x]
oneround _ = []

shuffle :: [Int] -> [Int] -> Int
shuffle deck ref = 
    if deck == ref
    then 0
    else 1 + shuffle (oneround deck) ref

roundsuntilsame :: [Int] -> Int
roundsuntilsame deck = 1 + shuffle (oneround deck) deck
