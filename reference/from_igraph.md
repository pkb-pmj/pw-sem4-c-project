# Creates graph from igraph object.

Creates a graph object from an igraph object.

Currently, internally uses igraph::as_edgelist and
graphs::from_edge_list, but that might change and shouldn't be relied
upon.

## Usage

``` r
from_igraph(ig)
```

## Arguments

- ig:

  igraph object

## Value

Graph object created from the igraph.
