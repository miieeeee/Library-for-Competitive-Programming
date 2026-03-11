#pragma once

#include <functional>
#include <concepts>

namespace my_concept{
    template <typename T>
    concept Hashable = requires(T x) {
        { std::hash<T>{}(x) } -> std::convertible_to<unsigned long long>;
    };
};