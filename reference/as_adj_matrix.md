# Exports graph as an adjacency matrix.

Exports graph as an adjacency matrix.

## Usage

``` r
as_adj_matrix(sexp)
```

## Arguments

- sexp:

  Graph object.

## Value

Adjacency matrix - a numeric matrix of size (V, V), where V is the
number of vertices. Element (i, j) will be set to 1 if there's an edge
between vertices i, j and 0 if there isn't. The matrix is of course
square and symmetric.
