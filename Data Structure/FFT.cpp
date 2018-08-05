#define PI acos(-1.0)

struct Complex {
  double a, b; // a + bi
  Complex(){
    a = 0.0;
    b = 0.0;
  };
  Complex(double _a, double _b) {
    a = _a;
    b = _b;
  }
  Complex operator+(const Complex &o)const {
    return Complex(o.a + a, b + o.b);
  }

  Complex operator/(double v) const {
    return Complex(a / v, b / v);
  }
  Complex operator*(const Complex &o)const {
    return Complex(a * o.a - b * o.b, a * o.b + b * o.a);
  }

  Complex operator-(const Complex &o) const {
    return Complex(a - o.a, b - o.b);
  }
};

int rev[N];
Complex wlen_pw[N];
 
void fft (Complex a[], int n, bool invert) {
  for (int i = 0; i < n; ++i) if (i < rev[i]) swap (a[i], a[rev[i]]);
  for (int len = 2; len <= n; len <<= 1) {
    double ang = 2 * PI / len * (invert ? -1 : +1);
    int len2 = len >> 1;
    Complex wlen (cos(ang), sin(ang));
    wlen_pw[0] = Complex(1, 0);
    for (int i = 1; i < len2; ++i) wlen_pw[i] = wlen_pw[i - 1] * wlen;
    for (int i=0; i<n; i+=len) {
      Complex t, *pu = a+i, *pv = a+i+len2,  *pu_end = a+i+len2, *pw = wlen_pw;
      for (; pu!=pu_end; ++pu, ++pv, ++pw) {
        t = *pv * *pw;
        *pv = *pu - t;
        *pu = *pu + t;
      }
    }
  }
  if (invert) for (int i=0; i<n; ++i) a[i] = a[i] / n;
}
 
void calc_rev (int n, int log_n) {
  for (int i = 0; i < n; ++i) {
    rev[i] = 0;
    for (int j = 0; j < log_n; ++j)
      if (i & (1 << j)) rev[i] |= 1 << (log_n - 1 - j);
  }
}
