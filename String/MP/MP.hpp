#include<bits/stdc++.h>
using namespace std;

vector<int> MP(string &s){
    int n = s.size();
    vector<int> mpArray(n+1, -1);
    for(int i=0; i<n; i++){
        int j = mpArray[i];
        while(j >= 0 && s[i] != s[j]){
            j = mpArray[j];
        }
        mpArray[i+1] = j+1;
    }
    return mpArray;
}