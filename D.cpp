#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

bool isPalindrome(const std::string &s, int i, int j) {
  while (i < j and s[i] == s[j])  {
    ++i;
    --j;
  }
  return i >= j;
}

class Trie {
 public:
  static constexpr int64_t Null = -1;
  struct Node {
    Node() = default;
    Node(int64_t parent, char symbol) : parent(parent), symbol(symbol){}

    bool HasChild(char symbol) {
      return children.find(symbol) != children.end();
    }

    std::unordered_map<char, int64_t> children;
    int64_t parent{-1};
    char symbol{};
    bool is_terminal{false};
  };

  std::vector<int> vector_of_idxs;
  int index = -1;
  Trie* alphabet[26] = {};

};

void Add(std::string& key, int idx, Trie& trie) {
  auto node = &trie;
  for (int i = key.size() - 1; i >= 0; --i) {
    if (isPalindrome(key, 0, i)) {
      node->vector_of_idxs.push_back(idx);
    }
    if (!node->alphabet[key[i] - 'a']) {
      node->alphabet[key[i] - 'a'] = new Trie();
    }
    node = node->alphabet[key[i] - 'a'];
  }
  node->index = idx;
  node->vector_of_idxs.push_back(idx);
}

int main() {
  Trie trie;
  int n;
  std::cin >> n;
  std::vector<std::string> strings;
  for (int i = 0; i < n; ++i) {
    std::string st;
    std::cin >> st;
    strings.push_back(st);
    Add(st, i, trie);
  }
  std::vector<std::pair<int, int>> result;
  for (int i =  0; i < n; ++i) {
    auto st = strings[i];
    auto node = &trie;
    for (int j = 0; j < st.size() and node; ++j) {
      if (node->index != -1 and node->index != i and isPalindrome(st, j, st.size() - 1)) {
        result.emplace_back(i + 1, node->index + 1);
      }
      node = node->alphabet[st[j] - 'a'];
    }
    if (!node) {
      continue;
    }
    for (auto j : node->vector_of_idxs) {
      if (j != i) {
        result.emplace_back(i + 1, j + 1);
      }
    }
  }
  std::cout << result.size() << "\n";
  for (auto pair : result) {
    std::cout << pair.first << " " << pair.second << "\n";
  }
}
