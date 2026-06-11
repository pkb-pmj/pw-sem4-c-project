#ifdef _OPENMP
#include <omp.h>
#endif

#include "Span.h"

#include "triangle_count.h"
#include "triangle_count_internal.h"

size_t triangle_count_brute(const Graph& g) {
    size_t count = 0;

    // O(E * deg(v) * log(deg(w))) -> O(E * V * log(V))
    #ifdef _OPENMP
    #pragma omp parallel for schedule(dynamic) reduction(+:count)
    #endif
    for (size_t u = 0; u < g.V(); u++) {
        for (auto v : g[u]) {
            // only count each edge once, in order u > v
            if (v >= u) break;

            for (auto w : g[v]) {
                // only count each triangle once, in order u > v > w
                if (w >= v) break;
                if (g[w].has_neighbor(u)) count++;
            }
        }
    }

    return count;
}

size_t intersect_count(const Span<const size_t>u, const Span<const size_t> v, size_t max_w) {
    size_t i = 0;
    size_t j = 0;
    size_t count = 0;
    while (i < u.size() && j < v.size()) {
        if (u[i] >= max_w || v[j] >= max_w) break;
        else if (u[i] == v[j]) {
            count++;
            i++;
            j++;
        }
        else if (u[i] < v[j]) i++;
        else j++;
    }
    return count;
}

size_t triangle_count_intersect(const Graph& g) {
    size_t count = 0;

    // O(E * max(deg(u), deg(v))) -> O(E * V)
    #ifdef _OPENMP
    #pragma omp parallel for schedule(dynamic) reduction(+:count)
    #endif
    for (size_t u = 0; u < g.V(); u++) {
        for (auto v : g[u]) {
            // only count each edge once, in order u > v
            if (v >= u) break;
            // only count each triangle once, in order u > v > w
            count += intersect_count(g[u], g[v], v);
        }
    }

    return count;
}
