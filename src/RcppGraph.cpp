#include <Rcpp.h>

#include <vector>

#include "Graph.h"

using namespace Rcpp;

// [[Rcpp::export]]
SEXP new_graph(int V) {
    return XPtr(new Graph(V));
}

// [[Rcpp::export]]
SEXP from_edge_list(DataFrame df, int V) {
    XPtr<Graph> g(new Graph(V));

    IntegerVector from1 = df["from"];
    IntegerVector to1 = df["to"];

    for (size_t i = 0; i < from1.size(); i++) {
        g->add_edge(from1[i] - 1, to1[i] - 1);
    }
    
    return g;
}

// [[Rcpp::export]]
SEXP from_adj_list(List list) {
    size_t V = list.size();
    XPtr<Graph> g(new Graph(V));

    for (size_t u = 0; u < V; u++) {
        IntegerVector neighbors = list[u];
        for (auto v : neighbors) {
            g->add_edge(u, v - 1);
        }
    }

    return g;
}

// [[Rcpp::export]]
SEXP from_adj_matrix(NumericMatrix matrix) {
    size_t V = matrix.nrow();
    XPtr<Graph> g(new Graph(V));

    for (size_t i = 0; i < V; i++) {
        for (size_t j = i; j < V; j++) {
            if (matrix[i + j * V])
                g->add_edge(i, j);
        }
    }

    return g;
}

// [[Rcpp::export]]
DataFrame as_edge_list(SEXP sexp) {
    XPtr<Graph> g(sexp);

    vector<int> from1;
    vector<int> to1;

    for (size_t u = 0; u < g->vertices.size(); u++) {
        for (auto v : g->vertices[u].neighbors) {
            // avoid double edges, neighbors are sorted
            // loops, if allowed, will only be encountered once anyway, so don't need special handling
            if (u < v) break;
            // this way we get edges (u, v) where u <= v
            from1.push_back(v + 1);
            to1.push_back(u + 1);
        }
    }

    return DataFrame::create(
        Named("from") = from1,
        Named("to") = to1
    );
}

// [[Rcpp::export]]
List as_adj_list(SEXP sexp) {
    XPtr<Graph> g(sexp);

    return List::import_transform(
        g->vertices.begin(),
        g->vertices.end(),
        [](Vertex u) {
            return IntegerVector::import_transform(
                u.neighbors.begin(),
                u.neighbors.end(),
                [](size_t v) {
                    return v + 1;
                }
            );
        }
    );
}

// [[Rcpp::export]]
NumericMatrix as_adj_matrix(SEXP sexp) {
    XPtr<Graph> g(sexp);

    size_t V = g->V();
    NumericMatrix m = NumericMatrix::zeros(V);

    for (size_t u = 0; u < V; u++) {
        for (auto v : g->vertices[u].neighbors) {
            m(u, v) = 1;
        }
    }

    return m;
}
