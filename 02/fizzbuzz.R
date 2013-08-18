n <- 1:100
res <- ifelse(n %% 3 == 0 & n%% 5 ==0,"fizzbuzz",ifelse(n %% 3 ==0,"fizz",ifelse(n %% 5 ==0,"buzz",n)))
print(res)