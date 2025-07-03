#include <span>
#include "common.h"
#pragma once

template <typename T>
/**
 * @class BubbleSorter
 * @brief Implements the bubble sort algorithm for sorting arrays.
 * 
 * @tparam T The type of elements to sort.
 *
 * Inherits from the Sorter base class and provides an implementation of the
 * bubble sort algorithm. The class supports sorting arrays using
 * the standard bubble sort technique.
 */ 
class BubbleSorter : virtual public Sorter<T>
{
protected:
    /**
     * @brief Sorts the given array using bubble sort going from left-to-right.
     *
     * @param ary A std::span<T> representing the array to be sorted.
     * @return true if values in the array were swapped, false if the array was already sorted.
     */
    bool ltr_sort(std::span<T> ary) const;

public:
    /**
     * @brief Constructs a BubbleSorter object with the name "Bubble".
     *
     * This constructor initializes the BubbleSorter by calling the base Sorter
     * class constructor with the sorting algorithm name "Bubble".
     */
    BubbleSorter() : Sorter<T>("Bubble") {}

    /**
     * @brief Sorts the given array in-place using a specific sorting algorithm.
     * 
     * This function overrides a virtual method from a base class and sorts the elements
     * of the provided std::span<T> in ascending order.
     * 
     * @param ary A std::span<T> representing the array to be sorted.
     */
    void sort(std::span<T> ary) const override;
};

template <typename T>
/**
 * @class CocktailShakerSorter
 * @brief Implements the cocktail shaker sort algorithm, a bidirectional variant of bubble sort.
 * 
 * @tparam T The type of elements to sort.
 *
 * Inherits from BubbleSorter and provides an implementation of the cocktail shaker sort,
 * which sorts the array in both directions on each pass through the list, improving performance
 * over the traditional bubble sort in some cases.
 *
 * @note The class overrides the sort method to perform cocktail shaker sorting.
 */
class CocktailShakerSorter : public BubbleSorter<T>
{
private:
    /**
     * @brief Sorts the given array using bubble sort going from right-to-left.
     * 
     * @param ary A std::span<T> representing the array to be sorted.
     * @return true if values in the array were swapped, false if the array was already sorted.
     */
    bool rtl_sort(std::span<T> ary) const;

public:
    /**
     * @brief Constructs a CocktailShakerSorter object with the name "Cocktail Shaker".
     *
     * This constructor initializes the CocktailShakerSorter by calling the base Sorter
     * class constructor with the sorting algorithm name "CocktailShaker".
     */
    CocktailShakerSorter() : Sorter<T>("Cocktail Shaker") {}

    /**
     * @brief Sorts the given array in-place using a specific sorting algorithm.
     * 
     * This function overrides a virtual method from a base class and sorts the elements
     * of the provided std::span<T> in ascending order.
     * 
     * @param ary A std::span<T> representing the array to be sorted.
     */
    void sort(std::span<T> ary) const override;
};
