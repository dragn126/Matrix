#include <iostream>
using namespace std;

class Matrix
{
protected:
	int n;
	int m;
	double* data;
public:
	Matrix()
	{
		n = 0;
		m = 0;
		data = NULL;
	}
	Matrix(int _m, int _n)
	{
		m = _m;
		n = _n;
		data = new double[n*m];
		for (int i = 0;i<n*m;i++)
		{
			data[i] = 0;
		}
	}
	Matrix(int _m, int _n, double*  _data)
	{
		m = _m;
		n = _n;
		data = new double[n*m];
		for (int i = 0;i<n*m;i++)
		{
			data[i] = _data[i];
		}
	}
	Matrix(const Matrix& a)
	{
		data = new double[a.n*a.m];
		n = a.n;
		m = a.m;
		if (a.data != NULL)
		{
			for (int i = 0; i < n*m; i++)
				data[i] = a.data[i];
		}
		else
		{
			data = NULL;
		}
	}
	Matrix operator = (Matrix a)
	{
		if (data != NULL)
		{
			delete data;
		}
		data = new double[a.n*a.m];
		n = a.n;
		m = a.m;
		if (a.data != NULL)
		{
			for (int i = 0; i < n*m; i++)
				data[i] = a.data[i];
		}
		else
		{
			data = NULL;
		}
		return *this;
	}
	~Matrix()
	{
		delete[] data;
	}
	bool failed()
	{
		return (n <= 0 || m <= 0 || data == NULL);
	}
	Matrix operator + (Matrix a)
	{
		Matrix c;
		if (n == a.n && m == a.m && !(failed()) && !(a.failed()))
		{
			c = Matrix(n, m);
			for (int i = 0; i < n*m; i++)
			{
				c.data[i] = data[i] + a.data[i];
			}
		}
		return Matrix(c);
	}
	Matrix operator * (double a)
	{
		Matrix c;
		if (!(failed()))
		{
			c = Matrix(n, m);
			for (int i = 0; i < m*n; i++)
			{
				c.data[i] = data[i] * a;
			}
		}
		return Matrix(c);
	}
	Matrix operator -(Matrix a)
	{
		if (n == a.n && m == a.m && !(failed()) && !(a.failed()))
		{
			return *this + a*(-1);
		}
		else
		{
			Matrix c(0, 0, NULL);
			return c;
		}
	}
	double get(int i, int j)const
	{
		return data[i + j*n];
	}
	void set(int i, int j, double _data)
	{
		data[i + j*n] = _data;
	}
	int getM()
	{
		return n;
	}
	int getN()
	{
		return m;
	}
	Matrix operator * (Matrix a)
	{
		Matrix c;
		if (!(failed()) && !(a.failed()) && m == a.n)
		{
			c = Matrix(n, a.m);
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < a.m; j++)
				{
					double tmp = 0;
					for (int k = 0; k < a.n; k++)
					{
						tmp += get(k, i) * a.get(j, k);
					}
					c.set(j, i, tmp);
				}
			}
		}
		return Matrix(c);
	}
	Matrix GetMinor_(int i, int j)
	{
		Matrix c;
		if (n != 1 && m != 1 && !(failed()))
		{
			c = Matrix(n - 1, m - 1);
			for (int z = 0; z < i; z++)
			{
				for (int x = 0; x < j; x++)
				{
					c.set(x, z, get(x, z));
				}
				for (int y = j + 1; y < m; y++)
				{
					c.set(y - 1, z, get(y, z));
				}
			}
			for (int k = i + 1; k < n; k++)
			{
				for (int l = 0; l < j; l++)
				{
					c.set(l, k - 1, get(l, k));
				}
				for (int h = j + 1; h < m; h++)
				{
					c.set(h - 1, k - 1, get(h, k));
				}
			}
		}
		return Matrix(c);
	}
	double determinant()
	{
		if (n != m || failed())
			return 0;
		if (n == 1)
			return data[0];
		double det = 0;
		for (int i = 0; i < n; i++)
			det = det + powf(-1, i)*data[i] * GetMinor_(0, i).determinant();
		return det;
	}
	Matrix transpose()
	{
		Matrix c;
		if (!(failed()))
		{
			c = Matrix(n, m);
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < m; j++)
				{
					c.set(i, j, this->get(j, i));
				}
			}
		}
		return Matrix(c);
	}
	Matrix reverse()
	{
		if (failed())
			return *this;
		double det = determinant();
		if (det == 0)
			return *this;
		Matrix c(n, m, new double[n*m]);
		for (int j = 0; j < n; j++)
			for (int i = 0; i < m; i++)
			{
				c.set(j, i, powf(-1, i + j) * GetMinor_(j, i).determinant());
			}
		c = c*pow(det, -1);
		return Matrix(c);
	}
	friend istream& operator >>(istream &i, Matrix& a);
	friend ostream& operator <<(ostream &o, Matrix& a);
	void read(istream &i)
	{
		i >> m;
		i >> n;
		data = new double[m*n];
		for (int j = 0; j < m*n; j++)
			i >> data[j];
	}
	void print(ostream &o)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				o << get(j, i) << '\t';
			}
			o << '\n' << endl;
		}
	}
};
Matrix* get_init(int m, int n)
{
	return new Matrix(n, m, new double[n*m]);
}
istream& operator >>(istream &i, Matrix& a)
{
	i >> a.m;
	i >> a.n;
	a.data = new double[a.m*a.n];
	for (int j = 0; j < a.m*a.n; j++)
		i >> a.data[j];
	return i;
}
ostream& operator <<(ostream &o, Matrix& a)
{
	for (int i = 0; i < a.n; i++)
	{
		for (int j = 0; j < a.m; j++)
		{
			o << a.get(j, i) << '\t';
		}
		o << '\n' << endl;
	}
	return o;
}
