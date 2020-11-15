struct berlekamp-massey {
	struct poly { std::vector <int> a; poly() { a.clear(); }
		poly (std::vector <int> &a) : a (a) {}
		int length () const { return a.size(); }
		poly move (int d) { std::vector <int> na (d, 0);
			na.insert (na.end (), a.begin (), a.end ());
			return poly (na); }
		int calc(std::vector <int> &d, int pos) { int ret = 0;
			for (int i = 0; i < (int) a.size (); ++i) {
				if ((ret += 1LL * d[pos - i] * a[i] % MOD) >= MOD) {
					ret -= MOD; } }
			return ret; }
		poly operator - (const poly &b) {
			std::vector <int> na (std::max (this -> length (), b.length ()));
			for (int i = 0; i < (int) na.size (); ++i) {
				int aa = i < this -> length () ? this -> a[i] : 0,
					bb = i < b.length () ? b.a[i] : 0;
				na[i] = (aa + MOD - bb) % MOD; }
			return poly (na); } };
	poly operator * (const int &c, const poly &p) {
		std::vector <int> na (p.length ());
		for (int i = 0; i < (int) na.size (); ++i) {
			na[i] = 1LL * c * p.a[i] % MOD; }
		return na; }
	std::vector <int> solve(vector<int> a) {
		int n = a.size (); poly s, b;
		s.a.push_back (1), b.a.push_back (1);
		for (int i = 0, j = -1, ld = 1; i < n; ++i) {
			int d = s.calc(a, i); if (d) {
				if ((s.length () - 1) * 2 <= i) {
					poly ob = b; b = s;
					s = s - 1LL * d * inverse (ld) % MOD * ob.move (i - j);
					j = i; ld = d;
				} else {
					s = s - 1LL * d * inverse (ld) % MOD * b.move (i - j); } } }
		return s.a; } };
