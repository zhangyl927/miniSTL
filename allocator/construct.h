#ifndef __CONSTRUCT_H
#define __CONSTRUCT_H

#include <new>  // placement new
#include "../iterator/type_traits.h"

namespace SimpleSTL
{

template <class T1, class T2>
inline void* construct(T1* ptr, const T2& value)
{
	new(ptr) T1(value);
}

template <class T>
inline void destroy(T* ptr)
{
	ptr->~T();
}

template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last)
{
	__destroy(first, last, value_type(first));
}

template <class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T*)
{
	using trivial_destructor = __type_traits<T>::has_trivial_destructor;
	__destroy_aux(first, last, trivial_destructor);
}

template <class ForwardIterator>
inline void __destroy_aux(ForwardIterator first, ForwardIterator last,__false_type)
{
	for (; first!=last; ++first)
	{
		destroy(&*first);
	}
}

template <class ForwardIterator>
inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __true_type) { }

inline void destroy(char*, char*) { }
inline void destroy(wchar_t*, wchar_t*) { }

}

#endif