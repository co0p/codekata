# run like this: R -f reverse_hannes.R --args foo
paste0(rev(strsplit(commandArgs(trailingOnly = TRUE),"",fixed=T)[[1]]),collapse="")