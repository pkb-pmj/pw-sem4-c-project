#' Creates graph from igraph object.
#'
#' @description Creates a graph object from an igraph object.
#'
#' Currently, internally uses igraph::as_edgelist and graphs::from_edge_list,
#' but that might change and shouldn't be relied upon.
#' @param ig igraph object
#' @returns Graph object created from the igraph.
from_igraph <- function(ig) {
  edge_list <- igraph::as_edgelist(ig)
  V <- max(edge_list)
  edge_list <- data.frame(edge_list)
  colnames(edge_list) <- c("from", "to")
  graphs::from_edge_list(edge_list, V)
}
