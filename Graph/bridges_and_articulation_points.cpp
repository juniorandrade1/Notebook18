// Untested
// DFS has to be called from 0

const int MAXN = 312345;

struct Edge {
	int x, y, id;
	bool isCut;

	Edge () { isCut = false; }
	Edge (int _x, int _y, int _id) {
		x = _x;
		y = _y;
		id = _id;
		isCut = false;
	}

	int get (int z) {
		return (x == z) ? y : x;
	}
};

vector <Edge> edges;
vector <int> g[MAXN];

void addEdge (int x, int y) {
	g[x].push_back (edges.size());
	g[y].push_back (edges.size());
	edges.push_back (Edge (x, y, edges.size()));
}

int cnt;
int d[MAXN];
int low[MAXN];
bool vis[MAXN];
bool isCut[MAXN];

void dfs (int x, int p) {
	vis[x] = true;

	int nf = 0;
	d[x] = low[x] = cnt++;
	bool any = false;

	for (int i = 0; i < g[x].size(); ++i) {
		Edge & e = edges[g[x][i]];
		int y = e.get();

		if (!vis[y]) {
			dfs (y);
			nf++;
			low[x] = min (low[x], low[y]);
			
			if (low[y] >= d[x]) any = true;
			if (low[y] > d[x])
				e.isCut = true;
		} else if (y != p) low[x] = min (low[x], d[y]);
	}

	if (x == 0 && nf >= 2) // x == root if root != 0
		isCut[x] = true;
	else if (x != 0 && any)
		isCut[x] = true;
}