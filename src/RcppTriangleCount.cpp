#include <Rcpp.h>

#include "triangle_count_brute.h"

using namespace Rcpp;

// [[Rcpp::export(name = "triangle_count_brute")]]
int rcpp_triangle_count_brute(SEXP sexp) {
    XPtr<Graph> g(sexp);
    return triangle_count_brute(*g);
}
