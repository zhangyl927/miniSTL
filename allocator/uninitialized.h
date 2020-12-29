#ifndef __UNINITIALIZED_H
#define __UNINITIALIZED_H

#include "construct.h"
#include "../algorithm/stl_algobase.h"
#include "../iterator/type_traits.h"

template <class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x)
{
    return __uninitialized_fill_n(first, n, x, value_type(first));
}

template <class ForwardIterator, class Size, class T, class T1>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x, T1*)
{
    using isPOD = typename __type_traits<T1>::is_Pod_type;
    return __uninitialized_fill_n_aux(first, n, x, isPOD());
}

template <class ForwardIterator, class Size, class T>
inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, __true_type)
{
    return stl_algobase::fill_n(first, n, value);
}

template <class ForwardIterator, class Size, class T>
inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& value, __false_type)
{
    ForwardIterator cur = first;
    // 摘除了 异常处理部分代码；
    for (; n>0; --n, ++cur) construct(&*cur, value);
    return cur;
}

#endif