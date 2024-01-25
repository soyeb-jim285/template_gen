void solve() {
  int n;
  cin >> n;
  vector<pair<pii, int>> vec(n);
  for (int i = 0; i < n; i++) {
    cin >> vec[i].first.first >> vec[i].first.second;
    vec[i].second = i;
  }
  sort(vec.begin(), vec.end());
  ll ans = 1e18L;
  int a = -1, b = -1;
  set<pair<pii, int>> st;
  for (int i = 0, j = 0; i < n; i++) {
    int d = ceil(sqrt(ans));
    while (j < i && vec[j].first.first + d < vec[j].first.first) {
      st.erase({{vec[j].first.second, vec[j].first.first}, vec[j].second});
      j++;
    }
    auto it1 =
        st.lower_bound({{vec[i].first.second - d, vec[i].first.first}, -1});
    auto it2 =
        st.lower_bound({{vec[i].first.second + d, vec[i].first.first}, -1});
    for (auto it = it1; it != it2; it++) {
      int dx = vec[i].first.first - it->first.second;
      int dy = vec[i].first.second - it->first.first;
      ll curr = 1LL * dx * dx + 1LL * dy * dy;
      if (curr < ans) {
        ans = curr;
        a = vec[i].second;
        b = it->second;
      }
    }
    st.insert({{vec[i].first.second, vec[i].first.first}, vec[i].second});
  }
  if (a > b)
    swap(a, b);
  cout << a << " " << b << " ";
  cout << fixed << setprecision(6) << sqrt(ans) << "\n";
}
