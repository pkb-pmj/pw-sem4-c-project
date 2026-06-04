#pragma once

#include <vector>

#include "Span.h"
#include "VertexAdjacency.h"

using namespace std;

template<typename W>
class GraphAdjacency {
  private:
    vector<VertexAdjacency<W>> vertices;

  public:
    GraphAdjacency(size_t num_vertices) {
        vertices = vector<VertexAdjacency<W>>(num_vertices);
    }

    void add_edge(size_t from, size_t to, W weight) {
        vertices[from].add_edge(to, weight);
    }

    void add_edges(Span<size_t> from, Span<size_t> to, Span<W> weights) {
        for (size_t i = 0; i < from.size(); i++)
            vertices[from[i]].add_edge(to[i], weights[i]);
    }

    DirectedEdge<W>* get_edge(size_t from, size_t to) {
        return vertices[from].get_edge_to(to);
    }

    const size_t num_vertices() const {
        return vertices.size();
    }

    const size_t num_edges() const {
        size_t n = 0;
        for (auto& vertex : vertices)
            n += vertex.num_edges();
        return n;
    }

    const vector<VertexAdjacency<W>>& get_all_vertices() {
        return vertices;
    }
};
