#define gcd __gcd

template <typename T>
typename enable_if<is_integral<T>::value, T>::type lcm(T a, T b) {
  return a / gcd(a, b) * b;
}