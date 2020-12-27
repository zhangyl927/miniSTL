#include "allocator.h"

template <class T>
struct StackNode
{
	T val;
	StackNode* next;
};

template <class T, class Alloc>
class Stack
{
	public:
		typedef StackNode<T> Node;

		typedef typename Alloc::template rebind<Node>::other allocator; 		// 将 simpleAlloc 模板中的 T 变为 Node 类型

	public:
		Stack() { head = nullptr; }
		~Stack() 
		{ 
			clear(); 
		}
		void clear()
		{
			Node* cur = head;
			while (nullptr != cur)              // 从头开始往后删除；
			{
				Node* tmp = cur->next;
				alloc.destroy(cur);             // 析构对象
				alloc.deallocate(cur, sizeof(Node));        // 回收空间
				cur = tmp;
			}
			count = 0;
			head = nullptr;
		}

		void push(T elements)
		{
			count++;
			Node* newNode = reinterpret_cast<Node*>(alloc.allocate(sizeof(T)));                  // 分配空间
			alloc.construct(reinterpret_cast<Node*>(newNode), Node());  // 构造对象
			newNode->next = head;
			newNode->val = elements;
			head = newNode;
		}

		void pop()
		{
			count--;
			Node* tmp = head->next;
			alloc.destroy(head);
			alloc.deallocate(head,sizeof(Node));
			head = tmp;
		}

		int size()
		{
			return count;
		}

	private:
		allocator alloc;
		Node* head;
		int count = 0;
};
