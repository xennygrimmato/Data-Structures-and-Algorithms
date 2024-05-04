#ifndef CP_ALGO_ALGEBRA_POLY_HPP
#define CP_ALGO_ALGEBRA_POLY_HPP
#include "poly/impl/euclid.hpp"
#include "poly/impl/base.hpp"
#include "poly/impl/div.hpp"
#include "number_theory.hpp"
#include "fft.hpp"
#include <functional>
#include <algorithm>
#include <iostream>
#include <optional>
#include <utility>
#include <vector>
#include <list>
namespace cp_algo::algebra {
    template<typename T>
    struct poly_t {
        using base = T;
        std::vector<T> a;
        
        void normalize() {poly::impl::normalize(*this);}
        
        poly_t(){}
        poly_t(T a0): a{a0} {normalize();}
        poly_t(std::vector<T> const& t): a(t) {normalize();}
        
        poly_t operator -() const {return poly::impl::neg(*this);}
        poly_t& operator += (poly_t const& t) {return poly::impl::add(*this, t);}
        poly_t& operator -= (poly_t const& t) {return poly::impl::sub(*this, t);}
        poly_t operator + (poly_t const& t) const {return poly_t(*this) += t;}
        poly_t operator - (poly_t const& t) const {return poly_t(*this) -= t;}
        
        poly_t mod_xk(size_t k) const {return poly::impl::mod_xk(*this, k);} // %= x^k
        poly_t mul_xk(size_t k) const {return poly::impl::mul_xk(*this, k);} // *= x^k
        poly_t div_xk(size_t k) const {return poly::impl::div_xk(*this, k);} // /= x^k
        poly_t substr(size_t l, size_t k) const {return poly::impl::substr(*this, l, k);}
        
        poly_t operator *= (const poly_t &t) {fft::mul(a, t.a); normalize(); return *this;}
        poly_t operator * (const poly_t &t) const {return poly_t(*this) *= t;}

        poly_t& operator /= (const poly_t &t) {return *this = divmod(t)[0];}
        poly_t& operator %= (const poly_t &t) {return *this = divmod(t)[1];}
        poly_t operator / (poly_t const& t) const {return poly_t(*this) /= t;}
        poly_t operator % (poly_t const& t) const {return poly_t(*this) %= t;}

        poly_t& operator *= (T const& x) {return *this = poly::impl::scale(*this, x);}
        poly_t& operator /= (T const& x) {return *this *= x.inv();}
        poly_t operator * (T const& x) const {return poly_t(*this) *= x;}
        poly_t operator / (T const& x) const {return poly_t(*this) /= x;}
        
        poly_t reverse(size_t n) const {return poly::impl::reverse(*this, n);}
        poly_t reverse() const {return reverse(size(a));}
        
        std::array<poly_t, 2> divmod(poly_t const& b) const {
            return poly::impl::divmod(*this, b);
        }
        
        // reduces A/B to A'/B' such that
        // deg B' < deg A / 2
        static std::pair<std::list<poly_t>, linfrac<poly_t>> half_gcd(auto &&A, auto &&B) {
            return poly::impl::half_gcd(A, B);
        }
        // reduces A / B to gcd(A, B) / 0
        static std::pair<std::list<poly_t>, linfrac<poly_t>> full_gcd(auto &&A, auto &&B) {
            return poly::impl::full_gcd(A, B);
        }
        static poly_t gcd(poly_t &&A, poly_t &&B) {
            full_gcd(A, B);
            return A;
        }
        
        // Returns a (non-monic) characteristic polynomial
        // of the minimum linear recurrence for the sequence
        poly_t min_rec(size_t d) const {
            return poly::impl::min_rec(*this, d);
        }
        
        // calculate inv to *this modulo t
        std::optional<poly_t> inv_mod(poly_t const& t) const {
            return poly::impl::inv_mod(*this, t);
        };
        
        poly_t negx() const { // A(x) -> A(-x)
            auto res = *this;
            for(int i = 1; i <= deg(); i += 2) {
                res.a[i] = -res[i];
            }
            return res;
        }
        
