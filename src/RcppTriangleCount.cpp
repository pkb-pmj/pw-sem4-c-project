#include <Rcpp.h>

#include "triangle_count.h"

using namespace Rcpp;

//' Counts triangles (cycles of length 3) in an undirected, unweighted graph
//'
//' @param sexp The graph object, created using `new_graph` or any of the `from_*` functions
//' @param method The algorithm used to count triangles: \itemize{
//' \item brute - for each edge (u, v) count how many neighbors of u are also neighbors of v, O(E * V * log(V))
//' \item intersect - for each edge (u, v) count the size of the intersection of their sets of neighbors, O(E * V)
//' }
//' @returns Number of unique triangles (cycles of length 3) in the graph
// [[Rcpp::export]]
int triangle_count(SEXP sexp, String method) {
    XPtr<Graph> g(sexp);

    if (method == "brute")
        return triangle_count_brute(*g);
    else if(method == "intersect")
        return triangle_count_intersect(*g);
    else
        stop("method must be one of \"brute\", \"intersect\"");
}

//' Enable/disable online triangle counting
//' @description Enables or disables optimized online triangle counting for the provided graph object.
//' When enabled, computes initial triangle count using an offline algorithm (the same as triangle_count(method = "intersect")).
//' Enabling when already enabled or disabling when already disabled does nothing.
//' @param sexp Graph object.
//' @param enable Whether to enable (TRUE) or disable (FALSE) online triangle counting.
// [[Rcpp::export]]
void enable_triangle_count(SEXP sexp, bool enable = true) {
    XPtr<Graph> g(sexp);
    g->enable_triangle_count(enable);
}
