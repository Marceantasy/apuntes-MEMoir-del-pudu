int n, k, sz[mxN], mxtree[mxN], ans; 
vector<int> adj[mxN];
bool used[mxN];

int dfs(int u, int p = -1){
    sz[u] = 1;
    for(int v : adj[u]){
        if(v != p && !used[v]){
            sz[u] += dfs(v, u); 
        }
    }
    return sz[u];
}

int get_centroid(int u, int ms, int p = -1){ // u = node, ms = size of the current tree delimited by previous centroids, p = parent
    for(int v : adj[u]){
        if(v != p && !used[v]){
            if(sz[v]*2 > ms) return get_centroid(v, ms, u);
        }
    }
    return u;
}

void solve(int u){
    int sz_curr_tree = dfs(u);
    int centroid = get_centroid(u, sz_curr_tree);
    used[centroid] = 1;
    // do something with the centroid 
    for(int v : adj[centroid]){
        
    }
    // end that something with the centroid

    // solve for child trees centroids
    for(int v : adj[centroid]){
        if(used[v]) continue;
        solve(v);
    }
}