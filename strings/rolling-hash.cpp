struct RollingHash {
  static const ll BASE = 31;
  static const ll MOD1 = 1e9 + 9, MOD2 = 1e9 + 7, MOD3 = (119LL << 23) | 1;
  const vector<ll> MODS = {MOD1, MOD2, MOD3};

  vector<vector<ll>> prefixes, powers;
  int n;

  RollingHash(const string &text) {
    n = text.size();
    prefixes.assign(3, vector<ll>(n + 2));
    powers.assign(3, vector<ll>(n + 2, 1));

    for (int j = 0; j < 3; j++)
      for (int i = 1; i <= n + 1; i++)
        powers[j][i] = (powers[j][i - 1] * BASE) % MODS[j];

    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < n; i++)
        prefixes[j][i + 1] = (prefixes[j][i] * BASE + text[i]) % MODS[j];

      prefixes[j][n + 1] = (prefixes[j][n] * BASE) % MODS[j];
    }
  }

  tuple<int, int, int> query(int left, int right) {
    vector<int> result(3);

    for (int i = 0; i < 3; i++) {
      ll hash = (prefixes[i][right + 1] -
                 prefixes[i][left] * powers[i][right - left + 1] + MODS[i]) %
                MODS[i];

      if (hash < 0)
        hash += MODS[i];

      result[i] = hash;
    }

    return {result[0], result[1], result[2]};
  }
};
