#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

class SuffixAutomaton {
  static constexpr int64_t kBeforeRoot = -1;

  struct State {
    std::unordered_map<char, int64_t> go; // переходики
    int64_t len; // размер longest
    int64_t suffix_link; // суфлинк ведет в класс где лежит самый большой
    // суффикс longest-а, который лежит в другом классе
    // (класс эквивалентности состоит из longest и нескольких его самых длинных суффиксов)
  };

 public:

  void ResetState() {
    use_state_ = 0;
  }

  bool Step(char symbol) {
    if (states_[use_state_].go.contains(symbol)) {
      use_state_ = states_[use_state_].go[symbol];
      return true;
    }
    return false;
  }

  SuffixAutomaton() : states_(1, {{}, 0, kBeforeRoot}) {}

  // добавляем по символу и перестраиваем автомат
  void AddChar(char symbol) {
    // создадим класс соответствующий [Sc]
    int64_t curr = MakeState(
        states_[last_state_].len + 1,
        0
    );

    ino64_t p = last_state_;
    // пока нет переходов добавляем новые переходы в класс [Sc]
    while (p != kBeforeRoot && !states_[p].go.contains(symbol)) {
      states_[p].go[symbol] = curr;
      p = states_[p].suffix_link;
    }

    if (p == kBeforeRoot) {
      // случай когда мы ушли за корень - символ был в нашей строке впервые
      states_[curr].suffix_link = 0;
    } else {
      int64_t q = states_[p].go[symbol];
      if (states_[p].len + 1 == states_[q].len) {
        // случай когда не появляется новых классов
        states_[curr].suffix_link = q;
      } else {
        int64_t clone_id = MakeState(
            states_[p].len + 1, // s0 - лонгест
            states_[q].suffix_link // суфлинк
        );
        states_[clone_id].go = states_[q].go;
        // нужно перенаправить переходы в клона
        while (p != kBeforeRoot && states_[p].go[symbol] == q) {
          states_[p].go[symbol] = clone_id;
          p = states_[p].suffix_link;
        }
        states_[q].suffix_link = states_[curr].suffix_link = clone_id;
      }
    }

    last_state_ = curr; // longest класса [Sc]
  }

  bool CheckSubstr(std::string& st) {
    use_state_ = 0;
    for (auto chr : st) {
      if (!Step(chr)) return false;
    }
    return true;
  }

 private:

  int64_t MakeState(int64_t len, int64_t suffix_link) {
    int64_t id = states_.size();
    states_.push_back({{}, len, suffix_link});
    return id;
  }
  int64_t last_state_{0};
  std::vector<State> states_;

  int64_t use_state_{0};
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string text = "";
  char temp;
  std::string sub_str;
  SuffixAutomaton suffix_automaton;
  bool result;
  while (std::cin >> temp >> sub_str) {
    std::transform(sub_str.begin(), sub_str.end(), sub_str.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    if (temp == 'A') {
      for (auto chr : sub_str) {
        suffix_automaton.AddChar(chr);
      }
    } else {
      std::vector<std::string> patterns = {sub_str};
      result = suffix_automaton.CheckSubstr(sub_str);
      if (result) {
        std::cout << "YES" << '\n';
      } else {
        std::cout << "NO" << '\n';
      }
    }
  }
}

