#pragma once

struct SuffixAutomaton {
    struct State {
        int suffix_link, sz;
        unordered_map<char, int> nxt;
    };
    vector<State> states;
    private:
        int _last;
        int _cur;

        int find_suffix_with_transition(int start, int nxt_to, char c) {
            int v = start;
            while(v != -1 && !states[v].nxt.contains(c)) {
                states[v].nxt[c] = nxt_to;
                v = states[v].suffix_link;
            }
            return v;
        }


        void redirect_transitions_to_clone(int start, int orig, int clone, char c) {
            int v = start;
            while(v != -1 && states[v].nxt[c] == orig) {
                states[v].nxt[c] = clone;
                v = states[v].suffix_link;
            }
        }

    public:
        SuffixAutomaton(string s="") : states(1, State{-1, {}}), _last(0) {
            for(auto c : s) extend(c);
        }

        void extend(char c) {
            _cur = states.size();
            states.push_back(State{-1, states[_last].sz+1, {}});
            int p = find_suffix_with_transition(_last, _cur, c);
            if(p == -1) {
                states[_cur].suffix_link = 0;
            }
            else {
                int q = states[p].nxt[c];
                if(states[q].sz == states[p].sz+1) {
                    states[_cur].suffix_link = q;
                }
                else {
                    int clone = states.size();
                    states.emplace_back(states[q]);
                    states[clone].sz = states[p].sz+1;
                    states[_cur].suffix_link = clone;
                    states[q].suffix_link = clone;
                    redirect_transitions_to_clone(p, q, clone, c);

                }
            }
            _last = _cur;
        }

        vector<int> get_terminals() {
            int v = _last;
            vector<int> terminals;
            while(v != -1) {
                terminals.push_back(v);
            }

            return terminals;
        }

        void tsort() {
            int n = states.size();
            vector<int> order;
            {
                order.reserve(n);
                vector<vector<int>> sid(n+1);
                for(int i=0; i<n; i++) sid[states[i].sz].push_back(i);
                for(int i=0; i<n; i++) {
                    if(!sid[i].empty()) copy(begin(sid[i]), end(sid[i]), back_inserter(order));
                }
            }
            {
                vector<State> states2;
                states2.reserve(n);
                for(int i=0; i<n; i++) states2.emplace_back(move(states[order[i]]));
                states.swap(states2);
            }
            vector<int> inv(n);
            for(int i=0; i<n; i++) inv[order[i]] = i;
            for(auto &state : states) {
                for(auto &[_, to] : state.nxt) to = inv[to];
                if(state.suffix_link != -1) state.suffix_link = inv[state.suffix_link];
            }
        }

        int size() { return states.size(); }
};