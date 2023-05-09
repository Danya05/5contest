#include <iostream>
#include <set>
#include <unordered_map>
#include <string>
#include <vector>

static const int64_t prod1 = 37;
static const int64_t mod1 = 1000008719;

static const int64_t prod2 = 31;
static const int64_t mod2 = 1000003777;

int64_t n_th_hash(std::string& pattern, int64_t last, std::vector<int64_t>& pow, int64_t mod) {
  int64_t start = 0;
  for (int i = 0; i < last; ++i) {
    start = (start + (pattern[i] -'a' + 1) * pow[last - 1 - i]) ;
  }
  return start;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string pattern;
  std::string text;
  std::cin >> pattern >> text;
  if (text.size() < pattern.size()) {
    std::cout << 0;
  } else {
    std::string new_pattern = pattern + pattern;
    size_t num = std::max(text.size(), new_pattern.size());
    std::vector<int64_t> pow1(num);
    pow1[0] = 1;
    for (int i = 1; i < pattern.size() + 1; ++i) {
      pow1[i] = (pow1[i - 1] * prod1) ;
    }
    std::vector<int64_t> pow2(num);
    pow2[0] = 1;
    for (int i = 1; i < pattern.size() + 1; ++i) {
      pow2[i] = (pow2[i - 1] * prod2) ;
    }

    std::unordered_map<int64_t, int64_t> vec_of_patterns_hash1;
    std::unordered_map<int64_t, int64_t> vec_of_patterns_hash2;
    std::unordered_map<int64_t, int64_t> vec_of_text_hash1;
    std::unordered_map<int64_t, int64_t> vec_of_text_hash2;

    int64_t hash1 = n_th_hash(pattern, pattern.size(), pow1, mod1);
    int64_t hash2 = n_th_hash(pattern, pattern.size(), pow2, mod2);

    vec_of_patterns_hash1[hash1] = 0;
    vec_of_patterns_hash2[hash2] = 0;

    for (int i = 1; i < pattern.size(); ++i) {
      hash1 = ((hash1 - (new_pattern[i - 1] - 'a' + 1) * pow1[pattern.size() - 1]) * prod1
          + new_pattern[i + pattern.size() - 1] - 'a' + 1) ;
      hash2 = ((hash2 - (new_pattern[i - 1] - 'a' + 1) * pow2[pattern.size() - 1]) * prod2
          + new_pattern[i + pattern.size() - 1] - 'a' + 1) ;
      vec_of_patterns_hash1.insert({hash1, i});
      vec_of_patterns_hash2.insert({hash2, i});
    }

    int64_t st_hash1 = n_th_hash(text, pattern.size(), pow1, mod1);
    int64_t st_hash2 = n_th_hash(text, pattern.size(), pow2, mod2);
    int result = 0;

    for (int i = 0; i < text.size() - pattern.size() + 1; ++i) {
      if (i != 0) {
        st_hash1 = ((st_hash1 - (text[i - 1] - 'a' + 1) * pow1[pattern.size() - 1]) * prod1
            + text[i + pattern.size() - 1] - 'a' + 1) ;
        st_hash2 = ((st_hash2 - (text[i - 1] - 'a' + 1) * pow2[pattern.size() - 1]) * prod2
            + text[i + pattern.size() - 1] - 'a' + 1) ;
      }
      if (vec_of_patterns_hash1.contains(st_hash1) and vec_of_patterns_hash2.contains(st_hash2)) {
        ++result;
      }
    }
    std::cout << result;
  }
}
