/*
C++实现矩阵类
用于总结类中常见的方法～
*/



#include<iostream>
#include<vector>

using namespace std;

class Matrix{
    public:
      Matrix(int m=1,int n=1):m(m),n(n)
      {
         cout<<"init function"<<endl;
         data = new double[m*n];
         for(int i=0;i<m*n;i++)
            data[i]=0.0;
      }
      //复制构造函数
      Matrix(const Matrix &matrix)
      {
         cout<<"copy init function"<<endl;
         this->m=matrix.m;
         this->n=matrix.n;
         cout<<m<<" "<<n<<endl;
         data = new double[matrix.m*matrix.n];
         for(int i=0;i<m*n;i++)
         {
            data[i]=0.0;
         }
      }
      //移动构造函数
      Matrix(Matrix&& matrix)
      {
         this->m=matrix.m;
         this->n=matrix.n;
         this->data=matrix.data;
         matrix.data=nullptr;
      }
      //赋值运算符重载
      

      double get_item(int i)const{
         return data[i];
      }
      double get_m()const{
        return this->m;
      }
      double get_n()const{
        return this->n;
      }

      virtual ~Matrix()
      {
        cout<<"delete function"<<endl;
        delete[] data;
      }

    //重载+运算符: Matrix+Matrix
    Matrix operator+(Matrix matirx){
        if(matrix.m!=m||matirx.n!=n)
        {
            cout<<"shape error!"<<endl;
            return nullptr;
        }
        Matrix res(m,n);
        for(int i=0;i<m*n;i++)
        {
            res.data[i]=data[i]+matirx.data[i];
        }
        return res;
      }
    //重载+运算符: Matrix+double
    Matrix operator+(double x)
    {
        Matrix res(m,n);
        for(int i=0;i<m*n;i++)
        {
            res.data[i]=data[i]+x;
        }
    }

    // 重载[]运算符: Matrix[i][j]
    double& operator[](int i,int j);
    private:
      double *data;
      int m;
      int n;

};

double& Matrix::operator[](int i,int j)
{

}
