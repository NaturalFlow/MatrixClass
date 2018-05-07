#include <iostream>
#include "intMatrix.h"

using namespace std;

int main() {
    Matrix m1(4,4);
    //Operation over all items in the matrix
    m1.for_each_item([](int& item){item = 1;});
    //Acess
    m1(2,1) = 0;
    Matrix m2(4,4);
    m2.for_each_item([](int& item){item  = 2;});
    m1+=m2;
    //m1.for_each_item([](int& item){cout << item;});
    Matrix m3(3,3);
    m3.for_each_item([](int& item){item = 0;});
    m3 = m1 + m2;
   //cout << m3(2,1) << endl;
    m3 = m1 - m2;
    m3.transpose();
    cout << m1;
    cout << '\n' << m2 << endl;
    m3.print();

    Matrix m4(10,10);
    m4.for_each_item_in_row(0, [](int& item){item =1;});
    m4.for_each_item_in_row(9, [](int& item){item =1;});
    m4.for_each_item_in_column(0, [](int& item){item = 1;});
    m4.for_each_item_in_column(9, [](int& item){item = 1;});
    cout << '\n' << m4 << endl;

    m4*=3;
    cout << m4 << endl;

    m4 = m4+m4;
    cout << m4 << endl;

    Matrix m5(10,10);
    m5 = m2 * m3;
    cout << m5 << endl;
    m5*= m2;
    cout << m2 << endl;
    cout << m5 << endl;

    Matrix mi6(3,3);
    //1 4 1
    //0 6 4
    //0 0 1
    cin >> mi6;
    cout << "upper? " << mi6.is_upper_triangle();

    return 0;
}
