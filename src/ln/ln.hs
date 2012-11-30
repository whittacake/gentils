module Main(main) where
import System.Environment (getArgs)
import System.Console.GetOpt
import System.Posix.Files
import Control.Monad (when, void)

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
nonoptions opts xs = let (x:xs') = reverse xs in
                     opts { source = xs', target = x }

usage = error $ "usage: ln [-fs] source target\n" ++
                "\tln [-fs] source ... [directory]"

link :: Options -> FilePath -> FilePath -> IO ()
link opts src tgt = when (force opts) $ removeLink tgt >>
                    (if symbolic opts
                        then createSymbolicLink
                        else createLink) src tgt

multiLink :: Options -> IO ()
multiLink opts = do
            void $ mapM (go) (source opts)
            where go x = link opts x $ dir ++ "/" ++ x
                  dir = target opts

singleLink :: Options -> IO ()
singleLink opts = do link opts (head $ source opts) (target opts)

start :: Options -> IO ()
start opts = do st <- getFileStatus (target opts)
                if (isDirectory st)
                    then multiLink opts
                    else singleLink opts

main :: IO ()
main = do
    args <- getArgs
    
    let (actions, nonOptions, errors) = getOpt RequireOrder options args
    let opts = foldl (flip id) defaultOptions actions
    start $ nonoptions opts nonOptions
