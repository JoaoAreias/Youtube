#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <tuple>
#include <vector>

#define MAX 4000

int main() {
  int t, p;
  int penalties[100][2];
  auto ties = std::vector<std::vector<std::tuple<int, int>>>(11);

  while (scanf("%d%d", &t, &p) && t != 0 && p != 0) {
    for (auto &v : ties) {
      v.clear();
    }
    for (int i = 0; i < t; i++) {
      int a = 0, b = 0, solved = 0;

      for (int j = 0; j < p; j++) {
        int tries;
        char time[10];
        scanf("%d/%s", &tries, &time);

        if (time[0] == '-')
          continue;

        solved++;
        a += tries - 1;
        b += atoi(time);
      }

      penalties[i][0] = a;
      penalties[i][1] = b;
      ties[solved].push_back(std::make_tuple(20 * a + b, i));
    }

    // Resolvendo o problema
    int lower_bound = 1, upper_bound = MAX;
    bool break_loop = false;
    for (int i = 0; i < 11 && !break_loop; i++) {
      if (ties[i].size() == 0)
        continue;

      std::sort(ties[i].begin(), ties[i].end());
      for (int j = 0; j < ties[i].size() - 1; j++) {
        int idx_1 = std::get<1>(ties[i][j]);
        int idx_2 = std::get<1>(ties[i][j + 1]);

        int a1 = penalties[idx_1][0], b1 = penalties[idx_1][1];
        int a2 = penalties[idx_2][0], b2 = penalties[idx_2][1];

        if (a1 == a2)
          continue;

        int ep = (b2 - b1) / (a1 - a2);
        if (ep > 20 || (ep == 20 && (b2 - b1) % (a1 - a2) != 0))
          upper_bound =
              std::min(upper_bound, ((b2 - b1) % (a1 - a2) == 0 ? ep - 1 : ep));
        else if (ep < 20)
          lower_bound = std::max(lower_bound, ep + 1);
        else {
          lower_bound = 20;
          upper_bound = 20;
          break_loop = true;
        }
      }
    }

    // Imprimindo a solução
    printf("%d ", lower_bound);
    if (upper_bound != MAX)
      printf("%d\n", upper_bound);
    else
      printf("*\n");
  }
  return 0;
}
