#include "DataStructure/AreaOfUnionOfRectangle/AreaOfUnionOfRectangles.hpp"
#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    AreaOfUnionOfRectangle area;
    for(int i=0; i<n; i++) {
        long long l, d, r, u;
        cin >> l >> d >> r >> u;
        area.add(l, d, r, u);
    }

    cout << area.get() << endl;
}