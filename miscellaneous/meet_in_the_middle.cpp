// Meet in the Middle - Finding Cliques
// Time Complexity: O ( N * 2 ^ ( N / 2 ) )
// Memo Complexity: O ( N * 2 ^ ( N / 2 ) )

const int MAXN = 40;

int n, k, m;

long long g[MAXN];
int memo[1 << 20];

int solve (int msk) {
	int & p = memo[msk];
	if (p + 1) return p;

	int temp = msk;
	for (int i = 0; i < m; ++i)
		if (msk & (1 << i))
			temp &= (g[i + k] >> k);

	if (temp == msk) return p = __builtin_popcount(msk);

	for (int i = 0; i < m; ++i)
		if (msk & (1 << i))
			p = max (p, solve (msk ^ (1 << i)));

	return p;
}

int main () {

	memset (memo, -1, sizeof memo);

	cin >> n;

	// Reading Adjecency Matrix Graph
	for (long long i = 0; i < n; ++i) {
		g[i] = 1LL << i;
		for (long long j = 0; j < n; ++j) {
			long long tt;
			scanf ("%lld", &tt);
			g[i] |= tt << j;
		}
	}

	k = n >> 1;
	m = n - k;

	int ans = solve ( ( 1 << m ) - 1 );
	long long init = ~( ( 1LL << k ) - 1 );

	for (long long i = 1; i < ( 1LL << k ); ++i) {
		long long msk = init | i;
		
		for (int j = 0; j < k; ++j) {
			if (i & (1LL << j))
				msk &= g[j];
		}

		if (__builtin_popcountll ( i ) != __builtin_popcountll ( msk & ( ~init ) )) continue;
		ans = max (ans, __builtin_popcountll ( i ) + solve ( msk >> k ));
	}

	cout << ans << endl;

	return 0;
}

