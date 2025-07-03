#include <span>
#include "merge.h"
#include "managed_dynamic_array.h"

template <typename T>
void MergeSorter<T>::sort(std::span<T> ary) const
{
    int count = ary.size();
    if (count < 10)
    {
        static_cast<const Sorter<T>&>(small_sorter_).sort(ary);
        return;
    }

    int mid_idx = count / 2;
    auto x = ManagedDynamicArray<T>::as_slice_from(ary, 0, mid_idx - 1);
    auto y = ManagedDynamicArray<T>::as_slice_from(ary, mid_idx, count - 1);
    auto x_span = x.to_span();
    auto y_span = y.to_span();
    int x_cnt = x_span.size();
    int y_cnt = y_span.size();
    int x_idx, y_idx;
    x_idx = y_idx = 0;

    sort(x_span);
    sort(y_span);
    for (int i = 0; i < count; ++i)
    {
        bool can_take_x = x_idx < x_cnt;
        bool can_take_y = y_idx < y_cnt;
        if (can_take_x && (!can_take_y || x_span[x_idx] <= y_span[y_idx]))
        {
            ary[i] = x_span[x_idx++];
        }
        else
        {
            ary[i] = y_span[y_idx++];
        }
    }
}

template class MergeSorter<int>;