        void print(int n) const {
            for(int i = 0; i < n; i++) {
                std::cout << (*this)[i] << ' ';
            }
            std::cout << "\n";
        }
        
        void print() const {
            print(deg() + 1);
        }
        
        T eval(T x) const { // evaluates in single point x
            T res(0);
            for(int i = deg(); i >= 0; i--) {
                res *= x;
                res += a[i];
            }
            return res;
        }
        
        T lead() const { // leading coefficient
            assert(!is_zero());
            return a.back();
        }
        
        int deg() const { // degree, -1 for P(x) = 0
            return (int)a.size() - 1;
        }
        
        bool is_zero() const {
            return a.empty();
        }
        
        T operator [](int idx) const {
            return idx < 0 || idx > deg() ? T(0) : a[idx];
        }
        
        T& coef(size_t idx) { // mutable reference at coefficient
            return a[idx];
        }
        
        bool operator == (const poly_t &t) const {return a == t.a;}
        bool operator != (const poly_t &t) const {return a != t.a;}
        
        poly_t deriv(int k = 1) const { // calculate derivative
            if(deg() + 1 < k) {
                return poly_t(T(0));
            }
            std::vector<T> res(deg() + 1 - k);
            for(int i = k; i <= deg(); i++) {
                res[i - k] = fact<T>(i) * rfact<T>(i - k) * a[i];
            }
            return res;
        }
        
        poly_t integr() const { // calculate integral with C = 0
            std::vector<T> res(deg() + 2);
            for(int i = 0; i <= deg(); i++) {
                res[i + 1] = a[i] * small_inv<T>(i + 1);
            }
            return res;
        }
        
        size_t trailing_xk() const { // Let p(x) = x^k * t(x), return k
            if(is_zero()) {
                return -1;
            }
            int res = 0;
            while(a[res] == T(0)) {
                res++;
            }
            return res;
        }
        
        poly_t log(size_t n) const { // calculate log p(x) mod x^n
            assert(a[0] == T(1));
            return (deriv().mod_xk(n) * inv(n)).integr().mod_xk(n);
        }
        
        poly_t exp(size_t n) const { // calculate exp p(x) mod x^n
            if(is_zero()) {
                return T(1);
            }
            assert(a[0] == T(0));
            poly_t ans = T(1);
            size_t a = 1;
            while(a < n) {
                poly_t C = ans.log(2 * a).div_xk(a) - substr(a, 2 * a);
                ans -= (ans * C).mod_xk(a).mul_xk(a);
                a *= 2;
            }
            return ans.mod_xk(n);
        }
        
        poly_t pow_bin(int64_t k, size_t n) const { // O(n log n log k)
            if(k == 0) {
                return poly_t(1).mod_xk(n);
            } else {
                auto t = pow(k / 2, n);
                t = (t * t).mod_xk(n);
                return (k % 2 ? *this * t : t).mod_xk(n);
            }
        }

        poly_t circular_closure(size_t m) const {
            if(deg() == -1) {
                return *this;
            }
            auto t = *this;
            for(size_t i = t.deg(); i >= m; i--) {
                t.a[i - m] += t.a[i];
            }
            t.a.resize(std::min(t.a.size(), m));
            return t;
        }

        static poly_t mul_circular(poly_t const& a, poly_t const& b, size_t m) {
            return (a.circular_closure(m) * b.circular_closure(m)).circular_closure(m);
        }

        poly_t powmod_circular(int64_t k, size_t m) const {
            if(k == 0) {
                return poly_t(1);
            } else {
                auto t = powmod_circular(k / 2, m);
                t = mul_circular(t, t, m);
                if(k % 2) {
                    t = mul_circular(t, *this, m);
                }
                return t;
            }
        }
        
        poly_t powmod(int64_t k, poly_t const& md) const {
            return poly::impl::powmod(*this, k, md);
        }
        
