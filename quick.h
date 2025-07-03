#include <span>
#include "common.h"
#pragma once

template <typename T>
/**
 * @class QuickSorter
 * @brief Implements the Quick Sort algorithm for sorting arrays.
 * 
 * @tparam T The type of elements to sort.
 *
 * Inherits from the Sorter base class and provides an implementation of the
 * quick sort algorithm using std::span<T> for array manipulation.
 *
 * @note The sorting is performed in-place.
 */
class QuickSorter : public Sorter<T>
{
    /**
     * @brief Partitions the given array segment for the quicksort algorithm.
     *
     * Organizes the values between the high and low indexes where the
     * chosen pivot is moved to a new index where all values greater than
     * the pivot are to its right. The new index for the pivot is returned.
     *
     * @param ary A std::span<T> representing the array to partition.
     * @param low The starting index of the segment to partition.
     * @param high The ending index of the segment to partition (pivot element).
     * @return The index position of the pivot after partitioning.
     */
    int partition(std::span<T> ary, int low, int high) const;

    /**
     * @brief Sorts a subrange of the given array in place.
     *
     * This function sorts the elements of the provided array between the specified
     * low and high indexes.
     *
     * @param ary A std::span<T> representing the array to sort.
     * @param low The starting index of the subrange to sort.
     * @param high The ending index of the subrange to sort.
     */
    void sort_between_indexes(std::span<T> ary, int low, int high) const;

public:
    /**
     * @brief Constructs a QuickSorter object and initializes its base Sorter with the name "Quick".
     *
     * This constructor sets up the QuickSorter by calling the base Sorter class constructor
     * with the string "Quick", identifying the sorting algorithm implemented by this class.
     */
    QuickSorter() : Sorter<T>("Quick") {}

    /**
     * @brief Sorts the given array in-place.
     *
     * This function overrides the base class sort method to sort the elements
     * of the provided std::span<T> using the specific sorting algorithm
     * implemented in the derived class.
     *
     * @param ary A std::span<T> representing the array to be sorted.
     */
    void sort(std::span<T> ary) const override;
};