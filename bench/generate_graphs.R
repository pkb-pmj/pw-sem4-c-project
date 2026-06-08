library(igraph)

set.seed(2137)

igraphs <- list(
  gnm1 = sample_gnm(1e3, 4e3),
  gnm2 = sample_gnm(1e4, 8e4),
  gnm3 = sample_gnm(1e5, 16e5),
  
  pa1 = sample_pa(1e4, m = 4, directed = FALSE),
  pa2 = sample_pa(1e5, m = 8, directed = FALSE),
  pa3 = sample_pa(1e5, m = 16, directed = FALSE),
  
  smallworld1 = sample_smallworld(dim = 1, size = 10000, nei = 4, p = 0.05),
  smallworld2 = sample_smallworld(dim = 1, size = 10000, nei = 8, p = 0.05),
  smallworld3 = sample_smallworld(dim = 1, size = 10000, nei = 16, p = 0.05),
  
  lattice = make_lattice(c(1e3, 1e3)),
  full = make_full_graph(100),
  star = make_star(10000),
  full_bipartite = make_full_bipartite_graph(1000, 1000),
  ring = make_ring(10000)
)

edgelists <- lapply(igraphs, as_edgelist)

metadata <- data.frame(
  name = names(igraphs),
  vertices = sapply(igraphs, vcount),
  edges = sapply(igraphs, ecount),
  mean_degree = sapply(igraphs, mean_degree),
  max_degree = sapply(igraphs, max_degree)
)

saveRDS(edgelists, file = "bench/data/edgelists.rds")
write.csv(metadata, file = "bench/data/metadata.csv", row.names = FALSE)
