#ifndef __LIST_NODE_H
#define __LIST_NODE_H

template <class T>
struct __list_node
{
    __list_node* prev;
    __list_node* next;
    T data;
};

#endif