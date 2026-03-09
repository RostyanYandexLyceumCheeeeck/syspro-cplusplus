#ifndef __SCOPEDPOINTERDC_H__
#define __SCOPEDPOINTERDC_H__

#include <iostream>


// Scoped Pointer Deep Copying
template<typename T>
class ScopedPtrDC {
    T* ptr_ = nullptr;

public:
    ScopedPtrDC(T* raw = nullptr) : ptr_(new T(*raw)) {}
    ScopedPtrDC(const ScopedPtrDC& other) : ptr_(new T(*other.ptr_)) {}
    ScopedPtrDC(ScopedPtrDC&& other) noexcept { std::swap(ptr_, other.ptr_); }

    ScopedPtrDC& operator=(const ScopedPtrDC& other) {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_ ? new T(*other.ptr_) : nullptr;
        }
        return *this;
    }

    ScopedPtrDC& operator=(ScopedPtrDC&& other) noexcept {
        if (this != &other) { 
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
        }
        return *this;
    }
    
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }

    ~ScopedPtrDC() { if (ptr_) { delete ptr_; } }
};

#endif // __SCOPEDPOINTERDC_H__