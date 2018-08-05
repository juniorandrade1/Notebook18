#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef pair< ll, ll > ii;
typedef vector< ll > vi;
typedef vector< ii > vii;

#define INF 0x3F3F3F3F
#define LINF 0x3F3F3F3F3F3F3F3FLL
#define pb push_back
#define mp make_pair
#define pq priority_queue
#define LSONE(s) ((s)&(-s))
#define DEG_to_RAD(X)   (X * PI / 180)
#define F first
#define S second

#ifdef ONLINE_JUDGE
#define debug(args...)
#else
#define debug(args...) fprintf(stderr,args)
#endif

#define eps 1e-9

#define pi acos(-1.0)

const int N = 100010;

int cmpDouble(double x, double y) {
  if(fabs(x - y) < eps) return 0;
  if(x < y) return -1;
  return 1;
}

struct Point {
  ld x, y;
  Point(){};
  Point(ld _x, ld _y) {
    x = _x;
    y = _y;
  }
  void read(){ 
    double _x, _y;
    scanf("%lf %lf", &_x, &_y);
    x = _x;
    y = _y;
  }
  ld operator % (Point other) { return x * other.y - other.x * y; }
  ld operator * (Point other) { return x * other.x + y * other.y; }
  Point operator * (double t) { return Point(x * t, y * t); }
  Point operator - (Point other) { return Point(x - other.x, y - other.y); }
  Point operator + (Point other) { return Point(x + other.x, y + other.y); }
  ld norm() { return sqrt(x * x + y * y); }
  ld distToPoint(Point other) {
    return hypot(other.y - y, other.x - x);
  }
};

struct Line {
  Point a;
  Point ab;
  Line(){
    a = Point(0, 0);
    ab = Point(1, 0);
  };
  Line(Point _a, Point _b) {
    a = Point(_a);
    ab = Point(_b.x - _a.x, _b.y - _a.y);
  }
  Line(double _a, double _b, double _c) {
    if(fabs(_a) < eps) _a = eps;
    if(fabs(_b) < eps) _b = eps;
    double x0 = rand() % 1000000000 + 1;
    double y1 = rand() % 1000000000 + 1;
    Point s, t;
    s = Point(x0, (-_c - _a * x0) / _b);
    t = Point((-_c - _b * y1) / _a, y1);
    a = Point(s);
    ab = t - s;
  }
  double distToPoint(Point p) {
    return fabs((p - a) % ab) / ab.norm();
  }
  bool areParallel(Line l) { return cmpDouble(ab % l.ab, 0) == 0; }
  Point intersectionPoint(Line l) {
    // A + iAB
    double i = ((l.ab - a) % l.ab) / (ab % l.ab);
    return a + ab * i;
  }
};

struct Segment {
  Point s, t;
  Line l;
  Segment(){};
  Segment(Point _s, Point _t) {
    s = _s;
    t = _t;
    l = Line(s, t);
  }
  ld distToPoint(Point p) {
    int o1 = cmpDouble((t - s) * (t - p), 0);
    int o2 = cmpDouble((s - t) * (s - p), 0);
    if(o1 * o2 >= 0) return l.distToPoint(p);
    return min(s.distToPoint(p), t.distToPoint(p));
  }
  ld distToSegment(Segment other) {
    int ds = cmpDouble((t - s) % (other.s - s), 0);
    int dt = cmpDouble((t - s) % (other.t - s), 0);
    int os1 = cmpDouble((t - s) * (t - other.s), 0);
    int os2 = cmpDouble((s - t) * (s - other.s), 0);
    int ot1 = cmpDouble((t - s) * (t - other.t), 0);
    int ot2 = cmpDouble((s - t) * (s - other.t), 0);
    if(os1 * os2 >= 0 && ot1 * ot2 >= 0 && ds * dt <= 0) return 0.0; //Segment intersect
    return min(min(other.distToPoint(s), other.distToPoint(t)), min(distToPoint(other.s), distToPoint(other.t)));
  }
};

int main() {
  srand(time(NULL));

  return 0;
}