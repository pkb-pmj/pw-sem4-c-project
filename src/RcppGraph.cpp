#include <Rcpp.h>

#include <string>
#include <vector>

#include "GraphDW.h"
#include "Span.h"

using namespace Rcpp;

// [[Rcpp::export]]
SEXP new_graph(IntegerVector num_vertices) {
    return XPtr(new GraphDW<double>(num_vertices[0]));
}

// [[Rcpp::export]]
SEXP from_adj_list(List list) {
    size_t n = list.size();
    XPtr<GraphDW<double>> g(new GraphDW<double>(n));
    for (size_t from = 0; from < n; from++) {
        NumericVector weights = list[from];
        CharacterVector names = weights.names();
        for (size_t j = 0; j < weights.size(); j++) {
            size_t to = stoi(names[j].begin()) - 1;
            g->add_edge(from, to, weights[j]);
        }
    }
    return g;
}

// [[Rcpp::export]]
SEXP from_edge_list(DataFrame df, IntegerVector num_vertices) {
    IntegerVector from = df["from"];
    IntegerVector to = df["to"];
    NumericVector weights = df["weight"];

    XPtr<GraphDW<double>> g(new GraphDW<double>(num_vertices[0]));

    for (size_t i = 0; i < from.size(); i++) {
        g->add_edge(from[i] - 1, to[i] - 1, weights[i]);
    }

    return g;
}

// [[Rcpp::export]]
SEXP from_adj_matrix(NumericMatrix matrix) {
    size_t n = matrix.nrow();
    XPtr<GraphDW<double>> g(new GraphDW<double>(n));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            double weight = matrix[i + j * n];
            if (weight > 0)
                g->add_edge(i, j, weight);
        }
    }
    return g;
}

// [[Rcpp::export]]
void add_edges(SEXP sexp, IntegerVector from, IntegerVector to, NumericVector weights) {
    XPtr<GraphDW<double>> g(sexp);

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
    XPtr<GraphDW<double>> g(sexp);
    return List::import_transform(
        g->get_all_vertices().begin(),
        g->get_all_vertices().end(),
        [](VertexDW<double> vertex) {
            auto weights = NumericVector::import_transform(
                vertex.get_all_edges().begin(),
                vertex.get_all_edges().end(),
                [](EdgeDW<double> edge) {
                    return edge.weight;
                }
            );
            weights.names() = CharacterVector::import_transform(
                vertex.get_all_edges().begin(),
                vertex.get_all_edges().end(),
                [](EdgeDW<double> edge) {
                    return std::to_string(edge.to + 1);
                }
            );
            return weights;
        }
    );
}

// [[Rcpp::export]]
DataFrame as_edge_list(SEXP sexp) {
    XPtr<GraphDW<double>> g(sexp);

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

// [[Rcpp::export]]
NumericMatrix as_adj_matrix(SEXP sexp) {
    XPtr<GraphDW<double>> g(sexp);

    size_t n = g->num_vertices();
    NumericMatrix m = NumericMatrix::zeros(n);

    auto& vertices = g->get_all_vertices();
    for (size_t i = 0; i < n; i++) {
        auto& vertex = vertices[i];
        for (auto& edge : vertex.get_all_edges()) {
            m(i, edge.to) += edge.weight;
        }
    }

    return m;
}
