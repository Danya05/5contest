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

void Operator(std::string& st1, std::string& st2) {
  int max_idx;
  if (st1.size() <= st2.size()) {
    std::vector<int> pf_of_st = PrefixFunction(st2 + '#' + st1);
    max_idx = pf_of_st[st1.size() + st2.size()];
  } else {
    std::string sub_str = st1.substr(st1.size() - st2.size(), 2 * st2.size());
    std::vector<int> pf_of_st = PrefixFunction(st2 + '#' + sub_str);
    max_idx = pf_of_st[sub_str.size() + st2.size()];
  }
  st1 += st2.substr(max_idx, st2.size() - max_idx);
}

void Solution() {
  int num;
  std::cin >> num;
  if (num == 0) {
    return;
  }
  std::string st1;
  std::string st2;
  std::cin >> st1;
  for (int i = 0; i < num - 1; ++i) {
    std::cin >> st2;
    Operator(st1, st2);
  }
  std::cout << st1;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Solution();
}
