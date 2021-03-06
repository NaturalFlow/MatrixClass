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

std::vector<int> Matrix::main_diagonal() {
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
bool Matrix::is_anti_symmetry(){
    if(row != column)
       return false;
    Matrix transposed(*this);
    transposed.transpose();
    Matrix opposite(transposed);
    opposite.for_each_item([](int& item){item *= -1;});
    return transposed == opposite;
}
bool Matrix::is_upper_triangle() {
    for(unsigned int i = 1; i < row; ++i) {
        for(unsigned int j = 0; j < i; ++j) {
            if(matrix[i][j] != 0)
                return false;
        }
    }
    return true;
}
bool Matrix::is_lower_triangle(){
     for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = i + j ; j < column; ++j) {
            if(matrix[i][j]  != 0)
                return false;
        }
    }
    return true;
}
bool Matrix::is_identity() {
    std::vector<int> diagonal = main_diagonal();
    return std::equal(diagonal.begin()+1,diagonal.end(),diagonal.begin());
}

void Matrix::for_each_item(std::function<void(int& item)> lambda) {
    for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = 0; j < column; ++j) {
            lambda(matrix[i][j]);
        }
    }
}

void Matrix::for_each_item_in_row(unsigned int current, std::function<void(int& item)> lambda) {
    if(current >= row)
        throw std::runtime_error("This row do not exist.");
    for(unsigned int i = 0; i < column ; ++i)
        lambda(matrix[current][i]);
}

void Matrix::for_each_item_in_column(unsigned int current, std::function<void(int& item)> lambda) {
    if(current >= column)
        throw std::runtime_error("This column do not exist.");
    for(unsigned int i = 0; i < row ; ++i)
        lambda(matrix[i][current]);
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

Matrix Matrix::operator * (const Matrix& m) {
    if(column != m.row)
        throw std::runtime_error("product(*) of matrices failed due to their different sizes");
    Matrix result(row,m.column);
    for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = 0; j < m.column; ++j) {
            for(unsigned int k = 0; k < column; ++k){
                result(i,j) += matrix[i][k] * m(k,j);
            }
        }
    }
    return result;
}

void Matrix::operator *= (const Matrix& m) {
    if(column != m.row)
        throw std::runtime_error("product(*) of matrices failed due to their different sizes");
    Matrix result(row,m.column);
    for(unsigned int i = 0; i < row; ++i) {
        for(unsigned int j = 0; j < m.column; ++j) {
            for(unsigned int k = 0; k < column; ++k){
                result(i,j) += matrix[i][k] * m(k,j);
            }
        }
    }
    (*this) = result;
}
Matrix Matrix::operator * (unsigned int k) {
    for_each_item([&k](int& item){item *= k;});
    return *this;
}

void Matrix::operator *= (unsigned int k) {
    for_each_item([&k](int& item){item *= k;});
}
Matrix Matrix::operator ^ (unsigned int k) {
    if(row != column)
        throw std::runtime_error("Not a square to be power.");
    Matrix result(*this);
    for(unsigned int i = 0; i < k; ++i)
        result.for_each_item([](int& n){n*=n;});
}
void Matrix::operator ^= (unsigned int k){
    if(row != column)
        throw std::runtime_error("Not a square to be power.");
    for(unsigned int i = 0; i < k; ++i)
        for_each_item([](int& n){n*=n;});
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
bool Matrix::operator != (const Matrix& m) {
    return !((*this) == m);
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
