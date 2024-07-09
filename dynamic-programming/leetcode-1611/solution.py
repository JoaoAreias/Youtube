from math import log2


class Solution:
    def _left_most_bit(self, n: int) -> int:
        return int(log2(n))

    def minimumOneBitOperations(self, n: int) -> int:
        if n <= 1:
            return n

        left_most_bit = self._left_most_bit(n)
        bitmask = 0b11 << (left_most_bit - 1)

        return self.minimumOneBitOperations(n ^ bitmask) + (2**left_most_bit)


def test_1():
    assert Solution().minimumOneBitOperations(0) == 0


def test_2():
    assert Solution().minimumOneBitOperations(3) == 2


def test_3():
    assert Solution().minimumOneBitOperations(6) == 4


def test_4():
    assert Solution().minimumOneBitOperations(9) == 14


def test_5():
    assert Solution().minimumOneBitOperations(16) == 31
