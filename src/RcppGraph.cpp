#include <Rcpp.h>

#include <vector>

#include "Graph.h"

using namespace Rcpp;


//' Creates an undirected, unweighted graph with the provided number of vertices.
//'
//' @param V Number of vertices, must be an integer vector of length 1.
//' @returns Graph object with the provided number of vertices and no edges.
// [[Rcpp::export]]
SEXP new_graph(int V) {
    return XPtr(new Graph(V));
}

//' Creates an undirected, unweighted graph from an edgelist.
//'
//' @param df Edgelist dataframe, must have two columns: "from" and "to", representing the two vertices of each edge.
//' Duplicated edges are silently ignored. Indexes outside of range (or NA) throw an error.
//' @param V Number of vertices, must be an integer vector of length 1.
//' @returns Graph constructed from the edgelist.
// [[Rcpp::export]]
SEXP from_edge_list(DataFrame df, int V) {
    XPtr<Graph> g(new Graph(V));

    IntegerVector from1 = df["from"];
    IntegerVector to1 = df["to"];

    for (size_t i = 0; i < from1.size(); i++) {
        if (from1[i] == NA_INTEGER)
            stop("invalid vertex index NA at df$from[%d]", i + 1);
        if (from1[i] < 1 || from1[i] > V)
            stop("invalid vertex index %d at df$from[%d]", from1[i], i + 1);
    }
    for (size_t i = 0; i < to1.size(); i++) {
        if (to1[i] == NA_INTEGER)
            stop("invalid vertex index NA at df$to[%d]", i + 1);
        if (to1[i] < 1 || to1[i] > V)
            stop("invalid vertex index %d at df$to[%d]", to1[i], i + 1);
    }

    for (size_t i = 0; i < from1.size(); i++) {
        g->add_edge(from1[i] - 1, to1[i] - 1);
    }
    
    return g;
}

//' Creates an undirected, unweighted graph from an adjacency list.
//'
//' @param list Adjacency list, represented as a list of integer vectors;
//' k-th vector in the list represents the set of neighbors of vertex k.
//' Neighbors might be in any order, edges can be specified from any one direction or both,
//' duplicated edges will be silently ignored, leaving only a single one.
//' Indexes outside of range (or NA) throw an error.
//' @returns Graph constructed from the adjacency list.
// [[Rcpp::export]]
SEXP from_adj_list(List list) {
    size_t V = list.size();
    XPtr<Graph> g(new Graph(V));

    for (size_t u = 0; u < V; u++) {
        IntegerVector neighbors = list[u];
        for (size_t i = 0; i < neighbors.size(); i++) {
            if (neighbors[i] == NA_INTEGER)
                stop("invalid vertex index NA at list[[%d]][%d]", u + 1, i + 1);
            if (neighbors[i] < 1 || neighbors[i] > V)
                stop("invalid vertex index %d at list[[%d]][%d]", neighbors[i], u + 1, i + 1);
        }
    }

    for (size_t u = 0; u < V; u++) {
        IntegerVector neighbors = list[u];
        for (auto v : neighbors) {
            g->add_edge(u, v - 1);
        }
    }

    return g;
}

//' Creates an undirected, unweighted graph from an adjacency matrix.
//'
//' @param matrix Adjacency matrix. A nonzero element at position (i, j) represent an edge between vertices (i, j).
//' Must be square obviously, and symmetric. NA elements will throw an error.
//' @returns Graph constructed from the adjacency matrix.
// [[Rcpp::export]]
SEXP from_adj_matrix(IntegerMatrix matrix) {
    if (matrix.nrow() != matrix.ncol())
        stop("matrix must be square");

    size_t V = matrix.nrow();

    for (size_t i = 0; i < V; i++) {
        for (size_t j = i; j < V; j++) {
            if (matrix[i + j * V] == NA_INTEGER || matrix[j + i * V] == NA_INTEGER)
                stop("matrix must not contain NA");
            if ((matrix[i + j * V] == 0) != (matrix[j + i * V] == 0))
                stop("matrix must be symmetric");
        }
    }
    
    XPtr<Graph> g(new Graph(V));

    for (size_t i = 0; i < V; i++) {
        for (size_t j = i; j < V; j++) {
            if (matrix[i + j * V])
                g->add_edge(i, j);
        }
    }

    return g;
}

