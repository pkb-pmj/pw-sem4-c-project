from_igraph <- function(ig) {
  edge_list <- igraph::as_edgelist(ig)
  V <- max(edge_list)
  edge_list <- data.frame(edge_list)
  colnames(edge_list) <- c("from", "to")
  graphs::from_edge_list(edge_list, V)
}
