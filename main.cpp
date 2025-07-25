#include <cassert>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "main.h"
#include "bubble.h"
#include "heap.h"
#include "insertion.h"
#include "managed_dynamic_array.h"
#include "merge.h"
#include "quick.h"
#include "selection.h"
#include "stopwatch.h"
#include <memory>

bool are_identical(std::span<const int> x, std::span<const int> y, int count)
{
    for (int i = 0; i < count; ++i)
    {
        if (x[i] != y[i])
        {
            return false;
        }
    }
    return true;
}

bool is_sorted(std::span<const int> ary, int count)
{
    for (int i = 0; i < (count - 1); ++i)
    {
        if (ary[i] > ary[i + 1])
        {
            return false;
        }
    }
    return true;
}

ManagedDynamicArray<int> get_randoms(int capacity, int max_exclusive)
{
    srand(time(NULL));
    ManagedDynamicArray<int> randoms(capacity);
    int i = capacity;
    while (i--)
    {
        randoms[i] = rand() % max_exclusive;
    }
    return randoms;
}

int main(int argc, char * argv[])
{
    const int PREDEF_CAPACITY = 200;
    const int RAND_CAPACITY = 20000;
    const int MAX_EXCLUSIVE = 100000;
    auto randoms = get_randoms(RAND_CAPACITY, MAX_EXCLUSIVE);
    ManagedDynamicArray<int> to_sort(RAND_CAPACITY); // Use const int[] to avoid error "taking address of temporary array"
    auto unsorted = (const int[]){10305, 17829, 2006, 4451, 9215, 29867, 11673, 15716, 32718, 14891, 6134, 17621, 12297, 20414, 25271, 25334, 15818, 14262, 19925, 5898, 9876, 28097, 14935, 13288, 18322, 19375, 28130, 9168, 21761, 19164, 16927, 6963, 21180, 16374, 18165, 15393, 8972, 31301, 1941, 28127, 22404, 16556, 6994, 23000, 10680, 6707, 14938, 9120, 5152, 22219, 15043, 28882, 30818, 7221, 26435, 26363, 27927, 12987, 10943, 32249, 9048, 5378, 23803, 29246, 27413, 23601, 11808, 27628, 31971, 17970, 3859, 15621, 20739, 19678, 9994, 9159, 24451, 8655, 16745, 608, 31720, 19106, 26200, 16238, 1186, 14332, 5711, 18243, 5650, 6100, 4968, 9291, 16037, 27575, 28820, 5035, 18778, 16429, 2725, 32380, 4206, 9696, 6048, 5530, 13907, 11605, 21674, 8736, 27896, 18199, 26215, 1776, 10198, 25176, 8557, 13935, 13824, 17930, 30904, 32677, 11320, 15187, 18866, 21894, 2470, 12264, 26935, 11968, 32201, 14663, 31118, 6569, 23023, 28606, 23429, 10691, 31989, 19764, 5124, 10520, 9142, 8328, 25968, 22589, 10386, 9134, 8554, 29413, 9762, 14193, 3492, 3100, 8650, 23945, 20117, 14553, 16372, 27419, 29540, 18921, 25667, 5374, 23250, 6878, 2564, 6727, 21135, 13237, 14318, 2433, 12979, 10268, 32671, 14523, 1389, 30897, 17119, 30645, 9873, 5664, 19810, 4520, 13484, 3515, 32388, 5288, 14028, 14089, 17832, 10087, 28487, 11920, -2636, 3936, -31316, 13306, 2069, 18239, 7416, 24140};
    auto sorted = (const int[]){-31316, -2636, 608, 1186, 1389, 1776, 1941, 2006, 2069, 2433, 2470, 2564, 2725, 3100, 3492, 3515, 3859, 3936, 4206, 4451, 4520, 4968, 5035, 5124, 5152, 5288, 5374, 5378, 5530, 5650, 5664, 5711, 5898, 6048, 6100, 6134, 6569, 6707, 6727, 6878, 6963, 6994, 7221, 7416, 8328, 8554, 8557, 8650, 8655, 8736, 8972, 9048, 9120, 9134, 9142, 9159, 9168, 9215, 9291, 9696, 9762, 9873, 9876, 9994, 10087, 10198, 10268, 10305, 10386, 10520, 10680, 10691, 10943, 11320, 11605, 11673, 11808, 11920, 11968, 12264, 12297, 12979, 12987, 13237, 13288, 13306, 13484, 13824, 13907, 13935, 14028, 14089, 14193, 14262, 14318, 14332, 14523, 14553, 14663, 14891, 14935, 14938, 15043, 15187, 15393, 15621, 15716, 15818, 16037, 16238, 16372, 16374, 16429, 16556, 16745, 16927, 17119, 17621, 17829, 17832, 17930, 17970, 18165, 18199, 18239, 18243, 18322, 18778, 18866, 18921, 19106, 19164, 19375, 19678, 19764, 19810, 19925, 20117, 20414, 20739, 21135, 21180, 21674, 21761, 21894, 22219, 22404, 22589, 23000, 23023, 23250, 23429, 23601, 23803, 23945, 24140, 24451, 25176, 25271, 25334, 25667, 25968, 26200, 26215, 26363, 26435, 26935, 27413, 27419, 27575, 27628, 27896, 27927, 28097, 28127, 28130, 28487, 28606, 28820, 28882, 29246, 29413, 29540, 29867, 30645, 30818, 30897, 30904, 31118, 31301, 31720, 31971, 31989, 32201, 32249, 32380, 32388, 32671, 32677, 32718};
    std::span<int> span_sorted((int*)sorted, PREDEF_CAPACITY);

    auto bubble_sorter = BubbleSorter<int>();
    auto cocktail_sorter = CocktailShakerSorter<int>();
    auto insertion_sorter = InsertionSorter<int>();
    auto selection_sorter = SelectionSorter<int>();
    auto heap_sorter = HeapSorter<int>();
    auto merge_sorter = MergeSorter<int>(insertion_sorter);
    auto quick_sorter = QuickSorter<int>();

    const int num_sorters = 7;
    Sorter<int> * sorters[num_sorters];
    sorters[0] = &bubble_sorter;
    sorters[1] = &cocktail_sorter;
    sorters[2] = &insertion_sorter;
    sorters[3] = &selection_sorter;
    sorters[3] = &selection_sorter;
    sorters[4] = &heap_sorter;
    sorters[5] = &merge_sorter;
    sorters[6] = &quick_sorter;
    for (int i = 0; i < num_sorters; ++i)
    {
        Sorter<int> * sorter = sorters[i];

        to_sort.copy_from(unsorted, PREDEF_CAPACITY);
        std::span<int> span_to_sort(to_sort.to_span(PREDEF_CAPACITY));
        sorter->sort(span_to_sort);
        bool identical = are_identical(span_to_sort, span_sorted, PREDEF_CAPACITY);
        std::cout << sorter->name() << " Sort of predefined array is correct: "
            << (identical ? "true" : "false") << std::endl;

        to_sort.copy_from(randoms);
        span_to_sort = to_sort.to_span();
        Stopwatch stopwatch;
        sorter->sort(span_to_sort);
        int elapsed = stopwatch.elapsed_milliseconds();
        bool srted = is_sorted(span_to_sort, RAND_CAPACITY);
        std::cout << sorter->name() << " Sort of random array is correct: "
             << (srted ? "true" : "false") << std::endl;
        std::cout << sorter->name() << " Sort of random array finished "
             << (srted ? "successfully" : "unsuccessfully") << " in " << elapsed << " milliseconds" << std::endl;
    }
}