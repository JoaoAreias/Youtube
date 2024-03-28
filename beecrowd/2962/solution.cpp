#include <cstdio>
#include <cmath>


class UnionFind {
    int parent[1004];
    int rank[1004];
public:
    UnionFind(int n) {
        for (int i = 0; i < n; i++){
            parent[i] = i;
            rank[i] = 1;
        }
    }

    int find(int n) {
        if (parent[n] != n) {
            parent[n] = find(parent[n]);
        }
        return parent[n];
    }

    void merge(int a, int b) {
        int parent_a = find(a);
        int parent_b = find(b);

        if (rank[parent_a] > rank[parent_b]) {
            parent[parent_b] = parent_a;
        } else if (rank[parent_a] < rank[parent_b]) {
            parent[parent_a] = parent_b; 
        } else {
            parent[parent_b] = parent_a;
            rank[parent_a]++;
        }
    }

    bool connected(int a, int b) {
        return find(a) == find(b);
    }
};


double dist(int p1[3], int p2[3]) {
    return sqrt(
        (p1[0] - p2[0]) * (p1[0] - p2[0]) +
        (p1[1] - p2[1]) * (p1[1] - p2[1])
    );
}


int main (int argc, char *argv[]) {
    int m, n, k;
    int sensors[1000][3];

    scanf("%d %d %d", &m, &n, &k);
    /* Nós 0, 1, 2, e 3 são reservados para o topo, a direita, em baixo, e a
     * esquerda respectivamente. */
    auto union_find = UnionFind(k + 4);

    for (int i = 0; i < k; i++){
        scanf("%d %d %d", &sensors[i][0], &sensors[i][1], &sensors[i][2]);

        // Sensor encherga a parede do topo
        if (sensors[i][1] + sensors[i][2] >= n)
            union_find.merge(0, i + 4);

        // Sensor encherga a parede da direita
        if (sensors[i][0] + sensors[i][2] >= m)
            union_find.merge(1, i + 4);

        // Sensor encherga a parede de baixo
        if (sensors[i][1] - sensors[i][2] <= 0)
            union_find.merge(2, i + 4);

        // Sensor encherga a parede da esquerda
        if (sensors[i][0] - sensors[i][2] <= 0)
            union_find.merge(3, i + 4);
    }

    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++){
            if (dist(sensors[i], sensors[j]) <= sensors[i][2] + sensors[j][2])
                union_find.merge(i + 4, j + 4);
        }
    }

    if (union_find.connected(0, 1) || union_find.connected(0, 2) ||
        union_find.connected(3, 1) || union_find.connected(3, 2))
        printf("N\n");
    else
        printf("S\n");

    return 0;
}
