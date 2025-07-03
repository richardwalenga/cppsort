#include <memory>
#include <span>
#pragma once

template <typename T>
/**
 * @class Sorter
 * @brief Abstract base class for sorting algorithms.
 * 
 * @tparam T The type of elements to sort.
 *
 * Provides a common interface and utility functions for implementing
 * different sorting algorithms. Derived classes must implement the
 * pure virtual sort() method.
 *
 * @note This class is not intended to be instantiated directly.
 */
class Sorter
{
    /// @brief Pointer to a null-terminated string representing the name associated with the object.
    /// @note The lifetime and ownership of the string are not managed by this class.
    const char * name_;

protected:
    /**
     * @brief Swaps the values at two specified indices in the given array.
     *
     * @param ary A std::span<T> representing the array.
     * @param x Index of the first element to swap.
     * @param y Index of the second element to swap.
     */
    void swap_values(std::span<T> ary, int x, int y) const;

public:
    /**
     * @brief Constructs a Sorter object with the specified name.
     * 
     * @param name The name to assign to the sorter.
     */
    Sorter(const char * name) : name_(name) {}

    /**
     * @brief Returns the name associated with the object.
     * 
     * @return A pointer to a null-terminated string representing the object's name.
     */
    const char * name() const;

    /**
     * @brief Sorts the given array in-place.
     *
     * This is a pure virtual function that must be implemented by derived classes.
     * The function takes a std::span<T> and sorts its elements.
     *
     * @param ary A std::span<T> representing the array to be sorted.
     */
    virtual void sort(std::span<T> ary) const = 0;
};
