#define mat vector<vector<ll>> 

const int M =1e9+7;
const ll M2 = (ll)M*M;

mat cn(int n, int m){
    return vector<vector<ll>>(n, vector<ll>(m));
}
 
mat mult(mat &a, mat &b){
    mat c = cn(a.size(), b[0].size());
    for(int i=0; i<a.size(); ++i){
        for(int k = 0; k<b.size(); ++k){
            for(int j = 0; j<b[0].size(); ++j){
                c[i][j]+=a[i][k]*b[k][j];
                if(c[i][j]>=M2){
                    c[i][j] -= M2;
                }
            }
        }
    }
    for(int i = 0; i<a.size(); ++i){
        for(int j=0; j<b[0].size(); ++j){
            c[i][j] %= M;
        }
    }
    return c;
}
