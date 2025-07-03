#include <span>
#include "common.h"
#pragma once

template <typename T>
/**
 * @class InsertionSorter
 * @brief Implements the insertion sort algorithm for sorting arrays.
 * 
 * @tparam T The type of elements to sort.
 *
 * InsertionSorter is a concrete subclass of the Sorter base class, providing
 * an implementation of the insertion sort algorithm. It overrides the sort()
 * method to sort a given array in-place.
 *
 * @note The sorter is identified by the name "Insertion Sort".
 */
class InsertionSorter : public Sorter<T>
{
public:
    /**
     * @brief Constructs an InsertionSorter object with the name "Insertion Sort".
     *
     * This constructor initializes the base Sorter class with the algorithm name,
     * allowing identification and usage of the insertion sort algorithm.
     */
    InsertionSorter() : Sorter<T>("Insertion Sort") {}

    /**
     * @brief Sorts the given array in-place using the insertion sort algorithm.
     * 
     * @param ary A std::span<T> representing the array to be sorted.
     * 
     * @note This function overrides a virtual method from a base class.
     */
    void sort(std::span<T> ary) const override;
};
