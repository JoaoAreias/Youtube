#include <complex>
#include <iostream>
#include <vector>

const int MAX_SUM = 1 << 22;
const int MAX_SIZE = 100005;
const double PI = std::acos(-1);

int char_to_wt(char c) { return c - 'a' + 1; }

typedef std::complex<double> Complex;

void fft(std::vector<Complex> &p, bool invert) {
  size_t n = p.size();
  for (size_t i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j & bit; bit >>= 1)
      j ^= bit;
    j ^= bit;
    if (i < j)
      std::swap(p[i], p[j]);
  }

  for (size_t len = 2; len <= n; len <<= 1) {
    double ang = 2 * PI / len * (invert ? -1 : 1);
    Complex wlen(cos(ang), sin(ang));

    for (size_t i = 0; i < n; i += len) {
      Complex w(1);

      for (size_t j = 0; j < len / 2; j++) {
        Complex u = p[i + j];
        Complex v = p[i + j + len / 2] * w;

        p[i + j] = u + v;
        p[i + j + len / 2] = u - v;
        w *= wlen;
      }
    }
  }

  if (invert) {
    for (auto &x : p)
      x /= n;
  }
}

void multiply(std::vector<Complex> &p, std::vector<Complex> &q) {
  fft(p, false);
  fft(q, false);

  for (size_t i = 0; i < p.size(); i++)
    p[i] *= q[i];

  fft(p, true);
}

int round_abs(Complex c) { return std::round(std::abs(c)); }

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::string input;
  std::vector<int> prefix_sum;
  std::vector<Complex> p, q;

  std::cin >> input;
  prefix_sum.resize(input.size());

  /**
   * Computa a soma de prefixos para montar o polinomio
   */
  prefix_sum[0] = char_to_wt(input[0]);
  for (size_t i = 1; i < input.size(); i++)
    prefix_sum[i] = prefix_sum[i - 1] + char_to_wt(input[i]);

  // Encontra o maior valor da soma de prefixos
  int max_sum = prefix_sum[input.size() - 1];

  // Encontra o menor valor de n que é uma potência de 2 e é maior que 2 *
  // max_sum
  int n = 1 << (8 * sizeof(int) - __builtin_clz(max_sum) + 1);

  p.resize(n);
  q.resize(n);
  std::fill(p.begin(), p.end(), Complex(0, 0));
  std::fill(q.begin(), q.end(), Complex(0, 0));
  /**
   * Monta os polinomios para serem multiplicados
   */
  for (size_t i = 0; i < input.size(); i++)
    p[prefix_sum[i]] = Complex(1, 0);

  q[max_sum] = Complex(1, 0);
  for (size_t i = 0; i < input.size() - 1; i++)
    q[max_sum - prefix_sum[i]] = Complex(1, 0);

  multiply(p, q);
  int count = 0;
  for (size_t i = max_sum + 1; i < p.size(); i++)
    if (round_abs(p[i]) > 0)
      count++;

  std::cout << count << std::endl;
}
