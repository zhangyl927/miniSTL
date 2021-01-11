#ifndef __LIST_H
#define __LIST_H

#include "../../allocator/allocator.h"
#include "list_iterator.h"
#include "list_node.h"

template <class T, class Alloc=SimpleAlloc<T>>
class list
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

protected:
    using list_node = __list_node<T>;
    using list_alloc = SimpleAlloc<list_node>;

    using iterator = __list_iterator<T>;
    using reverse_iterator = __list_reverse_iterator<T>;
   	using const_iterator = __list_const_iterator<T>;

private:
    list_node* node;

public:    // ctor && dctor
    list();
    ~list();

    // copy ctor and copy assign
    list(const list&);
    list& operator=(const list &);

    // move ctor and move assign
    list(list&&);
    list& operator=(list&&);
    
public:     // iterators
    iterator begin() const;
    iterator end() const;
    reverse_iterator rbegin() const;
    reverse_iterator rend() const;
    const_iterator cbegin() const;
    const_iterator cend() const;
    // const_iterator crbegin();
    // const_iterator crend();
    

public:         // capacity
    bool empty() const;
    size_type size() const;

public:         // element access
    reference front();              // 获取链首元素值
    reference back();               // 获取链尾元素值

public:         // modifiers
    iterator insert(iterator position, const value_type& val);
	iterator insert(iterator position, size_type n, const value_type& val);
    
	template <class InputIterator>
	iterator insert(iterator position, InputIterator first, InputIterator last);

	iterator erase(iterator position);
    void push_front(const value_type& value);
    void push_back(const value_type& value);
    void pop_front();
    void pop_back();

private:        // realize detail   
    list_node* get_node();          // 配置一个节点并传回
    void put_node(list_node* p);    // 释放一个节点
    list_node* create_node(const value_type& value);
    void destroy_node(list_node* p);
    void empty_initialize();        // 产生一个空链表
    void clear();                   // 清空链表
    void swap(list& rhs) { ::swap(node, rhs.node); }
};

//---------- ctor and dctor
template <class T, class Alloc>
inline list<T, Alloc>::list()
{
    empty_initialize();             
}

template <class T, class Alloc>
inline list<T, Alloc>::~list()
{
    clear();
    put_node(node);
}

//----------- copy ctor and copy assign
template <class T, class Alloc>
inline list<T, Alloc>::list(const list& rhs)
{
	empty_initialize();	
	insert(begin(), rhs.begin(), rhs.end());
}

template <class T, class Alloc>
inline typename list<T, Alloc>::list&
list<T, Alloc>::operator=(const list& rhs)
{
    list temp(rhs);
    swap(rhs);
	return *this;
}

//--------------move ctor and move assign
template <class T, class Alloc>
inline list<T, Alloc>::list(list&& rhs) : node(rhs.node)
{
    rhs.node = nullptr;
}

template <class T, class Alloc>
inline typename list<T, Alloc>::list&
list<T, Alloc>::operator=(list&& rhs)
{
    clear();
    list temp(rhs);
    swap(temp);
    return *this;
}

//---------- iterators
template <class T, class Alloc>
inline typename list<T, Alloc>::iterator
list<T, Alloc>::begin() const
{
    return iterator(node->next);
}

template <class T, class Alloc>
inline typename list<T, Alloc>::iterator
list<T, Alloc>::end() const
{
    return iterator(node);
}

template <class T, class Alloc>
inline typename list<T, Alloc>::reverse_iterator
list<T, Alloc>::rbegin() const
{
    return reverse_iterator(node->prev);
}

template <class T, class Alloc>
inline typename list<T, Alloc>::reverse_iterator
list<T, Alloc>::rend() const
{
    return reverse_iterator(node);
}

template <class T, class Alloc>
inline typename list<T, Alloc>::const_iterator
list<T, Alloc>::cbegin() const
{
	return const_iterator(*node.next);
}

template <class T, class Alloc>
inline typename list<T, Alloc>::const_iterator
list<T, Alloc>::cend() const
{
	return const_iterator(node);
}

