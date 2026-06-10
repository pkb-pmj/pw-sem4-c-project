# Exports graph as edgelist.

Exports graph as edgelist.

## Usage

``` r
as_edge_list(sexp)
```

## Arguments

- sexp:

  Graph object.

## Value

Edgelist - data frame with two columns: "from" and "to", representing
two endpoints of every edge. Every edge (u, v) is only included once, in
order u \< v. The ordering of edges is guaranteed to be deterministic,
and will be the same for every created graph object with the same set of
vertices and edges. Also, in the current implementation edges are sorted
first by v and then by u, but this specific ordering definitely
shouldn't be relied upon and might change in the future.
