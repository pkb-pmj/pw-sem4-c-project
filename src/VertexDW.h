#pragma once

#include <vector>

#include "EdgeDW.h"
#include "Span.h"

using namespace std;

template<typename W>
class VertexDW {
  private:
    vector<EdgeDW<W>> edge_vector;

  public:
    VertexDW() {};

    void add_edge(size_t to, W weight) {
        edge_vector.push_back({ to, weight });
    }

    void add_edges(Span<EdgeDW<W>> edges) {
        edge_vector.insert(edge_vector.end(), edges.begin(), edges.end());
    }

    EdgeDW<W>* get_edge_to(size_t to) {
        for (auto& edge : edge_vector)
            if (edge.to == to)
                return &edge;
        return nullptr;
    }

    const size_t num_edges() const {
        return edge_vector.size();
    }

    const vector<EdgeDW<W>>& get_all_edges() const {
        return edge_vector;
    }
};
