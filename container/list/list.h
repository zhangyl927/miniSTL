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
    using list_node_allocator = SimpleAlloc<list_node>;
    using iterator = __list_iterator<T>;
    using list_alloc = SimpleAlloc<list_node>;
    
private:
    list_node* node;

public:    // ctor && dctor
    list();
    ~list();
    //list(const list&);
    //list& operator=(const list &);

    
public:     // iterators
    iterator begin();
    iterator end();
    //reverse_iterator rbegin();
    //reverse_iterator rend();
    // const_iterator cbegin();
    // const_iterator cend();
    // const_iterator crbegin();
    // const_iterator crend();
    

public:         // capacity
    bool empty() const;
    //size_type size() const;

public:         // element access
    reference front();              // 获取链首元素值
    reference back();               // 获取链尾元素值

public:         // modifiers
    iterator insert(iterator position, const value_type& value);
    iterator erase(iterator position);
    void push_front(const value_type& value);
    void push_back(const value_type& value);
    void pop_front();
    void pop_back();

private:        // realize detail   
    list_node* get_node();          // 配置一个节点并传回
    void put_node(list_node* p);    // 释放一个节点
    list_node* create_node(const value_type& value);
    void empty_initialize();        // 产生一个空链表
    void clear();                   // 清空链表
};

//---------- ctor
template <class T, class Alloc>
list<T, Alloc>::list()
{
    empty_initialize();             
}

template <class T, class Alloc>
list<T, Alloc>::~list()
{
    clear();
    put_node(node);
}

//---------- iterators
template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::begin()
{
    return iterator(node->next);
}

template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::end()
{
    return iterator(node);
}



//---------- capacity
template <class T, class Alloc>
bool list<T, Alloc>::empty() const
{
    return node->next==node;
}

// template <class T, class Alloc>
// typename list<T, Alloc>::size_type
// list<T, Alloc>::size() const
// {
//     size_type result = 0;
//     distance(begin(), end(), result);
//     return result;
// }



//---------- element access
template <class T, class Alloc>
typename list<T, Alloc>::reference
list<T, Alloc>::front()
{
    return *begin();
}

template <class T, class Alloc>
typename list<T, Alloc>::reference
list<T, Alloc>::back()
{
    iterator tmp = end();
    return *(--tmp);
}


//---------- modifiers
template <class T, class Alloc>
typename list<T, Alloc>::iterator 
list<T, Alloc>::insert(iterator position, const value_type& value)
{
    list_node *tmp = create_node(value);
    tmp->next = position.node;
    tmp->prev = position.node->prev;
    position.node->prev->next = tmp;
    position.node->prev = tmp;

    return iterator(tmp);
}

template <class T, class Alloc>
typename list<T, Alloc>::iterator
list<T, Alloc>::erase(iterator position)
{
    position.node->prev->next = position.node->next;
    position.node->next->prev = position.node->prev;
    list_node* next_node = position.node->next;
    put_node(position.node);
    
    return iterator(next_node);
}

template <class T, class Alloc>
void list<T, Alloc>::push_front(const value_type& value)
{
    insert(begin(), value);
}

template <class T, class Alloc>
void list<T, Alloc>::push_back(const value_type& value)
{
    insert(end(), value);
}

template <class T, class Alloc>
void list<T, Alloc>::pop_front()
{
    erase(begin());
}

template <class T, class Alloc>
void list<T, Alloc>::pop_back()
{
    iterator tmp = end();
    erase(--tmp);
}






template <class T, class Alloc>
typename list<T, Alloc>::list_node* 
list<T, Alloc>::get_node()
{
    return reinterpret_cast<list_node*>(list_alloc::allocate(1));
}

template <class T, class Alloc>
void list<T, Alloc>::put_node(list_node* p)
{
    list_alloc::destroy(p);                      // 析构对象
    list_alloc::deallocate(p, sizeof(T));        // 释放空间
}

template <class T, class Alloc>
typename list<T, Alloc>::list_node*
list<T, Alloc>::create_node(const value_type& value)
{
    list_node* p = get_node();
    try
    {
        SimpleAlloc<T>::construct(&p->data, value);
    }
    catch(const std::exception& e)
    {
        put_node(p);
        throw;
    }
    return p;
}

template <class T, class Alloc>
void list<T, Alloc>::empty_initialize()
{
    node = get_node();
    node->next = node;
    node->prev = node;
}

template <class T, class Alloc>
void list<T, Alloc>::clear()
{
    list_node* cur = node->next;
    while (cur != node)
    {
        list_node* tmp = cur;
        cur = cur->next;
        put_node(tmp);          // 销毁、释放一个节点
    }
    node->next = node;
    node->prev = node;
}