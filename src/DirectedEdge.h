#pragma once

#include <cstddef>

template<typename W>
struct EdgeDW {
    size_t to;
    W weight;
};
