#include<bits/stdc++.h>
using namespace std;
typedef string::const_iterator State;
class ParseError {};

int number(State &begin);
int term(State &begin);
int expression(State &begin);
int factor(State &begin);
int p;
bool flag;
int pow_mod(int n, int k){
    if(k == 0) return 1;
    if(k == 1) return n;
    if(k%2 == 1) return (n*pow_mod(n,k-1))%p;
    int x = pow_mod(n, k/2);
    return (x*x)%p;
}
int inv(int n){
  return pow_mod(n, p-2);
}
int number(State &begin){
    int ret =0;
    while(isdigit(*begin)){
        ret = ret*10+(*begin - '0');
        ret %= p;
        begin++;
    }
    // cout << ret << endl;
    return ret;
}
int term(State &begin){
    int ret = factor(begin);
    while(true){
        if(*begin == '*'){
            begin++;
            ret *= factor(begin);
            ret %= p;
        }
        else if(*begin == '/'){
            begin++;
            int x = factor(begin);
            if(x == 0) {
              flag = false;
            }
            ret *= inv(x);
            ret %= p;
        }
        else{
            break;
        }
    }
    ret %= p;
    return ret;
}
int expression(State &begin) {
    int ret = term(begin);
    for (;;) {
        if (*begin == '+') {
            begin++;
            ret += term(begin);
            ret %= p;
        } else if (*begin == '-') {
            begin++;
            ret -= term(begin);
            ret = (ret+p)%p;
        } else {
            break;
        }
    }
    ret %= p;
    return ret;
}
int factor(State &begin) {
    if (*begin == '(') {
        begin++; // '('を飛ばす。
        int ret = expression(begin);
        begin++; // ')'を飛ばす。
        return ret;
    } else {
        return number(begin);
    }
}
bool solve(){
    string s;
    cin >> p;
    getline(cin, s);
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
    if(p == 0) return false;
    State begin = s.begin();
    begin++;
    flag = true;
    int ans = expression(begin);
    // cout << ans << endl;
    if(flag){
      cout << s.substr(1, s.size()-1) << " = " << ans << " (mod " << p << ")" << endl;
    }
    else cout << "NG" << endl;
    return true;
}
int main(){
    while(solve());
}
