#include "alloc.h"
#include "construct.h"

template <class T, class Alloc=__default_alloc<T>>
class SimpleAlloc
{
public:
    template <class U>
    struct rebind
    {
        typedef SimpleAlloc<U> other;
    };

    static void* allocate(size_t n);
    static void deallocate(T* ptr, size_t n);

    static void* construct(T* ptr, T value);
    static void destroy(T* ptr);
	static void destroy(T* frist, T* last);				// 析构迭代器 [first, last) 范围内的对象
};

template <class T, class Alloc>
void* SimpleAlloc<T, Alloc>::allocate(size_t n)
{
    return Alloc::allocate(n*sizeof(T));
}

template <class T, class Alloc>
void SimpleAlloc<T, Alloc>::deallocate(T* ptr, size_t n)
{
    Alloc::deallocate(static_cast<void*>(ptr), n);
}

template <class T, class Alloc>
void* SimpleAlloc<T, Alloc>::construct(T*ptr, T value)
{
   //new(ptr) T(value);
	SimpleSTL::construct(ptr, value);
}

template <class T, class Alloc>
void SimpleAlloc<T, Alloc>::destroy(T* ptr)
{
   // ptr->~T();
	SimpleSTL::destroy(ptr);
}

template <class T, class Alloc>
void SimpleAlloc<T, Alloc>::destroy(T* first, T* last)
{
	for (; first!=last; ++first)
	{
		first->~T();
	}
}
