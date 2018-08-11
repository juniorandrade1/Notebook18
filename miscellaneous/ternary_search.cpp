// Ternary Search on Real Numbers
long double ternary_real (long double l, long double r) {

	for (int i = 0; i < LOG; ++i) {
		long double m1 = (l * 2 + r) / 3.0;
		long double m2 = (l + r * 2) / 3.0;
		
		if (f (m1) > f (m2))
			l = m1;
		else
			r = m2;
	}

	return f (l);
}


// Ternary Search on Integers
long double ternary_integer (int l, int r) {
	while (r - l > 4) {
		int m1 = (l + r) / 2;
		int m2 = (l + r) / 2 + 1;

		if (f (m1) > f (m2))
			l = m1;
		else
			r = m2;
	}

	int ans = INF;

	for (int i = l; i <= r; ++i)
		ans = min (ans, f (i));

	return ans;
}