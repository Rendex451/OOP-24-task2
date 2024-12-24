#pragma once

#include <vector>
#include <stdexcept>

template <std::size_t Size>
class Mask {
private:
    int mask[Size];

public:
    Mask(std::initializer_list<int> init);
    size_t size() const;
    int at(size_t index) const;
    template <typename Container>
    void slice(Container& container) const;
    template <typename Container, typename Func>
    Container transform(const Container& container, Func func) const;
    template <typename Container, typename Func>
    Container slice_and_transform(const Container& container, Func func) const;
};

template<std::size_t Size>
int Mask<Size>::at(size_t index) const {
    if (index >= Size) {
        throw std::out_of_range("Index out of range!");
    }
    return mask[index];
}

template<size_t Size>
Mask<Size>::Mask(std::initializer_list<int> init) {
    if (init.size() != Size) {
        throw std::invalid_argument("Initializer list size must match mask size!");
    }
    std::copy(init.begin(), init.end(), mask);
    for (int value : mask) {
        if (value != 0 && value != 1) {
            throw std::invalid_argument("Mask values must be 0 or 1!");
        }
    }
}

template<std::size_t Size>
template<typename Container>
void Mask<Size>::slice(Container &container) const {
    auto it = container.begin();
    size_t idx = 0;
    while (it != container.end()) {
        if (mask[idx % Size] == 0) {
            it = container.erase(it);
        } else {
            it++;
        }
        idx++;
    }
}

template<size_t Size>
template<typename Container, typename Func>
Container Mask<Size>::transform(const Container &container, Func func) const {
    Container result = container;
    auto it = result.begin();
    size_t idx = 0;
    for (; it != result.end(); ++it, ++idx) {
        if (mask[idx % Size] == 1) {
            *it = func(*it);
        }
    }
    return result;
}

template<size_t Size>
template<typename Container, typename Func>
Container Mask<Size>::slice_and_transform(const Container &container, Func func) const {
    Container result;
    size_t idx = 0;
    for (const auto& value : container) {
        if (mask[idx % Size] == 1) {
            result.push_back(func(value));
        }
        idx++;
    }
    return result;
}

template<size_t Size>
size_t Mask<Size>::size() const {
    return Size;
}
