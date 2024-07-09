#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

class Solution {
public:
  int maxProfit(int k, vector<int> &prices) {
    int n = prices.size();
    int current[101][2];
    int next[101][2];

    // Caso onde posso fazer quantas transações quiser
    if (k >= n / 2) {
      int profit = 0;
      for (int i = 1; i < n; i++) {
        if (prices[i] > prices[i - 1]) {
          profit += prices[i] - prices[i - 1];
        }
      }
      return profit;
    }
    // Inicialização da matriz
    memset(current, 0, sizeof(current));
    memset(next, 0, sizeof(next));

    // Programação dinâmica
    for (int i = n - 1; i >= 0; i--) {
      for (int j = 1; j <= k; j++) {
        // Caso onde não tenho ações
        current[j][0] = max(next[j][0],            // Não fazer nada
                            next[j][1] - prices[i] // Comprar a ação
        );
        // Caso eu tenha ações
        current[j][1] = max(next[j][1],                // Não fazer nada
                            next[j - 1][0] + prices[i] // Vender a ação
        );

        next[j][0] = current[j][0];
        next[j][1] = current[j][1];
      }
    }
    return current[k][0];
  }
};

int main(int argc, char *argv[]) {
  // Teste sua solução com novos casos de teste
  Solution solution;

  vector<int> prices = {2, 4, 1};
  printf("%d\n", solution.maxProfit(2, prices));

  prices = {3, 2, 6, 5, 0, 3};
  printf("%d\n", solution.maxProfit(2, prices));

  prices = {3, 3, 5, 0, 0, 3, 1, 4};
  printf("%d\n", solution.maxProfit(2, prices));

  prices = {3, 3, 5, 0, 0, 3, 1, 4};
  printf("%d\n", solution.maxProfit(2, prices));

  return 0;
}
