const double eps = 1e-9;
template <class T> struct Point {
  typedef Point P;
  T x, y;
  Point(T _x = 0, T _y = 0) {
    x = _x;
    y = _y;
  }
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  P operator*(T d) const { return P(x * d, y * d); }
  P operator/(T d) const { return P(x / d, y / d); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  T cross(P a, P b) const { return (a - *this).cross(b - *this); }
  T dist2() const { return x * x + y * y; }
  double dist() const { return sqrt(double(dist2())); }
  double angle() const { return atan2(y, x); }
  P unit() const { return *this / dist(); }
  P perp() const { return P(-y, x); }
  P normal() const { return perp().unit(); }
  P rotate(double a) const {
    return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
};
template <class P>
int lineIntersection(const P &s1, const P &e1, const P &s2, const P &e2, P &r) {
  if ((e1 - s1).cross(e2 - s2)) // if not parallel
  {
    r = s2 - (e2 - s2) * (e1 - s1).cross(s2 - s1) / (e1 - s1).cross(e2 - s2);
    return 1;
  }
  return -((e1 - s1).cross(s2 - s1) == 0 || s2 == e2);
}
typedef Point<ld> P;
struct Line {
  P P1, P2;
  // right hand side of the ray P1 --> P2
  Line(P a = P(), P b = P()) {
    P1 = a;
    P2 = b;
  }
  P intpo(Line y) {
    P r;
    assert(lineIntersection(P1, P2, y.P1, y.P2, r) == 1);
    return r;
  }
  P dir() { return P2 - P1; }
  bool contains(P x) { return (P2 - P1).cross(x - P1) < eps; }
  bool out(P x) { return !contains(x); }
};
template <class T> bool mycmp(Point<T> a, Point<T> b) {
  if (a.x * b.x < 0)
    return a.x < 0;
  if (abs(a.x) < eps) {
    if (abs(b.x) < eps)
      return a.y > 0 && b.y < 0;
    if (b.x < 0)
      return a.y > 0;
    if (b.x > 0)
      return true;
  }
  if (abs(b.x) < eps) {
    if (a.x < 0)
      return b.y < 0;
    if (a.x > 0)
      return false;
  }
  return a.cross(b) > 0;
}
bool cmp(Line a, Line b) { return mycmp(a.dir(), b.dir()); }
ld Intersection_Area(vector<Line> b) {
  sort(b.begin(), b.end(), cmp);
  int n = b.size();
  int q = 1, h = 0;
  vector<Line> c(b.size() + 10);
  for (int i = 0; i < n; i++) {
    while (q < h && b[i].out(c[h].intpo(c[h - 1])))
      h--;
    while (q < h && b[i].out(c[q].intpo(c[q + 1])))
      q++;
    c[++h] = b[i];
    if (q < h && abs(c[h].dir().cross(c[h - 1].dir())) < eps) {
      h--;
      if (b[i].out(c[h].P1))
        c[h] = b[i];
    }
  }
  while (q < h - 1 && c[q].out(c[h].intpo(c[h - 1])))
    h--;
  while (q < h - 1 && c[h].out(c[q].intpo(c[q + 1])))
    q++;
  if (h - q <= 1)
    return 0;
  c[h + 1] = c[q];
  vector<P> s;
  for (int i = q; i <= h; i++)
    s.push_back(c[i].intpo(c[i + 1]));
  s.push_back(s[0]);
  ld ans = 0;
  for (int i = 0; i < int(s.size()) - 1; i++)
    ans += s[i].cross(s[i + 1]);
  ans /= 2.0;
  return ans;
}
void solve() {
  int n;
  cin >> n;
  vector<P> vec(n);
  for (int i = 0; i < n; i++) {
    ld x, y;
    cin >> x >> y;
    vec[i] = P(x, y);
  }
  vector<Line> halfplanes;
  for (int i = 0; i < n; i++) {
    int j = (i + 1) % n;
    halfplanes.push_back(Line(vec[i], vec[j]));
  }
  ld ans = Intersection_Area(halfplanes);
  cout << fixed << setprecision(10) << ans << "\n";
}
