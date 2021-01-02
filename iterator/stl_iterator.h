#ifndef __STL_ITERATOR_H
#define __STL_ITERATOR_H

#include <cstddef>

namespace stl_iterator
{

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {}; 

template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
struct iterator
{
    using iterator_category = Category;
    using value_type = T;
    using difference_type = Distance;
    using pointer = Pointer;
    using reference = Reference;
};

template <class Iterator>
struct iterator_traits
{
    using iterator_category = typename Iterator::iterator_category;
    using value_type = typename Iterator::value_type;
    using difference_type = typename Iterator::difference_type;
    using pointer = typename Iterator::pointer;
    using reference = typename Iterator::reference;
};

template <class T>
struct iterator_traits<T*>
{
    using iterator_category = random_access_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;
};

template <class T>
struct iterator_traits<const T*>
{
    using iterator_category = random_access_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;
};


// --------------------- distance --------------------
template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag)
{
	typename iterator_traits<InputIterator>::difference_type n = 0;
	while (first != last)
	{
		++first;
		++n;
	}
	return n;
}

template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, random_access_iterator_tag)
{
	return last-first;
}

template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last)
{
	using category = typename iterator_traits<InputIterator>::iterator_category;
	__distance(first, last, category());
}


// ------------------------- advance ---------------------------
template <class InputIterator, class Distance>
inline void __advance(InputIterator& it, Distance n, input_iterator_tag)
{
	while (n--)
	{
		++it;
	}
}

template <class BidirectionalIterator, class Distance>
inline void __advance(BidirectionalIterator& it, Distance n, bidirectional_iterator_tag)
{
	if (n >= 0)
	{
		while (n--) ++it;
	}
	else
	{
		while (n++ < 0) --it;
	}
}

template <class RandomAccessIterator, class Distance>
inline void __advance(RandomAccessIterator& it, Distance n, random_access_iterator_tag)
{
	it += n;
}

template <class InputIterator, class Distance>
inline void advance(InputIterator& it, Distance n)
{
	using category = typename iterator_traits<InputIterator>::iterator_category;
	__advance(it, n, category());
}

}

#endif
