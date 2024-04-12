#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>

#define EPS 1e-6

double weekness(double x, double values[], int limit) {
  double max = std::abs(values[0] - x);
  double running_sum_pos = values[0] - x;
  double running_sum_neg = values[0] - x;

  for (int i = 1; i < limit; i++) {
    running_sum_pos = std::max(values[i] - x, values[i] - x + running_sum_pos);
    running_sum_neg = std::min(values[i] - x, values[i] - x + running_sum_neg);
    max = std::max(std::max(running_sum_pos, -running_sum_neg), max);
  }

  return max;
}

int main() {
  int n;
  double a[200000], lb = INT_MAX, ub = INT_MIN;

  // Lê o Input
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%lf", &a[i]);
    ub = std::max(ub, a[i]);
    lb = std::min(lb, a[i]);
  }

  // Busca ternária
  double m1, m2, w1, w2, error;
  do {
    m1 = lb + (ub - lb) / 3;
    m2 = ub - (ub - lb) / 3;

    w1 = weekness(m1, a, n);
    w2 = weekness(m2, a, n);

    if (w2 > w1)
      ub = m2;
    else
      lb = m1;

    error = std::abs(w2 - w1);
  } while (error > EPS);

  double x = (m1 + m2) / 2;
  printf("%.6lf\n", weekness(x, a, n));

  return 0;
}
