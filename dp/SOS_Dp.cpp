// itera sobre los subconjuntos de todos los subconjuntos en O(3^n)
for(int mask=0; mask<(1<<n); ++mask){
    for(int smask=mask; smask; smask=(smask-1)&mask){
        ;
    }
}

// SOS DP en O(n * 2^n)
for(int mask = 0; mask < (1<<N); ++mask){
	dp[mask][-1] = A[mask];	//handle base case separately (leaf states)
	for(int i = 0;i < N; ++i){
		if(mask & (1<<i)){
			dp[mask][i] = dp[mask][i-1] + dp[mask^(1<<i)][i-1];
        }else{
			dp[mask][i] = dp[mask][i-1];
        }
    }
	F[mask] = dp[mask][N-1]; // F es la acumulada en todas las smask de mask
}