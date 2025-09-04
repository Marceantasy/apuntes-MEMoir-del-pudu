struct Mod2System {
  vector<vector<int>> matrix;
  int rows, columns, variables;
  vector<int> pivotPosition, freeColumns;

  Mod2System(vector<vector<int>> matrixTosolve) {
    matrix = matrixTosolve;
    rows = matrix.size();
    columns = (rows > 0 ? matrix[0].size() : 0);
    variables = columns - 1;

    pivotPosition = vector<int>(rows, -1);

    int pivotRow = 0;
    for (int pivotColumn = 0; pivotColumn < variables && pivotRow < rows;
         pivotColumn++) {
      int pivotIndex = pivotRow;

      while (pivotIndex < rows && matrix[pivotIndex][pivotColumn] == 0)
        pivotIndex++;

      if (pivotIndex == rows)
        continue;

      swap(matrix[pivotRow], matrix[pivotIndex]);
      pivotPosition[pivotRow] = pivotColumn;

      for (int i = 0; i < rows; i++)
        if (i != pivotRow && (matrix[i][pivotColumn] & 1))
          for (int j = pivotColumn; j < columns; j++)
            matrix[i][j] = matrix[i][j] ^ matrix[pivotRow][j];

      pivotRow++;
    }

    vector<bool> isPivot(variables);

    for (int position : pivotPosition)
      if (position != -1)
        isPivot[position] = true;

    for (int j = 0; j < variables; j++)
      if (!isPivot[j])
        freeColumns.push_back(j);
  }

  vector<int> findOneSolution() {
    vector<int> solution(variables);

    if (freeColumns.empty())
      return solution;

    solution[freeColumns[0]] = 1;

    for (int i = 0; i < rows; i++) {
      if (pivotPosition[i] == -1)
        continue;

      int position = pivotPosition[i];
      solution[position] = matrix[i][freeColumns[0]];
    }

    return solution;
  }

  vector<vector<int>> findSolutions(int maxSolutions = 1e5) {
    if (freeColumns.empty())
      return {vector<int>(variables)};

    vector<vector<int>> solutions;

    for (int freeColumn : freeColumns) {
      vector<int> solution(variables);
      solution[freeColumn] = 1;

      for (int i = 0; i < rows; i++) {
        if (pivotPosition[i] == -1)
          continue;

        int pivotCol = pivotPosition[i];
        solution[pivotCol] = matrix[i][freeColumn];
      }

      solutions.push_back(solution);

      if (solutions.size() == maxSolutions)
        break;
    }

    return solutions;
  }

  bool isTrivial(vector<int> &solution) {
    return count(solution.begin(), solution.end(), 1) == 0;
  }

  bool onlyHasTrivialSolution() {
    if (freeColumns.empty())
      return true;

    vector<int> solution = findOneSolution();

    return isTrivial(solution);
  }
};