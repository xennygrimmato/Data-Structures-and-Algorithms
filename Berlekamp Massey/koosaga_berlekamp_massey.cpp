// https://codeforces.com/contest/506/submission/45057436
#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int mod = 1e4 + 7;
 
lint ipow(lint x, lint p){
	lint ret = 1, piv = x;
	while(p){
		if(p & 1) ret = ret * piv % mod;
		piv = piv * piv % mod;
		p >>= 1;
	}
	return ret;
}
 
namespace linear_seq {
	vector<int> berlekamp_massey(vector<int> x){
		vector<int> ls, cur;
		int lf, ld;
		for(int i=0; i<x.size(); i++){
			lint t = 0;
			for(int j=0; j<cur.size(); j++){
				t = (t + 1ll * x[i-j-1] * cur[j]) % mod;
			}
			if((t - x[i]) % mod == 0) continue;
			if(cur.empty()){
				cur.resize(i+1);
				lf = i;
				ld = (t - x[i]) % mod;
				continue;
			}
			lint k = -(x[i] - t) * ipow(ld, mod - 2) % mod;
			vector<int> c(i-lf-1); 
			c.push_back(k);
			for(auto &j : ls) c.push_back(-j * k % mod);
			if(c.size() < cur.size()) c.resize(cur.size());
			for(int j=0; j<cur.size(); j++){
				c[j] = (c[j] + cur[j]) % mod;
			}
			if(i-lf+(int)ls.size()>=(int)cur.size()){
				tie(ls, lf, ld) = make_tuple(cur, i, (t - x[i]) % mod);
			}
			cur = c;
		}
		for(auto &i : cur) i = (i % mod + mod) % mod;
		return cur;
	}
	int get_nth(vector<int> rec, vector<int> dp, lint n){
		int m = rec.size();
		vector<int> s(m), t(m);
		s[0] = 1;
		if(m != 1) t[1] = 1;
		else t[0] = rec[0];
		auto mul = [&rec](vector<int> v, vector<int> w){
			int m = v.size();
			vector<int> t(2 * m);
			for(int j=0; j<m; j++){
				for(int k=0; k<m; k++){
					t[j+k] += 1ll * v[j] * w[k] % mod;
					t[j+k] %= mod;
				}
			}
			for(int j=2*m-1; j>=m; j--){
				for(int k=1; k<=m; k++){
					t[j-k] += 1ll * t[j] * rec[k-1] % mod;
					t[j-k] %= mod;
				}
			}
			t.resize(m);
			return t;
		};
		while(n){
			if(n & 1) s = mul(s, t);
			t = mul(t, t);
			n >>= 1;
		}
		lint ret = 0;
		for(int i=0; i<m; i++) ret += 1ll * s[i] * dp[i] % mod;
		return ret % mod;
	}
	int guess_nth_term(vector<int> x, lint n){
		if(n < x.size()) return x[n];
		vector<int> v = berlekamp_massey(x);
		if(v.empty()) return 0;
		return get_nth(v, x, n);
	}
}
