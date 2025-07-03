#include <memory>
#include <span>
#pragma once

template <typename T>
/**
 * @brief A managed dynamic array that handles memory allocation and provides utility functions.
 * 
 * @tparam T The type of elements stored in the array.
 */
class ManagedDynamicArray
{
private:
    /**
     * @brief Pointer to the dynamically allocated array data.
     */
    std::unique_ptr<T[]> data_;

    /**
     * @brief Number of bytes allocated for the array.
     */
    size_t num_bytes_;

    /**
     * @brief Number of elements in the array.
     */
    int size_;

public:
    /**
     * @brief Constructs a ManagedDynamicArray with the specified size.
     * @param size Number of elements to allocate.
     */
    ManagedDynamicArray(int size);

    /**
     * @brief Creates a ManagedDynamicArray as a slice from a given span.
     * @param src Source span to slice from.
     * @param start_idx Starting index of the slice (inclusive).
     * @param end_idx Ending index of the slice (exclusive).
     * @return ManagedDynamicArray<T> containing the sliced elements.
     */
    static ManagedDynamicArray<T> as_slice_from(std::span<T> &src, int start_idx, int end_idx);

    /**
     * @brief Returns a pointer to the underlying array data.
     * @return Pointer to the array data.
     */
    const T * data() const;

    /**
     * @brief Returns the number of bytes allocated for the array.
     * @return Number of bytes.
     */
    size_t num_bytes() const;

    /**
     * @brief Returns the number of elements in the array.
     * @return Number of elements.
     */
    int size() const;

    /**
     * @brief Returns a std::span representing the entire array.
     * @return Span of the array data.
     */
    std::span<T> to_span() const;

    /**
     * @brief Returns a std::span representing the first @p size elements of the array.
     * @param size Number of elements in the span.
     * @return Span of the specified size.
     */
    std::span<T> to_span(int size) const;

    /**
     * @brief Copies data from another ManagedDynamicArray.
     * @param src Source ManagedDynamicArray to copy from.
     */
    void copy_from(ManagedDynamicArray<T> & src);

    /**
     * @brief Copies data from a raw pointer.
     * @param src Pointer to the source data.
     * @param num_elements Number of elements to copy.
     */
    void copy_from(const T * src, int num_elements);

    /**
     * @brief Accesses the element at the specified index.
     * @param idx Index of the element.
     * @return Reference to the element at @p idx.
     */
    T & operator[](size_t idx);

    /**
     * @brief Accesses the element at the specified index (const version).
     * @param idx Index of the element.
     * @return Const reference to the element at @p idx.
     */
    const T & operator[](size_t idx) const;
};
