template<typename T>
struct SlopeTrick{
    priority_queue<T> _L;
    priority_queue<T, vector<T>, greater<T>> _R;
    T _min_f;

    SlopeTrick() : _min_f(0) {}

    void add_constant(T x) {
        _min_f += x;
    }

    void add_x_minus_a(T a) {
        if(!_L.empty()) {
            T l0 = _L.top();
            _min_f += max(T(0), l0 - a);
        }
        _L.push(a);
        T x = _L.top();
        _L.pop();
        _R.push(x);
    }

    void add_a_minus_x(T a) {
        if(!_R.empty()) {
            T r0 = _R.top();
            _min_f += max(T(0), a - r0);
        }
        _R.push(a);
        T x = _R.top();
        _R.pop();
        _L.push(x);
    }

    void add_abs(T a) {
        add_x_minus_a(a);
        add_a_minus_x(a);
    }

    int size() {
        return _L.size() + _R.size();
    }

    T min() {
        return _min_f;
    }

    T get(T x) {
        priority_queue<T> L2;
        priority_queue<T, vector<T>, greater<T>> R2;

        T ret = _min_f;
        while(_L.size()) {
            T a = _L.top();
            _L.pop();
            L2.push(a);
            ret += max(T(0), a - x);
        }

        while(_R.size()) {
            T a = _R.top();
            _R.pop();
            R2.push(a);
            ret += max(T(0), x - a);
        }
        
        swap(_L, L2);
        swap(_R, R2);

        return ret;
    }
    
    void clear_l() {
        _L = {};
    }

    void clear_r() {
        _R = {};
    }

    static void merge(SlopeTrick &a, SlopeTrick &b) {
        if(a.size() < b.size()) swap(a, b);
        while(b._L.size()) {
            auto c = b._L.top();
            b._L.pop();
            a.add_a_minus_x(c);
        }
        while(b._R.size()) {
            auto c = b._R.top();
            b._R.pop();
            a.add_x_minus_a(c);
        }

        a.add_constant(b._min_f);
    }
};
