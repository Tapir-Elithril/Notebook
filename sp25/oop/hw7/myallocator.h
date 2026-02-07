#ifndef MY_ALLOCATOR_H
#define MY_ALLOCATOR_H
#include <cstddef>
#include <type_traits>
#include <climits>
#include <utility>
#include <iostream>

constexpr size_t MAX_POOLED_SIZE = 256;
//use memory pool if sizeof(object) <= 256Bytes
//use new & delete otherwise
constexpr size_t ALIGNMENT = 16; 
constexpr size_t MEMORY_POOL_SIZE = 65536;
constexpr size_t BLOCK_SIZE = 16;
constexpr size_t BLOCK_NUM = MEMORY_POOL_SIZE / BLOCK_SIZE;

//object free list
union obj {
    union obj *free_list_link;
    char data[1];
};
/*
free list[0](16B) -> free list[1](32B)
    |
    ↓
free_list_link
    |
    ↓
free_list_link
*/

class MemoryPoolAllocator {
public:
    static void* allocate(size_t size) {
        if (size <= MAX_POOLED_SIZE) {
            // Round up to the nearest ALIGNMENT
            size_t aligned_size = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
            //std::cout << "Pool request: " << size << " -> " << aligned_size << "\n";
            // Find the appropriate free list
            size_t index = aligned_size / ALIGNMENT - 1;
            if(index >= BLOCK_NUM)
                return ::operator new(size);

            obj* result = free_list[index];
            if(result) {
                free_list[index] = result->free_list_link;
                return result;
            } else
                return refill(aligned_size);
        } else {
            //std::cout << "Direct new: " << size << "\n"; 
            return ::operator new(size); // use global new for larger sizes
        }
    }

    static void deallocate(void* ptr, size_t size) {
        if (size <= MAX_POOLED_SIZE) {
            size = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
            
            size_t index = size / ALIGNMENT - 1;
            if(index >= BLOCK_NUM)
                ::operator delete(ptr);
                return;

            obj* block = static_cast<obj*>(ptr);
            block->free_list_link = free_list[index];
            free_list[index] = block;
            //restore free_list[index] to ptr
        } else {
            ::operator delete(ptr); // use global delete for larger sizes
        }
    }
private:
    static obj* free_list[BLOCK_NUM];
    static void* refill(size_t size) {
        //chunk(大块内存) allocation in memory(1 block at a time)
        const int refill_block_num = 1;
        char* chunk = static_cast<char*>(::operator new(refill_block_num * size));
        //add new blocks to free list
        obj* current = reinterpret_cast<obj*>(chunk);
        obj* next;
        for(int i = 1;i < refill_block_num; ++i) {
            next = reinterpret_cast<obj*>(chunk + i * size);
            current->free_list_link = next;
            current = next;
        }
        current -> free_list_link = nullptr;

        //return the first block
        size_t index = size / ALIGNMENT - 1;
        void* result = chunk;
        free_list[index] = current;
        return result;
    }
};

//static member initialization
obj* MemoryPoolAllocator::free_list[BLOCK_NUM] = {0};

//The interface of my allocator
template<typename T>
class MyAllocator{
public:
    typedef void _Not_user_specialized;
    typedef T value_type;
    typedef value_type *pointer;
    typedef const value_type *const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef std::true_type propagate_on_container_move_assignment;
    typedef std::true_type is_always_equal;  

    pointer address(reference _Val) const noexcept {
        return &_Val;
    }

    const_pointer address(const_reference _Val) const noexcept {
        return &_Val;
    }

    void deallocate(pointer _Ptr, size_type _Count) {
        MemoryPoolAllocator::deallocate(_Ptr, _Count * sizeof(T));
    }

    //initialize,push_back,resize
    pointer allocate(size_type _Count) {
        return static_cast<pointer>(MemoryPoolAllocator::allocate(_Count * sizeof(T)));
    }

    template<class _Uty> 
    void destroy(_Uty *_Ptr) {
        _Ptr->~_Uty();
    }

    template<class _Objty, class... _Types>
    void construct(_Objty *_Ptr, _Types&&... _Args) {
        //perfect forwarding,keep value type and avoid unnecessary copies
        //new (addr) type
        ::new ((void *)_Ptr) _Objty(std::forward<_Types>(_Args)...);
    }
};

#endif