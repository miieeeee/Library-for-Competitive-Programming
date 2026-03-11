#pragma once

template<int X=26, char margin='a'>
struct Trie{
    struct Node{
        array<int, X> nxt;
        int cnt;
        int prefix_cnt;
        char alph;
        Node(char c) : alph(c), cnt(0), prefix_cnt(0){
            fill(nxt.begin(), nxt.end(), -1);
        }
    };
    vector<Node> nodes;
    Trie(char start='$'){
        nodes.push_back(Node(start));
    }

    void add(string s){
        int now = 0;
        for(auto c : s){
            nodes[now].prefix_cnt++;
            int k = c - margin;
            int id = nodes[now].nxt[k];
            if(id == -1){
                id = nodes.size();
                nodes.push_back(Node(c));
                nodes[now].nxt[k] = id;
            }
            now = id;
        }
        nodes[now].prefix_cnt++;
        nodes[now].cnt++;
    }

    int count(string s, bool prefix=false){
        int now = 0;
        for(auto c : s){
            int k = c - margin;
            int id = nodes[now].nxt[k];
            if(id == -1) return 0;
        }
        return (prefix ? nodes[now].prefix_cnt : nodes[now].cnt);
    }

    void del(string s){
        if(count(s) == 0) return;
        int now = 0;
        for(auto c : s){
            nodes[now].prefix_cnt--;
            int k = c - margin;
            int id = nodes[now].nxt[k];
            now = id;
        }
        nodes[now].prefix_cnt--;
        nodes[now].cnt--;
    }
};