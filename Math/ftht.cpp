const ll N = (ll)1e5 + 10;
const ll K = (1 << 16);

//Compute XOR of two polynomials A xor B = C
vector< ll > FWHT(vector< ll > P, bool inverse) {
  int n = P.size();
  for (int len = 1; 2 * len <= n; len <<= 1) {
    for (int i = 0; i < n; i += 2 * len) {
      for (int j = 0; j < len; j++) {
        ll u = P[i + j];
        ll v = P[i + len + j];
        P[i + j] = u + v;
        P[i + len + j] = u - v;
      }
    }
  }
  if(inverse) {
    for(int i = 0; i < n; i++) P[i] = P[i] / n;
  }
  return P;
}