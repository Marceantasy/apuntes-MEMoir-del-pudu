vector<vector<int>> solveHomogeneousSystemMod2(vector<vector<int>> &A,
                                               int maxSolutions = 1e5) {
  int rows = A.size(), columns = A[0].size();

  int variables = columns - 1;

  vector<int> pivotPosition(rows, -1);

  int pivotRow = 0;

  for (int pivotColumn = 0; pivotColumn < variables && pivotRow < rows;
       pivotColumn++) {
    int pivotIndex = pivotRow;

    while (pivotIndex < rows && A[pivotIndex][pivotColumn] == 0)
      pivotIndex++;

    if (pivotIndex == rows)
      continue;

    swap(A[pivotRow], A[pivotIndex]);

    pivotPosition[pivotRow] = pivotColumn;

    for (int i = 0; i < rows; i++)
      if (i != pivotRow && A[i][pivotColumn] & 1)
        for (int j = pivotColumn; j < columns; j++)
          A[i][j] = A[i][j] ^ A[pivotRow][j];

    pivotRow++;
  }

  vector<bool> isPivot(variables);

  for (int position : pivotPosition) {
    if (position == -1)
      continue;

    isPivot[position] = true;
  }

  vector<int> freeColumns;

  for (int j = 0; j < variables; j++)
    if (!isPivot[j])
      freeColumns.push_back(j);

  if (freeColumns.empty())

    return {vector<int>(variables)};

  vector<vector<int>> solutions;

  for (int freeColumn : freeColumns) {
    vector<int> solution(variables);

    solution[freeColumn] = 1;

    for (int i = 0; i < rows; i++) {
      if (pivotPosition[i] == -1)
        continue;

      int positionColumn = pivotPosition[i];
      solution[positionColumn] = A[i][freeColumn];
    }

    solutions.push_back(solution);

    if (solutions.size() == maxSolutions)
      break;
  }

  return solutions;
}