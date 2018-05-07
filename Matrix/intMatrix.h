#ifndef INTMATRIX_H_INCLUDED
#define INTMATRIX_H_INCLUDED

#include <functional>
#include <utility>
#include <vector>
#include <iostream>

class Matrix {
private:
    int** matrix = nullptr;
    unsigned int row = 0, column = 0;
public:
    Matrix();
    Matrix(unsigned int row,unsigned int column);
    Matrix(const Matrix& m);
    void print() const;

    std::pair<unsigned int, unsigned int> dimension();
    std::vector<int> first_diagonal();
    unsigned int rows()const;
    unsigned int columns()const;

    bool is_equal(const Matrix& m);
    bool rotate_matrix();
    void transpose();
    bool is_symmetry();
    bool is_anti_symmetry();
    bool is_identity();
    bool is_top_triangle();
    bool is_bottom_triangle();

    // Operation in which one of the matrix members;
    void for_each_item(std::function<void(int& item)> lambda);
    void for_each_item_in_row(unsigned int current, std::function<void(int& item)> lambda);
    void for_each_item_in_column(unsigned int current, std::function<void(int& item)> lambda);

    //Acess the matrix using () ,so to acess the second item matrix(0,1)

    Matrix& operator = (const Matrix& m);
    Matrix operator + (const Matrix& m);
    void operator += (const Matrix& m);
    Matrix operator - (const Matrix& m);
    void operator -= (const Matrix& m);
    bool operator == (const Matrix& m);
    Matrix operator * (const Matrix& m);
    void operator *= (const Matrix& m);
    int& operator () (unsigned int x, unsigned int y);
    const int& operator()(unsigned int x, unsigned int y) const;
    friend std::ostream & operator << (std::ostream& out, const Matrix& object) {
        object.print();
        return out;
    };
    friend std::istream & operator >> (std::istream& in,  Matrix& object) {
        for(unsigned int i = 0; i < object.rows(); ++i) {
            for(unsigned int j = 0; j < object.columns(); ++j) {
                in >> object(i, j);
            }
        }
        return in;
    };
    ~Matrix();
};


#endif // INTMATRIX_H_INCLUDED
