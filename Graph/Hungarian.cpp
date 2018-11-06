template <typename T>
class Hungarian {
  const T FINF = numeric_limits<T>::max() / 2.0;
  int n, m;
  vector< T > u, v, p, way;
public:
  Hungarian(){};
  Hungarian(vector< vector< T > > a) { // n <= m 
    n = a.size() - 1;
    m = a[0].size() - 1;
    u.resize(n + 1);
    v.resize(m + 1);
    p.resize(m + 1);
    way.resize(m + 1);
    for (int i = 1; i <= n; ++i) {
      p[0] = i;
      int j0 = 0;
      vector< T > minv (m + 1, FINF);
      vector< bool > used (m + 1, false);
      do {
        used[j0] = true;
        int i0 = p[j0],  j1;
        T delta = FINF;
        for (int j = 1; j <= m; ++j)
          if (!used[j]) {
            int cur = a[i0][j] - u[i0] - v[j];
            if (cur < minv[j])
              minv[j] = cur,  way[j] = j0;
            if (minv[j] < delta)
              delta = minv[j],  j1 = j;
          }
        for (int j=0; j<=m; ++j)
          if (used[j])
            u[p[j]] += delta,  v[j] -= delta;
          else
            minv[j] -= delta;
        j0 = j1;
      } while (p[j0] != 0);
      do {
        int j1 = way[j0];
        p[j0] = p[j1];
        j0 = j1;
      } while (j0);
    }
  }
  T getCost() {
    return -v[0];
  }
  vector< int > getAns() {
    vector< int > ans (n + 1);
    for (int j = 1; j <= m; ++j) ans[p[j]] = j;
    return ans;
  }
};