#include <span>
#include "common.h"
#pragma once

template <typename T>
/**
 * @class SelectionSorter
 * @brief Implements the selection sort algorithm for sorting arrays.
 * 
 * @tparam T The type of elements to sort.
 *
 * This class derives from the Sorter base class and provides an implementation
 * of the selection sort algorithm. It overrides the sort() method to perform
 * in-place sorting of the provided array.
 *
 * @note The selection sort algorithm has O(n^2) time complexity and is not stable.
 */
class SelectionSorter : public Sorter<T>
{
public:
    /**
     * @brief Constructs a SelectionSorter object with the name "Selection Sort".
     *
     * This constructor initializes the base Sorter class with the algorithm name,
     * allowing identification and usage of the selection sort algorithm.
     */
    SelectionSorter() : Sorter<T>("Selection Sort") {}

    /**
     * @brief Sorts the given array in-place.
     *
     * This function overrides the base class sort method and sorts the elements
     * of the provided std::span<T> in ascending order.
     *
     * @param ary Reference to a std::span<T> representing the array to be sorted.
     */
    void sort(std::span<T> ary) const override;
};
