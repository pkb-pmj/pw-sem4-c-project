# Counts triangles (cycles of length 3) in an undirected, unweighted graph

Counts triangles (cycles of length 3) in an undirected, unweighted graph

## Usage

``` r
triangle_count(sexp, method = NA_character_)
```

## Arguments

- sexp:

  The graph object, created using \`new_graph\` or any of the
  \`from\_\*\` functions

- method:

  The algorithm used to count triangles:

  - "brute" - for each edge (u, v) count how many neighbors of u are
    also neighbors of v, O(E \* V \* log(V)).

  - "intersect" - for each edge (u, v) count the size of the
    intersection of their sets of neighbors, O(E \* V).

  - "online" - use the online algorithm, incrementally updating after
    every edge addition/removal. If enable_online_triangle_count(sexp,
    TRUE) wasn't called manually, this function will do it, computing
    triangle count using the offline "intersect" algorithm - so if you
    want maximum performance from the first call of triangle_count(sexp,
    "online"), call enable_online_triangle_count(sexp, TRUE) manually
    beforehand.

  - NA - uses online triangle counting if it was enabled, or "intersect"
    otherwise.

## Value

Number of unique triangles (cycles of length 3) in the graph
