#include "heap.h"
#include "managed_dynamic_array.h"
#include <optional>
#include <cassert>

static const int ROOT_INDEX = 1;
static const int INVALID_INDEX = -1;

enum class HeapifyDirection
{
    DOWN = 0,
    UP = 1
};

template <typename T>
bool min_comparer(T x, T y)
{
    return x < y;
}

template <typename T>
bool max_comparer(T x, T y)
{
    return x > y;
}

template <typename T>
/**
 * @class Heap
 * @brief A generic heap data structure with dynamic storage.
 * 
 * The Heap class provides a flexible implementation of a heap (priority queue)
 * that supports dynamic resizing and custom comparison logic. It manages its
 * elements using a managed dynamic array and allows for efficient insertion,
 * removal, and access to the top element. The heap supports both min-heap and
 * max-heap behavior through the virtual compare function.
 * 
 * @tparam T The type of elements stored in the heap.
 * 
 * @section Features
 * - Dynamic storage management via ManagedDynamicArray.
 * - Customizable comparison logic for heap ordering.
 * - Efficient access to the top element.
 * - Bounds checking utilities.
 * 
 * @section Usage
 * Construct a Heap with a specified capacity, then use store() to insert elements,
 * take() to remove the top element, and peek() to access the top element without removal.
 * 
 * @section Example
 * @code
 * Heap<int> minHeap(100);
 * minHeap.store(42);
 * int top = minHeap.peek();
 * int removed = minHeap.take();
 * @endcode
 */
class Heap
{
    // Stores the current number of elements in the heap.
    int size_;

    /**
     * @brief Internal storage for the heap elements.
     * 
     * This managed dynamic array holds the elements of the heap,
     * providing dynamic resizing and memory management.
     * 
     * @tparam T Type of elements stored in the heap.
     */
    ManagedDynamicArray<T> storage_;

public:
    /**
     * @brief Constructs a Heap with a specified capacity.
     * 
     * Initializes the heap with zero elements and allocates internal storage
     * to hold up to the given capacity. The storage is sized as (capacity + 1)
     * to accommodate heap indexing starting from 1.
     * 
     * @param capacity The maximum number of elements the heap can hold.
     */
    Heap(int capacity)
        : size_(0), storage_(capacity + 1)
    {
    }

    /**
     * @brief Compares two values of type T using the min_comparer function.
     *
     * This virtual function determines the ordering between two elements, x and y,
     * by delegating the comparison to the min_comparer. It returns true if x should
     * come before y according to the comparison logic, and false otherwise.
     *
     * @param x The first value to compare.
     * @param y The second value to compare.
     * @return true if x is before y; false otherwise.
     */
    virtual bool compare(T x, T y) const
    {
        return min_comparer(x, y);
    }

    /**
     * @brief Provides access to the element at the specified index.
     * 
     * This operator returns a reference to the element in the underlying storage
     * at the given index, allowing both reading and modification of the value.
     * 
     * @param idx The index of the element to access.
     * @return Reference to the element at the specified index.
     * @throws std::out_of_range If idx is out of bounds (behavior depends on storage_ implementation).
     */
    T & operator[](size_t idx)
    {
        return storage_[idx];
    }

    /**
     * @brief Provides read-only access to the element at the specified index.
     * 
     * @param idx The index of the element to access.
     * @return const int& A constant reference to the element at the given index.
     * @note No bounds checking is performed.
     */
    const T & operator[](size_t idx) const
    {
        return storage_[idx];
    }

    /**
     * @brief Checks if the given index is out of the valid range.
     *
     * Determines whether the specified index exceeds the current size of the container.
     *
     * @param index The index to check.
     * @return true if the index is greater than the current size; false otherwise.
     */
    bool is_out_of_range(int index) const
    {
        return index > size_;
    }

    /**
     * @brief Returns the element at the top of the heap without removing it.
     * 
     * @tparam T The type of the elements stored in the heap.
     *
     * @return std::optional<T> The top element if the heap is not empty; std::nullopt otherwise.
     */
    std::optional<T> peek() const
    {
        if (size_ == 0) return std::nullopt;

        return storage_[ROOT_INDEX];
    }

