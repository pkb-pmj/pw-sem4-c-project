#include <Rcpp.h>

#include <vector>

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

    size_t n = from.size();

    std::vector<size_t> from0(n);
    std::vector<size_t> to0(n);
    for (size_t i = 0; i < n; i++) {
        from0[i] = from[i] - 1;
        to0[i] = to[i] - 1;
    }

    g->add_edges(Span<size_t>(from0), Span<size_t>(to0), Span<double>(weights));
}

// [[Rcpp::export]]
List as_adj_list(SEXP sexp) {
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

// [[Rcpp::export]]
DataFrame as_edge_list(SEXP sexp) {
    XPtr<GraphAdjacency<double>> g(sexp);

    vector<int> from1;
    vector<int> to1;
    vector<double> weights;

    auto& vertices = g->get_all_vertices();
    for (size_t i = 0; i < vertices.size(); i++) {
        auto& vertex = vertices[i];
        for (auto& edge : vertex.get_all_edges()) {
            from1.push_back(i + 1);
            to1.push_back(edge.to + 1);
            weights.push_back(edge.weight);
        }
    }

    return DataFrame::create(
        Named("from") = from1,
        Named("to") = to1,
        Named("weight") = weights
    );
}
