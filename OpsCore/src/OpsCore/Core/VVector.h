#pragma once

#include "Core.h"
#include "Log.h"

#ifdef OC_PLATFORM_WINDOWS
    #include <Windows.h>
#endif

#include <stdexcept>

namespace oc {

    template<typename T>
    class VVector {

    private:

        T* base_block;
        uint32_t reserved;
        uint32_t page_count;
        uint32_t  block_offset;
        size_t _size;
        DWORD PAGE_SIZE;

    public:

        VVector(uint32_t reserve)
            : block_offset(0), _size(0), page_count(1), reserved(reserve) {

            SYSTEM_INFO info;
            GetSystemInfo(&info);
            PAGE_SIZE = info.dwPageSize;

            base_block = (T*)VirtualAlloc(NULL, reserve, MEM_RESERVE, PAGE_READWRITE);

            _commit();
        }

        ~VVector() {

            VirtualFree(base_block, 0, MEM_RELEASE);

        }


        inline T& operator[](int index) {
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
            OC_ASSERT( base_block != NULL, "Virtual memory allocation failure: ", GetLastError());

        }

    };

}