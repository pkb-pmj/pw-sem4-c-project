# Add edge to graph

Adds an edge between vertices (u, v) if it doesn't already exist in the
graph.

## Usage

``` r
add_edge(sexp, u, v)
```

## Arguments

- sexp:

  Graph object.

- u:

  First vertex of the edge to be added. Must be a valid vertex in the
  graph, and not NA.

- v:

  Second vertex of the edge to be added. Must be a valid vertex in the
  graph, and not NA.

## Value

TRUE if the edge has been added, FALSE if it already existed and hasn't
been added.
