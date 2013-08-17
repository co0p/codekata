# run like this: R -f reverse.R --args "word1 word2 word3"
paste0(rev(strsplit(commandArgs(trailingOnly = TRUE)," ",fixed=T)[[1]]),collapse=" ")