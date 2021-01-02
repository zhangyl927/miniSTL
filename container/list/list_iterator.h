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
    reference operator*() const { return node->data; }
    pointer operator->() const { return &(operator*()); }

    self& operator++();
    self operator++(int);
    self& operator--();
    self operator--(int);

    bool operator==(const self& rhs) const;
    bool operator!=(const self& rhs) const;
};

template <class T>
inline typename __list_iterator<T>::self& 
__list_iterator<T>::operator++() 
{
    node = (*node).next;
    return *this;
}

template <class T>
inline typename __list_iterator<T>::self 
__list_iterator<T>::operator++(int)
{
    self tmp = *this;
    ++(*this);
    return tmp;
} 

template <class T>
inline typename __list_iterator<T>::self& 
__list_iterator<T>::operator--()
{
    node = (*node).prev;
    return *this;
}

template <class T>
inline typename __list_iterator<T>::self 
__list_iterator<T>::operator--(int)
{
    self tmp = *this;
    --(*this);
    return tmp;
}

template <class T>
inline bool __list_iterator<T>::operator==(const self& rhs) const
{
    return node==rhs.node;
}

template <class T>
inline bool __list_iterator<T>::operator!=(const self& rhs) const
{
    return !(*this==rhs);
}




// ------------------ list reverse iterator ----------------------
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
	__list_reverse_iterator(const self& rhs) : node(rhs.node) { }

	// op
	reference operator*() const { return (*node).data; }
	pointer operator->() const { return &(operator*()); }

    self& operator++();
    self operator++(int);
    self& operator--();
    self operator--(int);

    bool operator==(const self& rhs) const;
    bool operator!=(const self& rhs) const;
};

template <class T>
inline typename __list_reverse_iterator<T>::self&
__list_reverse_iterator<T>::operator++()
{
	node = (*node).prev;
    return *this;
}

template <class T>
inline typename __list_reverse_iterator<T>::self
__list_reverse_iterator<T>::operator++(int)
{
    self tmp = *this;
    ++(*this);
    return tmp;
}

template <class T>
inline typename __list_reverse_iterator<T>::self&
__list_reverse_iterator<T>::operator--()
{
    return (*node).next;
}

template <class T>
inline typename __list_reverse_iterator<T>::self
__list_reverse_iterator<T>::operator--(int)
{
    self tmp = *this;
    --(*this);
    return tmp;
}

template <class T>
inline bool __list_reverse_iterator<T>::operator==(const self& rhs) const
{
    return node==rhs.node;
}

template <class T>
inline bool __list_reverse_iterator<T>::operator!=(const self& rhs) const
{
    return !(*this==rhs);
}



// ------------------ list const iterator ----------------------
template <class T>
struct __list_const_iterator : public stl_iterator::iterator<stl_iterator::bidirectional_iterator_tag, T>
{
    using iterator_category = stl_iterator::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = ptrdiff_t;
    using reference = const T&;
    using pointer = const T*;
    
    using link_type = __list_node<T>*;
    using self = __list_const_iterator<T>;

    link_type node;

	// ctor
	__list_const_iterator() { }
	explicit __list_const_iterator(const link_type x) : node(x) { }
	__list_const_iterator(const self& rhs) : node(rhs.node) { }

	// op
    reference operator*() const { return *node.data; }
    pointer operator->() const { return *node.data; }

    self& operator++();
    self operator++(int);
    self& operator--();
    self operator--(int);

    bool operator==(const self& rhs) const;
    bool operator!=(const self& rhs) const;
};

template <class T>
inline typename __list_const_iterator<T>::self&
__list_const_iterator<T>::operator++()
{
    node = (*node).next;
    return *this;
}

template <class T>
inline typename __list_const_iterator<T>::self
__list_const_iterator<T>::operator++(int)
{
    self tmp = *this;
    ++(*this);
	return tmp;
}

template <class T>
inline typename __list_const_iterator<T>::self&
__list_const_iterator<T>::operator--()
{
	node = (*node).prev;
	return *this;
}

template <class T>
inline typename __list_const_iterator<T>::self
__list_const_iterator<T>::operator--(int)
{
	self tmp = *this;
	--(*this);
	return tmp;
}

#endif
