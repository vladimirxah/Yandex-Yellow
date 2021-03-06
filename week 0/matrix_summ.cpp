#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iomanip>

using namespace std;

/*
Предисловие
Если вы не уверены, стоит ли вам сначала пройти наш первый курс, или у вас достаточно знаний, чтобы начать с «Жёлтого пояса», попробуйте решить эту задачу. Если вы не понимаете её условие или не можете быстро решить, скорее всего, вам надо сначала пройти «Белый пояс»

Условие
В этой задаче вам надо разработать класс Matrix для представления целочисленной матрицы. Более подробно класс Matrix должен иметь:

+конструктор по умолчанию, который создаёт матрицу с нулём строк и нулём столбцов
+конструктор от двух целочисленных параметров: num_rows и num_cols, — которые задают количество строк и столбцов матрицы соответственно
+метод Reset, принимающий два целочисленных параметра, которые задают количество строк и столбцов матрицы соответственно
+константный метод At, который принимает номер строки и номер столбца (именно в этом порядке; нумерация строк и столбцов начинается с нуля) и возвращает значение в соответствущей ячейке матрицы
+неконстантный метод At с такими же параметрами, но возвращающий ссылку на значение в соответствущей ячейке матрицы
+константные методы GetNumRows и GetNumColumns, которые возвращают количество строк и столбцов матрицы соответственно

+Если количество строк или количество столбцов, переданное в конструктор класса Matrix или метод Reset, оказалось отрицательным, то должно быть выброшено стандартное исключение out_of_range.

+Это же исключение должен бросать метод At, если переданная в него ячейка выходит за границы матрицы.

Кроме того для класса Matrix должны быть определены следующие операторы:

+оператор ввода из потока istream; формат ввода простой — сначала задаётся количество строк и столбцов (именно в этом порядке), а затем все элементы матрицы: сначала элемент первой строки и первого столбца, затем элемент первой строки и второго столбца и так далее
+оператор вывода в поток ostream; он должен выводить матрицу в том же формате, в каком её читает оператор ввода, — в первой строке количество строк и столбцов, во второй — элементы первой строки, в третьей — элементы второй строки и т.д.
оператор проверки на равенство (==): он должен возвращать true, если сравниваемые матрицы имеют одинаковый размер и все их соответствующие элементы равны между собой, в противном случае он должен возвращать false.
оператор сложения: он должен принимать две матрицы и возвращать новую матрицу, которая является их суммой; если переданные матрицы имеют разные размеры этот оператор должен выбрасывать стандартное исключение invalid_argument.
*/
//-----------------------------
/*Тестирование:
 * 3 5
6 4 -1 9 8
12 1 2 9 -5
-4 0 12 8 6

3 5
5 1 0 -8 23
14 5 -6 6 9
8 0 5 4 1

3 6
5 1 0 -8 23
14 5 -6 6 9
8 0 5 4 1
8 0 5 4 1

*/
//-----------------------------

