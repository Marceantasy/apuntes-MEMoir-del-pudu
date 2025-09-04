struct Sieve {
  vector<int> primes, smallestFactor;

  Sieve(int n) {
    smallestFactor.resize(n + 1);

    for (ll i = 2; i <= n; i++) {
      if (smallestFactor[i] == 0) {
        smallestFactor[i] = i;
        primes.push_back(i);
      }

      for (ll prime : primes) {
        if (prime * i > n || prime > smallestFactor[i])
          break;

        smallestFactor[prime * i] = prime;
      }
    }
  }

  bool getIsPrime(int n) { return smallestFactor[n] == n; }

  map<int, int> factorize(int n) {
    map<int, int> factors;

    while (n > 1) {
      int factor = smallestFactor[n];

      factors[factor]++;
      n /= factor;
    }

    return factors;
  }
};