/***
    * 1 based index for variables
    * F = (a op b) and (c op d) and ...... (y op z)
      a, b, c ... are the variables
      sat::satisfy() returns true if there is some assignment(True/False)
      for all the variables that make F = True
    * init() at the start of every case
***/
namespace sat {
#define CLR(ara, n) fill(ara + 1, ara + n + 1, 0)
const int MAX = 200010; /// number of variables * 2
bool vis[MAX];
vector<int> ed[MAX], rev[MAX];
int n, m, ptr, dfs_t[MAX], ord[MAX], par[MAX];
inline int inv(int x) { return ((x) <= n ? (x + n) : (x - n)); }
/// Call init once
void init(int vars) {
  n = vars, m = vars << 1;
  for (int i = 1; i <= m; i++) {
    ed[i].clear();
    rev[i].clear();
  }
}
/// Adding implication, if a then b ( a --> b )
inline void add(int a, int b) {
  ed[a].push_back(b);
  rev[b].push_back(a);
}
inline void OR(int a, int b) {
  add(inv(a), b);
  add(inv(b), a);
}
inline void AND(int a, int b) {
  add(a, b);
  add(b, a);
}
void XOR(int a, int b) {
  add(inv(b), a);
  add(a, inv(b));
  add(inv(a), b);
  add(b, inv(a));
}
inline void XNOR(int a, int b) {
  add(a, b);
  add(b, a);
  add(inv(a), inv(b));
  add(inv(b), inv(a));
}
/// (x <= n) means forcing variable x to be true
/// (x = n + y) means forcing variable y to be false
inline void force_true(int x) { add(inv(x), x); }
inline void topsort(int s) {
  vis[s] = true;
  for (int x : rev[s])
    if (!vis[x])
      topsort(x);
  dfs_t[s] = ++ptr;
}
inline void dfs(int s, int p) {
  par[s] = p;
  vis[s] = true;
  for (int x : ed[s])
    if (!vis[x])
      dfs(x, p);
}
void build() {
  CLR(vis, m);
  ptr = 0;
  for (int i = m; i >= 1; i--) {
    if (!vis[i])
      topsort(i);
    ord[dfs_t[i]] = i;
  }
  CLR(vis, m);
  for (int i = m; i >= 1; i--) {
    int x = ord[i];
    if (!vis[x])
      dfs(x, x);
  }
}
/// Returns true if the system is 2-satisfiable and returns the solution (vars
/// set to true) in vector res
bool satisfy(vector<int> &res) {
  build();
  CLR(vis, m);

  for (int i = 1; i <= m; i++) {
    int x = ord[i];
    if (par[x] == par[inv(x)])
      return false;
    if (!vis[par[x]]) {
      vis[par[x]] = true;
      vis[par[inv(x)]] = false;
    }
  }
  res.clear();
  for (int i = 1; i <= n; i++) {
    if (vis[par[i]])
      res.push_back(i);
  }
  return true;
}
#undef CLR
