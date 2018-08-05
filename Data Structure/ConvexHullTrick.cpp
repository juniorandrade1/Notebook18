template <typename T> 
class ConvexHullTrick { //Mantains upper_hull
private:
  const T CHINF = numeric_limits<T>::max() / (T)2.0; //Be careful here with overflow
  struct Line {
    T m, b;
    Line(){};
    Line(T _m, T _b) {
      m = _m;
      b = _b;
    }
    bool operator < (Line other) const {
      if(m != other.m) return m > other.m;
      return b > other.b;
    }
    T getVal(T x) {
      return m * x + b;
    }
  };
public:
  vector< Line > st;
  bool badLine(Line s, Line t, Line u) {
    if(t.m == u.m) return true;
    return 1.0 * (t.b - s.b) * (s.m - u.m) >= 1.0 * (u.b - s.b) * (s.m - t.m); //don't forget 1.0
  }
  void addLine(T a, T b) {
    Line l = Line(a, b);
    while(st.size() >= 2 && badLine(st[st.size() - 2], st[st.size() - 1], l)) st.pop_back();
    st.push_back(l);
  }
  T query(T x) {
    if(st.size() == 0) return CHINF;
    int lo = 0, hi = st.size() - 1;
    while(lo < hi) {
      int md = (lo + hi) >> 1;
      if(st[md].getVal(x) <= st[md + 1].getVal(x)) hi = md;
      else lo = md + 1;
    }
    return st[lo].getVal(x);
  }
};