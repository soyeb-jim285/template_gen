#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const int RANDOM =
    chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
  int operator()(int x) const { return x ^ RANDOM; }
};
gp_hash_table<int, int, chash> table;
struct chash {
  int operator()(pii x) const { return x.first * 31 + x.second; }
};
gp_hash_table<pii, int, chash> table; // for pairs
