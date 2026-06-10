# Creates an undirected, unweighted graph from an adjacency matrix.

Creates an undirected, unweighted graph from an adjacency matrix.

## Usage

``` r
from_adj_matrix(matrix)
```

## Arguments

- matrix:

  Adjacency matrix. A nonzero element at position (i, j) represent an
  edge between vertices (i, j). Must be square obviously, and symmetric.
  NA elements will throw an error.

## Value

Graph constructed from the adjacency matrix.
