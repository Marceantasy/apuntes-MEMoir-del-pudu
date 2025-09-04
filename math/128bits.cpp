#if defined(__LP64__) || defined(_WIN64)
using int128 = __int128;
using uint128 = __uint128_t;
#else
using int128 = ll;
using uint128 = ull;
#endif

template <typename T>
typename enable_if<is_same<T, int128>::value || is_same<T, uint128>::value,
                   istream &>::type
operator>>(istream &is, T &value) {
  string input;
  is >> input;

  value = 0;

  for (char character : input)
    if (isdigit(character))
      value = 10 * value + character - '0';

  if (input[0] == '-')
    value *= -1;

  return is;
}

template <typename T>
typename enable_if<is_same<T, int128>::value || is_same<T, uint128>::value,
                   ostream &>::type
operator<<(ostream &os, T value) {
  string output;

  bool isNegative = value < 0;

  if (isNegative) {
    value *= -1;
    output += '-';
  }

  do {
    output += value % 10 + '0';
    value /= 10;
  } while (value > 0);

  reverse(output.begin() + isNegative, output.end());

  return os << output;
}