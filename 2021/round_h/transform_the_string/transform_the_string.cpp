#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using DiffType = unsigned long long;

bool solve_next_case(const std::size_t case_index) {
  std::string padlock;
  if (!std::getline(std::cin, padlock) || padlock.empty()) {
    std::cerr << "can't read padlock for case " << case_index << std::endl;
    return false;
  }

  std::string available_chars;
  if (!std::getline(std::cin, available_chars) || available_chars.empty()) {
    std::cerr << "can't read available characters " << case_index << std::endl;
    return false;
  }

  DiffType min_operations{0};
  for (const auto character : padlock) {
    DiffType up_operations{0};
    if (const auto greater_it = std::lower_bound(
            begin(available_chars), end(available_chars), character);
        greater_it != end(available_chars)) {
      up_operations = static_cast<DiffType>((*greater_it) - character);
    } else {
      up_operations = static_cast<DiffType>(available_chars.front() - 'a') +
                      static_cast<DiffType>('z' - character) + 1;
    }

    DiffType down_operations{0};
    if (const auto lower_it =
            std::lower_bound(rbegin(available_chars), rend(available_chars),
                             character, std::greater<char>{});
        lower_it != rend(available_chars)) {
      down_operations = static_cast<DiffType>(character - *lower_it);
    } else {
      down_operations = static_cast<DiffType>('z' - available_chars.back()) +
                        static_cast<DiffType>(character - 'a') + 1;
    }

    min_operations += std::min(up_operations, down_operations);
  }

  std::cout << "Case #" << case_index << ": " << min_operations << std::endl;
  return true;
}

template <typename Error>
void report_error(const char *message, const Error &error) {
  std::cerr << message << " " << error.what();
}

int main(int /*argc*/, char ** /**argv[]*/) {
  std::string input_string;
  if (!std::getline(std::cin, input_string)) {
    std::cerr << "number of test cases is not provided" << std::endl;
    return -1;
  }

  try {
    const auto test_cases_count = std::stoi(input_string);
    for (int i{1}; i <= test_cases_count; ++i) {
      if (!solve_next_case(i)) {
        return -1;
      }
    }
    return 0;
  } catch (const std::invalid_argument &e) {
    report_error("invalid argument", e);
  } catch (const std::out_of_range &e) {
    report_error("out of range", e);
  }
  return -1;
}
