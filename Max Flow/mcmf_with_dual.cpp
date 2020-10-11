// CF Submission: https://codeforces.com/contest/1430/submission/95221926
// #pragma GCC optimize("Ofast")
// #pragma GCC target("avx2,bmi,bmi2,lzcnt")
// #define NDEBUG
 
#include <bits/extc++.h>
#include <x86intrin.h>
 
struct rep {
  struct iter {
    int i;
    constexpr void operator++() { ++i; }
    constexpr int operator*() const { return i; }
    friend constexpr bool operator!=(iter a, iter b) { return *a != *b; }
  };
  const int l, r;
  constexpr rep(int _l, int _r) : l(std::min(_l, _r)), r(_r) {}
  constexpr rep(int n) : rep(0, n) {}
  constexpr iter begin() const { return {l}; }
  constexpr iter end() const { return {r}; }
};
struct per {
  struct iter {
    int i;
    constexpr void operator++() { --i; }
    constexpr int operator*() const { return i; }
    friend constexpr bool operator!=(iter a, iter b) { return *a != *b; }
  };
  const int l, r;
  constexpr per(int _l, int _r) : l(std::min(_l, _r)), r(_r) {}
  constexpr per(int n) : per(0, n) {}
  constexpr iter begin() const { return {r - 1}; }
  constexpr iter end() const { return {l - 1}; }
};
template <class T, class U>
constexpr bool chmin(T& a, U&& b) {
  return b < a ? a = std::forward<U>(b), true : false;
}
template <class T, class U>
constexpr bool chmax(T& a, U&& b) {
  return a < b ? a = std::forward<U>(b), true : false;
}
 
namespace atcoder {
 
template <class Cap, class Cost>
struct mcf_graph {
 public:
  mcf_graph() {}
  mcf_graph(int n) : _n(n), g(n) {}
 
  int add_edge(int from, int to, Cap cap, Cost cost) {
    assert(0 <= from && from < _n);
    assert(0 <= to && to < _n);
    int m = int(pos.size());
    pos.push_back({from, int(g[from].size())});
    int from_id = int(g[from].size());
    int to_id = int(g[to].size());
    if (from == to) to_id++;
    g[from].push_back(_edge{to, to_id, cap, cost});
    g[to].push_back(_edge{from, from_id, 0, -cost});
    return m;
  }
 
  struct edge {
    int from, to;
    Cap cap, flow;
    Cost cost;
  };
 
  edge get_edge(int i) {
    int m = int(pos.size());
    assert(0 <= i && i < m);
    auto _e = g[pos[i].first][pos[i].second];
    auto _re = g[_e.to][_e.rev];
    return edge{
        pos[i].first, _e.to, _e.cap + _re.cap, _re.cap, _e.cost,
    };
  }
  std::vector<edge> edges() {
    int m = int(pos.size());
    std::vector<edge> result(m);
    for (int i = 0; i < m; i++) {
      result[i] = get_edge(i);
    }
    return result;
  }
 
  std::pair<Cap, Cost> flow(int s, int t) {
    return flow(s, t, std::numeric_limits<Cap>::max());
  }
  std::pair<Cap, Cost> flow(int s, int t, Cap flow_limit) {
    return slope(s, t, flow_limit).back();
  }
  std::vector<std::pair<Cap, Cost>> slope(int s, int t) {
    return slope(s, t, std::numeric_limits<Cap>::max());
  }
  std::vector<std::pair<Cap, Cost>> slope(int s, int t, Cap flow_limit) {
    assert(0 <= s && s < _n);
    assert(0 <= t && t < _n);
    assert(s != t);
    // variants (C = maxcost):
    // -(n-1)C <= dual[s] <= dual[i] <= dual[t] = 0
    // reduced cost (= e.cost + dual[e.from] - dual[e.to]) >= 0 for all edge
    std::vector<Cost> dual(_n, 0), dist(_n);
    std::vector<int> pv(_n), pe(_n);
    std::vector<bool> vis(_n);
    auto dual_ref = [&]() {
      std::fill(dist.begin(), dist.end(), std::numeric_limits<Cost>::max());
      std::fill(pv.begin(), pv.end(), -1);
      std::fill(pe.begin(), pe.end(), -1);
      std::fill(vis.begin(), vis.end(), false);
      struct Q {
        Cost key;
        int to;
        bool operator<(Q r) const { return key > r.key; }
      };
      std::priority_queue<Q> que;
      dist[s] = 0;
      que.push(Q{0, s});
      while (!que.empty()) {
        int v = que.top().to;
        que.pop();
        if (vis[v]) continue;
        vis[v] = true;
        if (v == t) break;
        // dist[v] = shortest(s, v) + dual[s] - dual[v]
        // dist[v] >= 0 (all reduced cost are positive)
        // dist[v] <= (n-1)C
        for (int i = 0; i < int(g[v].size()); i++) {
          auto e = g[v][i];
          if (vis[e.to] || !e.cap) continue;
          // |-dual[e.to] + dual[v]| <= (n-1)C
          // cost <= C - -(n-1)C + 0 = nC
          Cost cost = e.cost - dual[e.to] + dual[v];
          if (dist[e.to] - dist[v] > cost) {
            dist[e.to] = dist[v] + cost;
            pv[e.to] = v;
            pe[e.to] = i;
            que.push(Q{dist[e.to], e.to});
          }
        }
      }
      if (!vis[t]) {
        return false;
      }
 
      for (int v = 0; v < _n; v++) {
        if (!vis[v]) continue;
        // dual[v] = dual[v] - dist[t] + dist[v]
        //         = dual[v] - (shortest(s, t) + dual[s] - dual[t]) +
        //         (shortest(s, v) + dual[s] - dual[v]) = - shortest(s, t) +
        //         dual[t] + shortest(s, v) = shortest(s, v) - shortest(s, t) >=
        //         0 - (n-1)C
        dual[v] -= dist[t] - dist[v];
      }
      return true;
    };
    Cap flow = 0;
    Cost cost = 0, prev_cost_per_flow = -1;
    std::vector<std::pair<Cap, Cost>> result;
    result.push_back({flow, cost});
    while (flow < flow_limit) {
      if (!dual_ref()) break;
      Cap c = flow_limit - flow;
      for (int v = t; v != s; v = pv[v]) {
        c = std::min(c, g[pv[v]][pe[v]].cap);
      }
      for (int v = t; v != s; v = pv[v]) {
        auto& e = g[pv[v]][pe[v]];
        e.cap -= c;
        g[v][e.rev].cap += c;
      }
      Cost d = -dual[s];
      flow += c;
      cost += c * d;
      if (prev_cost_per_flow == d) {
        result.pop_back();
      }
      result.push_back({flow, cost});
      prev_cost_per_flow = d;
    }
    return result;
  }
 
