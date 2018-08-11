const int MAXN = 1123456;

int n, m;
vector <int> g[MAXN];

int pre[MAXN];
int id[MAXN];	// id[X] = strongly connected component index of X
int low[MAXN];	// Lowlink value for entire subtree
stack <int> stk;
int preordercounter;
int numSCCs;

void dfs (int x) {
	pre[x] = preordercounter++;
	low[x] = pre[x];
	stk.push (x);

	for (int i = 0; i < g[x].size(); ++i) {
		int y = g[x][i];
		if (pre[y] == -1)
			dfs (y);

		low[x] = min (low[x], low[y]);
	}

	if (low[x] == pre[x]) {
		while (true) {
			int y = stk.top();
			stk.pop();
			id[y] = numSCCs;
			low[y] = n;

			// Y is a member of the strongly
			// connected component of index numSCCs

			if (x == y) break;
		}
		numSCCs++;
	}
}

void tarjan () {
	numSCCs = 0;
	preordercounter = 0;
	memset (pre, -1, sizeof pre);

	for (int i = 0; i < n; ++i)
		if (pre[i] == -1)
			dfs (i);
}