        // O(d * n) with the derivative trick from
        // https://codeforces.com/blog/entry/73947?#comment-581173
        poly_t pow_dn(int64_t k, size_t n) const {
            if(n == 0) {
                return poly_t(T(0));
            }
            assert((*this)[0] != T(0));
            std::vector<T> Q(n);
            Q[0] = bpow(a[0], k);
            auto a0inv = a[0].inv();
            for(int i = 1; i < (int)n; i++) {
                for(int j = 1; j <= std::min(deg(), i); j++) {
                    Q[i] += a[j] * Q[i - j] * (T(k) * T(j) - T(i - j));
                }
                Q[i] *= small_inv<T>(i) * a0inv;
            }
            return Q;
        }
        
        // calculate p^k(n) mod x^n in O(n log n)
        // might be quite slow due to high constant
        poly_t pow(int64_t k, size_t n) const {
            if(is_zero()) {
                return k ? *this : poly_t(1);
            }
            int i = trailing_xk();
            if(i > 0) {
                return k >= int64_t(n + i - 1) / i ? poly_t(T(0)) : div_xk(i).pow(k, n - i * k).mul_xk(i * k);
            }
            if(std::min(deg(), (int)n) <= magic) {
                return pow_dn(k, n);
            }
            if(k <= magic) {
                return pow_bin(k, n);
            }
            T j = a[i];
            poly_t t = *this / j;
            return bpow(j, k) * (t.log(n) * T(k)).exp(n).mod_xk(n);
        }
        
        // returns std::nullopt if undefined
        std::optional<poly_t> sqrt(size_t n) const {
            if(is_zero()) {
                return *this;
            }
            int i = trailing_xk();
            if(i % 2) {
                return std::nullopt;
            } else if(i > 0) {
                auto ans = div_xk(i).sqrt(n - i / 2);
                return ans ? ans->mul_xk(i / 2) : ans;
            }
            auto st = algebra::sqrt((*this)[0]);
            if(st) {
                poly_t ans = *st;
                size_t a = 1;
                while(a < n) {
                    a *= 2;
                    ans -= (ans - mod_xk(a) * ans.inv(a)).mod_xk(a) / 2;
                }
                return ans.mod_xk(n);
            }
            return std::nullopt;
        }
        
        poly_t mulx(T a) const { // component-wise multiplication with a^k
            T cur = 1;
            poly_t res(*this);
            for(int i = 0; i <= deg(); i++) {
                res.coef(i) *= cur;
                cur *= a;
            }
            return res;
        }

        poly_t mulx_sq(T a) const { // component-wise multiplication with a^{k choose 2}
            T cur = 1, total = 1;
            poly_t res(*this);
            for(int i = 0; i <= deg(); i++) {
                res.coef(i) *= total;
                cur *= a;
                total *= cur;
            }
            return res;
        }

        // be mindful of maxn, as the function
        // requires multiplying polynomials of size deg() and n+deg()!
        poly_t chirpz(T z, int n) const { // P(1), P(z), P(z^2), ..., P(z^(n-1))
            if(is_zero()) {
                return std::vector<T>(n, 0);
            }
            if(z == T(0)) {
                std::vector<T> ans(n, (*this)[0]);
                if(n > 0) {
                    ans[0] = accumulate(begin(a), end(a), T(0));
                }
                return ans;
            }
            auto A = mulx_sq(z.inv());
            auto B = ones(n+deg()).mulx_sq(z);
            return semicorr(B, A).mod_xk(n).mulx_sq(z.inv());
        }

        // res[i] = prod_{1 <= j <= i} 1/(1 - z^j)
        static auto _1mzk_prod_inv(T z, int n) {
            std::vector<T> res(n, 1), zk(n);
            zk[0] = 1;
            for(int i = 1; i < n; i++) {
                zk[i] = zk[i - 1] * z;
                res[i] = res[i - 1] * (T(1) - zk[i]);
            }
            res.back() = res.back().inv();
            for(int i = n - 2; i >= 0; i--) {
                res[i] = (T(1) - zk[i+1]) * res[i+1];
            }
            return res;
        }
        
