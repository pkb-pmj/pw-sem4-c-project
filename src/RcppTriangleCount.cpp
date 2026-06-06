#include <Rcpp.h>

#include "triangle_count.h"

using namespace Rcpp;

// [[Rcpp::export]]
int triangle_count(SEXP sexp, String method) {
    XPtr<Graph> g(sexp);

    if (method == "brute")
        return triangle_count_brute(*g);
    else
        stop("method must be one of \"brute\"");
}
