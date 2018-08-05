class Tree {
public:
  bool dfsProcessed;
  int n, lg;
  vector< vector< int > > adj;
  vector< vector< int > > lca;
  vector< int > in, out, h, sz;
  int dc;
  Tree(){};
  Tree(int _n) {
    n = _n;
    lg = log2(n) + 1;
    adj.resize(n);
    lca.resize(n, vector< int >(lg));
    h.resize(n);
    in.resize(n);
    out.resize(n);
    sz.resize(n);
    dc = 0;
    dfsProcessed = false;
  }
  void addEdge(int x, int y) {
    adj[x].emplace_back(y);
    adj[y].emplace_back(x);
  }
  void dfs(int x, int ult) {
    sz[x] = 1;
    lca[x][0] = ult;
    in[x] = dc++;
    for(int i = 1; i < lg; ++i) lca[x][i] = lca[lca[x][i - 1]][i - 1];
    for(int y : adj[x]) {
      if(y == ult) continue;
      h[y] = h[x] + 1;
      dfs(y, x);
      sz[x] += sz[y];
    }
    out[x] = dc++;
  }
  int getLca(int x, int y) {
    if(h[x] < h[y]) swap(x, y);
    int d = h[x] - h[y];
    for(int i = lg - 1; i >= 0; --i) if((d >> i) & 1) x = lca[x][i];
    if(x == y) return x;
    for(int i = lg - 1; i >= 0; --i) if(lca[x][i] != lca[y][i]) {
      x = lca[x][i];
      y = lca[y][i];
    }
    return lca[x][0];
  }
  int getDad(int x) { return lca[x][0]; }
  int getDist(int x, int y) {
    return h[x] + h[y] - 2 * h[getLca(x, y)];
  }
  void process() {
    if(dfsProcessed) return;
    dfsProcessed = true;
    dfs(0, 0);
  }
};

template <typename T>
class HLD {
public:
  int n;
  Tree t;
  vector< int > chain, posInBase, chainHead;
  int bc, cc;
  HLD(Tree _t) {
    t = _t;
    n = t.n;
    t.process();

    chainHead.resize(n + 1);
    posInBase.resize(n + 1);
    chain.resize(n + 1);
    chainHead[0] = 0;
    
    bc = cc = 0;
    dfs(0, 0);
  }
  void dfs(int x, int ult) {
    chain[x] = cc;
    posInBase[x] = bc++;
    int idx = -1, bst = -1;
    for(int y : t.adj[x]) {
      if(y == ult) continue;
      if(t.sz[y] > bst) {
        bst = t.sz[y];
        idx = y;
      }
    }
    if(idx != -1) dfs(idx, x);
    for(int y : t.adj[x]) {
      if(y == ult || y == idx) continue;
      cc++;
      chainHead[cc] = y;
      dfs(y, x);
    }
  }
};