#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
const int N = 300 + 10;
int mod = 1e9 + 7;
ll n,m;
ll a[N];
map<int, int> mp;
bool sign;
int sz[N], mi[N], mx[N];
vector<int> g[N];
vector<int> ans;
void dfs(int cur, int fa) {
    if(mp[cur] != 0) {
        mi[cur] = mp[cur];
        mx[cur] = mp[cur];
        sz[cur] = 1;
        return;
    }
    for(auto i: g[cur]) {
        if(i == fa) continue;
        dfs(i, cur);
        mi[cur] = min(mi[cur], mi[i]);
        mx[cur] = max(mx[cur], mx[i]);
        sz[cur] += sz[i];
    }
    if(mx[cur] - mi[cur] + 1 != sz[cur]) {
        sign = 0;
    }
}
void dfs1(int cur, int fa) {
    ans.push_back(cur);
    if(mp[cur] != 0) return;
    vector<pi> t;
    for(auto i: g[cur]) {
        if(i == fa) continue;
        t.push_back({mi[i], i});
    }
    sort(t.begin(), t.end());
    for(auto i: t) {
        dfs1(i.second, cur);
        ans.push_back(cur);
    }
}
void solve()
{
    cin >> n;
    sign = 1;
    for(int i = 1; i <= n; i++) mi[i] =  mod;
    for(int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int x, cnt = 0;
    while(cin >> x) {
        mp[x] = cnt + 1;
        a[++cnt] = x;
    }
    
    dfs(1, -1);
    if(!sign) {
        cout << -1;
        return;
    }
    dfs1(1, -1);
    for(auto i: ans) cout << i << ' ';
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _ = 1;
    while(_--) solve();
}
