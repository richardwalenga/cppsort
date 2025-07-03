#include "selection.h"
#include "common.h"

template <typename T>
void SelectionSorter<T>::sort(std::span<T> ary) const
{
    int count = ary.size();
    if (count < 2)
    {
        return;
    }
    
    for (int i = 0; i < (count - 1); ++i)
    {
        int min_idx = i;
        for (int j = i + 1; j < count; ++j)
        {
            if (ary[min_idx] > ary[j])
            {
                min_idx = j;
            }
        }
        if (i != min_idx)
        {
            this->swap_values(ary, i, min_idx);
        }
    }
}

template class SelectionSorter<int>;