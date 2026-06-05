library(tinytest)
library(graphs)

g <- new_graph(10)

from <- 1:9
to <- 2:10
weights <- runif(9)

add_edges(g, from, to, weights)

adj_list <- as.list(weights)
for (i in seq_along(adj_list)) {
  names(adj_list[[i]]) <- to[i]
}
adj_list[[10]] <- numeric()
names(adj_list[[10]]) <- character()

edge_list <- data.frame(from = from, to = to, weight = weights)

adj_matrix <- matrix(0, nrow = 10, ncol = 10)
adj_matrix[cbind(from, to)] <- weights

expect_equal(as_edge_list(g), edge_list)
expect_equal(as_adj_list(g), adj_list)
expect_equal(as_adj_matrix(g), adj_matrix)

expect_equal(as_edge_list(from_edge_list(edge_list, 10)), edge_list)
expect_equal(as_adj_list(from_adj_list(adj_list)), adj_list)
expect_equal(as_adj_matrix(from_adj_matrix(adj_matrix)), adj_matrix)
