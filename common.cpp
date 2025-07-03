#include "common.h"

template <typename T>
void Sorter<T>::swap_values(std::span<T> ary, int x, int y) const
{
    if (x == y)
    {
        return;
    }
    int temp = ary[x];
    ary[x] = ary[y];
    ary[y] = temp;
}

template <typename T>
const char * Sorter<T>::name() const
{
    return name_;
}

template class Sorter<int>;
