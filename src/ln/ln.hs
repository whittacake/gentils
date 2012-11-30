module Main(main) where
import System.Environment (getArgs)
import System.Console.GetOpt
import System.Posix.Files (removeLink,
                           createLink,
                           createSymbolicLink)
import Control.Monad (when)

data Options = Options { force      :: Bool,
                         symbolic   :: Bool,
                         source     :: [FilePath],
                         target     :: FilePath }
                deriving (Show)

defaultOptions :: Options
defaultOptions = Options {
                        force    = False,
                        symbolic = False,
                        source   = [],
                        target   = [] 
                 }

options :: [ OptDescr (Options -> Options) ]
options =
    [ Option "f" [] (NoArg (\opts -> opts { force = True }))
        "Unlink any already existing file, permitting the link to occur.",
      Option "s" [] (NoArg (\opts -> opts { symbolic = True }))
        "Create a symbolic link."
    ]

nonoptions :: Options -> [String] -> Options
nonoptions opts (x:[]) = opts { source = [x], target = x }
nonoptions opts (x:y:[]) = opts { source = [x], target = y }
nonoptions _ _ = usage

usage = error "usage: ln [-fs] source target"

start opts = do when (force opts) $ removeLink $ target opts
                (if symbolic opts
                    then createSymbolicLink
                    else createLink) (head $ source opts) (target opts)

main :: IO ()
main = do
    args <- getArgs
    
    let (actions, nonOptions, errors) = getOpt RequireOrder options args
    let opts = foldl (flip id) defaultOptions actions
    start $ nonoptions opts nonOptions
