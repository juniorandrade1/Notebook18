struct SuffixArray {
  vector<int> lcp;
  vector< vector<pair<int, int> > > rmq;
  int n, h;
  vector< int > sa; //position in sa -> origin
  vector< int > invsa; //position in origin -> sa
  bool cmp(int a, int b) { return invsa[a + h] < invsa[b + h]; }
  void ternary_sort(int a, int b) {
    if (a == b) return;
    int pivot = sa[a + rand() % (b - a)];
    int left = a, right = b;
    for (int i = a; i < b; ++i) if (cmp(sa[i], pivot)) swap(sa[i], sa[left++]);
    for (int i = b-1; i >= left; --i) if (cmp(pivot, sa[i])) swap(sa[i], sa[--right]);
    ternary_sort(a, left);
    for (int i = left; i < right; ++i) invsa[sa[i]] = right-1;
    if (right - left == 1) sa[left] = -1;
    ternary_sort(right, b);
  }
  SuffixArray() {}
  SuffixArray(vector<int> v): n(v.size()), sa(n) {
    v.push_back(INT_MIN);
    invsa = v;
    iota(sa.begin(), sa.end(), 0);
    h = 0; ternary_sort(0, n);
    for (h = 1; h <= n; h *= 2) {
      for (int j = 0, i = j; i != n; i = j) {
        if (sa[i] < 0) {
          while (j < n && sa[j] < 0) j += -sa[j];
          sa[i] = -(j-i);
        } else {
          j = invsa[sa[i]]+1;
          ternary_sort(i, j);
        }
      }
    }
    for (int i = 0; i < n; ++i) sa[invsa[i]] = i;
    lcp.resize(n);
    int res = 0;
    for (int i = 0; i < n; ++i) {
      if (invsa[i] > 0) while (v[i+res] == v[sa[invsa[i]-1]+res]) ++res;
      lcp[invsa[i]] = res;
      res = max(res-1, 0);
    }
    int logn = 0; while ((1<<logn+1) <= n) ++logn;
    rmq.resize(logn + 1, vector< pair<int, int> >(n));
    for (int i = 0; i < n; ++i) rmq[0][i] = make_pair(lcp[i], i);
    for (int l = 1; l <= logn; ++l) for (int i = 0; i + (1 << l) <= n; ++i) rmq[l][i] = min(rmq[l-1][i], rmq[l-1][i+(1<<l-1)]);
  }
  pair<int, int> rmq_query(int a, int b) {
    int size = b - a + 1, l = 31 - __builtin_clz(size);
    return min(rmq[l][a], rmq[l][b - (1 << l) + 1]);
  }
  int get_lcp(int a, int b) {
    if(a == b) return n - a;
    int ia = invsa[a];
    int ib = invsa[b];
    return rmq_query(min(ia, ib)+1, max(ia, ib)).first;
  }
  int get_lcp2(int ia, int ib) {
    return rmq_query(min(ia, ib)+1, max(ia, ib)).first;
  }
  pair<int, int> get_range(int strpos, int size) {
    int pos = invsa[strpos];
    int start, end;
    {
      int l = 0, r = pos;
      while (l < r) {
        int m = (l+r)/2;
        if (get_lcp2(m, pos) < size) l = m+1;
        else r = m;
      }
      start = l;
    }
    {
      int l = pos, r = n-1;
      while (l < r) {
        int m = (l+r+1)/2;
        if (get_lcp2(m, pos) < size) r = m-1;
        else l = m;
      }
      end = l;
    }
    return {start, end};
  }
};