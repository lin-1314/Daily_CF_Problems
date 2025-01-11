#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int N = 10;
ll n,m;
ll a[N];

void solve()
{
    int x, y, z, x1, y1, z1;
    cin >> x >> y >> z >> x1 >> y1 >> z1;
    int ans = 0;
    for(int i = 1; i <= 6; i++) cin >> a[i];
    if(x < 0) ans += a[5];
    if(x > x1) ans += a[6];
    if(y < 0) ans += a[1];
    if(y > y1) ans += a[2];
    if(z < 0) ans += a[3];
    if(z > z1) ans += a[4];
    cout << ans;
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int _ = 1;
//     cin >> _;
    while(_--) solve();
}
