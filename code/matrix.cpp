#include<iostream>
using namespace std;

/*
写了一个简易的矩阵类学到了一些东西:
1. C++成员变量初始化方法: 声明时初始化 -> 初始化列表 -> 构造函数

2. 在实现矩阵加法时如果要实现 '整型 + 矩阵类' 的一个操作，那么就需要采用非成员运算符重载函数
   当调用成员运算符重载函数时，调用的那个对象本身就是函数的第一个参数；但使用非成员运算符重载函数
   则需要将参与运算的参数都按顺序写到函数的参数列表中.
   为了让非成员函数也像成员函数一样具有访问私有成员的权限，所以就需要将此非成员函数声明为友元

3. 引用传参 传递进来的参数相对于原始数据的地址不变，不管是否加const
   按值传参 传递进来的参数相对于原始数据的地址要变，不管是否加const(因为有拷贝发生)

*/


class Matrix{
private:
    int row;
    int col;
    int *data;

public:
    Matrix(const int row,const int col);
    Matrix(const Matrix& m1);
    Matrix& operator=(const Matrix& m1);
    Matrix(Matrix&& m1);
    Matrix operator+(const Matrix& m1);
    Matrix operator*(const Matrix& m1);
    // int operator[](int index);
    Matrix operator+(int x);
    friend Matrix operator+(int x,const Matrix&m1);
    void print();
    virtual ~Matrix(){
        delete[] data;
    }
};
//构造函数
Matrix::Matrix(const int row,const int col)
:row{row},col(col)
{
    data = new int[row*col];
    for(int i=0;i<row*col;i++)
    {
        data[i]=0;
    }
}

//复制构造函数
Matrix::Matrix(const Matrix& m1)
{
    row=m1.row;
    col=m1.col;
    data = new int[row*col];
    for(int i=0;i<row*col;i++)
    {
        data[i]=0;
    }
}
//移动构造函数
Matrix::Matrix(Matrix&& m1)
{
    row=m1.row;
    col=m1.col;
    data=m1.data;
    m1.data=nullptr;
}
//赋值构造函数
Matrix&  Matrix::operator=(const Matrix&m1)
{
    if(&m1==this)
      return *this;
    
    row=m1.row;
    col=m1.col;
    data = new int[row*col];
    for(int i=0;i<row*col;i++)
    {
        data[i]=0;
    }
    return *this;
}

//矩阵相加加法运算
Matrix Matrix::operator+(const Matrix& m1)
{
    Matrix res(0,0);
    if(m1.row!=row||m1.col!=col)
    {
        cout<<"shape different!"<<endl;
        return res;
    }
    res.row=row;
    res.col=col;
    res.data = new int[row*col];
    for(int i=0;i<row*col;i++)
    {
        res.data[i] = m1.data[i]+data[i];
    }
    return res;
}
//矩阵加实数
Matrix Matrix::operator+(int x)
{
    Matrix res(row,col);
    for(int i=0;i<row*col;i++)
    {
        res.data[i]=data[i]+x;
    }
    return res;
}
//乘法运算
Matrix Matrix::operator*(const Matrix& m1)
{
    Matrix res(0,0);
    if(col!=m1.row)
    {
        cout<<"shape not match"<<endl;
        return res;
    }
    res.row=row;
    res.col=m1.col;
    res.data=new int[res.col*res.row];

    for(int i=0;i<res.row;i++)
    {
        for(int j=0;j<res.col;j++)
        {
            int cur_sum=0;
            for(int k=0;k<col;k++)
            {
                cur_sum+=data[i*col+k]*m1.data[k*m1.col+j];
            }
            res.data[i*col+j]=cur_sum;
        }

    }
    return res;
}
void Matrix::print()
{
    for(int i=0;i<row*col;i++)
    {
        cout<<data[i]<<" ";
    }
    cout<<endl;
}

//实数+矩阵 以友元函数定义一个非成员函数来实现
Matrix operator+(int x,const Matrix&m1)
{
    Matrix res(m1.row,m1.col);
    for(int i=0;i<m1.row*m1.col;i++)
    {
        res.data[i]=m1.data[i]+x;
    }
    return res;
}
int main()
{
    Matrix matrix1(5,5);
    Matrix matrix2 = matrix1;
    matrix2.print();

    Matrix matrix3 = matrix1+5;
    matrix3.print();

    Matrix matrix4 = 5+matrix2;
    matrix4.print();
}