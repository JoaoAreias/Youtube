from typing import List


class Solution:
    def maxProfit(self, k: int, prices: List[int]) -> int:
        n = len(prices)
        """ 
        Indices:
            0 - Não tenho uma ação
            1 - Tenho uma ação
        """
        current = [[0, 0] for _ in range(k + 1)]
        _next = [[0, 0] for _ in range(k + 1)]

        for i in range(n - 1, -1, -1):
            for j in range(1, k + 1):
                # Caso eu não tenha a ação
                current[j][0] = max(
                    _next[j][0],  # Não fazer nada
                    _next[j][1] - prices[i],  # Comprar a ação
                )
                # Caso eu tenha a ação
                current[j][1] = max(
                    _next[j][1],  # Não fazer nada
                    _next[j - 1][0] + prices[i],  # Vender a ação
                )

                _next[j][0] = current[j][0]
                _next[j][1] = current[j][1]

        return current[k][0]


def test_solution():
    s = Solution()
    assert s.maxProfit(2, [2, 4, 1]) == 2
    assert s.maxProfit(2, [3, 2, 6, 5, 0, 3]) == 7
    assert s.maxProfit(0, [1, 2, 3, 4, 5]) == 0
    assert s.maxProfit(1, [7, 6, 4, 3, 1]) == 0
    assert s.maxProfit(2, [1, 2, 4, 2, 5, 7, 2, 4, 9, 0]) == 13
