#pragma once

#include "Graph.h"

size_t triangle_count_brute(const Graph& g) {
    size_t count = 0;

    // O(E * deg(v) * log(deg(w))) -> O(E * V * log(V))
    for (size_t u = 0; u < g.V(); u++) {
        for (auto v : g.vertices[u].neighbors) {
            // only count each edge once, in order u > v
            if (v >= u) break;

            for (auto w : g.vertices[v].neighbors) {
                // only count each triangle once, in order u > v > w
                if (w >= v) break;
                if (g.vertices[w].has_neighbor(u)) count++;
            }
        }
    }

    return count;
}
