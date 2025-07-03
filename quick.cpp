#include "quick.h"
#include "common.h"

template <typename T>
int QuickSorter<T>::partition(std::span<T> ary, int low, int high) const
{
    int pivot = ary[high];
    /* initialize the index below low because the index is guaranteed
     * to be incremented before the pivot is moved to its new home. */
    int new_pivot_index = low - 1;
    for (int i = low; i < high; ++i)
    {
        if (ary[i] <= pivot)
        {
            this->swap_values(ary, ++new_pivot_index, i);
        }
    }
    /* There will always be at least one swap call since if this is the
     * first time, it means every value checked is greater than the pivot. */
    this->swap_values(ary, ++new_pivot_index, high);
    return new_pivot_index;
}

template <typename T>
void QuickSorter<T>::sort_between_indexes(std::span<T> ary, int low, int high) const
{
    if (low < high)
    {
        int pivot_index = partition(ary, low, high);
        sort_between_indexes(ary, low, pivot_index-1);
        sort_between_indexes(ary, pivot_index+1, high);
    }
}

template <typename T>
void QuickSorter<T>::sort(std::span<T> ary) const
{
    sort_between_indexes(ary, 0, ary.size()-1);
}

template class QuickSorter<int>;