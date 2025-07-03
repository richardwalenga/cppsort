#include "insertion.h"
#include "common.h"

template <typename T>
void InsertionSorter<T>::sort(std::span<T> ary) const
{
    int count = ary.size();
    if (count < 2)
    {
        return;
    }
    
    for (int i = 1; i < count; ++i)
    {
        int j = i - 1;
        int old = ary[i];
        for (; j >= 0 && ary[j] > old; --j)
        {
            this->swap_values(ary, j, j+1);
        }
        bool shifted = j != i - 1;
        if (shifted)
        {
            /* Need to compensate for the last decrement of j
             * in the loop above */
            ary[j + 1] = old;
        }
    }
}

template class InsertionSorter<int>;