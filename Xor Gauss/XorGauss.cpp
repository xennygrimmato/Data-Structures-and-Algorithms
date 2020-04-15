// https://codeforces.com/contest/1336/submission/76861329
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <cassert>
 
std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());
 
template<const int N, class T = unsigned int>
class XorGauss {
public:
	XorGauss() {
		for(int i = 0; i < N; i++) { a[i] = 0; }
	}
	T reduce(T x) {
		for(int i = N-1; i >= 0; i--) {
			x = std::min(x, x ^ a[i]);
		}
		return x;
	}
 
	T augment(T x) { return ~reduce(~x); }
 
	bool add(T x) {
		for(int i = N-1; i >= 0; i--) {
			if((x & (((T)1) << i)) == 0) { continue; }
			if(a[i]) {
				x ^= a[i];
			} else {
				a[i] = x;
				for(int j = i-1; j >= 0; j--) {
					a[i] = std::min(a[i], a[i] ^ a[j]);
				}
				for(int j = i+1; j < N; j++) {
					a[j] = std::min(a[j], a[j] ^ a[i]);
				}
				return true;
			}
		}
		return false;
	}
 
	std::vector<T> getWeird() {
		//for(int i = 0; i < N; i++) {
		//	if(a[i]) std::cout << a[i] << ' ';
		//}std::cout << '\n';
		std::vector<int> good;
		for(int i = 0; i < N; i++) {
			if(a[i]) continue;
			bool ha = true;
			for(int j = 0; j < N; j++) {
				ha = ha || (a[j] & (1LL << j)) == 0;
			}
			if(ha) good.push_back(i);
		}
		std::vector<T> ans;
		for(int i = 0; i < N; i++) {
			if(!a[i]) continue;
			ans.push_back(0);
			for(int j = 0; j < (int) good.size(); j++) {
				if(a[i] & (1LL << good[j])) {
					ans.back() |= 1LL << j;
				}
			}
			//std::cout << ans.back() << ' ';
		}//std::cout << '\n';
		return ans;
	}
private:
	T a[N];
};
 
typedef XorGauss<60, long long> Gauss;
