int basis[d], sz; // Current size of the basis
void insertVector(int mask) {
  for (int i = 0; i < d; i++) {
    if ((mask & 1 << i) == 0)
      continue;      // continue if i != f(mask)
    if (!basis[i]) { // If there is no basis vector with the i'th bit set, then
      basis[i] = mask;
      ++sz;
      return;
    }
    mask ^= basis[i]; // Otherwise subtract the basis vector from this vector
  }
}
