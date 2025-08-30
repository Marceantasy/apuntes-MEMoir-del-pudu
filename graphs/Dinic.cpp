// time: O(E V^2)
//      O(E V^(2/3)) / O(E sqrt(E))    unit capacities
//      O(E sqrt(V))   (hopcroft-karp) unit networks
// unit network: c in {0,1} & forall v, indeg<=1 or outdeg<=1
// min-cut: nodes reachable from s in final residual graph

// en grafo bipartito:
// max matching = max flow 
// min edge cover = conjunto minimo de arista que cubran todos los nodos 
// min edge cover = n - max_matching
// min vertex cover = conjunto minimo de nodos que cubran todas las aristas
// min vertex cover = max_matching
// maximal independent set = conjunto de vertices que no compartan aristas
// maximal independent set = min edge cover

// dilworth: pongo todos los nodos a la izquierda y una copia a la derecha
// se une un nodo x de la izquierda a y de la derecha si existe camino de x a y
// anticadena = conjunto de nodos tal que no hay camino entre ellos
// cadena = conjunto de nodos tal que de cada uno puedo llegar al siguiente
// anticadena de mayor tamaño = minima cantidad de anticadenas que cubren todos los nodos
// min chain cover = conseguimos el max matching, si existe x -> y, y -> z, en el matching
//        consideramos x -> y -> z como una sola cadena (con dsu o un vector posiblemente)
// Anticadena maxima = hacemos min vertex cover y tomamos los nodos que no tienen ninguna 
//                     copia en el cubrimiento, este es el tamaño maximo

// Flujo con demandas (no necesariamente el maximo)
// Agregar s' y t' nuevos source and sink
// c'(s', v) = sum(d(u, v) for u in V) \forall arista (s', v)
// c'(v, t') = sum(d(v, w) for w in V) \forall arista (v, t')
// c'(u, v) = c(u, v) - d(u, v) \forall aristas antiguas
// c'(t, s) = INF (el flujo por esta arista es el flujo real)*/
class Dinic{
    struct Edge { int to, rev; ll f, c; };
    int n, t_; vector<vector<Edge>> G;
    vl D; vi q, W;
    bool bfs(int s, int t){
        W.assign(n, 0); D.assign(n, -1); D[s] = 0;
        int f = 0, l = 0; q[l++] = s;
        while (f < l){
            int u = q[f++];
            for (const Edge &e : G[u]) if (D[e.to] == -1 && e.f < e.c)
                D[e.to] = D[u] + 1, q[l++] = e.to;
        }
        return D[t] != -1;
    }
    ll dfs(int u, ll f){
        if (u == t_) return f;
        for (int &i = W[u]; i < (int)G[u].size(); ++i){
            Edge &e = G[u][i]; int v = e.to;
            if (e.c <= e.f || D[v] != D[u] + 1) continue;
            ll df = dfs(v, min(f, e.c - e.f));
            if (df > 0) { e.f += df, G[v][e.rev].f -= df; return df; }
        }
        return 0;
    }

public:
    Dinic(int N) : n(N), G(N), D(N), q(N) {}
    void addEdge(int u, int v, ll cap){
        G[u].push_back({v, (int)G[v].size(), 0, cap});
        G[v].push_back({u, (int)G[u].size() - 1, 0, 0}); // cap if bidirectional
    }
    ll maxFlow(int s, int t){
        t_ = t; ll ans = 0;
        while (bfs(s, t)) while (ll dl = dfs(s, LLONG_MAX)) ans += dl;
        return ans;
    }
};