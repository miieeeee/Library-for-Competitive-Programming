#pragma once

#include <functional>
#include <concepts>

namespace my_concept{
    template <typename T>
    concept Hashable = requires(T x) {
        { std::hash<T>{}(x) } -> std::convertible_to<unsigned long long>;
    };
};
/*
自作ハッシュの作り方
```
struct Hoge {
    int x;
    string s;
};

// Hoge 型の std::hash
namespace std {
    template <>
    struct hash<Hoge> {
        std::size_t operator()(const Hoge& hoge) const {
            return std::hash<std::string>()(hoge.s) ^ (std::hash<int>()(hoge.x) << 1);
        }
    };
}
```
*/