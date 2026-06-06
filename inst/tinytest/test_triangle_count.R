library(tinytest)
library(graphs)
library(igraph)

i <- seq(10, 300, 10)
set.seed(2137)
igraphs <- lapply(i, function(i) igraph::sample_gnm(i, as.integer(i**1.5), directed = FALSE))
my_graphs <- lapply(igraphs, from_igraph)

count_igraph <- sapply(igraphs, function(ig) sum(igraph::count_triangles(ig) / 3))
count_brute <- sapply(my_graphs, function(g) graphs::triangle_count(g, method = "brute"))
count_intersect <- sapply(my_graphs, function(g) graphs::triangle_count(g, method = "intersect"))
count_matrix <- sapply(my_graphs, function(g) {
  m <- graphs::as_adj_matrix(g)
  triangles_matrix <- sum(diag(m %*% m %*% m)) / 6
})

expect_equal(count_matrix, count_igraph)
expect_equal(count_brute, count_igraph)
expect_equal(count_intersect, count_igraph)
