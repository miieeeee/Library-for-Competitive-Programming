#pragma once

#include "HashMap.hpp"
#include "Concept/MyConcept.hpp"

template<my_concept::Hashable Key, typename Value>
struct CustomHashMap{
    HashMap<Value> hm;
    CustomHashMap(int n) : hm(n) {}
    Value &operator[](const Key &k){
        unsigned long long h = std::hash<Key>{}(k);
        return hm[h];
    }
    Value get(const Key &k, Value default_value){
        unsigned long long h = std::hash<Key>{}(k);
        return hm.get(h, default_value);
    }
};