// Реализуйте здесь
// * класс Matrix
class Matrix {
public:
	// * конструктор по умолчанию, который создаёт матрицу с нулём строк и нулём столбцов
	Matrix () {
//		* пробую с закоментированным "конструктором" по умолчанию
		/*vector<vector<int>> blank;
		matr = blank;*/
	}
//	* конструктор от двух целочисленных параметров: num_rows и num_cols, — которые задают количество строк и столбцов матрицы соответственно
	Matrix (const int& num_rows, const int& num_cols) {
//		* Если количество строк или количество столбцов, переданное в конструктор класса Matrix или метод Reset, оказалось отрицательным, то должно быть выброшено стандартное исключение out_of_range.
		Reset(num_rows, num_cols);
	}
//	* метод Reset, принимающий два целочисленных параметра, которые задают количество строк и столбцов матрицы соответственно
	void Reset (int num_rows, int num_cols) {
//		* Если количество строк или количество столбцов, переданное в конструктор класса Matrix или метод Reset, оказалось отрицательным, то должно быть выброшено стандартное исключение out_of_range.
		if (num_rows < 0 || num_cols < 0) {
			throw out_of_range("Try to reset matrix to negative size");
		}
//		Решение не принималось грейдером без этой строки, выдавал ошибку "unknown signal 6"
		if (num_rows == 0 || num_cols == 0) {
		      num_rows = num_cols = 0;
		    }
			matr.assign(num_rows, vector<int>(num_cols, 0));
//			try to show what i am maked
/*			for (auto i = 0; i < num_rows; i++) {
				for (auto j = 0; j < num_cols; j++) {
					cout << matr[i][j] << " ";
				}
				cout << endl;
			}*/
	}
//	* константный метод At, который принимает номер строки и номер столбца (именно в этом порядке; нумерация строк и столбцов начинается с нуля) и возвращает значение в соответствущей ячейке матрицы
	int At (const int& i, const int& k) const {
/*		if (i > matr.size() || k > matr[i-1].size()) {		//Это же исключение должен бросать метод At, если переданная в него ячейка выходит за границы матрицы.
			throw out_of_range("Try to get num from outside matrix");
		}*/
		return matr.at(i).at(k);
	}
//	* неконстантный метод At с такими же параметрами, но возвращающий ссылку на значение в соответствущей ячейке матрицы
	int& At (const int& i, const int& k) {
/*		if (i > matr.size() || k > matr[i-1].size()) {		//Это же исключение должен бросать метод At, если переданная в него ячейка выходит за границы матрицы.
			throw out_of_range("Try to get link from outside matrix");
		}*/
		return matr.at(i).at(k);
	}
//	* константные методы GetNumRows и GetNumColumns, которые возвращают количество строк и столбцов матрицы соответственно
	int GetNumRows () const {
//		* исключение, если нет ни одной строки
/*		if (matr.size() == 0) {
			throw out_of_range("Have not any rows");
		}*/
		return matr.size();
	}
	int GetNumColumns () const {
//		* исключение, если нет ни одной строки - нет и столбцов
/*		if (matr.size() == 0) {
			throw out_of_range("Have not any columns");
		}*/
		if (matr.empty()) {
			return 0;
		} else {
			return matr[0].size();
		}
	}

private:
	vector<vector<int>> matr;
};

// * оператор ввода для класса Matrix из потока istream
// * оператор ввода из потока istream; формат ввода простой — сначала задаётся количество строк и столбцов (именно в этом порядке), а затем все элементы матрицы: сначала элемент первой строки и первого столбца, затем элемент первой строки и второго столбца и так далее
istream& operator >> (istream& stream, Matrix& m) {
	int i, k;
	stream >> i >> k;
//	try {
		m.Reset(i, k);
//	} catch (out_of_range& o) {
//		cout << o.what() << endl;
//	}
	for (auto ci = 0; ci < i; ci++) {
		for (auto ki = 0; ki < k; ki++) {
			stream >> m.At(ci, ki);
		}
	}
	return stream;
}

// * оператор вывода класса Matrix в поток ostream
// * оператор вывода в поток ostream; он должен выводить матрицу в том же формате, в каком её читает оператор ввода, — в первой строке количество строк и столбцов, во второй — элементы первой строки, в третьей — элементы второй строки и т.д.
ostream& operator << (ostream& stream, const Matrix& m) {
//	try {
	stream << m.GetNumRows() << " " << m.GetNumColumns() << endl;
//	} catch (out_of_range& o) {
//		cout << o.what() << endl;
//	}
	for (auto ci = 0; ci < m.GetNumRows(); ci++) {
		for (auto ki = 0; ki < m.GetNumColumns(); ki++) {
			stream << m.At(ci, ki);
			stream << " ";
		}
		stream << endl;
	}
	return stream;
}

// * оператор проверки на равенство двух объектов класса Matrix
bool operator == (const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumRows() != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns()) {
		return false;
	}
	for (auto ci = 0; ci < lhs.GetNumRows(); ci++) {
		for (auto ki = 0; ki < lhs.GetNumColumns(); ki++) {
			if (lhs.At(ci, ki) != rhs.At(ci, ki)) {
				return false;
			}
		}
	}
	return true;
}

