#pragma once

#include <cstddef>

template<typename W>
struct DirectedEdge {
    size_t to;
    W weight;
};
