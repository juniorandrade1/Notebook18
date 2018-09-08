// Mo's Algorithm
// Time Complexity: O(n * sqrt(n))

int bsize;	// Bucket size

struct query {
	int l, r, t;
	query() {}
	query(int _l, int _r, int _t) {
		l = _l; r = _r; t = _t;
	}

	bool operator< (const query nd) const {
		if (l / bsize != nd.l / bsize) return l / bsize < nd.l / bsize;
		else return r < nd.r;
	}
};

const int MAXN = 212345;

pair<int, int> ans[MAXN];	// First: Frequency of most common element
							// Second: Most common element

int freq[MAXN];
int v[MAXN];				// Original array
vector<query> q;

void mo() {
	bsize = sqrt(n);

	for (int i = 0; i < m; ++i) {
		int l, r;
		scanf("%d %d", &l, &r);

		// Brute Force if L and R are at the same bucket
		if (l / bsize == r / bsize) {
			int maxi = 0; int elem = -1;
			for (int j = l; j <= r; ++j) {
				freq[v[j]]++;
				if (freq[v[j]] > maxi) { maxi = freq[v[j]]; elem = v[j];}
			}

			ans[i].first = maxi;
			ans[i].second = elem;

			// Reset frequency array
			for (int j = l; j <= r; ++j) freq[v[j]]--;

		} else {
			q.push_back(query(l, r, i));
		}
	}

	sort(q.begin(), q.end());

	int bucket = -1;		// Current bucket
	int endPos = -1;		// Final position of current bucket
	int R = 0;				// Right Pointer
	int maxfreq, maxelem;	// Highest frequency element

	for (int i = 0; i < q.size(); ++i) {
		// If L bucket changed
		if (q[i].l / bsize != bucket) {
			bucket = q[i].l / bsize;
			memset(freq, 0, sizeof freq);
			R = (bucket + 1) * bsize - 1;
			endPos = R;
			maxfreq = 0; maxelem = -1;
		}

		int l = q[i].l; int r = q[i].r;

		while (R < r) {
			++R;
			freq[v[R]]++;
			if (freq[v[R]] > maxfreq) {maxfreq = freq[v[R]]; maxelem = v[R];}
		}

		int maxi = maxfreq; int elem = maxelem;

		for (int j = l; j <= endPos; ++j) {
			freq[v[j]]++;
			if (freq[v[j]] > maxi) {maxi = freq[v[j]]; elem = v[j];}
		}

		ans[q[i].t].first = maxi;
		ans[q[i].t].second = elem;

		for (int j = l; j <= endPos; ++j) freq[v[j]]--;

	}

	return;
}