#include <iostream>
#include <stdlib.h>

using namespace std;

class Matrix
{
 int m;
 int n;
 double* data;
public:
 Matrix()
 {
     m=1;
     n=1;
     data = NULL;
 }

 Matrix(int m_, int n_)
 {
     m = m_;
     n = n_;
     data = new double[m*n];
     for(int i=0; i < m*n; i++)
     {
         data[i] = 0;
     }

 }
 ~Matrix()
 {
     delete data;
 }

 Matrix(const Matrix& A)
 {
     m = A.m;
     n = A.n;
     data = new double[n*m];
     for (int i = 0; i < n*m; i++)
         data[i] = A.data[i];
 }


 Matrix operator=(Matrix A)
 {
     m=A.m;
     n=A.n;
    delete data;
     data=new double[m*n];
    for(int i = 0; i < A.getN()*A.getN(); i++)
    {
     set(i,0,A.get(i,0));
    }
    return *this;
 }

 double get(int i, int j)
 {
     return data[i+j*m];
 }

 void set(int i, int j, double d)
 {
     this->data[i+j*m] = d;
 }

 virtual int getN()
 {
     return n;
 }

 virtual int getM()
 {
     return m;
 }

Matrix operator+(Matrix& A)
 {
    if((m!=A.getM())||(n!=A.getN()))
{
        return A;
}
        Matrix* C=new Matrix(getM(),getN());// = Matrix(m,n);
        for(int i = 0; i < m*n; i++)
        {
          C->data[i] = data[i] + A.get(i,0);
        }
    return *C;
 }
 Matrix operator*(Matrix& A)
 {
    if(getM() !=n)
    {
        Matrix* C = new Matrix();
        return *C;
    }
    Matrix B(getN(), m);
    for(int i = 0; i < getN(); i++)
        for(int j = 0; j < m; j++)
            for(int l = 1; l <= n; l++)
            {
                B.data[j*n+i] += get(i,j)*A.data[l*n+j];
            }
    return B;

 }

 Matrix operator*(double& l)
 {
    Matrix* B = new Matrix(m,n);
    for (int i = 0; i < m*n; i++)
    {
        B->data[i] = l*data[i];
    }
    return *B;
 }

 Matrix operator-(Matrix& A)
 {
    if((m!=A.getM())||(n!=A.getN()))
{
        return A;
}
        Matrix* C=new Matrix(getM(),getN());// = Matrix(m,n);
        for(int i = 0; i < m*n; i++)
        {
          C->data[i] = data[i] - A.get(0,i);
        }
    return *C;
 }


Matrix transpose()
 {
   Matrix mat(n,m);
   for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
		 mat.set(i, j, get(j, i));
         return Matrix(mat);
 }

virtual double determinant()
{
    Matrix tmp = *this;
    double k=0;
    int s;
    for(int l = 0; l < getM(); l++)
    {
        if(tmp.get(l,l) == 0)
        {
            s=l+1;
            while(s<getN())
            {
                if(tmp.get(l,s) != 0)
                {
                    for(int z=l;z<getM();z++)
                    {
                        k=-tmp.get(z,l);
                        tmp.set(z,l,tmp.get(z,s));
                        tmp.set(z,s,k);
                    }
                    s=getN();
                }
                s++;
            }
            if(getN()<=s)
                return 0;
        }
        for(int j =l+1; j < getM(); j++) // это строчки
            {
                k = tmp.get(j,l) / tmp.get(l,l);
                for(int i =l+1 ; i < getN(); i++) //это столбцы
                    tmp.set(j,i,tmp.get(j,i)-k*tmp.get(l,i));
            }
    }

    double det = get(0,0);
    for(int i = 1; i < getN(); i++)
      det *=tmp.get(i,i);
    cout << endl<< endl<<det<<endl;
    return det;
}


 virtual Matrix reverse()
{

    if (failed()||(getN()!=getM()))
    {
        Matrix A (0,0);
        return A;
    }
    int g;
    double D =this->determinant();
    if(D == 0)
        {
            Matrix A;
            return A;
        }
   Matrix A(getN(),getN());
   Matrix B(getN()-1,getN()-1);
    for(int k=0; k<getN(); k++)
    {
        for(int l=0; l<getN(); l++)
        {
            g=0;

            for (int i = 0; i < getN(); i++)
            {
                if (i == k) continue;
                if (getN() <= i) break;
                for (int j = 0; j < getN(); j++)
                {
                    if (j == l) continue;
                    if (getN() <= i) break;
                    B.set(g,0,this->get(j,i));
                    cout<<this->get(j,i);
                    g++;
                }
            }
                A.set(l,k,B.determinant()/D);
            }
}
return Matrix(A);

}
 ostream& print(ostream& o)
 {
     for(int i = 0; i < m*n; i++)
     {
         if(i%m == 0) o<<endl;
         o<<data[i]<<" ";
     }
     return o;
 }


 istream& read(istream& o)
 {
     delete data;
     o >> m >> n;
     double* d = new double[m*n];
     data = d;
     for (int i = 0; i < m*n; i++)
     {
         o >> data[i];
     }
     return o;
 }



 bool failed()
 {
     return ((data == NULL) || (n <= 0) || (m <= 0));
 }

};


Matrix* get_init(int n, int m)
{
    Matrix* q = new Matrix(n, m);
            return q;
}
