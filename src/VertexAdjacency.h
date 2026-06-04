#pragma once

#include <vector>

#include "DirectedEdge.h"
#include "Span.h"

using namespace std;

template<typename W>
class VertexAdjacency {
  private:
    vector<DirectedEdge<W>> edge_vector;

  public:
    VertexAdjacency() {};

    void add_edge(size_t to, W weight) {
        edge_vector.push_back({ to, weight });
    }

    void add_edges(Span<DirectedEdge<W>> edges) {
        edge_vector.insert(edge_vector.end(), edges.begin(), edges.end());
    }

    DirectedEdge<W>* get_edge_to(size_t to) {
        for (auto& edge : edge_vector)
            if (edge.to == to)
                return &edge;
        return nullptr;
    }

    const vector<DirectedEdge<W>>& get_all_edges() const {
        return edge_vector;
    }
};
