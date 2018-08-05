template <typename T> 
class SegmentTree {
private:
  vector< T > tr;
  int n;
  void build(int no, int l, int r, vector< T > &v) {
    if(l == r) {
      tr[no] = v[l];
      return;
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    build(nxt, l, mid, v); build(nxt + 1, mid + 1, r, v);
    tr[no] = tr[nxt] + tr[nxt + 1];
  }
  T query(int no, int l, int r, int i, int j) {
    if(r < i || l > j) return T();
    if(l >= i && r <= j) return tr[no];
    int nxt = (no << 1), mid = (l + r) >> 1;
    return query(nxt, l, mid, i, j) + query(nxt + 1, mid + 1, r, i, j);
  }
  void pointUpdate(int no, int l, int r, int i, T nw) {
    if(l == r) {
      tr[no] = nw;
      return;
    }
    int nxt = (no << 1), mid = (l + r) >> 1;
    if(i <= mid) pointUpdate(nxt, l, mid, i, nw);
    else pointUpdate(nxt + 1, mid + 1, r, i, nw);
    tr[no] = tr[nxt] + tr[nxt + 1];
  }
public:
  SegmentTree(){
    n = 100000;
    tr.resize(n * 4);
  };
  SegmentTree(int _n) {
    n = _n;
    tr.resize(n * 4);
  }
  SegmentTree(vector< T > &v) {
    n = (int)v.size();
    tr.resize(n * 4);
    build(1, 0, n - 1, v);
  }
  T queryRange(int l, int r) {
    return query(1, 0, n - 1, l, r);
  }
  void pointUpdate(int i, T nw) {
    pointUpdate(1, 0, n - 1, i, nw);
  }
};

struct NodeMin {
  long long x;
  NodeMin(){
    x = LINF;
  };
  NodeMin(long long _x) {
    x = _x;
  }
  NodeMin operator + (NodeMin other) const {
    return NodeMin(min(x, other.x));
  }
};
