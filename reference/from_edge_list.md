# Creates an undirected, unweighted graph from an edgelist.

Creates an undirected, unweighted graph from an edgelist.

## Usage

``` r
from_edge_list(df, V)
```

## Arguments

- df:

  Edgelist dataframe, must have two columns: "from" and "to",
  representing the two vertices of each edge. Duplicated edges are
  silently ignored. Indexes outside of range (or NA) throw an error.

- V:

  Number of vertices, must be an integer vector of length 1.

## Value

Graph constructed from the edgelist.
