const int mxN = 2e5+5;

int n, m, who[mxN], cc = 0;
vector<int> adj[mxN], adj_rev[mxN], adj2[mxN];
bool used[mxN];
vector<int> order, component, root_nodes;
 
void dfs1(int v) {
    used[v] = true;
    for (auto u : adj[v])
        if (!used[u])
            dfs1(u);
    order.push_back(v);
}
 
void dfs2(int v) {
    used[v] = true;
    component.push_back(v);
    for (auto u : adj_rev[v]){
        if (!used[u]){
            dfs2(u);
        }
    }
}

int main(){
    std::ios_base::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0);
 
	cin >> n >> m;
	for(int i = 0; i<m; ++i){
		int a, b; 
		cin >> a >> b, --a, --b; 
		adj[a].push_back(b);
		adj_rev[b].push_back(a);
	}
	for(int i = 0; i<n; ++i){
		if(!used[i]){
			dfs1(i);
		}
	}
	memset(used, false, sizeof(used));
	reverse(order.begin(), order.end());
	for(int v : order){
		if(!used[v]){
			dfs2(v);
			int root = component.front();
			for(int u : component){
				who[u] = root;
			}
			root_nodes.push_back(root);
			component.clear();
			cc++;
		}
	}

    // condensation graph construction
	for(int v = 0; v<n; ++v){
		for(auto u : adj[v]){
			int root_v = who[v];
            int root_u = who[u];
			if (root_u != root_v){
				adj2[root_v].push_back(root_u);
			}
		}
	}
}