    /**
     * @brief Stores the given number in the data structure.
     * 
     * @tparam T The type of the number to be stored.
     * @param num The number to store.
     */
    void store(T num);

    /**
     * @brief Removes and returns the top element from the heap, if available.
     * 
     * @tparam T The type of the elements stored in the heap.
     * @return std::optional<T> The top element if the heap is not empty; std::nullopt otherwise.
     */
    std::optional<T> take();
};

template <typename T>
/**
 * @class MaxHeap
 * @brief A heap data structure that always extracts the maximum element.
 * 
 * Inherits from the generic Heap<T> class and overrides the comparison
 * function to maintain the max-heap property, where each parent node is
 * greater than or equal to its child nodes.
 * 
 * @tparam T The type of elements stored in the heap.
 * 
 * @constructor
 * @param capacity The maximum number of elements the heap can hold.
 * 
 * @note The compare function uses max_comparer to determine the ordering
 *       of elements, ensuring the largest element is always at the root.
 */
class MaxHeap : public Heap<T>
{
public:
    /**
     * @brief Constructs a MaxHeap with the specified capacity.
     * 
     * @param capacity The maximum number of elements the heap can hold.
     */
    MaxHeap(int capacity) : Heap<T>(capacity) {}

    /**
     * @brief Compares two values of type T using the max_comparer function.
     *
     * This method overrides the base class compare function to provide a custom
     * comparison logic for type T. It returns the result of max_comparer(x, y),
     * which typically determines if x should be ordered before y in a max-heap.
     *
     * @param x The first value to compare.
     * @param y The second value to compare.
     * @return true if x should be ordered before y according to max_comparer; false otherwise.
     */
    bool compare(T x, T y) const override
    {
        return max_comparer(x, y);
    }
};

template <typename T>
/**
 * @brief Represents a node within a heap data structure.
 * 
 * @tparam T The type of value stored in the heap.
 */
class HeapNode
{
    /**
     * @brief The index of this node within the heap.
     */
    int index_ = INVALID_INDEX;

    /**
     * @brief Reference wrapper for the heap that contains this node.
     */
    std::reference_wrapper<Heap<T>> heap_;
    // NOTE: I initially stored a plain reference to the heap, but it as well
    // as a const pointer prevents me from reassigning a local variable
    // to another node like so:
    // HeapNode<T> node = some_other_node;
    // error: use of deleted function 'HeapNode<int>& HeapNode<int>::operator=(const HeapNode<int>&)'

public:
    /**
     * @brief Constructs a HeapNode for a given heap and index.
     * @param heap Constant pointer to the heap containing this node.
     * @param index Index of the node within the heap.
     */
    HeapNode(Heap<T> & heap, int index);

    /**
     * @brief Checks whether the object exists insofar as it references
     * a valid index in the heap.
     * 
     * @return true if the object exists; false otherwise.
     */
    bool exists() const;

    /**
     * @brief Retrieves the value stored at this node.
     * @return The value of type T at this node.
     */
    T get_value() const;

    /**
     * @brief Sets the value at this node.
     * @param new_val The new value to assign.
     */
    void set_value(T new_val) const;

    /**
     * @brief Restores the heap property by moving the node down the heap if necessary.
     */
    void heapify_down() const;

    /**
     * @brief Restores the heap property by moving the node up the heap if necessary.
     */
    void heapify_up() const;

    /**
     * @brief Returns the HeapNode at the specified index.
     * @param index The index of the desired node.
     * @return the HeapNode at the given index.
     */
    HeapNode from_index(int index) const;

    /**
     * @brief Returns the left child node.
     * @return the left child HeapNode.
     */
    HeapNode left() const;

    /**
     * @brief Returns the right child node.
     * @return the right child HeapNode.
     */
    HeapNode right() const;

    /**
     * @brief Returns the parent node.
     * @return the parent HeapNode.
     */
    HeapNode parent() const;

    /**
     * @brief Attempts to swap the value of this node with another node, based on heapify direction.
     * @param other Reference to the other HeapNode.
     * @param direction The direction of heapification (up or down).
     */
    void try_swap_value(const HeapNode & other, HeapifyDirection direction) const;
};

