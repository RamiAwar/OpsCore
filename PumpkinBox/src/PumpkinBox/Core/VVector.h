#pragma once

#include "Core.h"
#include "Log.h"

#ifdef PB_PLATFORM_WINDOWS
    #include <Windows.h>
#endif

#include <stdexcept>

namespace pb {

    template<typename T>
    class VVector {

    private:

        T* base_block;
        uint32_t page_count;
        uint32_t  block_offset;
        uint32_t reserved;
        size_t _size;
        DWORD PAGE_SIZE;

    public:

        VVector(uint32_t reserve)
            : block_offset(0), _size(0), page_count(1), reserved(reserve) {

            SYSTEM_INFO info;
            GetSystemInfo(&info);
            PAGE_SIZE = info.dwPageSize;

            base_block = (T*)VirtualAlloc(NULL, reserved, MEM_RESERVE, PAGE_READWRITE);

            _commit();
        }

        VVector() : VVector(0) {}

        ~VVector() {

            VirtualFree(base_block, 0, MEM_RELEASE);

        }

        VVector(const VVector& other)
            :reserved(other.reserved),
             _size(other._size),
             page_count(other.page_count),
             block_offset(other.block_offset),
             PAGE_SIZE(other.PAGE_SIZE)
        {
            base_block = (T*)VirtualAlloc(NULL, reserved, MEM_RESERVE, PAGE_READWRITE);
            base_block = (T*)VirtualAlloc((LPVOID)base_block, ((long long)page_count) * PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE);
            
            // Copy all elements one by one (could be parallelized)
            // TODO: parallelize
            for (int i = 0; i < _size; i++) {
                base_block[i] = other.base_block[i];
            }
        }


        inline T& operator[](int index) {
            if (index < 0) throw std::out_of_range("VVector: Attempt to access negative indices.");
            if (index >= _size) throw std::out_of_range("VVector : Index out of range");
            return base_block[index];
        }

        inline T& at(int index) {
            if (index < 0) throw std::out_of_range("VVector: Attempt to access negative indices.");
            if (index >= _size) throw std::out_of_range("VVector : Index out of range");
            return base_block[index];
        }


        /**
        *   Add element to the back of the array
        **/
        void push_back(T element) {

            if (block_offset == PAGE_SIZE) {
                _commit();
                block_offset = 0;
            }

            base_block[_size++] = element;
            block_offset += sizeof(T);
        }

        /**
        *   Erase element at index and move all elements back
        **/
        void erase(int index) {
            if (index < 0) throw std::out_of_range("VVector: Attempt to access negative indices.");
            if (index > 0 && index < _size) {
                for (int i = index + 1; i < _size; i++) {
                    base_block[i - 1] = base_block[i];
                }
            }
            _size--;
            block_offset -= sizeof(T);
        }

        size_t size() {
            return _size;
        }

        uint32_t _block_offset() {
            return block_offset;
        }

        DWORD _page_size() {
            return PAGE_SIZE;
        }

        T* _get_base_block() {
            return base_block;
        }

        uint32_t _get_page_count() {
            return page_count;
        }

    private:

        void _commit() {

            base_block = (T*)VirtualAlloc((LPVOID)base_block, ((long long)page_count++) * PAGE_SIZE, MEM_COMMIT, PAGE_READWRITE);
            PB_ASSERT( base_block != NULL, "Virtual memory allocation failure: ", GetLastError());

        }

    };

}