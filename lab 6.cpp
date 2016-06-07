// lab 6.cpp: определяет точку входа для консольного приложения.
//

	
#include <string> 
#include <stdlib.h> 
#include <iostream> 
#include <sstream> 
#include <iomanip> 
#include <conio.h> 
#include <time.h>
#include <algorithm>
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
	class iterator
	{
	private:
		t** m;
		int stroki, stolbcu;
	public:
		typedef ptrdiff_t difference_type;
		typedef t value_type;
		typedef t* pointer;
		typedef t& reference;
		typedef unsigned sizet_type;
		typedef std::forward_iterator_tag iterator_category;
		iterator(t** a, int b, int c) : m(a), stroki(b),stolbcu(c) {}
		iterator& operator++()
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
		friend bool operator!=(iterator& q, iterator& w) 
		{
		
			return &(*q) != &(*w);
		}
		friend bool operator==(iterator& q, iterator& w)
		{
			
			return &(*q) != &(*w);
		}
	};
	iterator begin()
	{
		return iterator(a, 0, 0);
	}
	iterator end()
	{
		return iterator(a, s1, 0);
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
	//in >> el;
	//stringstream ss;
	//ss << el;	
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



bool les(element& a)
{
	return (a < 30);
}

bool kx(element& a)
{
	return ((2 * a + (-4)) == 0);
}

void pl(element& a)
{
	a = a + 4;
	return;
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

	
	int l;
	for_each(b.begin(), b.end(), pl);//+4
	cout << b;

	l = count(b.begin(), b.end(), 30);
	cout << l << ' ';

	l = count_if(b.begin(), b.end(), kx);
	cout << l << ' ';

	l = count_if(b.begin(), b.end(), les);
	cout << l << ' ';

	auto n = find(b.begin(), b.end(), 20);
	if(n!=b.end())
		cout << "est " << *n;
	else cout << "net";

	system("pause");
	return 0;
}
