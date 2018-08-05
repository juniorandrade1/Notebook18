template <typename T> 
class SparseTable {
private:
  static const int SIZE = 20;
  vector< vector< T > > spt;
  int n;
public:
  SparseTable(){};
  SparseTable(vector< T > &v) {
    n = v.size();
    spt.resize(n);
    for(int i = 0; i < n; ++i) {
      spt[i].resize(SIZE);
      spt[i][0] = v[i];
    }
    for(int j = 1; j < SIZE; ++j) {
      for(int i = 0; i + (1 << (j - 1)) < n; ++i) {
        spt[i][j] = spt[i][j - 1] + spt[i + (1 << (j - 1))][j - 1];
      }
    }
  }
  T queryRange(int l, int r) {
    int lg = 31 - __builtin_clz(r - l + 1);
    return spt[l][lg] + spt[r - (1 << lg) + 1][lg];
  }
};

struct NodeMin {
  long long x;
  NodeMin(){

  };
  NodeMin(long long _x) {
    x = _x;
  }
  NodeMin operator + (NodeMin &other) const {
    return NodeMin(min(x, other.x));
  }
};