struct AC
{
    ll c = 0, ec = 0, M, A, af = -1;
    vector<vl> N, G; vl L, E;
    vector<vl> val;
    vl vis, cnt;
    // L -> suffix link G -> anti L
    // E -> string finish
    AC (ll M, ll A) : M(M), A(A), N(M, vl(A, 0)), G(M, vl(0)), E(M, 0), L(M, 0), val(M, vl(0)), vis(M, 0), cnt(M, 0){}
    ll add(string s, int id){ // return endpoint
        af++;
        ll p = 0;
        for (char l : s){
            int t = l - 'a';
            if (!N[p][t]) N[p][t] = ++c;
            p = N[p][t];
        }
        val[p].push_back(id);
        return p;
    }
    // construct aho corasick structure
    void init(){
        queue<int> q; q.push(0); L[0] = -1;
        while (!q.empty()){
            int p = q.front(); q.pop();
            for(int c = 0; c < A; c++){
                int u = N[p][c]; if (!u) continue;
                L[u] = L[p] == -1 ? 0 : N[L[p]][c], q.push(u);
                G[L[u]].push_back(u);
            }
            if (p) for(int c = 0; c < A; c++) if (!N[p][c]) N[p][c] = N[L[p]][c];
        }
    }
    // para un texto s, recorrer las aristas por el arbol
    void run(string &s){
        for(int p = 0, i = 0; i<(int)s.size(); ++i){
            int t = s[i]-'a';
            p = (N[p][t] == -1 ? 0 : N[p][t]);
            cnt[p]++;
        }
    }
    void dfs(int u = 0){
        vis[u] = true;
        for(int v : G[u]){
            if(v == -1) continue;
            if(!vis[v]) dfs(v);
            cnt[u] += cnt[v];
        }
        for(int v : val[u]){
            ans[v] = cnt[u];
        }
    }
};
