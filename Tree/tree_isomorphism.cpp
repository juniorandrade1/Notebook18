const int MAXN = 11234;

int n;
vector <int> g[MAXN];
int dist[MAXN];
int pai[MAXN];

map <vector <int>, int> m;

int dfs (int x) {
	for (int i = 0; i < g[x].size(); ++i) {
		int y = g[x][i];
		if (y == pai[x]) continue;

		pai[y] = x;
		dist[y] = dist[x] + 1;
		dfs (y);
	}
}

int c1, c2;

int getFarthest (int x) {
	pai[x] = -1;
	dist[x] = 0;
	dfs (x);

	int y = 0;
	for (int i = 0; i < n; ++i)
		if (dist[i] > dist[y])
			y = i;

	return y;
}

void getCenter () {
	c1 = -1; c2 = -1;
	int x = getFarthest (0);
	int y = getFarthest (x);

	int d = dist[y];

	while (y != -1) {
		if (dist[y] * 2 == d) c1 = y;
		else if (dist[y] * 2 - 1 == d) c1 = y;
		else if (dist[y] * 2 + 1 == d) c2 = y;
		y = pai[y];
	}

}

int cnt = 1;
int solve (int x, int p) {
	vector <int> curr;
	for (int i = 0; i < g[x].size(); ++i) {
		int y = g[x][i];
		if (y == p) continue;

		curr.push_back (solve (y, x));
	}

	sort (curr.begin(), curr.end());

	if (!m.count (curr))
		m[curr] = cnt++;

	return m[curr];
}

int main () {

	ios :: sync_with_stdio (false); cin.tie (0);

	while (cin >> n) {

		// Reading First Tree
		for (int i = 0; i < n; ++i) g[i].clear();
		for (int i = 1; i < n; ++i) {
			int a, b;
			cin >> a >> b;
			g[--a].push_back (--b);
			g[b].push_back (a);
		}

		getCenter();
		int ans = solve (c1, -1);


		// Reading Second Tree
		for (int i = 0; i < n; ++i) g[i].clear();
		for (int i = 1; i < n; ++i) {
			int a, b;
			cin >> a >> b;
			g[--a].push_back (--b);
			g[b].push_back (a);
		}

		getCenter();

		if (ans == solve (c1, -1) || (c2 != -1 && ans == solve (c2, -1)))
			printf ("Y\n");
		else
			printf ("N\n");
	}


	return 0;
}