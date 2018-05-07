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
    cout <<'\n' << m4;
    return 0;
}
