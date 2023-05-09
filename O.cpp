#include <algorithm>
#include <iostream>
#include <complex>
#include <cmath>
#include <vector>

std::vector<std::complex<double>> FFT(std::vector<std::complex<double>>& a, int N, bool inverted) {
  if (N == 1) {
    return std::vector<std::complex<double>>(1, a[0]);
  }
  std::vector<std::complex<double>> a_odd;
  std::vector<std::complex<double>> a_even;
  for (int i = 0; i < static_cast<int>(a.size()); ++i) {
    if (i % 2 == 0) {
      a_odd.push_back(a[i]);
    } else {
      a_even.push_back(a[i]);
    }
  }
  std::vector<std::complex<double>> z(N);
  for (int i = 0; i  < N; ++i) {
    double angle = (inverted ? -1 : 1) * 2 * M_PI * i / N;
    z[i] = std::complex<double>(cos(angle), sin(angle));
  }
  std::vector<std::complex<double>> f_odd = FFT(a_odd, N / 2, inverted);
  std::vector<std::complex<double>> f_even = FFT(a_even, N / 2, inverted);
  std::vector<std::complex<double>> f(N);
  for (int i = 0; i < N / 2; ++i) {
    f[i] = f_even[i] + z[i] * f_odd[i];
    f[i + N / 2] = f_even[i] - z[i] * f_odd[i];
  }
  return f;
}

std::vector<std::complex<double>> Multiply(std::vector<std::complex<double>>& a, std::vector<std::complex<double>>& b) {
  std::vector<std::complex<double>> f = FFT(a, a.size(), false);
  std::vector<std::complex<double>> g = FFT(b, b.size(), false);
  std::vector<std::complex<double>> h(std::max(a.size(), b.size()));
  for (int i = 0; i < h.size(); ++i) {
    h[i] = f[i] * g[i] / std::complex<double>(h.size(), 0);
  }
  std::reverse(h.begin(), h.end());
  std::vector<std::complex<double>> res = FFT(h, h.size(), true);
  return res;
}

int main() {
  std::vector<std::complex<double>> a;
  std::vector<std::complex<double>> b;
  int num;
  std::cin >> num;
  int next = pow(2, ceil(log(num + 1)/log(2)));
  for (int i = 0; i < num + 1; ++i) {
    int temp;
    std::cin >> temp;
    a.emplace_back(temp);
  }
  int num1;
  std::cin >> num1;
  int next1 = pow(2, ceil(log(num1 + 1)/log(2)));
  for (int i = 0; i < num1 + 1; ++i) {
    int temp;
    std::cin >> temp;
    b.emplace_back(temp);
  }
  if (a.size() == 1 and std::abs(round(std::real(a[0]))) == 0 or b.size() == 1 and
      std::abs(round(std::real(b[0]))) == 0) {
    std::cout << 0 << " " << 0;
    return 0;
  }
  int res = std::max(next, next1) * 2;
  std::reverse(a.begin(), a.end());
  std::reverse(b.begin(), b.end());
  while (a.size() < res) {
    a.emplace_back(0);
  }
  while (b.size() < res) {
    b.emplace_back(0);
  }
  std::vector<std::complex<double>> result = Multiply(a, b);
  std::cout << num + num1 << " ";
  int cnt = 0;
  while (static_cast<int>(round(std::real(result[cnt]))) == 0) {
    ++cnt;
  }
  for (int i = cnt; i < cnt + num + num1 + 1; ++i) {
    std::cout << static_cast<int>(round(std::real(result[i]))) << " ";
  }
}
