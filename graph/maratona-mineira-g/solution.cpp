#include <cstdio>
#include <queue>
#include <tuple>
#include <vector>

#define INF 2147483647
#define SIZE 100000

typedef std::vector<std::vector<std::tuple<int, int>>> Graph;

int constrained_shortest_path(const Graph &graph, int start, int end,
                              int capacity) {
  /*
   * Função que calcula o menor caminho entre dois nós de um grafo, com a
   * restrição de que o custo total do caminho não pode ser maior que a
   * capacidade máxima de custo.
   *
   * Parâmetros:
   * graph: Grafo representado por uma lista de adjacências
   * start: Nó de origem
   * end: Nó de destino
   * capacity: Custo máximo do caminho
   */

  // Fila de nós a serem visitados
  std::queue<std::tuple<int, int, int>> bfs_queue;

  // Vetor de nós visitados
  int visited[SIZE];
  std::fill(visited, visited + SIZE, INF);
  visited[start] = 0;

  // Inicializa a fila com o nó de origem
  bfs_queue.push(std::make_tuple(start, 0, 0));

  while (!bfs_queue.empty()) {
    int node, distance, cost;
    std::tie(node, distance, cost) = bfs_queue.front();
    bfs_queue.pop();

    if (node == end) {
      return distance;
    }

    for (auto [next_node, travel_cost] : graph.at(node)) {
      int total_cost = travel_cost + cost;
      /*
       * Adiciona o nó na fila apenas se o custo total
       * for menor que a capacidade e o nó não foi visitado
       * com um custo menor
       */
      if (total_cost <= capacity && total_cost < visited[next_node]) {
        bfs_queue.push(std::make_tuple(next_node, distance + 1, total_cost));
        visited[next_node] = total_cost;
      }
    }
  }
  return -1;
}

int main() {
  /*
   * Leitura dos dados de entrada
   *  n: Número de nós
   *  m: Número de arestas
   *  k: Preço máximo das passagens
   *  u, v: Nós conectados por uma aresta
   *  w: Custo da passagem entre os nós u e v
   */
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  Graph graph(n);

  for (int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    u--;
    v--;
    graph[u].push_back(std::make_tuple(v, w));
  }

  printf("%d\n", constrained_shortest_path(graph, 0, n - 1, k));
  return 0;
}
