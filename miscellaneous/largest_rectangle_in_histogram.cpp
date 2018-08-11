// O (log n)

long long largest_rectangle (vector <long long> v) {
	v.push_back (0);
	int n = v.size();

	stack <long long> s;
	long long ans = 0;

	for (long long i = 0; i < n; ++i) {
		while (!s.empty() && v[s.top()] > v[i]) {
			int x = s.top();
			s.pop();
			if (s.empty())
				ans = max (ans, v[x] * i);
			else
				ans = max (ans, v[x] * (i - s.top() - 1));
		}

		s.push (i);
	}

	return ans;
}