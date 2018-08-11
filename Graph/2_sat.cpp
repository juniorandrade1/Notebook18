// 2-Sat
// Time Complexity: O (N + M)

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 112;

int n, m;
vector <int> g[2 * MAXN];
bool vis[2 * MAXN];

stack <int> s;
int ptr = 0;
int comp[2 * MAXN];
int ans[2 * MAXN];

void addEdge ( int x, int y ) {
	g[x].push_back (y);
	g[y].push_back (x);
}

void dfs1 ( int x ) {
	if ( vis[x] ) return;
	vis[x] = true;
	for (int i = 0; i < g[x].size(); ++i) { dfs1 ( g[x][i] ); }
	s.push ( x );
}

void dfs2 ( int x ) {
	if ( vis[x] ) return;
	vis[x] = 1;
	for (int i = 0; i < g[x].size(); ++i) { dfs2 ( g[x][i] ); }
	comp[x] = ptr;
}

bool twosat () {
	for (int i = 0; i < 2 * n; ++i)
		if ( !vis[i] ) dfs1 ( i );

	memset (vis, 0, sizeof vis);

	while (!s.empty()) {
		int x = s.top();
		s.pop();

		if ( !vis[x] ) {
			dfs2 ( x );
			ptr++;
		}

		ans[x >> 1] = (x & 1);
	}

	for (int i = 0; i < 2 * n; i += 2)
		if ( comp[i] == comp[i + 1] ) return false;

	return true;
}

int main () {
	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		int x, y, c;
		scanf ("%d %d %d", &x, &y, &c);

		--x; --y; x <<= 1; y <<= 1;

		if (c) {
			addEdge ( x, y );
			addEdge ( x ^ 1, y ^ 1 );
		} else {
			addEdge ( x ^ 1, y );
			addEdge ( x, y ^ 1 );
		}
	}

	if ( !twosat() ) cout << "Impossible" << endl;
	else {
		vector <int> sol;
		for (int i = 0; i < n; ++i)
			if ( !ans[i] ) sol.push_back ( i + 1 );

		cout << sol.size() << endl;

		for (int i = 0; i < sol.size(); ++i)
			printf ("%d%c", sol[i], (i + 1 == sol.size()) ? '\n' : ' ');
	}

	return 0;
}