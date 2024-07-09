#include <cstdio>
#include <cstring>

#define MAXN 100000

long long det(const long long M[3][3]) {
  /* Computa a determinante de uma matriz 3x3
   *
   * M = | a b c |
   *     | d e f |
   *     | g h i |
   *
   *    det(M) = aei + bfg + cdh - ceg - bdi - afh
   **/
  return M[0][0] * M[1][1] * M[2][2] + M[0][1] * M[1][2] * M[2][0] +
         M[0][2] * M[1][0] * M[2][1] - M[0][1] * M[1][0] * M[2][2] -
         M[0][0] * M[1][2] * M[2][1] - M[0][2] * M[1][1] * M[2][0];
}

long long find_volume(const long long P[MAXN][3], int n) {
  /* Computa 6 vezes o volume do poliedro convexo formado pelos pontos P[0],
   * P[1], ..., P[n-1] do polígono e sua projeção no plano z = 0
   **/
  long long M[3][3];
  long long volume = 0;

  for (int i = 0; i < n; i++) {
    /* Primeiro tetraedro formado pelos pontos
     * ( 0,  0,  0)
     * (x1, y1, z1)
     * (x1,  0, z1)
     * (x2, y2, z2)
     **/
    memcpy(&M[0], &P[i], 3 * sizeof(long long));
    memcpy(&M[1], &P[i], 3 * sizeof(long long));
    memcpy(&M[2], &P[(i + 1) % n], 3 * sizeof(long long));
    M[1][2] = 0;
    volume += det(M);

    /* Segundo tetraedro formado pelos pontos
     * ( 0,  0,  0)
     * (x1,  0, z1)
     * (x2, y2, z2)
     * (x2,  0, z2)
     **/
    memcpy(&M[0], &P[(i + 1) % n], 3 * sizeof(long long));
    memcpy(&M[1], &P[(i + 1) % n], 3 * sizeof(long long));
    memcpy(&M[2], &P[i], 3 * sizeof(long long));
    M[0][2] = 0;
    M[2][2] = 0;

    volume += det(M);
  }
  return volume;
}

int main() {
  int n;
  long long P[MAXN][3];

  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%lld %lld", &P[i][0], &P[i][1]);
    P[i][2] = P[i][1];
  }

  printf("%lld\n", find_volume(P, n));
  return 0;
}
