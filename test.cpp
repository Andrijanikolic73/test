#include <bits/stdc++.h>
		 		
#define int long long 
		 
#define pb push_back 
		
#define F first
		 
#define S second
		 
using namespace std;
		 
const int N = 5000 + 10;
		 
const int mod = 1e9 + 7;
		 
const int inf = 1e18;

const int lg = 13;
	
vector<int>g[N],res(N,-1);
map<pair<int,int>,int>index;
int st[N][lg],in[N],out[N],timer = 0;

void dfs(int x,int par) {
	in[x] = ++timer;
	st[x][0] = par;
	for(auto X : g[x]) {
		if(X == par) continue;
		dfs(X,x);
	}
	out[x] = timer;
}	

bool inn(int u,int v) {
	//dal je v u u
	if(in[u] <= in[v] && out[u] >= out[v]) return true;
	return false;
}

int lca(int u,int v) {
	if(inn(u,v)) return u;
	if(inn(v,u)) return v;
	for(int j = lg - 1; j >= 0; j--) {
		if(!inn(st[v][j],u) && st[v][j] != 0) v = st[v][j];
	}
	return st[v][0];
}

			 		 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	
	int n,q;
	cin >> n;
	for(int i = 2; i <= n; i++) {
		int u,v;
		cin >> u >> v;
		index[{u,v}] = i - 1;
		index[{v,u}] = i - 1;
 		g[u].pb(v);
		g[v].pb(u);
	}
	cin >> q;
	dfs(1,0);
	for(int j = 1; j < lg; j++) {
		for(int i = 1; i <= n; i++) st[i][j] = st[st[i][j - 1]][j - 1];
	}
	vector<array<int,3>>a(q + 1);
	for(int i = 1; i <= q; i++) cin >> a[i][1] >> a[i][2] >> a[i][0];
	sort(a.begin() + 1,a.end());
	reverse(a.begin() + 1,a.end());
	for(int i = 1; i <= q; i++) {
		int LCA = lca(a[i][1],a[i][2]);
		int u = a[i][1],v = a[i][2],cnt = 0;
		while(u != LCA) {
			if(res[index[{u,st[u][0]}]] > a[i][0]) {
				u = st[u][0];
				continue;
			}
			cnt += 1;
			res[index[{u,st[u][0]}]] = a[i][0];
			u = st[u][0];
		}
		while(v != LCA) {
			if(res[index[{v,st[v][0]}]] > a[i][0]) {
				v = st[v][0];
				continue;
			}
			cnt += 1;
			res[index[{v,st[v][0]}]] = a[i][0];
			v = st[v][0];
		}
		if(!cnt) {
			cout << -1;
			return 0;
		}
	}
	for(int i = 1; i <= n - 1; i++) if(res[i] == -1) res[i] = 1e6;
	for(int i = 1; i <= n - 1; i++) cout << res[i] << " ";
	cout << "TEST";
    return 0; 
}
