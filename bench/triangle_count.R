library(graphs)
library(igraph)
library(bench)
library(dplyr)
library(ggplot2)

ig <- igraph::sample_gnm(10000, 1000000, directed = FALSE)
g <- from_igraph(ig)
bench::mark(
  sum(igraph::count_triangles(ig) / 3),
  graphs::triangle_count(g, method = "brute"),
  graphs::triangle_count(g, method = "intersect")
)

results <- bench::press(
  mean_degree = c(4, 16, 64),
  V = c(100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100000),
  {
    E <- min(V * mean_degree, V * (V - 1) / 2)
    ig <- igraph::sample_gnm(V, E, directed = FALSE)
    g <- from_igraph(ig)
    bench::mark(
      igraph = sum(igraph::count_triangles(ig) / 3),
      brute = graphs::triangle_count(g, method = "brute"),
      intersect = graphs::triangle_count(g, method = "intersect")
    )
  }
)

results <- results %>%
  mutate(method = as.factor(attr(expression, "description")))

results %>%
  ggplot(aes(x = V, y = median, color = method)) +
  geom_line() +
  facet_wrap(vars(mean_degree)) +
  scale_x_log10()

results %>%
  ggplot(aes(x = mean_degree, y = median, color = method)) +
  geom_line() +
  facet_wrap(vars(V)) +
  scale_x_log10()
