/* Li Chao Tree for maximum query, represents line as mx+b
 * for minimum query initialize line with (0,inf)
 * change the sign of update and query function too( > to <, max to min)
 * for update call update(1,n,1,{m,b})
 * for query at point x call query(1,n,1,x)
 * This tree works for almost any functions
 * just change the parameters of the Line
 */
const ll inf = 1LL << 62;
const int mx = 1e6 + 5;
struct Line {
  ll m, b;
  Line(ll _m = 0, ll _b = -inf) {
    m = _m;
    b = _b;
  }
};
ll f(Line line, int x) { return line.m * x + line.b; }
Line Tree[4 * mx];
void update(int l, int r, int at, Line line) {
  int mid = (l + r) / 2;
  bool left = f(line, l) > f(Tree[at], l);
  bool middle = f(line, mid) > f(Tree[at], mid);
  if (middle)
    swap(Tree[at], line);
  if (l == r)
    return;
  if (left != middle)
    update(l, mid, at * 2, line);
  else
    update(mid + 1, r, at * 2 + 1, line);
}
ll query(int l, int r, int at, int x) {
  ll val = f(Tree[at], x);
  if (l == r)
    return val;
  int mid = (l + r) / 2;
  if (x <= mid)
    return max(val, query(l, mid, at * 2, x));
  return max(val, query(mid + 1, r, at * 2 + 1, x));
}
