#pragma once

#include <vector>

#include "Span.h"
#include "Vertex.h"

struct Graph {
    std::vector<Vertex> vertices;

    Graph(size_t V): vertices(V) {}

    void add_edge(size_t u, size_t v) {
        vertices[u].add_neighbor(v);
        vertices[v].add_neighbor(u);
    }

    void add_edges(Span<size_t> u, Span<size_t> v) {
        // TODO: optimize
        for (size_t i = 0; i < u.size(); i++) {
            add_edge(u[i], v[i]);
        }
    }

    void remove_edge(size_t u, size_t v) {
        vertices[u].remove_neighbor(v);
        vertices[v].remove_neighbor(u);
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
};
