#pragma once
#include "core.h"

template<class T> struct Bipartite{
	Arr<T> a[2];
	Bipartite(int n,int m){}

	void add_edge(int a,int b,int w){}
	// int hungarian(){}
	// int hopcroft_karp(){}
};


// code from https://www.acmicpc.net/source/67122393
// assign 0 to the non-linked and negative pairs for maximum weight matching
// assign -infty to the non-linked pairs for maximum weight maximum matching
// infity should satisfy infity > n * (max_weight - min_weight)
// O(n^2 * m)
template<class T>
tuple<T, vector<int>, vector<int>> hungarian_weighted_bipartite_matching(vector<vector<T>> a){
	if(a.empty()) return {0, {}, {}};
	bool swapped = false;
	int n = (int)a.size() + 1, m = (int)a[0].size() + 1;
	for(auto i = 0; i < n - 1; ++ i) for(auto j = 0; j < m - 1; ++ j) a[i][j] = -a[i][j];
	if(n > m){
		swap(n, m);
		swapped = true;
		vector b(n - 1, vector<T>(m - 1));
		for(auto i = 0; i < n - 1; ++ i) for(auto j = 0; j < m - 1; ++ j) b[i][j] = a[j][i];
		swap(a, b);
	}
	vector<T> u(n), v(m);
	vector<int> p(m), mu(n - 1);
	for(auto i = 1; i < n; ++ i){
		p[0] = i;
		int j0 = 0; // add "dummy" worker 0
		vector<T> dist(m, numeric_limits<T>::max());
		vector<int> pv(m, -1), done(m + 1);
		do{ // dijkstra
			done[j0] = true;
			int i0 = p[j0], j1;
			T delta = numeric_limits<T>::max();
			for(auto j = 1; j < m; ++ j) if(!done[j]){
				T cur = a[i0 - 1][j - 1] - u[i0] - v[j];
				if(cur < dist[j]) dist[j] = cur, pv[j] = j0;
				if(dist[j] < delta) delta = dist[j], j1 = j;
			}
			for(auto j = 0; j < m; ++ j){
				if(done[j]) u[p[j]] += delta, v[j] -= delta;
				else dist[j] -= delta;
			}
			j0 = j1;
		}while(p[j0]);
		while(j0){ // update alternating path
			int j1 = pv[j0];
			p[j0] = p[j1], j0 = j1;
		}
	}
	vector<int> mv(m - 1, -1);
	for(auto j = 1; j < m; ++ j) if(p[j]) mu[p[j] - 1] = j - 1, mv[j - 1] = p[j] - 1;
	if(swapped) swap(mu, mv);
	return {v[0], mu, mv}; // min cost
}
