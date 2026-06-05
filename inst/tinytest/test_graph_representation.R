library(tinytest)
library(graphs)

g <- new_graph_dw(10)

from <- 1:9
to <- 2:10
weights <- runif(9)

add_edges_dw(g, from, to, weights)

adj_list <- as.list(weights)
for (i in seq_along(adj_list)) {
  names(adj_list[[i]]) <- to[i]
}
adj_list[[10]] <- numeric()
names(adj_list[[10]]) <- character()

edge_list <- data.frame(from = from, to = to, weight = weights)

adj_matrix <- matrix(0, nrow = 10, ncol = 10)
adj_matrix[cbind(from, to)] <- weights

expect_equal(as_edge_list_dw(g), edge_list)
expect_equal(as_adj_list_dw(g), adj_list)
expect_equal(as_adj_matrix_dw(g), adj_matrix)

expect_equal(as_edge_list_dw(from_edge_list_dw(edge_list, 10)), edge_list)
expect_equal(as_adj_list_dw(from_adj_list_dw(adj_list)), adj_list)
expect_equal(as_adj_matrix_dw(from_adj_matrix_dw(adj_matrix)), adj_matrix)
