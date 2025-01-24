
// 离线做法， 树的边权表示老板与员工关系建立的时间戳。
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
using ld = long double;
const int N = 1e5+ 10;
int mod = 1e9 + 7;
ll n,m;
ll a[N];
int fa[N];
vector<pi> g[N];
int tree[N][22], mx[N][22];
int sz[N];
int find(int x){
    return fa[x] == x?x:fa[x] = find(fa[x]);
}
void mer(int x, int y) {
    fa[x] = y;
}
int doc[N], ti[N];
void dfs(int cur, int fa, int weight, int dep) {
    tree[cur][0] = fa;
    mx[cur][0] = weight;
    sz[cur] = dep;
    for(int i = 1; i < 22; i++) {
        int ffa = tree[cur][i - 1];
        tree[cur][i] = tree[ffa][i - 1];
        mx[cur][i] = max(mx[cur][i - 1], mx[ffa][i - 1]);
    }
    for(auto [nxt, w]: g[cur]) {
        if(nxt == fa) continue;
        dfs(nxt, cur, w, dep + 1);
    }
}
pair<int, int> LCA(int x, int y) {
    if(sz[x] > sz[y]) { // x表示查询的员工， y表示文件最先开始签名的员工， 如果x在y的下面，则不可能签名成功
        return {-1, -1};
    }
    int tem = sz[y] - sz[x];
    int resmx = 0;
    for(int i = 21; i >= 0; i--) {
        if(tem >> i & 1) {
            resmx = max(resmx, mx[y][i]); // 维护x到y之间的边权时间戳的最大值，如果存在一条边的时间戳大于文件开始签名的时间戳
            // 那y签名之后不能到x。
            y = tree[y][i];
        }
    }
    if(y != x) {
        return {-1, -1};
    }
    else {
        return {0, resmx};
    }
}
void solve()
{
    cin >> n >> m;
    vector<array<int, 2>> t;
    int cnt = 1;
    for(int i = 1; i <= n; i++) fa[i] = i;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < 22; j++) {
            tree[i][j] = mx[i][j] = 0;
        }
    }
    for(int i = 1; i <= m; i++) {
        int op, x, y;
        cin >> op;
        if(op == 1) {
            cin >> x >> y;
            g[x].push_back({y, i});
            g[y].push_back({x, i});
            mer(x, y);
        }
        if(op == 2) {
            cin >> x;
            doc[cnt] = x;
            ti[cnt] = i;
            cnt++;
        }
        if(op == 3) {
            cin >> x >> y;
            t.push_back({x, y});
        }
    }
    set<int> st;
    for(int i = 1; i <= n; i++) {
        st.insert(find(i));
    }
    for(auto i: st) {
        dfs(i, 0, 0, 1);
    }
    for(auto [x, i]: t) {
        int xx = find(x), yy = find(doc[i]);
        if(xx != yy) {
            cout << "NO" << '\n'; // 不在一个连通块内，可以直接输出NO
        }
        else {
            pair<int, int> p = LCA(x, doc[i]);
            if(p.first == -1 || (p.first != -1 && p.second > ti[i])) { 
                cout << "NO" << '\n';
            }
            else cout << "YES" << '\n';
        }
    }
}
int main()
{
  // 请在此输入您的代码
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _ = 1;
//     cin >> _;
    while(_--) solve();
}
