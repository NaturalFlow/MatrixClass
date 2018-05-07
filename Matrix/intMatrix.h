#ifndef INTMATRIX_H_INCLUDED
#define INTMATRIX_H_INCLUDED

#include <functional>
#include <utility>
#include <vector>
class Matrix {
private:
    int** matrix = nullptr;
    unsigned int row=0, column=0;
public:
    Matrix();
    Matrix(unsigned int row,unsigned int column);
    Matrix(const Matrix& m);

    std::pair<unsigned int, unsigned int> dimension();
    std::vector<int> first_diagonal();
    unsigned int rows();
    unsigned int columns();

    bool is_equal(const Matrix& m);
    bool rotate_matrix();
    void transpose();
    bool is_symmetry();
    bool is_identity();

    // Operation in which one of the matrix members;
    void for_each_item(std::function<void(int& item)> lambda);
    void for_each_item_in_row(std::function<void(int& item))> lambda, unsigned int current);
    void for_each_item_in_column(std::function<void(int& item)> lambda, unsigned int current);

    //Acess the matrix using () ,so to acess the second item matrix(0,1)

    Matrix& operator = (const Matrix& m);
    Matrix operator + (const Matrix& m);
    void operator += (const Matrix& m);
    Matrix operator - (const Matrix& m);
    void operator -= (const Matrix& m);
    bool operator == (const Matrix& m);
    int& operator () (unsigned int x, unsigned int y);
    const int& operator()(unsigned int x, unsigned int y) const;

    ~Matrix();
};


#endif // INTMATRIX_H_INCLUDED
