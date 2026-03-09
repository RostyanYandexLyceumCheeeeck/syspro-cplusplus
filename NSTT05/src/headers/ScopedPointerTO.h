#ifndef __SCOPEDPOINTERTO_H__
#define __SCOPEDPOINTERTO_H__

#include <iostream>


// Scoped Pointer Transferring an Ownership 
template<typename T>
class ScopedPtrTO {
    T* ptr_ = nullptr;

public:
    ScopedPtrTO(T* raw = nullptr): ptr_(raw) {}
    ScopedPtrTO(const ScopedPtrTO&) = delete;
    ScopedPtrTO(ScopedPtrTO&& other) noexcept {
        if (this != &other) { 
            delete ptr_;
            ptr_ = std::move(other.ptr_);
        }
    }

    ScopedPtrTO& operator=(const ScopedPtrTO&) = delete;
    ScopedPtrTO& operator=(ScopedPtrTO&& other) noexcept {
        if (this != &other) { 
            delete ptr_;
            ptr_ = std::move(other.ptr_);
        }
        return *this;
    }

    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }

    ~ScopedPtrTO() { if (ptr_) { delete ptr_; } }
};


#endif // __SCOPEDPOINTERTO_H__