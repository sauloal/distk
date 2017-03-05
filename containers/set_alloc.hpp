#ifndef __SET_ALLOC_HPP
#define __SET_ALLOC_HPP

#include <vector>
#include <cassert>
#include <cstdlib>
#include <limits>
#include <set>

//http://forums.codeguru.com/showthread.php?406108-A-faster-std-set

/*
One of the slowest parts of std::set is... allocating and deallocating of memory.
When you use standard allocator it calls new and delete everytime you add/remove
element, and that makes it really slow.

I've written pool allocator, similar to boost::fast_pool_allocator but it frees
memory when set/map object is cleared or destroyed.

Using is very simple:

std::set<int, std::less<int>, bestAlloc<int> > s;

I hope you will find it useful
*/



#define PTR(x) *((T**)(&(x)))

template <typename T>
class bestAlloc
{
public:
	typedef T     value_type;

	typedef       value_type     * pointer;
	typedef const value_type     * const_pointer;
	typedef       value_type     & reference;
	typedef const value_type     & const_reference;
	typedef       std::size_t      size_type;
	typedef       std::ptrdiff_t   difference_type;

	template <typename U>
	struct rebind
	{
		typedef bestAlloc<U> other;
	};

	class Block
	{
	public:
		T* ptr;
		size_type size;

		Block(){};
		Block(const Block &b)
		{
			ptr  = b.ptr;
			size = b.size;
		}

		Block& operator=(const Block &b)
		{
			ptr  = b.ptr;
			size = b.size;

			return *this;
		}

		void Initialize()
		{
			for (size_type i=0; i<size-1; i++)
			{
				PTR(ptr[i]) = &ptr[i+1];
			}

			PTR(ptr[size-1]) = NULL;
		};
	};//class block

	std::vector<Block> m_vecBlocks;

	T* firstFree;

	size_type dSize;

	size_type numAllocated;

	void AddBlock()
	{
		Block b;
		b.size = dSize;

		if (dSize < 128*1024)dSize *= 4;

		assert(sizeof(T) >= sizeof(T*));

		b.ptr = (T*)(new char[b.size * sizeof(T)]);

		if (b.ptr == NULL) {
			throw std::bad_alloc();
		}

		b.Initialize(); // initialize list of pointers

		PTR(b.ptr[b.size-1]) = firstFree;

		firstFree = b.ptr;

		m_vecBlocks.push_back(b);
	}//AddBlock


	T* malloc_(size_type n)
	{
		assert(n == 1); // only single element malloc supported

		if (firstFree == NULL)
		{
			AddBlock();
		}

		T* ret    = firstFree;

		firstFree = PTR(*firstFree);

		numAllocated++;

		return ret;
	}


	void free_(void * const ptr, const size_type n)
	{
		assert(n == 1);

		if (ptr == NULL) {
			return;
		}

		T* p = (T*)ptr;

		PTR(*p)   = firstFree;

		firstFree = p;

		numAllocated--;

		if (numAllocated == 0) {
			releaseMemory();
		}
	} //free_


	void releaseMemory()
	{
		for (size_type i=0; i<m_vecBlocks.size(); i++)
		{
			delete [] ((char*)m_vecBlocks[i].ptr);
		}

		m_vecBlocks.clear();

		firstFree    = NULL;
		numAllocated = 0;
		dSize        = 8;
	} //releaseMemory()


public:
	bestAlloc()
	{
		dSize        = 8;
		numAllocated = 0;
		firstFree    = NULL;
		m_vecBlocks.clear();
    	}

	bestAlloc(const bestAlloc<T> &a)
	{
		dSize        = 8;
		numAllocated = 0;
		firstFree    = NULL;
		m_vecBlocks.clear();
	}

private:
	bestAlloc& operator=(const bestAlloc<T> &a)
	{
		dSize        = 8;
		numAllocated = 0;
		firstFree    = NULL;
		m_vecBlocks.clear();

		return *this;
	}

public:
    // not explicit, mimicking std::allocator [20.4.1]
	template <typename U>
	bestAlloc(const bestAlloc<U> &a)
    	{
		dSize        = 8;
		numAllocated = 0;
		firstFree    = NULL;
		m_vecBlocks.clear();
	}

	~bestAlloc()
	{
		releaseMemory();
	}

	static pointer address(reference r)
	{ return &r; }
	static const_pointer address(const_reference s)
	{ return &s; }
	static size_type max_size()
	{ return (std::numeric_limits<size_type>::max)(); }
	void construct(const pointer ptr, const value_type & t)
	{ new (ptr) T(t); }
	void destroy(const pointer ptr)
	{
		ptr->~T();
		(void) ptr; // avoid unused variable warning
	}

	// always different
	bool operator==(const bestAlloc &) const
	{ return false; }
	bool operator!=(const bestAlloc &) const
	{ return true; }

	pointer allocate(const size_type n)
	{
		const pointer ret = malloc_(n);

		if (ret == 0)
		{
			throw std::bad_alloc();
		}

		return ret;
	}

	pointer allocate(const size_type n, const void * const)
	{ return allocate(n); }

	pointer allocate()
	{
		const pointer ret = malloc_(1);

		if (ret == 0) {
			throw std::bad_alloc();
		}

		return ret;
	}

	void deallocate(const pointer ptr, const size_type n)
	{
		free_(ptr, n);
	}

	void deallocate(const pointer ptr)
	{
		free_(ptr, 1);
	}
}; //class bestAlloc


//typedef std::set< unsigned long , std::less<unsigned long>, bestAlloc<unsigned long> > orderedSetAlloc;
//typedef std::set< unsigned long > orderedSet;





/*
template<typename T>
class orderedSetAllocCls : public std::set< T , std::less<T>, bestAlloc<T> > {
    public:
        void reserve(size_t reserve_size) {
            //this->c.reserve(reserve_size);
			//this->get_allocator().allocate(reserve_size);
        }
		void resize(unsigned long t){}
		std::vector<T> get_container() {
			return std::vector<T>(this->begin(), this->end());
		}
};

typedef orderedSetAllocCls<unsigned long> orderedSetAlloc;

typedef orderedSetAlloc setuLongLess;
*/




template<typename T>
class orderedSetCls : public std::set< T , std::less<T> > {
	private:
		std::vector<T> cp;
		
    public:
        void reserve(size_t reserve_size) {
            //this->c.reserve(reserve_size);
			this->get_allocator().allocate(reserve_size);
        }
		void resize(size_t t){
			reserve(t);
		}
		std::vector<T> &get_container() {
			cp = std::vector<T>(this->begin(), this->end());
			return cp;
		}
};

typedef orderedSetCls     <unsigned long> orderedSet;

typedef orderedSet      setuLongLess;



/*
template<class T> using max_set  = std::set<T, std::greater<T> >;
template<class T> using min_set  = std::set<T, std::less<T> >;
typedef std::set<ulong, std::less<ulong> > setuLongLess;
*/


#undef PTR
#endif
