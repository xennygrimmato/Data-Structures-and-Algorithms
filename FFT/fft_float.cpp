// Source: https://discuss.codechef.com/t/notd-editorial/104445
#include <bits/stdc++.h>
#define ll long long int

using namespace std;
namespace FFT {
    using float_t = double;

    struct cd {
        float_t x, y;
        cd(float_t x = 0, float_t y = 0): x(x), y(y) {}
        friend ostream& operator<<(ostream& os, const cd& c) { 
            return os << '(' << c.x << ", " << c.y << ')';
        }

        float_t real() const { return x; }
        float_t imag() const { return y; }

        cd& operator+=(const cd& o) { x += o.x, y += o.y; return *this; }
        cd operator+(const cd& o) const { cd ret = *this; ret += o; return ret; }

        cd& operator-=(const cd& o) { x -= o.x, y -= o.y; return *this; }
        cd operator-(const cd& o) const { cd ret = *this; ret -= o; return ret; }

        cd& operator*=(const cd& o) { tie(x, y) = make_pair(x * o.x - y * o.y, x * o.y + y * o.x); return *this; }
        cd operator*(const cd& o) const { cd ret = *this; ret *= o; return ret; }

        cd& operator/=(const float_t& r) { x /= r, y /= r; return *this; }
        cd operator/(const float_t& r) const { cd ret = *this; ret /= r; return ret; }

    };

    const float_t PI = acos(float_t(-1));
    const int FFT_CUTOFF = 150;
    vector<cd> roots = {{0, 0}, {1, 0}}, inv_roots = {{0, 0}, {1, 0}};
    vector<int> bit_order;

    void prepare_roots(int n) {
        if(roots.size() >= n) return;
        int len = roots.size();
        roots.resize(n); inv_roots.resize(n);
        while(n > len) {
            const cd w(cos(PI / len), sin(PI / len)), inv_w(w.real(), -w.imag());
            for(int i = len >> 1; i < len; i++) {
                roots[i << 1] = roots[i];
                roots[i << 1 | 1] = roots[i] * w;
                inv_roots[i << 1] = inv_roots[i];
                inv_roots[i << 1 | 1] = inv_roots[i] * inv_w;
            } len <<= 1;
        }
    }

    void reorder_bits(int n, vector<cd>& a) {
        if(bit_order.size() != n) {
            bit_order.assign(n, 0);
            int len = __builtin_ctz(n);
            for(int i = 0; i < n; i++)
                bit_order[i] = (bit_order[i >> 1] >> 1) + ((i & 1) << len-1);
        }
        for(int i = 0; i < n; i++)
            if(i > bit_order[i]) swap(a[i], a[bit_order[i]]);
    }

    void fft(int n, vector<cd>& a, bool invert = false) {
        prepare_roots(n); reorder_bits(n, a);
        const auto& ws = invert? inv_roots : roots;
        for(int len = 1; len < n; len <<= 1)
            for(int i = 0; i < n; i += len << 1)
                for(int j = 0; j < len; j++) {
                    const cd& even = a[i + j];
                    cd odd = a[i + len + j] * ws[len + j];
                    a[i + len + j] = even - odd; a[i + j] = even + odd;
                }
        if(invert)
            for(auto& x: a) x /= n;
    }

    template<typename T>
    vector<T> multiply(const vector<T>& a, const vector<T>& b, bool trim = false) {
        int n = a.size(), m = b.size();
        if(n == 0 or m == 0)
            return vector<T>{0};

        if(min(n, m) < FFT_CUTOFF) {
            vector<T> res(n + m - 1);
            for(int i = 0; i < n; i++)
                for(int j = 0; j < m; j++)
                    res[i + j] += a[i] * b[j];
            
            if(trim) {
                while(!res.empty() && res.back() == 0)
                    res.pop_back();
            }

            return res;
        }

        int N = [](int x) { while(x & x-1) x = (x | x-1) + 1; return x; }(n + m - 1);
        vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        fa.resize(N); fb.resize(N);
        
        bool equal = n == m and a == b;
        fft(N, fa);

        if(equal) fb = fa;
        else fft(N, fb);

        for(int i = 0; i < N; i++)
            fa[i] *= fb[i];

        fft(N, fa, true);

        fa.resize(n + m - 1);
        vector<T> res(n + m - 1);
        for(int i = 0; i < n + m - 1; i++)
            res[i] = is_integral<T>::value? round(fa[i].real()) : fa[i].real();

        if(trim) {
            while(!res.empty() && res.back() == 0)
                res.pop_back();
        }

        return res;
    }

    template<typename T>
    T expo(T A, int64_t B) {
        T res{1}; while(B) {
            if(B & 1) res = res * A;
            B >>= 1; A = A * A;
        } return res;
    }

    template<typename T>
    vector<T> expo(const vector<T>& a, int e, bool trim = false) {
        int n = a.size();
        int N = [](int x) { while(x & x-1) x = (x | x-1) + 1; return x; }((n-1) * e + 1);
        vector<cd> fa(a.begin(), a.end()); fa.resize(N);

        fft(N, fa);

        for(int i = 0; i < N; i++)
            fa[i] = expo(fa[i], e);

        fft(N, fa, true);

        fa.resize((n-1) * e + 1);
        vector<T> res((n-1) * e + 1);
        for(int i = 0; i < res.size(); i++)
            res[i] = is_integral<T>::value? round(fa[i].real()) : fa[i].real();

        if(trim) {
            while(!res.empty() && res.back() == 0)
                res.pop_back();
        }

        return res;
    }

} // namespace FFT 
