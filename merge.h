#include <span>
#include "common.h"
#pragma once

template <typename T>
/**
 * @class MergeSorter
 * @brief Implements the merge sort algorithm using a helper sorter for small subarrays.
 * 
 * @tparam T The type of elements to sort.
 *
 * The MergeSorter class inherits from the Sorter base class and provides an implementation
 * of the merge sort algorithm. For small subarrays, it delegates the sorting to another
 * sorter (small_sorter), which can be optimized for small data sets (e.g., insertion sort).
 *
 * @note The small_sorter reference must remain valid for the lifetime of the MergeSorter instance.
 */
class MergeSorter : public Sorter<T>
{
    /// Reference to a sorter used for handling small subarrays during the merge sort process.
    std::reference_wrapper<const Sorter<T>> small_sorter_;

public:
    /**
     * @brief Constructs a MergeSorter with a specified small sorter.
     * 
     * This constructor initializes the MergeSorter and sets its name to "Merge Sort".
     * It also takes a reference to another Sorter, which will be used for sorting small subarrays
     * within the merge sort algorithm, allowing for hybrid sorting strategies.
     * 
     * @param small_sorter Constant reference to a Sorter object used for sorting small subarrays.
     */
    MergeSorter(const Sorter<T> & small_sorter) : Sorter<T>("Merge Sort"), small_sorter_(small_sorter) {}

    /**
     * @brief Sorts the given array in place.
     *
     * This function overrides the base class sort method and sorts the elements
     * of the provided std::span<T> in ascending order.
     *
     * @param ary A std::span<T> representing the array to be sorted.
     */
    void sort(std::span<T> ary) const override;
};
