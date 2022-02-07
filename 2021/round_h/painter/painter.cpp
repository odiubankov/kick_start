#include <array>
#include <iostream>
#include <string>
#include <unordered_map>

using ColorMapT = std::unordered_map<char, int>;

namespace {
constexpr int Uncolored{0b00000000000000000000000000000000};
constexpr int Red{0b00000000000000000000000000000001};
constexpr int Yellow{0b00000000000000000000000000000010};
constexpr int Blue{0b00000000000000000000000000000100};
constexpr int Orange{Red | Yellow};
constexpr int Purple{Red | Blue};
constexpr int Green{Yellow | Blue};
constexpr int Gray{Red | Yellow | Blue};
const ColorMapT ColorMap{{'U', Uncolored}, {'R', Red},    {'Y', Yellow},
                         {'B', Blue},      {'O', Orange}, {'P', Purple},
                         {'G', Green},     {'A', Gray}};
constexpr std::array<int, 3> PrimaryColors{Red, Yellow, Blue};
}  // namespace

int calc_strokes() {
  std::string input_string;
  std::getline(std::cin, input_string);
  std::getline(std::cin, input_string);
  int prev_color{0};
  int strokes_count = 0;
  for (const auto color_index : input_string) {
    auto color = ColorMap.at(color_index);
    for (size_t i = 0; i < PrimaryColors.size() && color != 0; ++i) {
      if ((color & PrimaryColors.at(i)) != 0 &&
          (prev_color & PrimaryColors.at(i)) == 0) {
        ++strokes_count;
        color ^= PrimaryColors.at(i);
      }
    }

    prev_color = ColorMap.at(color_index);
  }

  return strokes_count;
}

int main(int /*argc*/, char** /**argv[]*/) {
  std::string input_string;
  std::getline(std::cin, input_string);
  const auto tests_count = std::stoi(input_string);
  for (int i = 1; i <= tests_count; ++i) {
    std::cout << "Case #" << i << ": " << calc_strokes() << std::endl;
  }

  return 0;
}
