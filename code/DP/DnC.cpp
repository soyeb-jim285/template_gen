const ll inf = 1e15L;
const int mx = 1e5 + 5;
ll ara[mx], sum[mx];
ll dp[105][mx];
ll C(int i, int j, int k) { return 1LL * k * (sum[j] - sum[i - 1]); }
void compute(int groupNo, int l, int r, int optL, int optR) {
  if (l > r)
    return;
  int mid = (l + r) / 2;
  dp[groupNo][mid] = -inf;
  int optNow = optL;
  for (int endOfLast = optL; endOfLast <= optR && endOfLast < mid;
       endOfLast++) {
    ll ret = dp[groupNo - 1][endOfLast] + C(endOfLast + 1, mid, groupNo);
    if (ret >= dp[groupNo][mid]) {
      dp[groupNo][mid] = ret;
      optNow = endOfLast;
    }
  }
  compute(groupNo, l, mid - 1, optL, optNow);
  compute(groupNo, mid + 1, r, optNow, optR);
}
void solve() {
  for (int groupNo = 2; groupNo <= k; groupNo++) {
    compute(groupNo, 1, n, 1, n);
    for (int i = groupNo + 1; i <= n; i++)
      dp[groupNo][i] = max(dp[groupNo][i - 1], dp[groupNo][i]);
  }
  cout << dp[k][n] << "\n";
}
