#include <iostream>
#include <vector>

std::vector<int> PrefixFunction(const std::string& st) {
  int len_st = static_cast<int>(st.size());
  std::vector<int> result_prefix(len_st);
  result_prefix[0] = 0;
  for (int i = 1; i < len_st; ++i) {
    int j = result_prefix[i - 1];
    while (j > 0 and st[i] != st[j]) {
      j = result_prefix[j - 1];
    }
    if (st[i] == st[j]) {
      ++j;
    }
    result_prefix[i] = j;
  }
  return result_prefix;
}

void KMP(std::string& pattern, std::string& st) {
  int len_pattern = static_cast<int>(pattern.size());
  int len_st = static_cast<int>(st.size());
  std::vector<int> result(len_st, 0);
  std::vector<int> pf_of_st = PrefixFunction(pattern + '#' + st);
  int cnt = 0;
  for (int i = 0; i < len_st; ++i) {
    if (pf_of_st[len_pattern + i + 1] == len_pattern) {
      std::cout << i - len_pattern + 1 << '\n';
    }
  }
}

int main() {
  std::string pattern;
  std::string text;
  std::cin >> text >> pattern;
  KMP(pattern, text);
}
