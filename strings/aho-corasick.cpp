struct AC{ // code for finding number of ocurrences of each pattern
    ll c = 0, M, A;
    vector<vl> N, G; vl L, cnt;
    vector<vi> val;
    // L -> suffix link (G -> anti L (u -> v if u is suffix of v))
    AC (ll M, ll A) : M(M), A(A), N(M, vl(A, 0)), G(M, vl()), L(M, 0), val(M, vi()), cnt(M, 0){}
    
    ll add(string &s, int id){ // return endpoint
        ll p = 0;
        for (char l : s){
            int t = l - 'a';
            if(!N[p][t]) N[p][t] = ++c;
            p = N[p][t];
        }
        val[p].push_back(id);
        return p;
    }
    void init(){
        queue<int> q;
        for(int i = 0; i < A; i++) if(N[0][i]) q.push(N[0][i]);
        while(!q.empty()){
            int u = q.front(); q.pop();
            for(int i = 0; i < A; i++){
                int v = N[u][i];
                if(v) { L[v] = N[L[u]][i]; q.push(v); }
                else N[u][i] = N[L[u]][i];
            }
            G[L[u]].push_back(u); // Build fail tree
        }
    }
    void run(string &s){
        int p = 0;
        for(char l : s){
            p = N[p][l-'a'];
            cnt[p]++;
        }
    }
    void pull(int u = 0){
        for(int v : G[u]){
            pull(v);
            cnt[u] += cnt[v];
        }
        for(int id : val[u]){
            ans[id] = cnt[u];
        }
    }
};
