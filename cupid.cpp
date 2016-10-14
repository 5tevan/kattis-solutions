#include <iostream>
#include <vector>

// https://open.kattis.com/problems/cupid

int main()
{
  int people, intervals, languages, loops;

  std::cin >> people >> intervals >> languages;

  std::vector<int> men(people);
  std::vector<int> women(people);
  std::vector<int> matches(intervals);

  for (int i = 0; i < people; i++) {
    std::cin >> men[i];
  }

  for (int i = 0; i < people; i++) {
    std::cin >> women[i];
  }

  for (int i = 0; i < intervals; i++) {
    int intervalStart, intervalEnd;

    std::cin >> intervalStart >> intervalEnd;

    int speakers[1000000] = {};
    int numMatches = 0;

    for (int j = intervalStart; j < intervalEnd + 1; j++) {
      speakers[women[j]] = speakers[women[j]] + 1;
    }

    for (int j = intervalStart; j < intervalEnd + 1; j++) {
      if (speakers[men[j]] > 0) {
        speakers[men[j]] = speakers[men[j]] - 1;
        numMatches++;
      }
    }

    matches[i] = numMatches;

    loops++;
  }

  for (auto const& value: matches) {
    std::cout << value << "\n";
  }

  // std::cout << loops << "\n";

  return 0;
}
