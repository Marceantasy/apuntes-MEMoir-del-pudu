
// Maybe remove unroll-loops, might increase code size too much and lead to
// instruction cache misses.
#pragma GCC optimize("O3,unroll-loops")

// avx2 can be changed to avx, sse, sse2, sse3, sse4, see4.1, see4.2
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#include <bits/stdc++.h>

using namespace std;

#define SZ(x) (int)x.size()
#define rep(i, n) for (int i = 0; i < n; i++)
#define repx(i, a, b) for (int i = a; i < (int)b; ++i)
#define vl vector<ll>
#define vi vector<int>

using ll = long long;
using pii = pair<int, int>;

// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve() { ; }

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int t = 1;
  // cin >> t;

  while (t--)
    solve();
}