#include <iostream>

#include "MemReserver.h"

class SomeClass {
private:
    int* data = new int[] {10, 20, 30};
    int a, b, c;

public:
    SomeClass() {
        std::cout << "SomeClass created.\n";
    }
    SomeClass(int a, int b, int c)
        :a(a), b(b), c(c)
    {
        std::cout << "SomeClass created with args: " << a << ", " << b << ", " << c << "\n";
    }
    ~SomeClass() {
        delete[] data;
        data = nullptr;
        std::cout << "SomeClass destroyed.\n";
    }
};

int main() {
    MemReserver<std::string, 3> str_reserver;

    auto& str1 = str_reserver.create("Hello");
    auto& str2 = str_reserver.create("World");
    auto& str3 = str_reserver.create("C++");

    std::cout << "Created strings:\n";
    std::cout << "str1: " << str1 << "\n";
    std::cout << "str2: " << str2 << "\n";
    std::cout << "str3: " << str3 << "\n";

    try {
        str_reserver.create();
    } catch (NotEnoughSlotsError& e) {
        std::cout << e.what() << std::endl;
    }

    size_t obj1_index = str_reserver.position(str2);
    std::cout << "str2 index: " << obj1_index << std::endl;
    std::cout << str_reserver.get(obj1_index) << std::endl;


    MemReserver<SomeClass, 2> sc_reserver;

    auto& obj1 = sc_reserver.create();
    auto& obj2 = sc_reserver.create(1, 2, 3);

    try {
        sc_reserver.create();
    } catch (NotEnoughSlotsError& e) {
        std::cout << e.what() << std::endl;
    }

    sc_reserver.remove(sc_reserver.position(obj1));

    try {
        auto& obj3 = sc_reserver.get(0);
    } catch (EmptySlotError& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