        // prod_{0 <= j < n} (1 - z^j x)
        static auto _1mzkx_prod(T z, int n) {
            if(n == 1) {
                return poly_t(std::vector<T>{1, -1});
            } else {
                auto t = _1mzkx_prod(z, n / 2);
                t *= t.mulx(bpow(z, n / 2));
                if(n % 2) {
                    t *= poly_t(std::vector<T>{1, -bpow(z, n - 1)});
                }
                return t;
            }
        }

        poly_t chirpz_inverse(T z, int n) const { // P(1), P(z), P(z^2), ..., P(z^(n-1))
            if(is_zero()) {
                return {};
            }
            if(z == T(0)) {
                if(n == 1) {
                    return *this;
                } else {
                    return std::vector{(*this)[1], (*this)[0] - (*this)[1]};
                }
            }
            std::vector<T> y(n);
            for(int i = 0; i < n; i++) {
                y[i] = (*this)[i];
            }
            auto prods_pos = _1mzk_prod_inv(z, n);
            auto prods_neg = _1mzk_prod_inv(z.inv(), n);

            T zn = bpow(z, n-1).inv();
            T znk = 1;
            for(int i = 0; i < n; i++) {
                y[i] *= znk * prods_neg[i] * prods_pos[(n - 1) - i];
                znk *= zn;
            }

            poly_t p_over_q = poly_t(y).chirpz(z, n);
            poly_t q = _1mzkx_prod(z, n);

            return (p_over_q * q).mod_xk(n).reverse(n);
        }

        static poly_t build(std::vector<poly_t> &res, int v, auto L, auto R) { // builds evaluation tree for (x-a1)(x-a2)...(x-an)
            if(R - L == 1) {
                return res[v] = std::vector<T>{-*L, 1};
            } else {
                auto M = L + (R - L) / 2;
                return res[v] = build(res, 2 * v, L, M) * build(res, 2 * v + 1, M, R);
            }
        }

        poly_t to_newton(std::vector<poly_t> &tree, int v, auto l, auto r) {
            if(r - l == 1) {
                return *this;
            } else {
                auto m = l + (r - l) / 2;
                auto A = (*this % tree[2 * v]).to_newton(tree, 2 * v, l, m);
                auto B = (*this / tree[2 * v]).to_newton(tree, 2 * v + 1, m, r);
                return A + B.mul_xk(m - l);
            }
        }

        poly_t to_newton(std::vector<T> p) {
            if(is_zero()) {
                return *this;
            }
            int n = p.size();
            std::vector<poly_t> tree(4 * n);
            build(tree, 1, begin(p), end(p));
            return to_newton(tree, 1, begin(p), end(p));
        }

        std::vector<T> eval(std::vector<poly_t> &tree, int v, auto l, auto r) { // auxiliary evaluation function
            if(r - l == 1) {
                return {eval(*l)};
            } else {
                auto m = l + (r - l) / 2;
                auto A = (*this % tree[2 * v]).eval(tree, 2 * v, l, m);
                auto B = (*this % tree[2 * v + 1]).eval(tree, 2 * v + 1, m, r);
                A.insert(end(A), begin(B), end(B));
                return A;
            }
        }
        
        std::vector<T> eval(std::vector<T> x) { // evaluate polynomial in (x1, ..., xn)
            int n = x.size();
            if(is_zero()) {
                return std::vector<T>(n, T(0));
            }
            std::vector<poly_t> tree(4 * n);
            build(tree, 1, begin(x), end(x));
            return eval(tree, 1, begin(x), end(x));
        }
        
        poly_t inter(std::vector<poly_t> &tree, int v, auto ly, auto ry) { // auxiliary interpolation function
            if(ry - ly == 1) {
                return {*ly / a[0]};
            } else {
                auto my = ly + (ry - ly) / 2;
                auto A = (*this % tree[2 * v]).inter(tree, 2 * v, ly, my);
                auto B = (*this % tree[2 * v + 1]).inter(tree, 2 * v + 1, my, ry);
                return A * tree[2 * v + 1] + B * tree[2 * v];
            }
        }
        
