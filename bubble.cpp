#include <functional>
#include "bubble.h"

template <typename T>
bool BubbleSorter<T>::ltr_sort(std::span<T> ary) const
{
    bool swapped = false;
    int count = ary.size();
    for (int i = 1; i < count; ++i)
    {
        if (ary[i - 1] > ary[i])
        {
            this->swap_values(ary, i - 1, i);
            swapped = true;
        }
    }
    return swapped;
}

template <typename T>
bool CocktailShakerSorter<T>::rtl_sort(std::span<T> ary) const
{
    int count = ary.size();
    bool swapped = false;
    for (int i = count - 1; i > 0; --i)
    {
        if (ary[i] < ary[i - 1])
        {
            this->swap_values(ary, i - 1, i);
            swapped = true;
        }
    }
    return swapped;
}

template <typename T>
void BubbleSorter<T>::sort(std::span<T> ary) const
{
    int count = ary.size();
    if (count < 2)
    {
        return;
    }

    while(ltr_sort(ary));
}

template <typename T>
void CocktailShakerSorter<T>::sort(std::span<T> ary) const
{
    int count = ary.size();
    if (count < 2)
    {
        return;
    }

    /* By applying a bitmask of 1 less than a power of 2, I can cleanly
    * alternate sorting left to right followed by right to left. */
    const int BITMASK = 1;
    // One can't put member functions directly in the array,
    // so use a lambda to wrap them.
    std::function<bool(std::span<T>)> cmp[2] = { 
        [this](std::span<T> ary) { return this->ltr_sort(ary); }, 
        [this](std::span<T> ary) { return rtl_sort(ary); } 
    };
    int i = 0;
    while (true)
    {
        if (!cmp[i](ary))
        {
            break;
        }
        i = (i + 1) & BITMASK;
    }
}

template class BubbleSorter<int>;
template class CocktailShakerSorter<int>;