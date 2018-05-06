#ifndef INTMATRIX_H_INCLUDED
#define INTMATRIX_H_INCLUDED

#include <functional>
#include <utility>

class Matrix {
private:
    int** matrix = nullptr;
    unsigned int row=0, column=0;
public:
    Matrix();
    Matrix(unsigned int row,unsigned int column);
    //Copy construct
    Matrix(const Matrix& m);
    std::pair<unsigned int, unsigned int> dimension();

    bool is_equal(const Matrix& m);
    bool rotate_matrix();
    bool transpose();
    bool is_symmetry();


    // Operation in which one of the matrix members;
    void for_each_item(std::function<void(int& m)> lambda);
    // for each item until x y
    void for_each_item(std::function<void(int& m)> lambda, unsigned int x, unsigned int y);
    // x=row y=column
    //Acess the matrix using () so to acess the second item matrix(0,1)
    Matrix& operator = (const Matrix& m);
    Matrix operator + (const Matrix& m);
    void operator += (const Matrix& m);
    bool operator == (const Matrix& m);
    int& operator () (unsigned int x, unsigned int y);
    const int& operator()(unsigned int x, unsigned int y) const;
    ~Matrix();
};


#endif // INTMATRIX_H_INCLUDED
