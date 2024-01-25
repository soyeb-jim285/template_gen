const ll is_query = -(1LL << 62);
const ll inf = 1e18L;
struct Line {
  ll m, b;
  mutable function<const Line *()> succ;
  bool operator<(const Line &rhs) const {
    if (rhs.b != is_query)
      return m < rhs.m;
    const Line *s = succ();
    if (!s)
      return 0;
    int x = rhs.m;
    return b - s->b < (s->m - m) * x;
  }
};
/* will maintain upper hull for maximum
 * for minimum insert line as (-m,-b) !!
 * then the ans would be -ans
 */
struct HullDynamic : public multiset<Line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end())
        return 0;
      return y->m == z->m && y->b <= z->b;
    }

    auto x = prev(y);
    if (z == end())
      return y->m == x->m && y->b <= x->b;
    __int128 left = __int128(x->b - y->b) * (z->m - y->m);
    __int128 right = __int128(y->b - z->b) * (y->m - x->m);
    return left >= right;
  }
  void insert_line(ll m, ll b) {
    auto y = insert({m, b});
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) {
      erase(y);
      return;
    }
    while (next(y) != end() && bad(next(y)))
      erase(next(y));
    while (y != begin() && bad(prev(y)))
      erase(prev(y));
  }
  ll query(ll x) {
    auto l = *lower_bound((Line){x, is_query});
    return l.m * x + l.b;
  }
};
