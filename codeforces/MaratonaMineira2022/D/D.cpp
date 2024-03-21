#include <algorithm>
#include <cstdio>
#include <cstring>

#define MAX 1e9 + 1  // Valor maximo de tempo
#define MAX_SIDE 401 // Tamanho maximo de um dos lados do quadrado


void fill_prefix_sum(int country[][MAX_SIDE], int prefix_sum[][MAX_SIDE], int t, int n, int m) {
	memset(prefix_sum, 0, MAX_SIDE * MAX_SIDE * sizeof(int));
	
	prefix_sum[0][0] = (country[0][0] <= t);
	for (int row = 1; row < n; row++)
		prefix_sum[row][0] = prefix_sum[row - 1][0] + (country[row][0] <= t);

	for (int col = 1; col < m; col++)
		prefix_sum[0][col] = prefix_sum[0][col - 1] + (country[0][col] <= t);

	for (int row = 1; row < n; row++) {
		for (int col = 1; col < m; col++) {
			prefix_sum[row][col] = (country[row][col] <= t) + 
						prefix_sum[row-1][col] + 
						prefix_sum[row][col-1] - 
						prefix_sum[row-1][col-1];
		}
	}
}

int get_sum(int prefix_sum[][MAX_SIDE], int i, int j, int window_size){
	int top = i - window_size;
	int left = j - window_size;

	int sum = prefix_sum[i][j];
	if (top >= 0)
		sum -= prefix_sum[top][j];
	if (left >= 0)
		sum -= prefix_sum[i][left];
	if (top >= 0 && left >= 0)
		sum += prefix_sum[top][left];

	return sum;
}

bool is_collapsed(int country[][MAX_SIDE], int t, int n, int m, int window_size){
	int prefix_sum[MAX_SIDE][MAX_SIDE];
	fill_prefix_sum(country, prefix_sum, t, n, m);

	int window_sq = window_size * window_size;
	for (int i = window_size - 1; i < n; i++) {
		for (int j = window_size - 1; j < m; j++) {
			if (get_sum(prefix_sum, i, j, window_size) == window_sq)
				return true;
		}
	}

	return false;
}

int main () {
	int n, m, k, q;
	int a, b, d;

	int country[MAX_SIDE][MAX_SIDE];
	std::fill(&country[0][0], &country[0][0] + MAX_SIDE * MAX_SIDE, MAX);

	// Input dos dados
	scanf("%d %d %d %d", &n, &m, &k, &q);
	for (int i = 0; i < q; i++) {
		scanf("%d %d %d", &a, &b, &d);
		country[a-1][b-1] = d;
	}
	

	// Busca binaria pelo momento em que o pais
	// entrou em colapso
	int mid, l = 0, r = MAX;
	bool collapsed = false;
	while (l < r) {
		mid = (r + l) / 2;
		if (is_collapsed(country, mid, n, m, k)){
			collapsed = true;
			r = mid;
		} else {
			l = mid + 1;
		}

	}

	// Imprime a resposta
	printf("%d\n", (collapsed ? r : -1));

	return 0;
}