// * оператор сложения двух объектов класса Matrix
Matrix operator + (const Matrix& lhs, const Matrix& rhs) {
  if (lhs.GetNumRows() != rhs.GetNumRows()) {
    throw invalid_argument("Mismatched number of rows");
  }

  if (lhs.GetNumColumns() != rhs.GetNumColumns()) {
    throw invalid_argument("Mismatched number of columns");
  }

  Matrix result(lhs.GetNumRows(), lhs.GetNumColumns());
//	cout << result.GetNumRows() << " " << result.GetNumColumns() << endl;
  for (int row = 0; row < result.GetNumRows(); ++row) {
    for (int column = 0; column < result.GetNumColumns(); ++column) {
      result.At(row, column) = lhs.At(row, column) + rhs.At(row, column);
    }
  }

  return result;
}

int main() {
  Matrix one;
  Matrix two;

/*  string str = "3 5 6 4 -1 9 8 12 1 2 9 -5 -4 0 12 8 6";
  stringstream ss(str);
  ss >> one;
  str = "3 5 5 1 0 -8 23 14 5 -6 6 9 8 0 5 4 1";
	stringstream ss2(str);
	ss2 >> two;*/

/*  string str = "0 0";
	stringstream ss(str);
	ss >> one;
	str = "0 0";
	stringstream ss2(str);
	ss2 >> two;*/
//	cout << two.GetNumRows() << " " << two.GetNumColumns() << endl;
  cin >> one >> two;
  cout << one + two << endl;
  return 0;
}

/// example
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

using namespace std;

class Matrix {
private:
  int num_rows_;
  int num_columns_;

  vector<vector<int>> elements_;

public:
  Matrix() {
    num_rows_ = 0;
    num_columns_ = 0;
  }

  Matrix(int num_rows, int num_columns) {
    Reset(num_rows, num_columns);
  }

  void Reset(int num_rows, int num_columns) {
    if (num_rows < 0) {
      throw out_of_range("num_rows must be >= 0");
    }
    if (num_columns < 0) {
      throw out_of_range("num_columns must be >= 0");
    }
    if (num_rows == 0 || num_colums == 0) {
      num_rows = num_columns = 0;
    }

    num_rows_ = num_rows;
    num_columns_ = num_columns;
    elements_.assign(num_rows, vector<int>(num_columns));
  }

  int& At(int row, int column) {
    return elements_.at(row).at(column);
  }

  int At(int row, int column) const {
    return elements_.at(row).at(column);
  }

  int GetNumRows() const {
    return num_rows_;
  }

  int GetNumColumns() const {
    return num_columns_;
  }
};

bool operator==(const Matrix& one, const Matrix& two) {
  if (one.GetNumRows() != two.GetNumRows()) {
    return false;
  }

  if (one.GetNumColumns() != two.GetNumColumns()) {
    return false;
  }

  for (int row = 0; row < one.GetNumRows(); ++row) {
    for (int column = 0; column < one.GetNumColumns(); ++column) {
      if (one.At(row, column) != two.At(row, column)) {
        return false;
      }
    }
  }

  return true;
}

Matrix operator+(const Matrix& one, const Matrix& two) {
  if (one.GetNumRows() != two.GetNumRows()) {
    throw invalid_argument("Mismatched number of rows");
  }

  if (one.GetNumColumns() != two.GetNumColumns()) {
    throw invalid_argument("Mismatched number of columns");
  }

  Matrix result(one.GetNumRows(), one.GetNumColumns());
  for (int row = 0; row < result.GetNumRows(); ++row) {
    for (int column = 0; column < result.GetNumColumns(); ++column) {
      result.At(row, column) = one.At(row, column) + two.At(row, column);
    }
  }

  return result;
}

istream& operator>>(istream& in, Matrix& matrix) {
  int num_rows, num_columns;
  in >> num_rows >> num_columns;

  matrix.Reset(num_rows, num_columns);
  for (int row = 0; row < num_rows; ++row) {
    for (int column = 0; column < num_columns; ++column) {
      in >> matrix.At(row, column);
    }
  }

  return in;
}

ostream& operator<<(ostream& out, const Matrix& matrix) {
  out << matrix.GetNumRows() << " " << matrix.GetNumColumns() << endl;
  for (int row = 0; row < matrix.GetNumRows(); ++row) {
    for (int column = 0; column < matrix.GetNumColumns(); ++column) {
      if (column > 0) {
        out << " ";
      }
      out << matrix.At(row, column);
    }
    out << endl;
  }

  return out;
}

int main() {
  Matrix one;
  Matrix two;

  cin >> one >> two;
  cout << one + two << endl;
  return 0;
}