//' Exports graph as edgelist.
//'
//' @param sexp Graph object.
//' @returns Edgelist - data frame with two columns: "from" and "to",
//' representing two endpoints of every edge.
//' Every edge (u, v) is only included once, in order u < v.
//' The ordering of edges is guaranteed to be deterministic,
//' and will be the same for every created graph object with the same set of vertices and edges.
//' Also, in the current implementation edges are sorted first by v and then by u,
//' but this specific ordering definitely shouldn't be relied upon and might change in the future.
// [[Rcpp::export]]
DataFrame as_edge_list(SEXP sexp) {
    XPtr<Graph> g(sexp);

    vector<int> from1;
    vector<int> to1;

    for (size_t u = 0; u < g->vertices.size(); u++) {
        for (auto v : g->vertices[u].neighbors) {
            // avoid double edges, neighbors are sorted
            // loops, if allowed, will only be encountered once anyway, so don't need special handling
            if (u < v) break;
            // this way we get edges (u, v) where u <= v
            from1.push_back(v + 1);
            to1.push_back(u + 1);
        }
    }

    return DataFrame::create(
        Named("from") = from1,
        Named("to") = to1
    );
}

//' Exports graph as an adjacency list.
//'
//' @param sexp Graph object.
//' @returns Adjacency list - a list of integer vectors, where k-th vector represents neighbors of vertex k.
//' Every edge (u, v) will be included in both directions,
//' i.e. u will be included as neighbor of v, and v as neighbor of u.
//' The ordering of neighbors is guaranteed to be deterministic,
//' and will be the same for every created graph object with the same set of vertices and edges.
//' Also, in the current implementation neighbors of every vertex are sorted in increasing order.
//' This probably won't change, but isn't guaranteed, so shouldn't be relied upon too much.
// [[Rcpp::export]]
List as_adj_list(SEXP sexp) {
    XPtr<Graph> g(sexp);

    return List::import_transform(
        g->vertices.begin(),
        g->vertices.end(),
        [](Vertex u) {
            return IntegerVector::import_transform(
                u.neighbors.begin(),
                u.neighbors.end(),
                [](size_t v) {
                    return v + 1;
                }
            );
        }
    );
}


//' Exports graph as an adjacency matrix.
//' @param sexp Graph object.
//' @returns Adjacency matrix - a numeric matrix of size (V, V),
//' where V is the number of vertices. Element (i, j) will be set to 1
//' if there's an edge between vertices i, j and 0 if there isn't.
//' The matrix is of course square and symmetric.
// [[Rcpp::export]]
NumericMatrix as_adj_matrix(SEXP sexp) {
    XPtr<Graph> g(sexp);

    size_t V = g->V();
    NumericMatrix m = NumericMatrix::zeros(V);

    for (size_t u = 0; u < V; u++) {
        for (auto v : g->vertices[u].neighbors) {
            m(u, v) = 1;
        }
    }

    return m;
}

//' Add edge to graph
//' @description Adds an edge between vertices (u, v) if it doesn't already exist in the graph.
//' @param sexp Graph object.
//' @param u, v Vertices between which an edge will be added. Must be valid vertices in the graph, and not NA.
//' @returns TRUE if the edge has been added, FALSE if it already existed and hasn't been added.
// [[Rcpp::export]]
bool add_edge(SEXP sexp, int u, int v) {
    XPtr<Graph> g(sexp);

    if (u == NA_INTEGER)
        stop("invalid vertex u: NA");
    if (u < 1 || u > g->V())
        stop("invalid vertex u: %d", u);
    if (v == NA_INTEGER)
        stop("invalid vertex v: NA");
    if (v < 1 || v > g->V())
        stop("invalid vertex v: %d", v);

    return g->add_edge(u - 1, v - 1);
}

//' Remove edge from graph
//' @description Removes an edge between vertices (u, v) if it exists in the graph.
//' @param sexp Graph object.
//' @param u, v Vertices connected by the edge which will be removed. Must be valid vertices in the graph, and not NA.
//' @returns TRUE if the edge has been removed, FALSE if it didn't exist and so couldn't be removed.
// [[Rcpp::export]]
bool remove_edge(SEXP sexp, int u, int v) {
    XPtr<Graph> g(sexp);

    if (u == NA_INTEGER)
        stop("invalid vertex u: NA");
    if (u < 1 || u > g->V())
        stop("invalid vertex u: %d", u);
    if (v == NA_INTEGER)
        stop("invalid vertex v: NA");
    if (v < 1 || v > g->V())
        stop("invalid vertex v: %d", v);

    return g->remove_edge(u - 1, v - 1);
}
