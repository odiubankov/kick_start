#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::string solve_case() {
  std::string input_string;
  std::getline(std::cin, input_string);
  std::getline(std::cin, input_string);
  std::array<std::unordered_set<std::size_t>, 10> digit_positions;
  std::array<std::vector<std::size_t>, 10> digit_positions_to_process;
  std::string str_to_process = "*" + input_string + "*";
  for (size_t i = 1; i < str_to_process.size() - 1; ++i) {
    const size_t digit = static_cast<std::size_t>(str_to_process.at(i) - '0');
    digit_positions.at(digit).insert(i);
    digit_positions_to_process.at(digit).push_back(i);
  }

  std::vector<std::size_t> next_index(str_to_process.size(), 0);
  for (size_t i = 0; i < next_index.size() - 1; ++i) {
    next_index.at(i) = i + 1;
  }

  std::vector<std::size_t> prev_index(str_to_process.size(), 0);
  for (size_t i = 1; i < next_index.size(); ++i) {
    prev_index.at(i) = i - 1;
  }

  bool match_found = true;
  while (match_found) {
    match_found = false;
    for (size_t i = 0; i <= 9; ++i) {
      const size_t next_digit = (i + 1) % 10;
      const size_t substitute_digit = (next_digit + 1) % 10;

      auto& i_positions_to_process = digit_positions_to_process.at(i);
      auto& i_positions = digit_positions.at(i);

      auto& next_digit_positions_to_process =
          digit_positions_to_process.at(next_digit);
      auto& next_digit_positions = digit_positions.at(next_digit);

      auto& substitute_positions_to_process =
          digit_positions_to_process.at(substitute_digit);
      auto& substitute_positions = digit_positions.at(substitute_digit);

      // iterate over all positions of this digit that needs to be processed
      for (const auto i_position : i_positions_to_process) {
        // check if this digit is still at this postition. because it can be
        // removed at previous iteration
        if (i_positions.find(i_position) == end(i_positions)) {
          continue;
        }

        // find actual next position within string
        const auto next_pos = next_index.at(i_position);
        // find if there is a required digit at next position
        const auto next_digit_in_pos_it = next_digit_positions.find(next_pos);
        if (next_digit_in_pos_it != end(next_digit_positions)) {
          // substitute next position with a new one
          next_index.at(i_position) = next_index.at(next_pos);
          // set correct prev position
          prev_index.at(next_index.at(i_position)) = i_position;
          // actual substitution. there is a new digit in current position
          substitute_positions.insert(i_position);
          // this digit needs to be processed on some next iteration
          substitute_positions_to_process.push_back(i_position);
          // also its predecessor needs to be processed if it has correct value
          if (next_digit_positions.find(prev_index.at(i_position)) !=
              end(next_digit_positions)) {
            next_digit_positions_to_process.push_back(
                prev_index.at(i_position));
          }
          i_positions.erase(i_position);
          next_digit_positions.erase(next_digit_in_pos_it);
          match_found = true;
        }
      }

      i_positions_to_process.clear();
    }
  }

  for (auto& character : str_to_process) {
    character = '*';
  }

  for (std::size_t i = 0; i <= 9; ++i) {
    for (const auto pos : digit_positions.at(i)) {
      str_to_process.at(pos) = '0' + i;
    }
  }

  std::string res;
  std::copy_if(begin(str_to_process), end(str_to_process),
               std::back_inserter(res),
               [](const auto character) { return character != '*'; });
  return res;
}

int main(int /*argc*/, char** /**argv[]*/) {
  std::string input_string;
  std::getline(std::cin, input_string);
  const auto tests_count = std::stoi(input_string);
  for (int i = 1; i <= tests_count; ++i) {
    const auto result = solve_case();
    std::cout << "Case #" << i << ": " << result << std::endl;
  }
  return 0;
}
