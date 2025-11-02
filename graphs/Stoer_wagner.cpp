const int N = 155;

// O(n^3) but faster, 1 indexed, Finds global minimum cut
// Finds edge connectivity: minimum number of edges to be removed such that the graph gets disconnected
// vertex connectivity: minimun number of vertices to be removed such that the graph gets disconnected
// for vertex connec this has no use, but you can iterate over (s, t), split each node x s.t x is not s or t
// in (x1, x2) with an edge of capactity 1 and replace all edges (u, v) into (u2, v1), (v2, u1) with cap 1

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
struct StoerWagner {
  int n;
  long long G[N][N], dis[N];
  int idx[N];
  bool vis[N];
  const long long inf = 1e18;
  StoerWagner() {}
  StoerWagner(int _n) {
    n = _n;
    memset(G, 0, sizeof G);
  }
  void add_edge(int u, int v, long long w) { //undirected edge, multiple edges are merged into one edge
    if (u != v) {
      G[u][v] += w;
      G[v][u] += w;
    }
  }
  long long solve() {
    long long ans = inf;
    for (int i = 0; i < n; ++ i) idx[i] = i + 1;
    shuffle(idx, idx + n, rnd);
    while (n > 1) {
      int t = 1, s = 0;
      for (int i = 1; i < n; ++ i) {
        dis[idx[i]] = G[idx[0]][idx[i]];
        if (dis[idx[i]] > dis[idx[t]]) t = i;
      }
      memset(vis, 0, sizeof vis);
      vis[idx[0]] = true;
      for (int i = 1; i < n; ++ i) {
        if (i == n - 1) {
          if (ans > dis[idx[t]]) ans = dis[idx[t]]; //idx[s] - idx[t] is in two halves of the  mincut
          if (ans == 0) return 0;
          for (int j = 0; j < n; ++ j) {
            G[idx[s]][idx[j]] += G[idx[j]][idx[t]];
            G[idx[j]][idx[s]] += G[idx[j]][idx[t]];
          }
          idx[t] = idx[-- n];
        }
        vis[idx[t]] = true;
        s = t;
        t = -1;
        for (int j = 1; j < n; ++ j) {
          if (!vis[idx[j]]) {
            dis[idx[j]] += G[idx[s]][idx[j]];
            if (t == -1 || dis[idx[t]] < dis[idx[j]]) t = j;
          }
        }
      }
    }
    return ans;
  }
};

int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t, cs = 0;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    StoerWagner st(n);
    while (m--) {
      int u, v, w;
      cin >> u >> v >> w;
      st.add_edge(u, v, w);
    }
    cout << "Case #" << ++cs << ": " << st.solve() << '\n';
  }
  return 0;
}