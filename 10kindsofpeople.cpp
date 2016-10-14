#include <iostream>
#include <queue>
#include <vector>

/*
 * Legend for map:
 *  - 0 is for binary speakers
 *  - 1 is for decimal speakers
 *
 * Movement is allowed only on N,S,E,W directions.
 */

typedef std::vector<bool> Row;

typedef std::vector<Row> Matrix;

typedef struct {
  int row;
  int column;
} Coord;

typedef struct {
  Coord start;
  Coord end;
} Query;

Matrix readMatrix(int rows, int columns)
{
  Matrix matrix(rows, Row(columns));
  char next;
  int row = 0;
  int column = 0;

  std::cin.ignore();

  while (row < rows) {
    std::cin.get(next);

    if (next == '\n') {
      ++row;
      column = 0;
    }
    else {
      matrix[row][column] = next == '1';
      ++column;
    }
  }

  return matrix;
}

Query readNextQuery()
{
  Query query;

  std::cin >> query.start.row
           >> query.start.column
           >> query.end.row
           >> query.end.column;

  // Correct for zero index coords
  query.start.row--;
  query.start.column--;
  query.end.row--;
  query.end.column--;

  return query;
}

void printCoord(Coord c)
{
  std::cout << "Coord ("
            << c.row << "," << c.column
            << ")\n";
}

void printQuery(Query query)
{
  std::cout << "Found query from ("
            << query.start.row << "," << query.start.column
            << ") to ("
            << query.end.row << "," << query.end.column
            << ").\n";
}

void printMatrix(int rows, int columns, Matrix matrix)
{
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      std::cout << matrix[i][j];
    }
    std::cout << "\n";
  }
}

bool pathExists(bool type, Query query, int rows, int columns, Matrix matrix)
{
  if (matrix[query.start.row][query.start.column] != type ||
      matrix[query.end.row][query.end.column] != type) {
    return false;
  }

  if (query.start.row == query.end.row &&
      query.start.column == query.end.column) {
    return true;
  }

  Matrix visited(rows, Row(columns));
  std::queue<Coord> queue;

  queue.push(Coord{query.start.row, query.start.column});
  visited[query.start.row][query.start.column] = true;

  while (queue.empty() == false) {
    Coord current = queue.front();
    queue.pop();

    // printMatrix(rows, columns, visited);

    std::vector<Coord> coords = {
      {current.row + 1, current.column},
      {current.row - 1, current.column},
      {current.row, current.column + 1},
      {current.row, current.column - 1}
    };

    for (auto const& coord: coords) {
      if (coord.row == query.end.row &&
          coord.column == query.end.column) {
        return true;
      }

      if (coord.row >= 0 && coord.row < rows && coord.column >= 0 && coord.column < columns) {
        if (visited[coord.row][coord.column] == false &&
            matrix[coord.row][coord.column] == type) {
          // printCoord(coord);
          visited[coord.row][coord.column] = true;
          queue.push(coord);
        }
      }
    }
  }

  return false;
}

bool binaryPathExists(Query query, int rows, int columns, Matrix matrix)
{
  bool type = false;
  return pathExists(type, query, rows, columns, matrix);
}

bool decimalPathExists(Query query, int rows, int columns, Matrix matrix)
{
  bool type = true;
  return pathExists(type, query, rows, columns, matrix);
}

int main()
{
  int rows, columns, queries;

  std::ios::sync_with_stdio(false);
  std::cin.tie(NULL);

  std::cin >> rows >> columns;

  Matrix map = readMatrix(rows, columns);

  std::cin >> queries;

  for (int i = 0; i < queries; i++) {
    Query query = readNextQuery();

    if (binaryPathExists(query, rows, columns, map))
      std::cout << "binary\n";
    else if (decimalPathExists(query, rows, columns, map))
      std::cout << "decimal\n";
    else
      std::cout << "neither\n";
  }

  return 0;
}
