library(igraph)
library(graphs)

edgelists <- readRDS("bench/data/edgelists.rds")
metadata <- read.csv("bench/data/metadata.csv")

igraphs <- lapply(edgelists, graph_from_edgelist)
graphs_brute <- lapply(igraphs, from_igraph)
graphs_intersect <- lapply(igraphs, from_igraph)
graphs_online <- lapply(igraphs, from_igraph)

edges <- lapply(metadata$name, function(name) {
  set.seed(2137)
  V <- metadata$vertices[metadata$name == name]
  lapply(seq(10), function(x) sample.int(V, 2))
})
names(edges) <- metadata$name

results <- bench::press(
  name = metadata$name,
  bench::mark(
    igraph = sapply(edges[[name]], function(edge) {
      igraphs[[name]] <- igraph::add_edges(igraphs[[name]], edge)
      sum(igraph::count_triangles(igraphs[[name]])) / 3
    }),
    brute = sapply(edges[[name]], function(edge) {
      graphs::add_edge(graphs_brute[[name]], edge[1], edge[2])
      graphs::triangle_count(graphs_brute[[name]], method = "brute")
    }),
    intersect = sapply(edges[[name]], function(edge) {
      graphs::add_edge(graphs_intersect[[name]], edge[1], edge[2])
      graphs::triangle_count(graphs_intersect[[name]], method = "intersect")
    }),
    online = {
      sapply(graphs_online, graphs::enable_triangle_count)
      sapply(edges[[name]], function(edge) {
        graphs::add_edge(graphs_online[[name]], edge[1], edge[2])
        graphs::triangle_count(graphs_online[[name]], method = "online")
      })
    },
    check = FALSE
  )
)

commit <- system("git rev-parse --short HEAD", intern = TRUE)
commit_idx <- system("git rev-list --count HEAD", intern = TRUE)

filename <- paste0("bench/results/", format(Sys.time(), tz = "Z"), " sha", commit, ".rds")

results$commit_idx <- commit_idx
saveRDS(results, file = filename)
