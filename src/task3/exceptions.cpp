#include "exceptions.h"


const char* NotEnoughSlotsError :: what() const noexcept {
    return "Not enough slots available.";
}

const char* EmptySlotError :: what() const noexcept {
    return "Slot is empty.";
}

const char* ObjectNotFoundError :: what() const noexcept {
    return "Object not found in storage.";
}
