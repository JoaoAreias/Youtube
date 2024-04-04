from sys import stdin
from math import dist

class UnionFind:
    def __init__(self, n: int) -> None:
        self.rank = [0] * n
        self.parent = [i for i in range(n)]

    def find(self, n: int) -> int:
        # Comprime o caminho para o elemento pai
        if n != self.parent[n]:
            self.parent[n] = self.find(self.parent[n])
        return self.parent[n]

    def union(self, a: int, b: int) -> None:
        root_a = self.find(a)
        root_b = self.find(b)

        if self.rank[root_a] > self.rank[root_b]:
            self.parent[root_b] = root_a

        elif self.rank[root_b] > self.rank[root_a]:
            self.parent[root_a] = root_b

        else:
            self.parent[root_b] = root_a
            self.rank[root_a] += 1

    def connected(self, a: int, b: int) -> bool:
        return self.find(a) == self.find(b)



def main():
    m, n, k = map(int, stdin.readline().split())
    # Nós 0, 1, 2, e 3 são reservados respectivamente para o topo, a direita
    # em baixo, e a esquerda.
    union_find = UnionFind(k + 4)

    sensors = [None] * k
    for i, line in enumerate(stdin.readlines()):
        x, y, s = map(int, line.split())
        sensors[i] = (x, y, s) # type: ignore

        # Sensor enxerga a parede do topo
        if y + s >= n:
            union_find.union(0, i + 4)
        # Sensor encerga a parede da direita
        if x + s >= m:
            union_find.union(1, i + 4)
        # Sensor enxerga a parede de baixo
        if y - s <= 0:
            union_find.union(2, i + 4)
        # Sensor enxerga a parede da esquerda
        if x - s <= 0:
            union_find.union(3, i + 4)


    for i, (x1, y1, s1) in enumerate(sensors): # type: ignore
        for j, (x2, y2, s2) in enumerate(sensors[i+1:]): # type: ignore
            if dist((x1, y1), (x2, y2)) <= s1 + s2:
                idx_i = i + 4
                idx_j = i + j + 5

                union_find.union(idx_i, idx_j)


    if union_find.connected(0, 1) or union_find.connected(0, 2) or \
       union_find.connected(3, 1) or union_find.connected(3, 2):
        print("N")
    else:
        print("S")
 


if __name__ == "__main__":
    main()
