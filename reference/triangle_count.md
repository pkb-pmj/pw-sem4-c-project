# Counts triangles (cycles of length 3) in an undirected, unweighted graph

Counts triangles (cycles of length 3) in an undirected, unweighted graph

## Usage

``` r
triangle_count(sexp, method)
```

## Arguments

- sexp:

  The graph object, created using \`new_graph\` or any of the
  \`from\_\*\` functions

- method:

  The algorithm used to count triangles

  - brute - for each edge (u, v) count how many neighbors of u are also
    neighbors of v, O(E \* V \* log(V))

  - intersect - for each edge (u, v) count the size of the intersection
    of their sets of neighbors, O(E \* V)

## Value

Number of unique triangles (cycles of length 3) in the graph
