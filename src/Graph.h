#pragma once

#include <vector>

#include "Span.h"
#include "Vertex.h"
#include "triangle_count_internal.h"

struct Graph {
    std::vector<Vertex> vertices;
    size_t _triangle_count;
    bool _triangle_count_en;

    Graph(size_t V): vertices(V) {
        _triangle_count = 0;
        _triangle_count_en = false;
    }

    void enable_triangle_count(bool enable);

    bool add_edge(size_t u, size_t v) {
        if (vertices[u].add_neighbor(v)) {
            vertices[v].add_neighbor(u);
            if (_triangle_count_en)
                _triangle_count += intersect_count(vertices[u], vertices[v], u < v ? u : v);
            return true;
        } else {
            return false;
        }
    }

    void add_edges(Span<size_t> u, Span<size_t> v) {
        // TODO: optimize
        for (size_t i = 0; i < u.size(); i++) {
            add_edge(u[i], v[i]);
        }
    }

    bool remove_edge(size_t u, size_t v) {
        if (vertices[u].remove_neighbor(v)) {
            vertices[v].remove_neighbor(u);
            if (_triangle_count_en)
                _triangle_count -= intersect_count(vertices[u], vertices[v], u < v ? u : v);
            return true;
        } else {
            return false;
        }
    }

    void remove_edges(Span<size_t> u, Span<size_t> v) {
        for (size_t i = 0; i < u.size(); i++) {
            remove_edge(u[i], v[i]);
        }
    }

    bool has_edge(size_t u, size_t v) const {
        return vertices[u].has_neighbor(v);
    }

    size_t V() const {
        return vertices.size();
    }

    size_t E() const {
        size_t e = 0;
        for (auto& v : vertices)
            e += v.deg();
        return e / 2;
    }

    Vertex& operator[](size_t u) {
        return vertices[u];
    }

    const Vertex& operator[](size_t u) const {
        return vertices[u];
    }

    size_t triangle_count() const {
        return _triangle_count;
    }
};
