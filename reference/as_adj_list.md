# Exports graph as an adjacency list.

Exports graph as an adjacency list.

## Usage

``` r
as_adj_list(sexp)
```

## Arguments

- sexp:

  Graph object.

## Value

Adjacency list - a list of integer vectors, where k-th vector represents
neighbors of vertex k. Every edge (u, v) will be included in both
directions, i.e. u will be included as neighbor of v, and v as neighbor
of u. The ordering of neighbors is guaranteed to be deterministic, and
will be the same for every created graph object with the same set of
vertices and edges. Also, in the current implementation neighbors of
every vertex are sorted in increasing order. This probably won't change,
but isn't guaranteed, so shouldn't be relied upon too much.
