#include "Mask.h"

#include <iostream>

int main() {
    Mask<3> mask = {1, 0, 0};
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7};

    mask.slice(data);
    for (const auto& val : data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    Mask<3> transform_mask = {1, 0, 1};
    std::vector<int> transform_data = {10, 20, 30, 40, 50};

    auto transformed = transform_mask.transform(transform_data, [](int x) { return x * 2; });
    for (const auto& val : transformed) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    auto slice_transformed = transform_mask.slice_and_transform(transform_data, [](int x) { return x + 5; });
    for (const auto& val : slice_transformed) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
