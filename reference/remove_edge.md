# Remove edge from graph

Removes an edge between vertices (u, v) if it exists in the graph.

## Usage

``` r
remove_edge(sexp, u, v)
```

## Arguments

- sexp:

  Graph object.

- u:

  First vertex of the edge to be removed. Must be a valid vertex in the
  graph, and not NA.

- v:

  Second vertex of the edge to be removed. Must be a valid vertex in the
  graph, and not NA.

## Value

TRUE if the edge has been removed, FALSE if it didn't exist and so
couldn't be removed.
