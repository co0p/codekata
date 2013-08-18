# run like this: R -f unique.R --args foo

uniq <- function(string) {
	any(duplicated(strsplit(string,"",fixed=T)[[1]]))
}

uniq(commandArgs(trailingOnly = TRUE))