//---------- capacity
template <class T, class Alloc>
inline bool list<T, Alloc>::empty() const
{
    return node->next==node;
}

template <class T, class Alloc>
inline typename list<T, Alloc>::size_type
list<T, Alloc>::size() const
{
	size_type result = 0;
	result = stl_iterator::distance(begin(), end());
	return result;
}



//---------- element access
template <class T, class Alloc>
inline typename list<T, Alloc>::reference
list<T, Alloc>::front()
{
    return *begin();
}

template <class T, class Alloc>
inline typename list<T, Alloc>::reference
list<T, Alloc>::back()
{
    iterator tmp = end();
    return *(--tmp);
}


//---------- modifiers
template <class T, class Alloc>
inline typename list<T, Alloc>::iterator 
list<T, Alloc>::insert(iterator position, const value_type& val)
{
    list_node *tmp = create_node(val);
    tmp->next = position.node;
    tmp->prev = position.node->prev;
    position.node->prev->next = tmp;
    position.node->prev = tmp;

    return iterator(tmp);
}

template <class T, class Alloc>
inline typename list<T, Alloc>::iterator
list<T, Alloc>::insert(iterator position, size_type n, const value_type& val)
{
	while (n-- > 0)
	{
		list_node* tmp = create_node(val);
		tmp->next = position.node;
		tmp->prev = position.node->prev;
		position.node->prev->next = tmp;
		position.node->prev = tmp;

		position.node = tmp;
	}

	return position;
}


template <class T, class Alloc>
template <class InputIterator>
inline typename list<T, Alloc>::iterator 
list<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last)
{
	for (; first!=last; ++first)
	{
		insert(position, *first);
	}
	return position;
}

template <class InputIterator>
inline bool operator!=(InputIterator first, InputIterator second)
{
    return first == second;
}


template <class T, class Alloc>
inline typename list<T, Alloc>::iterator
list<T, Alloc>::erase(iterator position)
{
    position.node->prev->next = position.node->next;
    position.node->next->prev = position.node->prev;
    list_node* next_node = position.node->next;
    destroy_node(position.node);
    return iterator(next_node);
}

template <class T, class Alloc>
inline void list<T, Alloc>::push_front(const value_type& value)
{
    insert(begin(), value);
}

template <class T, class Alloc>
inline void list<T, Alloc>::push_back(const value_type& value)
{
    insert(end(), value);
}

template <class T, class Alloc>
inline void list<T, Alloc>::pop_front()
{
    erase(begin());
}

template <class T, class Alloc>
inline void list<T, Alloc>::pop_back()
{
    iterator tmp = end();
    erase(--tmp);
}




template <class T, class Alloc>
inline typename list<T, Alloc>::list_node* 
list<T, Alloc>::get_node()
{
    return static_cast<list_node*>(list_alloc::allocate(1));
}

template <class T, class Alloc>
inline void list<T, Alloc>::put_node(list_node* p)
{
    list_alloc::deallocate(p, sizeof(T));        // 释放空间
}

template <class T, class Alloc>
inline typename list<T, Alloc>::list_node*
list<T, Alloc>::create_node(const value_type& value)
{
    list_node* p = get_node();
    try
    {
        SimpleSTL::construct(&p->data, value);
    }
    catch(const std::exception& e)
    {
        put_node(p);
        throw;
    }
    return p;
}

template <class T, class Alloc>
inline void list<T, Alloc>::destroy_node(list_node* p)
{
    SimpleSTL::destroy(&p->data);
    put_node(p);
}

template <class T, class Alloc>
inline void list<T, Alloc>::empty_initialize()
{
    node = get_node();
    node->next = node;
    node->prev = node;
}

template <class T, class Alloc>
inline void list<T, Alloc>::clear()
{
    list_node* cur = node->next;
    while (cur != node)
    {
        list_node* tmp = cur;
        cur = cur->next;
        destroy_node(tmp);
    }
    node->next = node;
    node->prev = node;
}

template <class T>
inline void swap(T* p1, T *p2)
{
    T* temp = p1;
    p1 = p2;
    p2 = temp;
}

#endif
