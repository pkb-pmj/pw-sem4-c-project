#include "Graph.h"
#include "triangle_count.h"

void Graph::enable_triangle_count(bool enable) {
    if (enable && !_triangle_count_en)
        _triangle_count = triangle_count_intersect(*this);
    _triangle_count_en = enable;
}
