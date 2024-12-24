#pragma once

#include <exception>

class NotEnoughSlotsError : public std::exception {
public:
    const char* what() const noexcept override;
};

class EmptySlotError : public std::exception {
public:
    const char* what() const noexcept override;
};

class ObjectNotFoundError : public std::exception {
public:
    const char* what() const noexcept override;
};
