#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

class Trie {
 public:
  static constexpr int64_t Null = -1;
  struct Node {
    Node() : parent(Null), suff_links(Null) {};
    Node(int64_t parent, char symbol) : parent(parent), symbol(symbol){}

    bool HasChild(char symbol) {
      return children.find(symbol) != children.end();
    }
    int64_t number_of_abit = 0;
    int64_t suff_links;
    std::unordered_map<char, int64_t> children;
    int64_t parent{-1};
    char symbol{};
    bool is_terminal{false};

    void Add_Abit() {
      ++number_of_abit;
    }

    int64_t GetAbit() {
      return number_of_abit;
    }
  };

  Trie() : nodes_(1, Node()) {}

  int64_t Add(const std::string& key) {
    int64_t now = 0;
    for (auto symbol : key) {
      if (!nodes_[now].HasChild(symbol)) {
        nodes_.emplace_back(now, symbol);
        nodes_[now].children[symbol] = nodes_.size() - 1;
      }
      nodes_[now].Add_Abit();
      now = nodes_[now].children[symbol];
    }
    nodes_[now].is_terminal = true;
    nodes_[now].Add_Abit();
    return now;
  }

  Node& Get(int64_t index) {
    return nodes_.at(index);
  }

  size_t NodeCount() {
    return nodes_.size();
  }
 private:
  std::vector<Node> nodes_;
  std::unordered_map<int64_t, int64_t> flow_tree;
  friend void PrintRes(int64_t q, Trie& tr);
  friend void Solution(Trie& tr, int64_t k);
  friend void CheckGroup(Trie& tr, std::vector<int64_t>& distances, int64_t start_vertex, int64_t k);
};

void CheckGroup(Trie& tr, std::vector<int64_t>& distances, int64_t start_vertex, int64_t k) {
  if (tr.nodes_[start_vertex].GetAbit() >= k) {
    if (tr.flow_tree.find(distances[start_vertex]) == tr.flow_tree.end()) {
      tr.flow_tree[distances[start_vertex]] = 1;
    } else {
      ++tr.flow_tree[distances[start_vertex]];
    }
  }
}

void Solution(Trie& tr, int64_t k) { // aka BFS
  int64_t start = 0;
  int64_t n = tr.nodes_.size();
  std::vector<int64_t> distances(n, -1);
  std::queue<int64_t> queue;
  queue.push(start);
  distances[start] = 0;
  while (!queue.empty()) {
    int start_vertex = queue.front();
    queue.pop();
    for (auto i : tr.nodes_[start_vertex].children) {
      int64_t to_vertex = i.second;
      if (distances[to_vertex] == -1) {
        queue.push(to_vertex);
        distances[to_vertex] = 1 + distances[start_vertex];
      }
    }
    CheckGroup(tr, distances, start_vertex, k);
  }
}

void PrintRes(int64_t q, Trie& tr) {
  int i = 0;
  while (i < q) {
    int64_t l;
    std::cin >> l;
    std::cout << tr.flow_tree[2 * l] << '\n';
    ++i;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  Trie tr;
  int64_t n;
  int64_t k;
  std::cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    std::string temp, add_str;
    std::cin >> temp;
    for (int i = 0; i < temp.size(); ++i) {
      add_str += temp[i];
      add_str += temp[temp.size() - i - 1];
    }
    tr.Add(add_str);
  }
  Solution(tr, k);
  int64_t query;
  std::cin >> query;
  PrintRes(query, tr);
}