        static auto inter(std::vector<T> x, std::vector<T> y) { // interpolates minimum polynomial from (xi, yi) pairs
            int n = x.size();
            std::vector<poly_t> tree(4 * n);
            return build(tree, 1, begin(x), end(x)).deriv().inter(tree, 1, begin(y), end(y));
        }

        static auto resultant(poly_t a, poly_t b) { // computes resultant of a and b
            if(b.is_zero()) {
                return 0;
            } else if(b.deg() == 0) {
                return bpow(b.lead(), a.deg());
            } else {
                int pw = a.deg();
                a %= b;
                pw -= a.deg();
                auto mul = bpow(b.lead(), pw) * T((b.deg() & a.deg() & 1) ? -1 : 1);
                auto ans = resultant(b, a);
                return ans * mul;
            }
        }
                
        static poly_t xk(size_t n) { // P(x) = x^n
            return poly_t(T(1)).mul_xk(n);
        }
        
        static poly_t ones(size_t n) { // P(x) = 1 + x + ... + x^{n-1} 
            return std::vector<T>(n, 1);
        }
        
        static poly_t expx(size_t n) { // P(x) = e^x (mod x^n)
            return ones(n).borel();
        }

        static poly_t log1px(size_t n) { // P(x) = log(1+x) (mod x^n)
            std::vector<T> coeffs(n, 0);
            for(size_t i = 1; i < n; i++) {
                coeffs[i] = (i & 1 ? T(i).inv() : -T(i).inv());
            }
            return coeffs;
        }

        static poly_t log1mx(size_t n) { // P(x) = log(1-x) (mod x^n)
            return -ones(n).integr();
        }
        
        // [x^k] (a corr b) = sum_{i} a{(k-m)+i}*bi
        static poly_t corr(poly_t a, poly_t b) { // cross-correlation
            return a * b.reverse();
        }

        // [x^k] (a semicorr b) = sum_i a{i+k} * b{i}
        static poly_t semicorr(poly_t a, poly_t b) {
            return corr(a, b).div_xk(b.deg());
        }
        
        poly_t invborel() const { // ak *= k!
            auto res = *this;
            for(int i = 0; i <= deg(); i++) {
                res.coef(i) *= fact<T>(i);
            }
            return res;
        }
        
        poly_t borel() const { // ak /= k!
            auto res = *this;
            for(int i = 0; i <= deg(); i++) {
                res.coef(i) *= rfact<T>(i);
            }
            return res;
        }
        
        poly_t shift(T a) const { // P(x + a)
            return semicorr(invborel(), expx(deg() + 1).mulx(a)).borel();
        }
        
        poly_t x2() { // P(x) -> P(x^2)
            std::vector<T> res(2 * a.size());
            for(size_t i = 0; i < a.size(); i++) {
                res[2 * i] = a[i];
            }
            return res;
        }
        
        // Return {P0, P1}, where P(x) = P0(x) + xP1(x)
        std::array<poly_t, 2> bisect() const {
            std::vector<T> res[2];
            res[0].reserve(deg() / 2 + 1);
            res[1].reserve(deg() / 2 + 1);
            for(int i = 0; i <= deg(); i++) {
                res[i % 2].push_back(a[i]);
            }
            return {res[0], res[1]};
        }
        
        // Find [x^k] P / Q
        static T kth_rec(poly_t P, poly_t Q, int64_t k) {
            while(k > Q.deg()) {
                int n = Q.a.size();
                auto [Q0, Q1] = Q.mulx(-1).bisect();
                auto [P0, P1] = P.bisect();
                
                int N = fft::com_size((n + 1) / 2, (n + 1) / 2);
                
                auto Q0f = fft::dft(Q0.a, N);
                auto Q1f = fft::dft(Q1.a, N);
                auto P0f = fft::dft(P0.a, N);
                auto P1f = fft::dft(P1.a, N);
                
                if(k % 2) {
                    P = poly_t(Q0f * P1f) + poly_t(Q1f * P0f);
                } else {
                    P = poly_t(Q0f * P0f) + poly_t(Q1f * P1f).mul_xk(1);
                }
                Q = poly_t(Q0f * Q0f) - poly_t(Q1f * Q1f).mul_xk(1);
                k /= 2;
            }
            return (P * Q.inv(Q.deg() + 1))[k];
        }

