
// WA17!!!!!!

#include <algorithm>
#include <iostream>
#include <complex>
#include <vector>
const double PI = M_PI;

void fft(std::vector<std::complex<double>>& a, bool invert) {
  int n = a.size();
  for (int i = 1, j = 0; i < n; i++) {
    int bit = n >> 1;
    for (; j >= bit; bit >>= 1) j -= bit;
      j += bit;
      if (i < j) {
        swap(a[i], a[j]);
      }
  }
  for (int len = 2; len <= n; len <<= 1) {
    double ang = 2 * PI / len * (invert ? -1 : 1);
    std::complex<double> wlen(cos(ang), sin(ang));
    for (int i = 0; i < n; i += len) {
      std::complex<double> w(1);
      for (int j = 0; j < len / 2; j++) {
        std::complex<double> u = a[i+j], v = w * a[i+j+len/2];
        a[i+j] = u + v;
        a[i+j+len/2] = u - v;
        w *= wlen;
      }
    }
  }
  if (invert) {
    for (int i = 0; i < n; i++)
      a[i] /= n;
  }
}

std::vector<std::complex<double>> multiply(std::vector<std::complex<double>> const& a, std::vector<std::complex<double>> const& b) {
  int n = a.size(), m = b.size();

  int degree = n + m - 1;
  int N = 1;
  while (N < degree) N <<= 1;

  std::vector<std::complex<double>> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  fa.resize(N); fb.resize(N);

  fft(fa, false);
  fft(fb, false);

  for (int i = 0; i < N; i++) fa[i] *= fb[i];

  fft(fa, true);

  return fa;
}

int main() {
  std::vector<std::complex<double>> a;
  std::string st;
  std::cin >> st;
  int cnt = 0;
  for (int i = 0; i < st.size(); ++i) {
    if (st[i] == '1') {
      break;
    }
    ++cnt;
  }
  int new_start = cnt;
  for (int i = cnt; i < st.size(); ++i) {
    a.emplace_back(st[i] - '0');
  }
  std::vector<std::complex<double>> result = multiply(a, a);
  std::vector<int> p_square;
  cnt = result.size();
  int cnt_start = 0;
  while (static_cast<int>(round(std::real(result[cnt_start]))) == 0) {
    ++cnt_start;
  }
  for (int i = cnt_start; i < result.size(); ++i) {
    p_square.push_back(static_cast<int>(round(std::real(result[i]))));
  }
  int total = 0;
  for (int i = 1; i < st.size() - new_start - 1; ++i) {
    if (st[i + new_start] == '1') {
      total += static_cast<double>((p_square[2 * i] - 1)) / 2;
    }
  }
  std::cout << total;
}
