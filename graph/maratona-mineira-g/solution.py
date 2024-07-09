from collections import deque
from sys import stdin


def main():
    # Lê a quantidade de vértices, arestas e custo máximo
    n, _, k = map(int, stdin.readline().split())

    # Cria um grafo com n vértices
    graph = [[] for _ in range(n)]

    # Lê as arestas e seus respectivos pesos
    for line in stdin.readlines():
        u, v, w = map(int, line.split())
        u -= 1
        v -= 1
        graph[u].append((v, w))
        graph[v].append((u, w))

    queue = deque([(0, 0, 0)])
    visited = [float("inf")] * len(graph)
    visited[0] = 0

    while queue:
        node, path_length, path_cost = queue.pop()

        if node == n - 1:
            print(path_length)
            break

        for neighbor, cost in graph[node]:
            total_cost = path_cost + cost
            if total_cost <= k and total_cost < visited[neighbor]:
                queue.appendleft((neighbor, path_length + 1, total_cost))  # type: ignore
                visited[neighbor] = total_cost
    else:
        print(-1)


if __name__ == "__main__":
    main()
