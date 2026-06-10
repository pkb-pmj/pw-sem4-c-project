library(igraph)
library(graphs)

edgelists <- readRDS("bench/data/edgelists.rds")
metadata <- read.csv("bench/data/metadata.csv")

igraphs <- lapply(edgelists, graph_from_edgelist)
graphs <- lapply(igraphs, from_igraph)

results <- bench::press(
  name = metadata$name,
  bench::mark(
    igraph = sum(igraph::count_triangles(igraphs[[name]])) / 3,
    brute = graphs::triangle_count(graphs[[name]], method = "brute"),
    intersect = graphs::triangle_count(graphs[[name]], method = "intersect")
  )
)

commit <- system("git rev-parse --short HEAD", intern = TRUE)
commit_idx <- system("git rev-list --count HEAD", intern = TRUE)

filename <- paste0("bench/results/", format(Sys.time(), tz = "Z"), " sha", commit, ".rds")

results$commit_idx <- commit_idx
saveRDS(results, file = filename)