        // inverse series mod x^n
        poly_t inv(size_t n) const {
            return poly::impl::inv(*this, n);
        }
        // [x^k]..[x^{k+n-1}] of inv()
        // supports negative k if k+n >= 0
        poly_t inv(int64_t k, size_t n) const {
            return poly::impl::inv(*this, k, n);
        }
        
        // compute A(B(x)) mod x^n in O(n^2)
        static poly_t compose(poly_t A, poly_t B, int n) {
            int q = std::sqrt(n);
            std::vector<poly_t> Bk(q);
            auto Bq = B.pow(q, n);
            Bk[0] = poly_t(T(1));
            for(int i = 1; i < q; i++) {
                Bk[i] = (Bk[i - 1] * B).mod_xk(n);
            }
            poly_t Bqk(1);
            poly_t ans;
            for(int i = 0; i <= n / q; i++) {
                poly_t cur;
                for(int j = 0; j < q; j++) {
                    cur += Bk[j] * A[i * q + j];
                }
                ans += (Bqk * cur).mod_xk(n);
                Bqk = (Bqk * Bq).mod_xk(n);
            }
            return ans;
        }
        
        // compute A(B(x)) mod x^n in O(sqrt(pqn log^3 n))
        // preferrable when p = deg A and q = deg B
        // are much less than n
        static poly_t compose_large(poly_t A, poly_t B, int n) {
            if(B[0] != T(0)) {
                return compose_large(A.shift(B[0]), B - B[0], n);
            }
            
            int q = std::sqrt(n);
            auto [B0, B1] = std::make_pair(B.mod_xk(q), B.div_xk(q));
            
            B0 = B0.div_xk(1);
            std::vector<poly_t> pw(A.deg() + 1);
            auto getpow = [&](int k) {
                return pw[k].is_zero() ? pw[k] = B0.pow(k, n - k) : pw[k];
            };
            
            std::function<poly_t(poly_t const&, int, int)> compose_dac = [&getpow, &compose_dac](poly_t const& f, int m, int N) {
                if(f.deg() <= 0) {
                    return f;
                }
                int k = m / 2;
                auto [f0, f1] = std::make_pair(f.mod_xk(k), f.div_xk(k));
                auto [A, B] = std::make_pair(compose_dac(f0, k, N), compose_dac(f1, m - k, N - k));
                return (A + (B.mod_xk(N - k) * getpow(k).mod_xk(N - k)).mul_xk(k)).mod_xk(N);
            };
            
            int r = n / q;
            auto Ar = A.deriv(r);
            auto AB0 = compose_dac(Ar, Ar.deg() + 1, n);
            
            auto Bd = B0.mul_xk(1).deriv();
            
            poly_t ans = T(0);
            
            std::vector<poly_t> B1p(r + 1);
            B1p[0] = poly_t(T(1));
            for(int i = 1; i <= r; i++) {
                B1p[i] = (B1p[i - 1] * B1.mod_xk(n - i * q)).mod_xk(n - i * q);
            }
            while(r >= 0) {
                ans += (AB0.mod_xk(n - r * q) * rfact<T>(r) * B1p[r]).mul_xk(r * q).mod_xk(n);
                r--;
                if(r >= 0) {
                    AB0 = ((AB0 * Bd).integr() + A[r] * fact<T>(r)).mod_xk(n);
                }
            }
            
            return ans;
        }
    };
    
    static auto operator * (const auto& a, const poly_t<auto>& b) {
        return b * a;
    }
};
#endif // CP_ALGO_ALGEBRA_POLY_HPP
