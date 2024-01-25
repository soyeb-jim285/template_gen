#include <bits/stdc++.h>
using namespace std;
long long h[400005];
long long MOD[400005];
int L;
void pre_hash(string s) {
  long long p = 31;
  long long m = 1e9 + 9;
  long long power = 1;
  long long hash = 0;
  int z = 0;
  for (int i = s.size() - 1; i >= 0; i--) {
    hash = (hash * p + (s[i] - 'A' + 1)) % m;
    h[i] = hash;
    MOD[z] = power;
    z++;
    power = (power * p) % m;
  }
}
long long f(int l, int r) {
  long long val = h[r], m = 1e9 + 9;
  if (l != L - 1) {
    long long val2 = (h[l + 1] % m * MOD[l - r + 1] % m) % m;
    val -= val2;
    val += m;
    val %= m;
  }
  if (val < 0)
    val = (val + m) % m;
  return val;
}
int main() {
  string s;
  cin >> s;
  L = s.size();
  pre_hash(s);
  int q;
  cin >> q;
  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << f(l, r) << endl;
  }
  return 0;
}
