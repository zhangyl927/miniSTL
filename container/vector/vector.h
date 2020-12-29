#include "../../allocator/allocator.h"
#include "../../allocator/uninitialized.h"

template <class T, class Alloc=SimpleAlloc<T>>
class vector
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using difference_type = ptrdiff_t;

    using iterator = T*;
    using size_type = size_t;
    using vector_alloc = Alloc;
public:
    // ctor
    vector() : start(nullptr), finish(nullptr), end_of_storage(nullptr) {}
    explicit vector(size_type n) { fill_initialize(n, value_type()); }

    // iterators
    iterator begin();
    iterator end();

    // capacity
    size_type size();
    size_type max_size();
    bool empty();

    // 
private:
    // help func
    void fill_initialize(size_type n, const value_type& value);
    iterator allocate_and_fill(size_type n, const value_type& value);

private:
    iterator start;
    iterator finish;
    iterator end_of_storage;
};

//  help func
template <class T, class Alloc>
void vector<T, Alloc>::fill_initialize(size_type n, const value_type& value)
{
    start = allocate_and_fill(n, value);
    finish = start+n;
    end_of_storage = finish;
}

template <class T, class Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::allocate_and_fill(size_type n, const value_type& value)
{
    iterator result = vector_alloc::allocate(n);
    uninitialized_fill_n(result, n, value);
    return result;
}