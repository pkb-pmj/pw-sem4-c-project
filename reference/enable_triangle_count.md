# Enable/disable online triangle counting

Enables or disables optimized online triangle counting for the provided
graph object. When enabled, computes initial triangle count using an
offline algorithm (the same as triangle_count(method = "intersect")).
Enabling when already enabled or disabling when already disabled does
nothing.

## Usage

``` r
enable_triangle_count(sexp, enable = TRUE)
```

## Arguments

- sexp:

  Graph object.

- enable:

  Whether to enable (TRUE) or disable (FALSE) online triangle counting.
