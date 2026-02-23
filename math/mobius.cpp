short mu[MAXN] = {0,1};
void mobius(){
    repx(i,1,MAXN)if(mu[i])for(int j=i+i;j<MAXN;j+=i)mu[j]-=mu[i];
}

void phi_1_to_n(int n) {
    vector<int> phi(n+1);
    for(int i = 0; i<=n; i++) phi[i] = i;
    for(int i = 2; i<=n; i++){
        if(phi[i] == i){
            for (int j = i; j<=n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}
