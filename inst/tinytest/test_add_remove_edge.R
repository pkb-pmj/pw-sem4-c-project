library(graphs)
library(tinytest)

m <- matrix(rep(0, 9), 3, 3)
g <- from_adj_matrix(m)
expect_equal(as_adj_matrix(g), m)

m[1, 2] <- 1
m[2, 1] <- 1
expect_equal(add_edge(g, 1, 2), TRUE)
expect_equal(as_adj_matrix(g), m)

expect_equal(add_edge(g, 1, 2), FALSE)
expect_equal(as_adj_matrix(g), m)

expect_equal(remove_edge(g, 1, 3), FALSE)
expect_equal(as_adj_matrix(g), m)

m <- matrix(rep(0, 9), 3, 3)
expect_equal(remove_edge(g, 1, 2), TRUE)
expect_equal(as_adj_matrix(g), m)

expect_error(add_edge(g, 0, 1), "0")
expect_error(add_edge(g, -1, 1), "-1")
expect_error(add_edge(g, 4, 1), "4")
expect_error(add_edge(g, NA, 1), "NA")

expect_error(remove_edge(g, 0, 1), "0")
expect_error(remove_edge(g, -1, 1), "-1")
expect_error(remove_edge(g, 4, 1), "4")
expect_error(remove_edge(g, NA, 1), "NA")
