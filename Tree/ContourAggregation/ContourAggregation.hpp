#pragma once

#include "Concept/Algebra.hpp"
#include "DataStructure/SegTree.hpp"

template <typename G, my_concept::Monoid MX>
struct ContourAggregation {
    using X = MX::value_type;
    G g;

    private:

    public:
        ContourAggregation() {}
        ContourAggregation(G &_g): g(_g) {}

        // 重心分解して、各部分木のsegtreeを作成
        void build() {
        } 

};