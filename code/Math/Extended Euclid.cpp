PLL extEuclid(ll a, ll b) {
  ll s = 1, t = 0, st = 0, tt = 1;
  while (b) {
    s = s - (a / b) * st;
    swap(s, st);
    t = t - (a / b) * tt;
    swap(t, tt);
    a = a % b;
    swap(a, b);
  }
  return mp(s, t);
}
/// returns number of solutions for the equation ax + by = c
/// where minx <= x <= maxx and miny <= y <= maxy
ll numberOfSolutions(ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy) {
  if (a == 0 && b == 0) {
    if (c != 0)
      return 0;
    else
      return (maxx - minx + 1) *
             (maxy - miny +
              1); /// all possible (x,y) within the ranges can be a solution
  }
  ll gcd = __gcd(a, b);
  if (c % gcd != 0)
    return 0; /// no solution , gcd(a,b) doesn't divide c
  /// If b==0, x will be fixed, any y in the range can form a pair with that x
  if (b == 0) {
    c /= a;
    if (c >= minx && c <= maxx)
      return maxy - miny + 1;
    else
      return 0;
  }
  /// If a==0, x will be fixed, any x in the range can form a pair with that y
  if (a == 0) {
    c /= b;
    if (c >= miny && c <= maxy)
      return maxx - minx + 1;
    else
      return 0;
  }
  /// gives a particular solution to the equation ax + by = gcd(a,b) {gcd(a,b)
  /// can be negative also}
  PLL sol = extEuclid(a, b);
  a /= gcd;
  b /= gcd;
  c /= gcd;
  ll x, y;
  x = sol.xx * c;
  y = sol.yy * c;
  ll lx, ly, rx, ry;
  if (x < minx)
    lx = ceil((minx - x) / (double)abs(b));
  else
    lx = -floor((x - minx) / (double)abs(b));
  if (x < maxx)
    rx = floor((maxx - x) / (double)abs(b));
  else
    rx = -ceil((x - maxx) / (double)abs(b));
  /// Doing this I because I ignored sign of b before passing to
  /// getCeil/getFloor
  if (b < 0) {
    lx *= -1;
    rx *= -1;
    swap(lx, rx);
  }
  if (lx > rx)
    return 0;
  /// ly -> minimum value of k such that sol.yy - k * (a/g) is in
  /// range[miny,maxy] ry -> maximum value of k such that sol.yy - k * (a/g) is
  /// in range[miny,maxy]
  if (y < miny)
    ly = ceil((miny - y) / (double)abs(a));
  else
    ly = -floor((y - miny) / (double)abs(a));
  if (y < maxy)
    ry = floor((maxy - y) / (double)abs(a));
  else
    ry = -ceil((y - maxy) / (double)abs(a));
  /// Doing this because I ignored sign of a before passing to getCeil/getFloor
  if (a < 0) {
    ly *= -1;
    ry *= -1;
    swap(ly, ry);
  }
  if (ly > ry)
    return 0;
  ly *= -1;
  ry *= -1;
  swap(ly, ry);
  /// getting the intersection between (x range) and (y range) of k
  ll li = max(lx, ly);
  ll ri = min(rx, ry);
  return max(ri - li + 1, 0LL);
}
