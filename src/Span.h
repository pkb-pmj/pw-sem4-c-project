#pragma once

#include <cstddef>

template<typename T>
class Span {
  private:
    T* ptr;
    size_t n;

  public:
    Span(T* begin, T* end) {
        ptr = begin;
        n = end - begin;
    }

    Span(T* ptr, size_t size) {
        this->ptr = ptr;
        n = size;
    }

    template<class V>
    Span(V& v) {
        ptr = v.begin();
        n = v.end() - v.begin();
    }

    T* begin() const { return ptr; }
    T* end() const { return ptr + n; }

    size_t size() const { return n; }

    T& operator[](size_t i) const {
        return ptr[i];
    }
};
