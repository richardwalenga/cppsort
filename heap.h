#include "common.h"
#pragma once

template <typename T>
/**
 * @class HeapSorter
 * @brief Implements the heap sort algorithm for sorting arrays.
 * 
 * @tparam T The type of elements to sort.
 *
 * Inherits from the Sorter base class and provides an implementation of the
 * sort method using the heap sort technique. The class includes a private
 * helper function, heapify, to maintain the heap property during sorting.
 */
class HeapSorter : public Sorter<T>
{
public:
    /**
     * @brief Constructs a HeapSorter object with the name "Heap".
     *
     * This constructor initializes the base Sorter class with the sorting algorithm name "Heap".
     */
    HeapSorter() : Sorter<T>("Heap") {}

    /**
     * @brief Sorts the given array in-place using the heap sort algorithm.
     * 
     * @param ary A std::span<T> representing the array to be sorted.
     * 
     * @note This function overrides a virtual method from a base class.
     */
    void sort(std::span<T> ary) const override;
};
