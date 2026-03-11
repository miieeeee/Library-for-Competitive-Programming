#pragma once
#include <concepts>

namespace my_concept {

    template <typename T>
    concept Addable = requires(T a, T b) {
        { a + b } -> std::convertible_to<T>;
    };

    template <typename T>
    concept Multipliable = requires(T a, T b) {
        { a* b } -> std::convertible_to<T>;
    };

    template <typename M>
    concept Monoid = requires(M m, typename M::value_type a, typename M::value_type b) {
        { M::op(a, b) } -> std::same_as<typename M::value_type>;
        { M::id() } -> std::same_as<typename M::value_type>;
    };

    template <typename G>
    concept Group = Monoid<G> && requires(typename G::value_type a) {
        { a.inv() } -> std::same_as<typename G::value_type>;
    };

    template <typename T>
    concept Ring = requires(T a, T b) {
        { a + b } -> std::convertible_to<T>;
        { a* b } -> std::convertible_to<T>;
        { T::zero() } -> std::convertible_to<T>;
        { T::one() } -> std::convertible_to<T>;
    };

    template <typename T>
    concept Field = Ring<T> && requires(T a) {
        { a.inv() } -> std::convertible_to<T>;
    };

}  // namespace algebra
