#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const int N = 1e6 + 10;
ll n,m;
ll a[N];
ll max(ll a, ll b) {return a > b?a:b;}
void solve()
{
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<int> f(n+5, 0);
    // 求最大值
    for(int i = 1; i <= n; i++) {
        f[i] = max(f[i], a[i] + f[i - 1]);
        for(int j = i - 1; j >= 0; j--) {
            f[i] = max(f[i], (i - j) * (i - j) + f[j]);
        }
    }
    int r = n, sum = f[n];
    vector<pi> t;
    // 求区间方案
    while(r > 0) {
        if(f[r - 1] + a[r] == sum) {
            sum -= a[r];
            r--;
        }
        else {
            for(int j = r - 1; j >= 0; j--) {
                if(f[j] + (r - j) * (r - j) == sum) {
                    sum  -= (r - j) * (r - j);
                    t.push_back({j + 1, r});
                    r = j;
                    break;
                }
            }
        }
    }
    vector<pi> all;
    // 求长度为len的区间构造成{0，1，..，len-1} 的方法
    auto cal = [&](int len)->vector<pi>{
        vector<pi> res;
        res.push_back({0, 1});
        res.push_back({0, 0});
        if(len == 2) {
            return res;
        }
        for(int i = 2; i < len; i++) {
            vector<pi> tem;
            for(auto j: res) tem.push_back(j);
            tem.push_back({0, i});
            tem.push_back({0, i - 1});
            for(auto &p: res) {
                tem.push_back(p);
            }
            res = tem;
        }
        return res;
    };
    for(int i = 0; i < t.size(); i++) {
        int len = t[i].second - t[i].first + 1;
        int l = t[i].first, r = t[i].second;
        bool sign = 0;
        for(int j = l; j <= r; j++) {
            if(a[j] == 0) sign = 1;
        }
        if(sign) {
            all.push_back({l, r});
            all.push_back({l, r});
        } 
        else all.push_back({l, r});
        if(len == 1) {
            all.push_back({l, r});
            continue;
        }
        vector<pi> ans = cal(len);
        // 操作方案加上索引l
        for(auto &p: ans) {
            all.push_back({l + p.first, l + p.second});
        }
        all.push_back({l, r});
    }
    cout << f[n] << ' ' << all.size() << '\n';
    for(auto i: all) {
        cout << i.first << ' ' << i.second << '\n';
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _ = 1;
    while(_--) solve();
}
