class Graph {
private:
  struct Edge {
    int y, nxt;
    Edge(){};
    Edge(int _y, int _nxt) {
      y = _y;
      nxt = _nxt;
    }
  };
  vector< Edge > edges;
  vector< int > p;
  vector< int > num, low, vis;
  int n, dfsCounter = 0;
public:
  Graph(int _n) {
    n = _n;
    p.resize(n, 0);
    num.resize(n, 0);
    low.resize(n, 0);
    vis.resize(n, 0);
  }
  void addEdge(int x, int y) {
    edges.push_back(Edge(y, p[x]));
    p[x] = edges.size();
    edges.push_back(Edge(x, p[y]));
    p[y] = edges.size();
  }
  void dfs(int x, int ult, vector< int > &sol) {
    num[x] = low[x] = ++dfsCounter;
    vis[x] = 1;
    int cut = 0;
    int qtd = 0;
    for(int i = p[x]; i; i = edges[i - 1].nxt) {
      int y = edges[i - 1].y;
      if(y == ult) continue;
      if(!vis[y]) {
        dfs(y, x, sol);
        qtd++;
        low[x] = min(low[x], low[y]);
        if(low[y] >= num[x]) cut |= (x != ult); //articulação
        if(low[y] > num[x]);//ponte
      }
      else low[x] = min(low[x], num[y]);
    }
    cut |= (x == ult && qtd >= 2);
    if(cut) sol.push_back(x + 1);
  }
  vector< int > findCut() {
    vector< int > sol;
    for(int i = 0; i < n; ++i) {
      if(vis[i]) continue;
      dfs(i, i, sol); 
    }
    sort(sol.begin(), sol.end());
    return sol;
  }
};