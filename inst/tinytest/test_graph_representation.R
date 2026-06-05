library(tinytest)
library(graphs)

expect_silent(new_graph(10))
expect_error(new_graph(c(1, 2)), pattern = "Expecting a single value")

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

expect_error(from_edge_list(data.frame(from = c("a"), to = c(1, 2)), 2), "Not compatible with requested type")
expect_silent(from_edge_list(data.frame(from = 1, to = 2), 2))
expect_silent(from_edge_list(data.frame(from = 2, to = 1), 2))
expect_error(from_edge_list(data.frame(from = 3, to = 1), 2), "invalid vertex index 3")
expect_error(from_edge_list(data.frame(from = 1, to = 3), 2), "invalid vertex index 3")
expect_error(from_edge_list(data.frame(from = 0, to = 1), 2), "invalid vertex index 0")
expect_error(from_edge_list(data.frame(from = 1, to = 0), 2), "invalid vertex index 0")
expect_error(from_edge_list(data.frame(from = -1, to = 1), 2), "invalid vertex index -1")
expect_error(from_edge_list(data.frame(from = 1, to = -1), 2), "invalid vertex index -1")