 private:
  int _n;
 
  struct _edge {
    int to, rev;
    Cap cap;
    Cost cost;
  };
 
  std::vector<std::pair<int, int>> pos;
  std::vector<std::vector<_edge>> g;
};
 
}  // namespace atcoder
 
template <class Cap, class Cost>
struct min_cost_b_flow {
  struct result {
    bool feasible;
    Cost cost;
    std::vector<Cap> flow;
    std::vector<Cost> dual;
  };
 
  min_cost_b_flow() {}
  explicit min_cost_b_flow(int n) : g(n + 2), b(n) {}
 
  int size() const { return std::size(b); }
  int add_edge(int src, int dst, Cap lower, Cap upper, Cost cost) {
    assert(0 <= src), assert(src < size());
    assert(0 <= dst), assert(dst < size());
    assert(lower <= upper);
    if (rev.push_back(cost < 0), rev.back()) {
      std::swap(src, dst);
      std::tie(lower, upper) = std::pair{-upper, -lower};
      cost = -cost;
    }
    b[src] -= lower;
    b[dst] += lower;
    res.cost += lower * cost;
    res.flow.push_back(lower);
    return g.add_edge(src, dst, upper - lower, cost);
  }
  void add_supply(int v, Cap x) {
    assert(0 <= v), assert(v < size());
    b[v] += x;
  }
  void add_demand(int v, Cap x) {
    assert(0 <= v), assert(v < size());
    b[v] -= x;
  }
 
  result flow() {
    int source = size(), sink = source + 1;
    Cap positive{}, negative{};
    for (int v = 0; v < size(); ++v)
      if (b[v] > 0) {
        g.add_edge(source, v, b[v], 0);
        positive += b[v];
      } else if (b[v] < 0) {
        g.add_edge(v, sink, -b[v], 0);
        negative += -b[v];
      }
    if (positive != negative) return {};
    auto [flow, cost] = g.flow(source, sink);
    if (flow < positive) return {};
    res.feasible = true;
    res.cost += cost;
    std::vector<std::vector<std::pair<int, Cost>>> h(size());
    for (int i = 0; i < int(std::size(res.flow)); ++i) {
      auto e = g.get_edge(i);
      if (e.flow < e.cap) h[e.from].emplace_back(e.to, e.cost);
      if (e.flow > 0) h[e.to].emplace_back(e.from, -e.cost);
      res.flow[i] += e.flow;
      if (rev[i]) res.flow[i] = -res.flow[i];
    }
    res.dual.resize(size());
    std::vector<int> que(size());
    std::iota(begin(que), end(que), 0);
    std::vector in_que(size(), true);
    for (int bg = 0; bg < int(std::size(que));) {
      int v = que[bg++];
      in_que[v] = false;
      for (auto [u, c] : h[v]) {
        if (res.dual[v] + c < res.dual[u]) {
          res.dual[u] = res.dual[v] + c;
          if (not in_que[u]) in_que[u] = true, que.push_back(u);
        }
      }
    }
    return res;
  }
 
 private:
  atcoder::mcf_graph<Cap, Cost> g;
  std::vector<Cap> b;
  std::vector<bool> rev;
  result res{};
};

int main() {
  using namespace std;
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m;
  min_cost_b_flow<int, int64_t> g(n);
  while (m--) {
    int x, y, w;
    cin >> x >> y >> w;
    --x, --y;
    g.add_edge(x, y, -1e7, w, 1);
  }
  auto ans = g.flow().dual;
  auto mx = *max_element(begin(ans), end(ans));
  for (auto&& e : ans) e = mx - e;
  for (int i : rep(n)) cout << ans[i] << " \n"[i == n - 1];
}
