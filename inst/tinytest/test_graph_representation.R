library(tinytest)
library(graphs)

V <- 10
from <- 1:9
to <- 2:10

edge_list <- data.frame(from = from, to = to)

adj_list <- lapply(1:9, function(x) c(x-1, x+1))
adj_list[[1]] <- c(2)
adj_list[[10]] <- c(9)

adj_matrix <- matrix(0, nrow = 10, ncol = 10)
adj_matrix[cbind(from, to)] <- 1
adj_matrix[cbind(to, from)] <- 1

expect_equal(as_edge_list(from_edge_list(edge_list, V)), edge_list)
expect_equal(as_adj_list(from_adj_list(adj_list)), adj_list)
expect_equal(as_adj_matrix(from_adj_matrix(adj_matrix)), adj_matrix)
