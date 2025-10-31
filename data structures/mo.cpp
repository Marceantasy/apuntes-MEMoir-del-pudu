struct Query { int l, r, idx; };

// answer segment queries using only `add(i)`, `remove(i)` and `get()`
// functions.
//
// nota marcelo: borra el add, remove y get de la funcion mo y
// definelo afuera
// 
// complexity: O((N + Q) * sqrt(N) * F)
//   N = length of the full segment
//   Q = amount of queries
//   F = complexity of the `add`, `remove` functions
template <class A, class R, class G, class T>
void mo(vector<Query> &queries, vector<T> &ans, A add, R remove, G get) {
    int Q = queries.size(), B = (int)sqrt(Q);
    sort(queries.begin(), queries.end(), [&](Query &a, Query &b) {
        if (p.first / BLOCK_SIZE != q.first / BLOCK_SIZE)
            return p < q;
        return (p.first / BLOCK_SIZE & 1) ? (p.second < q.second) : (p.second > q.second);
    });
    ans.resize(Q);

    int l = 0, r = 0;
    for (auto &q : queries) {
        while (r < q.r) add(r), r++;
        while (l > q.l) l--, add(l);
        while (r > q.r) r--, remove(r);
        while (l < q.l) remove(l), l++;
        ans[q.idx] = get();
    }
}