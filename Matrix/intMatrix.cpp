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

void Matrix::print() const {
    for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = 0; j < column; ++j) {
            std::cout << matrix[i][j] << ((j == column -1) ? '\n' : ' ') ;
        }
    }
}

std::pair<unsigned int, unsigned int> Matrix::dimension() {
    return std::make_pair(row, column);
}

std::vector<int> Matrix::first_diagonal() {
    if(row != column)
        throw std::runtime_error("Must be a Square Matrix to get the diagonal.");
    std::vector<int> diagonal;
    for(unsigned int i = 0; i < row; ++i) {
        diagonal.push_back(matrix[i][i]);
    }


}
unsigned int Matrix::rows() const {
    return row;
}

unsigned int Matrix::columns() const {
    return column;
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
    return true;
}

void Matrix::transpose() {
    Matrix transposed(column,row);
    for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = 0; j < column; ++j) {
            transposed(j,i) = matrix[i][j];
        }
    }
    (*this) = transposed;
}
bool Matrix::is_symmetry() {
    if(row != column)
       return false;
    Matrix transposed(*this);
    transposed.transpose();
    return transposed == (*this);
}

bool Matrix::is_identity() {
    std::vector<int> diagonal = first_diagonal();
    return std::equal(diagonal.begin()+1,diagonal.end(),diagonal.begin());
}

void Matrix::for_each_item(std::function<void(int& item)> lambda) {
    for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = 0; j < column; ++j) {
            lambda(matrix[i][j]);
        }
    }
}

void Matrix::for_each_item_in_row(std::function<void(int& item)> lambda, unsigned int current) {
    if(current >= row)
        throw std::runtime_error("This row do not exist.");
    for(unsigned int i = 0; i < column ; ++i)
        lambda(matrix[current][i]);
}

void Matrix::for_each_item_in_column(std::function<void(int& item)> lambda, unsigned int current) {
    if(current >= column)
        throw std::runtime_error("This column do not exist.");
    for(unsigned int i = 0; i < row ; ++i)
        lambda(matrix[i][column]);
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
Matrix Matrix::operator - (const Matrix& m) {
    if(row != m.row || column != m.column)
        throw std::runtime_error("difference(-) of matrix failed due to their different sizes");

    Matrix result(m.row,m.column);
    for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = 0; j < column; ++j) {
            result(i,j) = matrix[i][j] - m(i,j);
        }
    }
    return result;
}

void Matrix::operator -= (const Matrix& m) {
    if(row != m.row || column != m.column) {
        throw std::runtime_error("difference(-) of matrix failed due to their different sizes");
    }
    for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = 0; j < column; ++j) {
            matrix[i][j] -= m(i,j);
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

int& Matrix::operator()(unsigned int x, unsigned int y) {
    return matrix[x][y];
}

const int& Matrix::operator()(unsigned int x, unsigned int y) const {
    return matrix[x][y];
}

Matrix::~Matrix() {
    for(unsigned int i = 0; i < row; ++i)
        delete [] matrix[i];
    delete [] matrix;
}
