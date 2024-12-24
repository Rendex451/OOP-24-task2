#pragma once

#include <cstdlib>
#include <stdexcept>

#include "exceptions.h"


template <typename T,  size_t N>
class MemReserver {
private:
    alignas(T) char storage_[N * sizeof(T)]{};
    bool occupied_[N] = {false};
    std::size_t count_ = 0;
    T* get_pointer(size_t index);

public:
    MemReserver() = default;
    template <typename... Args>
    T& create(Args&&... args);
    size_t count() const;
    T& get(size_t index);
    size_t position(const T& obj);
    void remove(size_t index);
    ~MemReserver();
};

template<typename T, size_t N>
T *MemReserver<T, N>::get_pointer(size_t index) {
    return reinterpret_cast<T*>(&storage_[index * sizeof(T)]);
}

template<typename T, size_t N>
MemReserver<T, N>::~MemReserver() {
    for (size_t i = 0; i < N; ++i){
        if (!occupied_[i]) {
            get_pointer(i)->~T();
        }
    }
}

template<typename T, size_t N>
size_t MemReserver<T, N>::position(const T& obj) {
    for (size_t i = 0; i < N; ++i) {
        if (occupied_[i] && get_pointer(i) == &obj) {
            return i;
        }
    }
    throw ObjectNotFoundError();
}

template<typename T, size_t N>
T &MemReserver<T, N>::get(size_t index) {
    if (index >= count_) {
        throw std::out_of_range("Index out of range.");
    }
    if (!occupied_[index]) {
        throw EmptySlotError();
    }
    return *get_pointer(index);
}

template<typename T, size_t N>
size_t MemReserver<T, N>::count() const {
    return count_;
}

template<typename T, size_t N>
template<typename... Args>
T &MemReserver<T, N>::create(Args &&... args) {
    for (std::size_t i = 0; i < N; ++i) {
        if (!occupied_[i]) {
            T* obj = new (get_pointer(i)) T(std::forward<Args>(args)...);
            occupied_[i] = true;
            count_++;
            return *obj;
        }
    }
    throw NotEnoughSlotsError();
}

template<typename T, size_t N>
void MemReserver<T, N>::remove(size_t index) {
    if (index >= count_) {
        throw std::out_of_range("Index out of range.");
    }
    if (!occupied_[index]) {
        throw EmptySlotError();
    }
    get_pointer(index)->~T();
    occupied_[index] = false;
}
