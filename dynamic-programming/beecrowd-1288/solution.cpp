#include <cstdio>
#define max(x, y) ((x) > (y) ? (x) : (y))
#define size 101
using namespace std;

int knapsack(int W, int wt[], int val[], int n) {
  int M[size][size];
  for (int i = 0; i <= n; i++) {
    for (int w = 0; w <= W; w++) {
      if (i == 0 || w == 0)
        M[i][w] = 0;
      else if (wt[i - 1] <= w)
        M[i][w] = max(val[i - 1] + M[i - 1][w - wt[i - 1]], M[i - 1][w]);
      else
        M[i][w] = M[i - 1][w];
    }
  }
  return M[n][W];
}

int main() {
  int T, n, val[100], wt[100], k, r;
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%d %d", &val[i], &wt[i]);
    scanf("%d", &k);
    scanf("%d", &r);
    printf("%s\n",
           (knapsack(k, wt, val, n) < r ? "Falha na missao"
                                        : "Missao completada com sucesso"));
  }

  return 0;
}
