namespace FFT {

  struct ComplexType {
    double a, b;
    ComplexType() {
      a = b = 0;
    }
    ComplexType(double _a, double _b) {
      a = _a;
      b = _b;
    }
    ComplexType(double _a) {
      a = _a;
      b = 0;
    }
    ComplexType operator + (ComplexType o) { return ComplexType(a + o.a, b + o.b); }
    ComplexType operator - (ComplexType o) { return ComplexType(a - o.a, b - o.b); }
    ComplexType operator * (ComplexType o) { return ComplexType(a * o.a - b * o.b, a * o.b + b * o.a); }
    void operator *= (ComplexType o) { 
      double na = a * o.a - b * o.b;
      double nb = a * o.b + b * o.a;
      a = na;
      b = nb;
    }
    void operator /= (double x) {
      a /= x;
      b /= x;
    }
    double real() { return a; }
    double imag() { return b; }
  };
  const int M = 21;
  const int N = (1 << M);
  int pre[N][M];
  int reverse(int num, int lg_n) {
    if(pre[num][lg_n]) return pre[num][lg_n] - 1;
    int res = 0;
    for (int i = 0; i < lg_n; i++) {
      if (num & (1 << i))
        res |= 1 << (lg_n - 1 - i);
    }
    pre[num][lg_n] = res + 1;
    return res;
  }
  void fft(vector<ComplexType> & a, bool invert) {
    int n = a.size();
    int lg_n = 0;
    while ((1 << lg_n) < n) lg_n++;
    for (int i = 0; i < n; i++) {
      if (i < reverse(i, lg_n)) swap(a[i], a[reverse(i, lg_n)]);
    }
    for (int len = 2; len <= n; len <<= 1) {
      double ang = 2 * PI / len * (invert ? -1 : 1);
      ComplexType wlen(cos(ang), sin(ang));
      for (int i = 0; i < n; i += len) {
        ComplexType w(1);
        for (int j = 0; j < len / 2; j++) {
          ComplexType u = a[i+j], v = a[i+j+len/2] * w;
          a[i+j] = u + v;
          a[i+j+len/2] = u - v;
          w *= wlen;
        }
      }
    }
    if (invert) {
      for (ComplexType & x : a) x /= n;
    }
  }
  inline vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<ComplexType> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    vector<int> result(n);
    for (int i = 0; i < n; i++) {
      ll x = fa[i].real() + 0.5;
      result[i] = x;
    }
    while(result.size() && !result[result.size() - 1]) result.pop_back();
    return result;
  }
  inline vector<int> multiplyWithModulo(vector<int> const& a, vector<int> const& b, ll MOD) {
    vector<ComplexType> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);
    vector<int> result(n);
    for (int i = 0; i < n; i++) {
      ll x = fa[i].real() + 0.5;
      if(x >= MOD) x %= MOD;
      result[i] = x;
    }
    while(result.size() && !result[result.size() - 1]) result.pop_back();
    return result;
  }
};