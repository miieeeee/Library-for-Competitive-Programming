#pragma once

/// @brief Binary Trie data structure. k番目の要素をとれるmultisetみたいな感じ.
/// @tparam T Type of the elements stored in the trie
/// @tparam SIZE ワードサイズ(入れる数字の最大のビット数)
template<typename T, int SIZE>
struct BinaryTrie{
    struct Node{
        array<Node*, 2> nxt;
        int cnt;
        int prefix_cnt;
        Node() : cnt(0){
            fill(nxt.begin(), nxt.end(), nullptr);
        }
    };
    Node* start;
    T xor_cum = 0;
    BinaryTrie(){
        start = new Node(); 
    }

    // 追加
    void add(T x){
        x ^= xor_cum;
        Node* node = start;
        for(int i=SIZE-1; i>=0; i--){
            int val = x>>i&1;
            node->prefix_cnt++;
            Node* nxt = node->nxt[val];
            if(!nxt){
                nxt = new Node();
                node->nxt[val] = nxt;
            }
            node = nxt;
        }
        node->prefix_cnt++;
        node->cnt++;
    }

    // 削除
    void del(T x){
        if(count(x) == 0) return;
        x ^= xor_cum;
        Node* node = start;
        for(int i=SIZE-1; i>=0; i--){
            int val = x>>i&1;
            node->prefix_cnt--;
            Node* nxt = node->nxt[val];
            if(!nxt){
                nxt = new Node();
                node->nxt[val] = nxt;
            }
            node = nxt;
        }
        node->prefix_cnt--;
        node->cnt--;
    }

    // xが何回追加されたか
    int count(T x){
        x ^= xor_cum;
        Node *node = start;
        for(int i=SIZE-1; i>=0; i--){
            int val = x>>i&1;
            node = node->nxt[val];
            if(!node) return 0;
        }
        return node->cnt;
    }

    /// @brief get kth smallest element (0-indexed)
    /// @param k 
    /// @return T, kth smallest element
    T kth_element(int k){
        assert(k >= 0);
        if(start->prefix_cnt <= k) return -1;
        k++;
        int add = 0;
        Node *node = start;
        T ret = 0;
        for(int i=SIZE-1; i>=0; i--){
            assert(node != nullptr);
            int val = xor_cum>>i&1;
            auto left = node->nxt[val];
            auto right = node->nxt[1^val];
            
            if(left != nullptr && left->prefix_cnt + add >= k){
                node = left;
                ret <<= 1;
            }
            else{
                add += (left == nullptr ? 0 : left->prefix_cnt);
                node = right;
                ret = (ret<<1) + 1;
            }
        }
        return ret;
    }

    int count_less_than(T x) {
        Node *node = start;
        int ret = 0;
        for(int i=SIZE-1; i>=0; i--) {
            if(node == nullptr) break;
            int val = xor_cum>>i&1;
            auto left = node->nxt[val];
            auto right = node->nxt[1^val];

            if(x>>i&1) {
                if(left != nullptr) ret += left->prefix_cnt;
                node = right;
            }
            else {
                node = left;
            }
        }

        return ret;
    }

    // 追加した値、これから追加する値すべてにxor xを作用させる
    void apply_xor(T x){
        xor_cum ^= x;
        return;
    }
};
