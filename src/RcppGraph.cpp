#include <Rcpp.h>

#include "GraphAdjacency.h"
#include "Span.h"

using namespace Rcpp;

// [[Rcpp::export]]
SEXP new_graph(IntegerVector num_vertices) {
    return XPtr(new GraphAdjacency<double>(num_vertices[0]));
}

// [[Rcpp::export]]
void add_edges(SEXP sexp, IntegerVector from, IntegerVector to, NumericVector weights) {
    XPtr<GraphAdjacency<double>> g(sexp);
    g->add_edges(Span<int>(from), Span<int>(to), Span<double>(weights));
}

// [[Rcpp::export]]
List get_adj_list(SEXP sexp) {
    XPtr<GraphAdjacency<double>> g(sexp);
    return List::import_transform(
        g->get_all_vertices().begin(),
        g->get_all_vertices().end(),
        [](VertexAdjacency<double> vertex) {
            return NumericVector::import_transform(
                vertex.get_all_edges().begin(),
                vertex.get_all_edges().end(),
                [](DirectedEdge<double> edge) {
                    return edge.to + 1;
                }
            );
        }
    );
}
