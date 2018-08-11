// Build: O (N log N)
// Query: O (log N)

const int MAXN = 112345;
const int LOGN = 21;

vector <int> g[MAXN];
int h[MAXN];
int memo[MAXN][LOGN];

void dfs_lca (int x) {
	for (int i = 0; i < g[x].size(); ++i) {
		int y = g[x][i];
		if (y == memo[x][0]) continue;
		
		h[y] = h[x] + 1;
		memo[y][0] = x;

		dfs_lca (y);
	}
}

void build_lca (int n) {
	for (int j = 1; j < LOGN; ++j)
		for (int i = 0; i < n; ++i)
			memo[i][j] = memo[memo[i][j - 1]][j - 1];
}

int lca (int x, int y) {
	if (h[x] < h[y]) swap (x, y);
	int d = h[x] - h[y];

	for (int i = 0; i < LOGN; ++i)
		if (d & (1 << i))
			x = memo[x][i];

	if (x == y) return x;

	for (int i = LOGN - 1; i >= 0; --i)
		if (memo[x][i] != memo[y][i]) {
			x = memo[x][i];
			y = memo[y][i];
		}

	return memo[x][0];
}