// Credits: Aeren
// https://codeforces.com/contest/1511/submission/112913505

#include <bits/stdc++.h>
using namespace std;

// Reorder N 2D points with max_x - min_x <= X, max_y - min_y <= Y
// so that sum(abs(xi - x(i+1)) + abs(yi - y(i+1)) is small
// and process queries on the new order.
// N BX inc_x and dec_x calls, X Y / BX inc_y and dec_y calls at max
// set BX = sqrt(X Y / N) to achieve sqrt(X Y N) calls at max
template<int BX>
struct mo_2d{
	vector<array<int, 3>> points; // x, y, ind
	void insert(int x, int y, int id){
		points.push_back({x, y, id});
	}
	// starting from (0, 0), access each points and execute queries
	void solve(auto inc_x, auto dec_x, auto inc_y, auto dec_y, auto process){
		auto cmp = [&](const auto &p, const auto &q)->bool{
			return p[0] / BX != q[0] / BX ? p < q : p[0] / BX & 1 ? p[1] < q[1] : p[1] > q[1];
		};
		sort(points.begin(), points.end(), cmp);
		int x = 0, y = 0;
		for(auto &[qx, qy, id]: points){
			while(qx < x) dec_x(), -- x;
			while(y < qy) inc_y(), ++ y;
			while(x < qx) inc_x(), ++ x;
			while(qy < y) dec_y(), -- y;
			process(id);
		}
	}
};

int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(ios::badbit | ios::failbit);
	int n, m;
	cin >> n >> m;
	vector<int> flag(m);
	for(auto i = 0; i < n; ++ i){
		int x;
		cin >> x, -- x;
		flag[x] ^= 1;
	}
	int qn;
	cin >> qn;
	mo_2d<int(sqrt(2e5))> mo;
	for(auto qi = 0; qi < qn; ++ qi){
		int l, r;
		cin >> l >> r, -- l;
		mo.insert(l, r, qi);
	}
	int l = 0, r = 0, xor_sum = 0;
	const int mx = __lg(m) + 1;
	vector<deque<bool>> cnt(mx);
	for(auto bit = 0; bit < mx; ++ bit){
		cnt[bit].assign(1 << bit, 0);
	}
	auto inc_x = [&](){
		if(flag[l]){
			for(auto bit = 0; bit < mx; ++ bit){
				cnt[bit].front() ^= true;
			}
		}
		for(auto bit = 0; bit < mx; ++ bit){
			xor_sum ^= cnt[bit].front() << bit;
			cnt[bit].push_back(cnt[bit].front());
			cnt[bit].pop_front();
		}
		++ l;
	};
	auto dec_x = [&](){
		-- l;
		for(auto bit = 0; bit < mx; ++ bit){
			xor_sum ^= cnt[bit].back() << bit;
			cnt[bit].push_front(cnt[bit].back());
			cnt[bit].pop_back();
		}
		if(flag[l]){
			for(auto bit = 0; bit < mx; ++ bit){
				cnt[bit][0] ^= true;
			}
		}
	};
	auto inc_y = [&](){
		if(flag[r]){
			int x = r - l;
			xor_sum ^= x;
			for(auto bit = 0; bit < mx; ++ bit){
				cnt[bit][x & (1 << bit) - 1] ^= true;
			}
		}
		++ r;
	};
	auto dec_y = [&](){
		-- r;
		if(flag[r]){
			int x = r - l;
			xor_sum ^= x;
			for(auto bit = 0; bit < mx; ++ bit){
				cnt[bit][x & (1 << bit) - 1] ^= true;
			}
		}
	};
	string res(qn, '?');
	auto process = [&](int qi){
		res[qi] = 'A' + !xor_sum;
	};
	mo.solve(inc_x, dec_x, inc_y, dec_y, process);
	cout << res << "\n";
	return 0;
}

/*

*/

////////////////////////////////////////////////////////////////////////////////////////
//                                                                                    //
//                                   Coded by Aeren                                   //
//                                                                                    //
////////////////////////////////////////////////////////////////////////////////////////
