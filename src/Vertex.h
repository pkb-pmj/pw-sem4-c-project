#pragma once

#include <algorithm>
#include <vector>

#include "Span.h"

struct Vertex {
    std::vector<size_t> neighbors;

    void add_neighbor(size_t v) {
        auto i = std::lower_bound(neighbors.begin(), neighbors.end(), v);
        if (i == neighbors.end() || *i != v)
            neighbors.insert(i, v);
    }

    void remove_neighbor(size_t v) {
        auto i = std::lower_bound(neighbors.begin(), neighbors.end(), v);
        if (i != neighbors.end() && *i == v)
            neighbors.erase(i);
    }

    void add_neighbors(const Span<size_t> v) {
        // TODO: implement merge instead
        neighbors.insert(neighbors.end(), v.begin(), v.end());
        sort(neighbors.begin(), neighbors.end());
    }

    void remove_neighbors(const Span<size_t> v) {
        // TODO: anything better than this lol, also using merge
        for (size_t i = 0; i < v.size(); i++)
            remove_neighbor(v[i]);
    }

    bool has_neighbor(size_t v) const {
        return binary_search(neighbors.begin(), neighbors.end(), v);
    }

    size_t num_neighbors() const {
        return neighbors.size();
    }
};
