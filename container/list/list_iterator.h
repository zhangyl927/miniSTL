#ifndef __LIST_ITERATOR
#define __LIST_ITERATOR

#include "list_node.h"
#include "../../iterator/stl_iterator.h"
#include <cstddef>

template <class T>
struct __list_iterator : public stl_iterator::iterator<stl_iterator::bidirectional_iterator_tag, T>
{
    using link_type = __list_node<T>*;
    using self = __list_iterator<T>;
    using iterator = __list_iterator<T>;

    using iterator_category = stl_iterator::bidirectional_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = ptrdiff_t;

    // pointer to __list_node
    link_type node;

    // ctor
    __list_iterator() { }
    explicit __list_iterator(link_type p) : node(p) { }
    __list_iterator(const iterator& x) : node(x.node) { }
    
    // op
    reference operator*() { return node->data; }
    pointer operator->() { return &(operator*()); }

    self& operator++();
    self operator++(int);
    self& operator--();
    self operator--(int);

    bool operator==(const self& rhs) const;
    bool operator!=(const self& rhs) const;
};

template <class T>
typename __list_iterator<T>::self& 
__list_iterator<T>::operator++() 
{
    node = (*node).next;
    return *this;
}

template <class T>
typename __list_iterator<T>::self 
__list_iterator<T>::operator++(int)
{
    self tmp = *this;
    ++(*this);
    return tmp;
} 

template <class T>
typename __list_iterator<T>::self& 
__list_iterator<T>::operator--()
{
    node = (*node).prev;
    return *this;
}

template <class T>
typename __list_iterator<T>::self 
__list_iterator<T>::operator--(int)
{
    self tmp = *this;
    --(*this);
    return tmp;
}

template <class T>
bool __list_iterator<T>::operator==(const self& rhs) const
{
    return node==rhs.node;
}

template <class T>
bool __list_iterator<T>::operator!=(const self& rhs) const
{
    return !(*this==rhs);
}




template <class T>
struct __list_reverse_iterator : public stl_iterator::iterator<stl_iterator::bidirectional_iterator_tag, T>
{
    using link_type = __list_node<T>*;
    using self = __list_reverse_iterator<T>;

    using iterator_category = stl_iterator::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    link_type node;

    // ctor
    __list_reverse_iterator() { }
    explicit __list_reverse_iterator(const link_type x) : node(x) { }

	// op
	reference operator*() { return (*node).data; }
	pointer operator->() { return &(operator*()); }

    self& operator++();
    self operator++(int);
    self& operator--();
    self operator--(int);

    bool operator==(const self& rhs) const;
    bool operator!=(const self& rhs) const;
};

template <class T>
typename __list_reverse_iterator<T>::self&
__list_reverse_iterator<T>::operator++()
{
	node = (*node).prev;
    return *this;
}

template <class T>
typename __list_reverse_iterator<T>::self
__list_reverse_iterator<T>::operator++(int)
{
    self tmp = *this;
    ++(*this);
    return tmp;
}

template <class T>
typename __list_reverse_iterator<T>::self&
__list_reverse_iterator<T>::operator--()
{
    return (*node).next;
}

template <class T>
typename __list_reverse_iterator<T>::self
__list_reverse_iterator<T>::operator--(int)
{
    self tmp = *this;
    --(*this);
    return tmp;
}

template <class T>
bool __list_reverse_iterator<T>::operator==(const self& rhs) const
{
    return node==rhs.node;
}

template <class T>
bool __list_reverse_iterator<T>::operator!=(const self& rhs) const
{
    return !(*this==rhs);
}


#endif
