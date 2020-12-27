#include "list_node.h"
#include "../../iterator/stl_iterator.h"

template <class T>
struct __list_iterator
{
    using link_type = __list_node<T>*;
    using self = __list_iterator<T>;

    using iterator_category = bidirectional_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = ptrdiff_t;

    // pointer to __list_node
    link_type node;

    // ctor
    __list_iterator() { }
    explicit __list_iterator(link_type p) : node(p) { }
    
    // op
    reference operator*() { return node->data; }
    pointer operator->() { return &(operator*()); }

    self& operator++();
    self operator++(int);
    self& operator--();
    self operator--(int);
};

template <class T>
typename __list_iterator<T>::self& 
__list_iterator<T>::operator++() 
{
    node = node->next;
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
    node = node->prev;
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