#include "intMatrix.h"
Matrix::Matrix() {}

Matrix::Matrix(unsigned int row, unsigned int column) {
    matrix = new int*[row];
    for(unsigned int i = 0; i < row; ++i)
        matrix[i] = new int[column]();
    this->row = row;
    this->column = column;
}

Matrix::Matrix(const Matrix& m) {
    matrix = new int*[m.row];
    for(unsigned int i = 0; i < m.column; ++i)
        matrix[i] = new int[m.column]();
    row = m.row;
    column = m.column;
    for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = 0; j < column; ++i) {
            matrix[i][j] = m(i,j);
        }
    }
}

std::pair<unsigned int, unsigned int> Matrix::dimension() {
    return std::make_pair(row, column);
}

bool Matrix::rotate_matrix() {
    if(row != column)
        return false;
    int currentLevel = 0;
	int last = column -1;
	int totalLevel = column/ 2;

	while (currentLevel < totalLevel) {
		for (unsigned short i = 0; i < last; ++i) {
			std::swap(matrix[currentLevel][i], matrix[i][last]);
			std::swap(matrix[currentLevel][i], matrix[last][last - i + currentLevel]);
			std::swap(matrix[currentLevel][i], matrix[last - i + currentLevel][currentLevel]);
		}
		++currentLevel;
		--last;
    }
}

bool Matrix::is_equal(const Matrix& m) {
    if(row != m.row || column != m.column)
        return false;
    for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = 0; j < column ; ++j) {
            if(matrix[i][j] != m(i,j))
                return false;
        }
    }
    return true;
}

int& Matrix::operator()(unsigned int x, unsigned int y) {
    return matrix[x][y];
}

const int& Matrix::operator()(unsigned int x, unsigned int y) const {
    return matrix[x][y];
}

Matrix& Matrix::operator = (const Matrix& m) {
    if(&m == this)
        return *this;
    for(unsigned int i = 0; i < column; ++i)
        delete [] matrix[i];
    delete [] matrix;

    matrix = nullptr;
    matrix = new int*[m.row];
    for(unsigned int i = 0; i < m.row; ++i)
        matrix[i] = new int[m.column]();
    row = m.row;
    column = m.column;

    for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = 0; j < column; ++j) {
            matrix[i][j] = m(i,j);
        }
    }
    return *this;
}

Matrix Matrix::operator + (const Matrix& m) {
    if(row != m.row || column != m.column)
        throw std::runtime_error("sum(+) of matrix failed due to their different sizes");

    Matrix result(m.row,m.column);
    for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = 0; j < column; ++j) {
            result(i,j) = matrix[i][j] + m(i,j);
        }
    }
    return result;
}

void Matrix::operator += (const Matrix& m) {
    if(row != m.row || column != m.column) {
        throw std::runtime_error("sum(+) of matrix failed due to their different sizes");
    }
    for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = 0; j < column; ++j) {
            matrix[i][j] += m(i,j);
        }
    }
}

bool Matrix::operator == (const Matrix& m) {
    if(row != m.row || column != m.column)
        return false;
    for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = 0; j < column ; ++j) {
            if(matrix[i][j] != m(i,j))
                return false;
        }
    }
    return true;

}

void Matrix::for_each_item(std::function<void(int& m)> lambda) {
    for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = 0; j < column; ++j) {
            lambda(matrix[i][j]);
        }
    }
}

void Matrix::for_each_item(std::function<void(int& m)> lambda, unsigned int x, unsigned int y) {
    for(unsigned int i = 0; i < x; ++i) {
        for(unsigned int j = 0; j < y; ++j) {
            lambda(matrix[i][j]);
        }
    }
}

Matrix::~Matrix() {
    for(unsigned int i = 0; i < row; ++i)
        delete [] matrix[i];
    delete [] matrix;
}
