template <typename T = double>
typename enable_if<is_floating_point<T>::value>
ternarySearch(function<T(T)> calculate, T left, T right, bool searchMin = true,
              T epsilon = 1e-9) { // [left, right]
  while (right - left > epsilon) {
    T midA = left + (right - left) / 3, midB = right - (right - left) / 3;

    T valueA = calculate(midA), valueB = calculate(midB);

    if (searchMin)
      valueA *= -1, valueB *= -1;

    if (valueA < valueB)
      left = midA;
    else
      right = midB;
  }

  return calculate(left);
}

template <typename T = int>
typename enable_if<is_integral<T>::value>
ternarySearch(function<T(T)> calculate, T left, T right, bool searchMin = true,
              T epsilon = 5) { // [left, right]
  while (right - left > epsilon) {
    T midA = left + (right - left) / 3, midB = right - (right - left) / 3;

    T valueA = calculate(midA), valueB = calculate(midB);

    if (searchMin)
      valueA *= -1, valueB *= -1;

    if (valueA < valueB)
      left = midA;
    else
      right = midB;
  }

  T answer = calculate(left);

  for (T i = left + 1; i <= right; i++) {
    T value = calculate(i);

    if (searchMin)
      answer = min(answer, value);
    else
      answer = max(answer, value);
  }

  return answer;
}
