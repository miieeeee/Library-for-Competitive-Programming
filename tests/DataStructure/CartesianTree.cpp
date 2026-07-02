#include "DataStructure/CartesianTree/CartesianTree.hpp"
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0; i<n; i++) cin >> a[i];
    CartesianTree<int> ct(a);

    for(int i=0; i<n; i++) cout << (ct.root == i ? i : ct.par[i]) << " ";
    cout << endl;
}