template <typename T>
void Heap<T>::store(T num)
{
    ++size_;
    storage_[size_] = num;
    bool setting_root = size_ == ROOT_INDEX;
    if (!setting_root)
    {
        HeapNode<T> added(*this, size_);
        added.heapify_up();
    }
}

template <typename T>
HeapNode<T>::HeapNode(Heap<T> & heap, int index) : heap_(heap), index_(index) {}

template <typename T>
std::optional<T> Heap<T>::take()
{
    auto taken = peek();
    if (!taken.has_value()) return taken;

    storage_[ROOT_INDEX] = storage_[size_--];
    if (size_ > 1)
    {
        HeapNode<T> root_node(*this, ROOT_INDEX);
        root_node.heapify_down();
    }
    return taken;
}

template <typename T>
bool HeapNode<T>::exists() const
{
    return index_ != INVALID_INDEX;
}

template <typename T>
T HeapNode<T>::get_value() const
{
    return static_cast<Heap<T>&>(heap_)[index_];
}

template <typename T>
void HeapNode<T>::set_value(T new_val) const
{
    static_cast<Heap<T>&>(heap_)[index_] = new_val;
}

template <typename T>
void HeapNode<T>::heapify_down() const
{
    HeapNode<T> lft = left();
    HeapNode<T> rght = right();
    bool left_exists = lft.exists();
    bool right_exists = rght.exists();
    if (!left_exists && !right_exists)
    {
        return;
    }

    HeapNode<T> other = rght;
    if (left_exists && right_exists)
    {
        /* Favor the smallest or largest child node as a swap partner
         * depending on if one is working with a min or max heap.
         * The comparer will return true if the first value meets this
         * criteria. */
        if (static_cast<Heap<T>&>(heap_).compare(
            lft.get_value(), rght.get_value()))
        {
            other = lft;
        }
    }
    else if (left_exists)
    {
        other = lft;
    }
    try_swap_value(other, HeapifyDirection::DOWN);
}

template <typename T>
void HeapNode<T>::heapify_up() const
{
    HeapNode node = parent();
    try_swap_value(node, HeapifyDirection::UP);
}

template <typename T>
HeapNode<T> HeapNode<T>::left() const
{
    return from_index(2 * index_);
}

template <typename T>
HeapNode<T> HeapNode<T>::right() const
{
    return from_index(2 * index_ + 1);
}

template <typename T>
HeapNode<T> HeapNode<T>::parent() const
{
    int new_index = index_ == ROOT_INDEX ? INVALID_INDEX : (index_ / 2);
    return HeapNode<T>(heap_, new_index);
}

template <typename T>
HeapNode<T> HeapNode<T>::from_index(int index) const
{
    int new_index = static_cast<Heap<T>&>(heap_).is_out_of_range(index) ? INVALID_INDEX : index;
    return HeapNode<T>(heap_, new_index);
}

template <typename T>
void HeapNode<T>::try_swap_value(const HeapNode<T> & other, HeapifyDirection direction) const
{
    if (!exists() || !other.exists()) return;

    int val = get_value();
    int other_val = other.get_value();
    Heap<T> & heap = static_cast<Heap<T>&>(heap_);
    if (direction == HeapifyDirection::DOWN && heap.compare(other_val, val))
    {
        set_value(other_val);
        other.set_value(val);
        other.heapify_down();
    }
    else if (direction == HeapifyDirection::UP && heap.compare(val, other_val))
    {
        set_value(other_val);
        other.set_value(val);
        other.heapify_up();
    }
}

template <typename T>
void HeapSorter<T>::sort(std::span<T> ary) const
{
    int count = ary.size();
    Heap<int> heap(count);
    int i = 0;
    for (; i < count; ++i)
    {
        heap.store(ary[i]);
    }
    for (i = 0; i < count; ++i)
    {
        auto taken = heap.take();
        assert(taken.has_value() == true);
        ary[i] = taken.value();
    }
}

template class Heap<int>;
template class MaxHeap<int>;
template class HeapNode<int>;
template class HeapSorter<int>;