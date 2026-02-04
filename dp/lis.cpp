int find_lis(const vector<int> &a) {
  vector<int> dp;

  for (int i : a) {
    int pos = lower_bound(dp.begin(), dp.end(), i) - dp.begin();

    if (pos == dp.size())
      dp.push_back(i);
    else
      dp[pos] = i;
  }

  return dp.size();
}
