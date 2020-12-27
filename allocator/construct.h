#include <new>  // placement new

namespace SimpleSTL
{

template <class T1, class T2>
void* construct(T1* ptr, const T2& value)
{
	new(ptr) T1(value);
}

template <class T>
void destroy(T* ptr)
{
	ptr->~T();
}

}
