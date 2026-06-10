# Creates an undirected, unweighted graph from an adjacency list.

Creates an undirected, unweighted graph from an adjacency list.

## Usage

``` r
from_adj_list(list)
```

## Arguments

- list:

  Adjacency list, represented as a list of integer vectors; k-th vector
  in the list represents the set of neighbors of vertex k. Neighbors
  might be in any order, edges can be specified from any one direction
  or both, duplicated edges will be silently ignored, leaving only a
  single one. Indexes outside of range (or NA) throw an error.

## Value

Graph constructed from the adjacency list.
