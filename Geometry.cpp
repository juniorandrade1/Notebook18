#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;

#define EPS 1e-8

inline int cmp(double a, double b = 0) {
  return (a < b + EPS) ? (a + EPS < b) ? -1 : 0 : 1;
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
  bool operator == (Point other) const { return !cmp(x, other.x) && !cmp(y, other.y); }
  ld operator % (Point other) const { return x * other.y - other.x * y; }
  ld operator * (Point other) const { return x * other.x + y * other.y; }
  Point operator / (ld t) const { return Point(x / t, y / t); }
  Point operator * (ld t) const { return Point(x * t, y * t); }
  Point operator - (Point other) const { return Point(x - other.x, y - other.y); }
  Point operator + (Point other) const { return Point(x + other.x, y + other.y); }
  ld norm() const { return sqrt(x * x + y * y); }
  ld distToPoint(Point other) const { return hypot(other.y - y, other.x - x); }
  bool operator < (Point other) const {
    if(int t = cmp(x, other.x)) return t < 0;
    return cmp(y, other.y) < 0;
  }
};

typedef Point Vector;
typedef vector<Point> Poly;

struct Line {
  Point a, ab;
  Line(){};
  Line(Point _a, Point _ab) {
    a = _a;
    ab = _ab;
  } 
  ld distToPoint(Point p) {
    return fabs((p - a) % ab) / ab.norm();
  }
  bool areParallel(Line l) { return !cmp(ab % l.ab, 0); }
  //From Ai-Cash blog
  Point intersectionPoint(Line l) {
    // A + iAB
    double i = ((l.ab - a) % l.ab) / (ab % l.ab);
    return a + ab * i;
  }
};

struct Segment {
  Point a, b;
  Line l;
  Segment(){};
  Segment(Point _a, Point _b) {
    a = _a;
    b = _b;
    l = Line(a, b - a);
  }
};

bool existSegmentIntersection(const Segment &sa, const Segment &sb) {
  Point p = sa.a, q = sa.b, r = sb.a, s = sb.b;
  Point A = q - p, B = s - r, C = r - p, D = s - q;
  int a = cmp(A % C) + 2 * cmp(A % D);
  int b = cmp(B % C) + 2 * cmp(B % D);
  if (a == 3 || a == -3 || b == 3 || b == -3) return false;
  if (a || b || p == r || p == s || q == r || q == s) return true;
  int t = (p < r) + (p < s) + (q < r) + (q < s);
  return t != 0 && t != 4;
}

Point segmentIntersection(const Segment &sa, const Segment &sb) {
  Point p = sa.a, q = sa.b, r = sb.a, s = sb.b;
  Point a = q - p, b = s - r, c = Point(p % q, r % s);
  assert(cmp(a % b));
  return Point(Point(a.x, b.x) % c, Point(a.y, b.y) % c) / (a % b);
}

void getLineEquation(Line l) {
  Point p = l.a;
  Point q = l.ab;
  double a = p.y - q.y;
  double b = q.x - p.y;
  double c = (p % q);
}

int main() {
  return 0;
}