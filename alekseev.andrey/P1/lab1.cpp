#include <iostream>

namespace alekseev {
  int findAlmostMax();
}

namespace {
  const int invalidInputCode = 1;
  const int internalErrorCode = 2;
  const int minSequenceLength = 2;
}

int alekseev::findAlmostMax()
{
  int x = 0;
  if (!(std::cin >> x)) {
    std::cerr << "Input is not a sequence\n";
    return invalidInputCode;
  }

  if (x == 0) {
    std::cerr << "Sequence is too short\n";
    return internalErrorCode;
  }

  int max1 = x;
  int max2 = 0;
  int count = 1;

  while (true) {
    if (!(std::cin >> x)) {
      std::cerr << "The data cannot be identified as a sequence\n";
      return invalidInputCode;
    }

    if (x == 0) {
      break;
    }

    ++count;

    if (x > max1) {
      max2 = max1;
      max1 = x;
    } else if (count == minSequenceLength || (x > max2 && x < max1)) {
      max2 = x;
    }
  }

  if (count < minSequenceLength) {
    std::cerr << "The second maximum cannot be found\n";
    return internalErrorCode;
  }

  std::cout << max2 << "\n";
  return 0;
}

int main()
{
  return alekseev::findAlmostMax();
}
