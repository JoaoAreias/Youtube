class Solution {
public:
  int minimumOneBitOperations(int n) {
    if (n <= 1) {
      return n;
    }

    int l = 31 - __builtin_clz(n);
    int mask = 0b11 << (l - 1);
    return (1 << l) + minimumOneBitOperations(n ^ mask);
  }
};
