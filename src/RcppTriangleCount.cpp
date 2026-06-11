#include <Rcpp.h>

#include "triangle_count.h"

using namespace Rcpp;

//' Counts triangles (cycles of length 3) in an undirected, unweighted graph
//'
//' @param sexp The graph object, created using `new_graph` or any of the `from_*` functions
//' @param method The algorithm used to count triangles: \itemize{
//' \item "brute" - for each edge (u, v) count how many neighbors of u are also neighbors of v, O(E * V * log(V)).
//' \item "intersect" - for each edge (u, v) count the size of the intersection of their sets of neighbors, O(E * V).
//' \item "online" - use the online algorithm, incrementally updating after every edge addition/removal.
//'     If enable_online_triangle_count(sexp, TRUE) wasn't called manually, this function will do it,
//'     computing triangle count using the offline "intersect" algorithm - so if you want maximum performance
//'     from the first call of triangle_count(sexp, "online"), call enable_online_triangle_count(sexp, TRUE)
//'     manually beforehand.
//' \item NA - uses online triangle counting if it was enabled, or "intersect" otherwise.
//' }
//' @returns Number of unique triangles (cycles of length 3) in the graph
// [[Rcpp::export]]
int triangle_count(SEXP sexp, String method = NA_STRING) {
    XPtr<Graph> g(sexp);

    if (method == NA_STRING && g->_triangle_count_en)
        return g->triangle_count();
    else if (method == "online") {
        g->enable_triangle_count(true);
        return g->triangle_count();
    } else if (method == "brute")
        return triangle_count_brute(*g);
    else if(method == "intersect" || method == NA_STRING)
        return triangle_count_intersect(*g);
    else
        stop("method must be one of \"brute\", \"intersect\", \"online\" or NA");
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
