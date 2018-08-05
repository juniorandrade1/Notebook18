template <typename FTYPE, typename CTYPE> 
class MinCostMaxFlow {
private:
  const CTYPE COSTINF = numeric_limits<CTYPE>::max() / 2.0; 
  const FTYPE FLOWINF = numeric_limits<FTYPE>::max() / 2.0;
  const CTYPE eps = (CTYPE)(1e-9);
  struct Edge {
    int to;
    FTYPE cap;
    CTYPE cost;
    Edge(int a, FTYPE cp, CTYPE ct) { to = a; cap = cp; cost = ct; }
  };
  int n, sta, fin;
  vector< vector< int > > adj;
  vector< Edge > edge;
  vector< FTYPE > flow;
  vector< CTYPE > dist;
  vector< int > prv, eIdx;
  pair<FTYPE, CTYPE> dijkstra() { 
    fill(dist.begin(), dist.end(), COSTINF);
    priority_queue< pair< CTYPE, int > > q; q.push(make_pair(0, sta));
    dist[sta] = 0;
    flow[sta] = FLOWINF;
    while(!q.empty()) {
      pair< CTYPE, int >foo = q.top(); q.pop();
      int x = foo.second;
      CTYPE d = -foo.first;
      for(size_t a = 0; a < adj[x].size(); ++a) {
        int ind = adj[x][a];
        int y = edge[ind].to;
        if(!edge[ind].cap || dist[y] - dist[x] - edge[ind].cost <= eps) continue;
        dist[y] = dist[x] + edge[ind].cost;
        q.push(make_pair(-dist[y], y));
        prv[y] = x;
        eIdx[y] = ind;
        flow[y] = min(flow[x], edge[ind].cap);
      }
    }
    if(dist[fin] == COSTINF) return make_pair(FLOWINF, COSTINF);
    pair<FTYPE, CTYPE> ret = make_pair(flow[fin], 0);
    for(int cur = fin; cur != sta; cur = prv[cur]) {
      int ind = eIdx[cur];
      edge[ind].cap -= flow[fin];
      edge[ind ^ 1].cap += flow[fin];
      ret.second += flow[fin] * edge[ind].cost; 
    }
    return ret;
  }
public:
  MinCostMaxFlow(int _n, int _sta, int _fin) {
    n = _n;
    sta = _sta;
    fin = _fin;
    adj.resize(n);
    flow.resize(n);
    dist.resize(n);
    prv.resize(n);
    eIdx.resize(n);
  }
  void addEdge(int u, int v, FTYPE flw, CTYPE cst) {
    adj[u].push_back(edge.size());
    edge.push_back(Edge(v, flw, cst));
    adj[v].push_back(edge.size());
    edge.push_back(Edge(u, 0, -cst));
  }
  pair<FTYPE, CTYPE> mcmf() {
    pair<FTYPE, CTYPE> ret = make_pair(0, 0), got;
    while(fabs((got = dijkstra()).first - FLOWINF) > eps) {
      ret.first += got.first;
      ret.second += got.second;
    }
    return ret;
  }
};