#include <bits/stdc++.h>
using namespace std;

// Problem link: https://open.kattis.com/problems/letsmeet

const double EPS = 1e-9;
const int INF = 2123123123;

int gauss(vector<vector<double>> a, vector<double> &ans) {
  // assuming a is a n x m matrix
  int n = (int)a.size();
  int m = (int)a[0].size() - 1;

  vector<int> where(m, -1);
  for (int col = 0, row = 0; col < m && row < n; ++col) {
    int sel = row;
    for (int i = row; i < n; ++i) {
      if (abs(a[i][col]) > abs(a[sel][col])) {
        sel = i;
      }
    }

    if (abs(a[sel][col]) < EPS) {
      continue;
    }

    for (int i = col; i <= m; ++i) {
      swap(a[sel][i], a[row][i]);
    }

    where[col] = row;
    for (int i = 0; i < n; ++i) {
      if (i != row) {
        double c = a[i][col] / a[row][col];
        for (int j = col; j <= m; ++j) {
            a[i][j] -= a[row][j] * c;
        }
      }
    }

    ++row;
  }
  
  ans.assign(m, 0);
  for (int i = 0; i < m; ++i) {
    if (where[i] != -1) {
      ans[i] = a[where[i]][m] / a[where[i]][i];
    }
  }

  for (int i = 0; i < n; ++i) {
    double sum = 0;
    for (int j = 0; j < m; ++j) {
      sum += ans[j] * a[i][j];
    }

    if (abs(sum - a[i][m]) > EPS) {
      return 0;
    }
  }

  for (int i = 0; i < m; ++i) {
    if (where[i] == -1) {
      return INF;
    }
  }

  return 1;
}

int node(int a, int b, int n) {
  return a * n + b;
}

int main() {
  int v, e, s, t;
  vector<int> graph[22];

  cin >> v >> e;
  for (int i = 0; i < e; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back (b);
    graph[b].push_back (a);
  }

  bool vis[22][22];
  memset(vis, 0, sizeof vis);

  vector<pair<int, int>> st;
  for (int i = 0; i < v; i++) {
    st.push_back (make_pair (i, i));
    vis[i][i] = true;
  }

  while (!st.empty ()) {
    pair <int, int> node = st.back();
    st.pop_back();

    for (int i = 0; i < graph[node.first].size(); i++) {
      for (int j = 0; j < graph[node.second].size(); j++) {
        if (!vis[graph[node.first][i]][graph[node.second][j]]) {
          st.push_back(make_pair(graph[node.first][i], graph[node.second][j]));
          vis[graph[node.first][i]][graph[node.second][j]] = true;
        }
      }
    }
  }

  int n = v * v;
  vector<vector<double>> a(n, vector<double>(n+1, 0));
  for (int i = 0; i < v; i++) {
    for (int j = 0; j < v; j++) {
      a[node(i, j, v)][node(i, j, v)] =
      a[node(i, j, v)][n] = 1.0 * graph[i].size() * graph[j].size();

      if (i == j || !vis[i][j]) {
        for (int k = 0; k <= n; k++) {
          a[node(i, j, v)][k] = 0;
        }

        a[node(i, j, v)][node(i, j, v)] = 1;
      } else {
        for (int ii = 0; ii < graph[i].size(); ii++) {
          for (int jj = 0; jj < graph[j].size(); jj++) {
            a[node(i, j, v)][node(graph[i][ii], graph[j][jj], v)] = -1;
          }
        }
      }
    }
  }

  vector<double> res;
  cerr << gauss(a, res) << endl;

  cin >> s >> t;
  double ans = res[node(s, t, v)];
  if (isnan(ans) || !vis[s][t]) {
    cout << "never meet\n";
  } else {
    cout << setprecision (10) << fixed << ans << "\n";
  }

  return 0;
}
