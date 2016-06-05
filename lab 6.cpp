// lab 6.cpp: определяет точку входа для консольного приложения.
//

	
#include <string> 
#include <stdlib.h> 
#include <iostream> 
#include <sstream> 
#include <iomanip> 
#include <conio.h> 
#include <time.h>
using namespace std;

const int modul = 100;

class element
{
protected:
	int data;
public:
	element(int a = 0)
	{
		data = a%modul;
	}
	friend element operator+(const element& s1, const element& s2);
	friend element operator+(element& s1, int s2);
	friend bool operator==(element& s1, int s2);
	friend bool operator<(element& s1, int s2);
	friend element operator*(const element& s1, const element& s2);
	friend ostream& operator << (ostream& out, element const& a);
	friend istream& operator >> (istream& in, element& a);
};

element operator+(const element& s1, const element& s2)
{
	int q = s1.data + s2.data;
	element a(q);
	return a;
}
element operator*(const element& s1, const element& s2)
{
	int q = s1.data * s2.data;
	element a(q);
	return a;
}
bool operator==(element& s1, int s2)
{
	if (s1.data == s2)
		return 1;
	else return 0;
}
bool operator<(element& s1, int s2)
{
	if (s1.data < s2)
		return 1;
	else return 0;
}
element operator+(element& s1, int s2)
{
	int q = s1.data + s2;
	element a(q);
	return a;
}
ostream& operator << (ostream& out, element const& a)
{
	out << a.data;
	return out;
}
istream& operator >> (istream& in, element& a)
{
	string el;
	in >> el;
	stringstream ss;
	ss << el;
	ss >> a.data;
	return in;
}

template<typename t, int s1, int s2>
class matrix
{
protected:
	t** a;
public:
	matrix(t** dv = 0)
	{
		a = new t*[s1];
		for (int i = 0;i < s1; i++)
		{
			a[i] = new t[s2];
		}
		for (int i = 0;i < s1; i++)
		{
			for (int j = 0;j < s2; j++)
			{
				if (dv != 0)
				{
					a[i][j] = dv[i][j];
				}
				else a[i][j] = 0;
			}
		}
	}
	t poluch(int c, int b)
	{

		return a[c][b];
	}
	void vstav(int c, int b, t d)
	{
		a[c][b] = d;
		return;
	}
	matrix<t, s1, s2> operator+(const matrix<t, s1, s2>& s)
	{
		matrix<t, s1, s2> q;
		for (int i = 0;i < s1; i++)
		{
			for (int j = 0;j < s2; j++)
			{
				q.a[i][j] = a[i][j] + s.a[i][j];
			}
		}
		return q;
	}
	template<int p>
	matrix<t, s1, s2 + p> operator|(const matrix<t, s1, p>& s)
	{
		matrix<t, s1, s2 + p> q;
		for (int i = 0;i < s1; i++)
		{
			for (int j = 0;j < (s2 + p); j++)
			{
				if (j < s2)
				{
					q.a[i][j] = a[i][j];
				}
				else q.a[i][j] = s.a[i][j - s2];
			}
		}
		return q;
	}
	matrix<t, s1, s2> povorot(void)
	{
		matrix<t, s1, s2> q;
		for (int i = 0; i<s1;i++)
		{
			for (int j = 0; j < s2;j++)
			{
				q.a[j][s1 - 1 - i] = a[i][j];
			}
		}
		return q;
	}
	class itterator
	{
	private:
		t** m;
		int stroki, stolbcu;
	public:
		itterator(t** a, int b, int c) : m(a), stroki(b),stolbcu(c) {}
		itterator& operator++()
		{
			stolbcu += 1;
			if (stolbcu == s2)
			{
				stolbcu = 0;
				stroki += 1;
			}
			return *this;
		}
		t& operator*()
		{
			return m[stroki][stolbcu];
		}
		t& operator->()
		{
			return &(m[stroki][stolbcu]);
		}
		friend bool operator!=(itterator& q, itterator& w) 
		{
			
			return &(*q) != &(*w);
		}
	};
	itterator begin()
	{
		return itterator(a, 0, 0);
	}
	itterator end()
	{
		return itterator(a, s1, 0);
	}
	
	template<typename t, int s1, int s2>
	friend ostream& operator << (ostream& out, matrix<t, s1, s2> const& a);
	template<typename t, int s1, int s2>
	friend istream& operator >> (istream& in, matrix<t, s1, s2>& a);
};

template<typename t, int s1, int s2>
ostream& operator << (ostream& out, matrix<t,s1,s2> const& a)
{
	for (int i = 0;i < s1; i++)
	{
		for (int j = 0;j < s2; j++)
		{
			out << ' ' << a.a[i][j];
		}
		out << endl;
	}
	return out;
}

template<typename t, int s1, int s2>
istream& operator >> (istream& in, matrix<t, s1, s2>& a)
{
	string el;

	for (int i = 0;i < s1; i++)
	{
		for (int j = 0;j < s2; j++)
		{
			in >> el;
			stringstream ss;
			ss << el;
			ss >> a.a[i][j];
		}
	}
	return in;
}

int main()
{
	srand(time(NULL));
	element** a;
	a = new element*[5];
	for (int i = 0;i < 5; i++)
	{
		a[i] = new element[5];
	}
	for (int i = 0;i < 5; i++)
	{
		for (int j = 0;j < 5; j++)
		{
			a[i][j] = rand();
		}
	}

	matrix<element, 5, 5> b(a);
	cout << "prost" << endl << b;

	b = b + b;
	cout << "plus" << endl << b;

	for (auto i = b.begin();i != b.end();++i)
	{
		cout << '!' << *i;
	}
	cout << endl;

	int h;
	cin >> h;
	for (auto i = b.begin();i != b.end();++i)
	{
		*i = *i + h;
	}
	cout << b;

	int l=0;
	cin>>h;
	for (auto i = b.begin();i != b.end();++i)
	{
		if (*i == h)
			l++;
	}
	cout << l << endl;

	l = 0;
	cin >> h;
	for (auto i = b.begin();i != b.end();++i)
	{
		if (*i < h)
			l++;
	}
	cout << l << endl<<"vvedite: kx+b=0"<<endl;

	cin >> h >> l;
	float d = (-l / h);
	l = 0;
	for (auto i = b.begin();i != b.end();++i)
	{
		if (*i == d)
			l++;
	}
	cout << l << endl;
	system("pause");
	return 0;
}
