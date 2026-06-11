#pragma once

#include <algorithm>
#include <vector>

#include "Span.h"

struct Vertex {
    std::vector<size_t> neighbors;

    bool add_neighbor(size_t v) {
        auto i = std::lower_bound(neighbors.begin(), neighbors.end(), v);
        if (i == neighbors.end() || *i != v) {
            neighbors.insert(i, v);
            return true;
        } else {
            return false;
        }
    }

    bool remove_neighbor(size_t v) {
        auto i = std::lower_bound(neighbors.begin(), neighbors.end(), v);
        if (i != neighbors.end() && *i == v) {
            neighbors.erase(i);
            return true;
        } else {
            return false;
        }
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

    size_t deg() const {
        return neighbors.size();
    }

    size_t& operator[](size_t v) {
        return neighbors[v];
    }

    size_t operator[](size_t v) const {
        return neighbors[v];
    }

    size_t* begin() { return neighbors.data(); }
    size_t* end() { return begin() + neighbors.size(); }

    const size_t* begin() const { return neighbors.data(); }
    const size_t* end() const { return begin() + neighbors.size(); }
};
