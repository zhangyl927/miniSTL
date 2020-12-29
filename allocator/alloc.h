#ifndef __ALLOC__H
#define __ALLOC__H

#include <cstdlib>

#define NUM 20

enum __freeListSetting
{
	__ALIGN = 8,
	__MAX_BYTES = 128,
	__NFREELISTS = __MAX_BYTES/__ALIGN
};

template <class T>
class __default_alloc
{
public:
	static void* allocate(size_t n);
	static void deallocate(void* p, size_t n);
private: 
	struct obj
	{
		obj* free_list_link;							// free_list 节点构造
	};

	static obj* volatile freeList[__NFREELISTS];		// 16 个 free_list

	static size_t RoundUp(size_t bytes)                 // 调整到 8 的倍数
	{
		return (bytes+__ALIGN-1) & ~(__ALIGN-1);
	}

	static size_t freeListFind(size_t bytes)			// 返回在 第几个 free_list 上，从第 0 个开始
	{
		return (bytes+__ALIGN-1)/__ALIGN - 1;
	}

	static void* refill(size_t n);
	static char* chunk_alloc(size_t size, int& nobjs);

	static char* start_free;
	static char* end_free;
	static size_t heap_size;
};

template <class T>
char* __default_alloc<T>::start_free = nullptr;

template <class T>
char* __default_alloc<T>::end_free = nullptr;

template <class T>
size_t __default_alloc<T>::heap_size = 0;

template <class T>
typename __default_alloc<T>::obj* volatile 
__default_alloc<T>::freeList[__NFREELISTS] = { nullptr, nullptr, nullptr, nullptr,
												nullptr, nullptr, nullptr, nullptr, 
												nullptr, nullptr, nullptr, nullptr, 
												nullptr, nullptr, nullptr, nullptr };


template <class T>
void* __default_alloc<T>::allocate(size_t n)
{
	obj* volatile * myfreelist;
	obj* result;

	myfreelist = freeList + freeListFind(n);		// 找到 n 所在的 free_list
	result = *myfreelist;
	if (nullptr == result)							// free_list 上没有块
	{
		void *r = refill(RoundUp(n));				// 填充 free_list 
		return r;
	}
	*myfreelist = result->free_list_link;			// 移除 free_list 上第一块
	return result;
}

template <class T>
void __default_alloc<T>::deallocate(void* p, size_t n)
{
	obj* volatile * myfreelist;
	myfreelist = freeList + freeListFind(n);
	obj* q = static_cast<obj*>(p);

	q->free_list_link = *myfreelist;				// 回收块放在 free_list 链首
	*myfreelist = q;
}

template <class T>
void* __default_alloc<T>::refill(size_t n)
{
	int nobjs = NUM;
	char* chunk = chunk_alloc(n, nobjs);

	if (1 == nobjs)									// 内存池只能分一块了
	{
		return static_cast<void*>(chunk);
	}

	obj* volatile * myfreelist;
	obj* result;
	obj* currObj;
	obj* nextObj;

	myfreelist = freeList+freeListFind(n);
	result = reinterpret_cast<obj*>(chunk);

	nextObj = reinterpret_cast<obj*>(chunk+n);
	*myfreelist = nextObj;

	// 切割内存池获取的块，挂到 free_list 上
	for (int i=1; ; i++)
	{
		currObj = nextObj;
		nextObj = reinterpret_cast<obj*>(reinterpret_cast<char*>(nextObj)+n);		// 第一块返回，从第二块开始挂
		if (nobjs-1 == i)
		{
			currObj->free_list_link = nullptr;
			break;
		}
		else
		{
			currObj->free_list_link = nextObj;
		}
	}

	return result;
}

template <class T>
char* __default_alloc<T>::chunk_alloc(size_t size, int& nobjs)
{
	char* result;
	size_t total_bytes = nobjs*size;				// 所需总区块的空间大小
	size_t bytes_left = end_free-start_free;		// 内存池剩余空间大小

	if (bytes_left >= total_bytes)					// 内存池剩余空间足以分配
	{
		result = start_free;
		start_free += total_bytes;					// 升高水位
		return result;
	}
	else if (bytes_left >= size)					// 足以分配一个以上区块
	{
		nobjs = bytes_left/size;					// 最多能分配区块数
		total_bytes = nobjs*size;
		result = start_free;
		start_free += total_bytes;
		return result;
	}
	else											// 一个区块都不能提供
	{
		if (bytes_left > 0)										// 将内存池残余空间挂到 free_list 上
		{
			obj* volatile * myfreelist;
			myfreelist = freeList+freeListFind(bytes_left);
			reinterpret_cast<obj*>(start_free)->free_list_link = *myfreelist;
			*myfreelist = reinterpret_cast<obj*>(start_free);
		}

		size_t bytes_to_get = 2*total_bytes+RoundUp(heap_size>>4);		// 应该注入内存池的空间
		start_free = static_cast<char*>(malloc(bytes_to_get));
		// 这个 if 没有机会执行吧？allocate 分配开始时，先查找了 freelist，没找到才 调用 refill，现在为什么有了？
		// 找到 大于 size 的块倒是有可能；那可以直接 i = size+1;
		if (nullptr == start_free)							// 请求注入内存池失败，heap 空间不足
		{													// 在 free_list 中查找可用空间
			obj* volatile * myfreelist;						
			obj* p;
			int i;
			for (i=size; i<=__MAX_BYTES; i+=__ALIGN)			// 从 size 大小的 free_list 开始遍历
			{
				myfreelist = freeList+freeListFind(i);
				p = *myfreelist;
				if (nullptr != p)							// 找到可用的块
				{
					*myfreelist = p->free_list_link;
					start_free = reinterpret_cast<char*>(p);
					end_free = start_free+i;
					return chunk_alloc(size, nobjs);		// 在调用一次，此时内存池有一个块可用
				}
			}
		}
		heap_size += bytes_to_get;
		end_free = start_free+bytes_to_get;
		return chunk_alloc(size, nobjs);					// 再调用一次，此时内存池应该已经注入活水
	}
	
}

#endif
