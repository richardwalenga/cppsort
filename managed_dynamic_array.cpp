#include "managed_dynamic_array.h"
#include <cstring>

template <typename T>
ManagedDynamicArray<T>::ManagedDynamicArray(int size)
    : size_(size), num_bytes_(sizeof(T) * size)
{
    data_ = std::make_unique<T[]>(size);
}

template <typename T>
ManagedDynamicArray<T> ManagedDynamicArray<T>::as_slice_from(std::span<T> & src, int start_idx, int end_idx)
{
    ManagedDynamicArray<T> obj(end_idx - start_idx + 1);
    obj.copy_from(src.data() + start_idx, obj.size());
    return obj;
}

template <typename T>
const T * ManagedDynamicArray<T>::data() const
{
    return data_.get();
}

template <typename T>
size_t ManagedDynamicArray<T>::num_bytes() const
{
    return num_bytes_;
}

template <typename T>
int ManagedDynamicArray<T>::size() const
{
    return size_;
}

template <typename T>
void ManagedDynamicArray<T>::copy_from(ManagedDynamicArray<T> & src)
{
    copy_from(src.data(), src.size());
}

template <typename T>
void ManagedDynamicArray<T>::copy_from(const T * src, int num_elements)
{
    if (num_elements > size_)
    {
        throw std::runtime_error("Number of elements from source exceeds ManagedDynamicArray size of " + std::to_string(size_));
    }

    size_t num_bytes = sizeof(T) * num_elements;
    memcpy(data_.get(), src, num_bytes);
}

template <typename T>
std::span<T> ManagedDynamicArray<T>::to_span() const
{
    return std::span<T>(data_.get(), size_);
}

template <typename T>
std::span<T> ManagedDynamicArray<T>::to_span(int size) const
{
    return std::span<T>(data_.get(), size);
}

template <typename T>
T & ManagedDynamicArray<T>::operator[](size_t idx)
{
    return data_[idx];
}

template <typename T>
const T & ManagedDynamicArray<T>::operator[](size_t idx) const
{
    return data_[idx];
}

template class ManagedDynamicArray<int>; // Explicit instantiation for int type to avoid linker errors
