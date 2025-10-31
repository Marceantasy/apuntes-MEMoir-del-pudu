const int mxN = 1e6+5, M = 1e9+7;
ll f1[mxN], f2[mxN], iv[mxN];

ll binpow(ll a, ll b){
    ll res = 1;
    while(b){
        if(b & 1) res = res*a%M;
        a = a*a%M;
        b >>= 1;
    }
    return res;
}

ll modinv(ll x){
    return binpow(x, M-2);
}

ll nCr(int a, int b){
    return f1[a]*f2[b]%M*f2[a-b]%M;
    // // si b muy chico y probablemente a muy grande
    // if(b > a) return 0;
    // ll res = 1;
    // for(ll i = 0; i<b; ++i){
    //     ans *= (n-i)%M;
    //     ans %= M; ans += M; ans %= M;
    // }
    // for(ll i = 0; i<b; ++i){
    //     ans *= (modinv(i+1)) % M;
    //     ans %= M; ans += M; ans %= M;
    // }
    // return ans;
}
 
void solve(){     
    int a, b;
    cin >> a >> b;
    cout << nCr(a, b) << "\n";
}
 
signed main(){
    iv[1] = 1;
    for(int i = 2; i<mxN; ++i){
        iv[i]=M-M/i*iv[M%i]%M;
    }
    f1[0]=f2[0]=1;
    for(int i = 1; i<mxN;++i){
        f1[i]=f1[i-1]*i%M;
        f2[i]=f2[i-1]*iv[i]%M;
    }
    solve();
}
