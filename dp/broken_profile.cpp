// Common problems solved using DP on broken profile include:

// finding number of ways to fully fill an area (e.g. chessboard/grid) with some figures (e.g. dominoes)
// finding a way to fill an area with minimum number of figures
// finding a partial fill with minimum number of unfilled space (or cells, in case of grid)
// finding a partial fill with the minimum number of figures, such that no more figures can be added

int n, m;
vector<vector<ll>> dp;

void calc (int x = 0, int y = 0, int mask = 0, int next_mask = 0){
    if (x == n) return;
    if (y >= m) dp[x+1][next_mask] += dp[x][mask];
    else{
        int my_mask = 1 << y;
        if(mask & my_mask){
            calc (x, y+1, mask, next_mask);
        }else{
            calc (x, y+1, mask, next_mask | my_mask);
            if (y+1 < m && ! (mask & my_mask) && ! (mask & (my_mask << 1)))
                calc (x, y+2, mask, next_mask);
        }
    }
}


int main(){
    cin >> n >> m;
    dp.resize (n+1, vector<long long> (1<<m));
    dp[0][0] = 1;
    for (int x=0; x<n; ++x)
        for (int mask=0; mask<(1<<m); ++mask)
            calc (x, 0, mask, 0);
    cout << dp[n][0];

}