// lb1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define A -10
#define B 10


class Vector {
private:
	int m_length;
	float* m_arr;

public:
	Vector() {
		m_length = 0;
		m_arr = NULL;
	}

	Vector(int length) {
		if(length > 0) {
			m_length = length;
			m_arr = new float[m_length];
		} else {
			m_length = 0;
			m_arr = NULL;
		}
	}

	Vector(Vector& o) {
		m_length = o.m_length;
		m_arr = new float[m_length];
		for(int i = 0; i < m_length; i++) {
			m_arr[i] = o[i];
		}
	}

	~Vector() {
		if(m_length > 0) delete[] m_arr;
	}

	int getLength() { return m_length; }

	void setRand(int cols) {
		if(m_length > 0) {
			delete[] m_arr;
		}

		m_length = cols;
		m_arr = new float[m_length];
		for(int i = 0; i < m_length; i++) {
			m_arr[i] = (B-A) * (float)rand() / RAND_MAX + A;
		}
	}

	void setWithKeyboard(int cols, int I) {
		if(m_length > 0) {
			delete[] m_arr;
		}

		m_length = cols;
		m_arr = new float[m_length];
		float value;
		for(int i = 0; i < m_length; i++) {
			std::cout << "M[" << I << "][" << i + 1 << "]= ";
			std::cin >> value;
			m_arr[i] = value;
		}
	}

	void setFormula(int cols, float a, float b, int I) {
		if(m_length > 0) {
			delete[] m_arr;
		}

		m_length = cols;
		m_arr = new float[m_length];
		for(int j = 0; j < m_length; j++) {
			m_arr[j] = a * I * sin( (j + 1) + b);
		}
	}


	void print() {
		if(m_length > 0) {
			for(int i = 0; i < m_length; i++) {
				printf("%8.2f ", m_arr[i]);
			}
			printf("\n");
		} else std::cout << "Vector empty\n";
	}


	
	float& operator[] (int index) {
		if(index >= 0 && index < m_length) {
			return m_arr[index];
		} else {
			std::cout << "Overflow... exit!\n";
			getch();
			exit(0);
		}
	}

	
	Vector& operator = (Vector & v) {
		if(&v == this) return *this;

		if(m_length > 0) {
			delete[] m_arr;
		}

		m_length = v.m_length;
		m_arr = new float[m_length];

		for(int i = 0; i < m_length; i++) {
			m_arr[i] = v[i]; 
		}

		return *this;
	}
	
};

class Matrix {
private:
	Vector* m_arr;
	int m_length;

public:
	Matrix() {
		m_length = 0;
		m_arr = NULL;
	}

	~Matrix() {
		if(m_length > 0) delete[] m_arr;
	}

	Matrix(int rows, int cols) {
		if(rows > 0) {
			m_length = rows;
			m_arr = new Vector[m_length];
			if(cols > 0) {
				for(int i = 0; i < m_length; i++) {
					m_arr[i].setRand(cols);				
				}
			}
		} else {
			m_length = 0;
			m_arr = NULL;
		}
	}

	Matrix(int rows, int cols, float a, float b) {
		if(rows > 0) {
			m_length = rows;
			m_arr = new Vector[m_length];
			if(cols > 0) {
				for(int i = 0; i < m_length; i++) {
					m_arr[i].setFormula(cols, a, b, i + 1);
				}
			}			
		} else {
			m_length = 0;
			m_arr = NULL;
		}
	}

	Matrix(int rows, int cols, bool f) {
		if(rows > 0) {
			m_length = rows;
			m_arr = new Vector[m_length];
			if(cols > 0) {
				for(int i = 0; i < m_length; i++) {
					m_arr[i].setWithKeyboard(cols, i + 1);
				}
			}
		} else {
			m_length = 0;
			m_arr = NULL;
		}
	}

	Matrix(Matrix& o) {
		m_length = o.m_length;
		m_arr = new Vector[m_length];
		for(int i = 0; i < m_length; i++) {
			m_arr[i] = o[i];
		}
	}

	void print() {
		if(m_length > 0) {
			for(int i = 0; i < m_length; i++) m_arr[i].print();
		} else std::cout << "Matrix empty\n" << std::endl;
	}

	int getLength() { return m_length; }

	float opredP() {
		float P = 1;
		int i, j, f = 0;
		for(int i = 0; i < m_length; i++) {
			for(int j = 0; j < m_arr[i].getLength(); j++) {
				if(m_arr[i][j] <= 3 && m_arr[i][j] >= -3) {
					if(m_arr[i][j] != 0) {
						P *= m_arr[i][j]; f = 1;
					}
				}
			}
		}

		if(f == 0) P = 0;
		return P;
	}

	void preobr() {
		int i, j;
		float p;
		for(i = 0; i < m_length; i++) {
			if(m_arr[i][0] > 0) {
				p = m_arr[i][0];
				for(j = 0; j < m_arr[i].getLength(); j++) {
					m_arr[i][j] *= p;
				}
			}
		}
	}



	Vector& operator[] (int index) {
		if(index >= 0 && index < m_length) {
			return m_arr[index];
		} else {
			std::cout << "\nOverflow\n";
			getch();
			exit(0);
		}
	}
};

Vector form_vec(Matrix& obj) {
	Vector v(obj.getLength());
	int i, j;
	float sr;
	float min;
	for(i = 0; i < obj.getLength(); i++) {
		min = obj[i][0]; sr = obj[i][0];
		for(j = 0; j < obj[i].getLength(); j++) {
			sr += obj[i][j];
			if(min > obj[i][j]) {
				min = obj[i][j];
			}
		}
		sr /= obj[i].getLength();
		v[i] = sr - min;
	}

	return v;
}


std::ostream& operator << (std::ostream& out, Vector& obj) {
	out << "\nVector:\n";
	for(int i = 0; i < obj.getLength(); i++) {
		out << obj[i] << "  "; 
	}

	out << std::endl;
	return out;
}

std::ostream& operator << (std::ostream& out, Matrix& obj) {
	out << "\nMatrix:\n";
	for(int i = 0; i < obj.getLength(); i++) {
		for(int j = 0; j < obj[i].getLength(); j++) {
			out << obj[i][j] << "  ";
		}
		out << std::endl;
	}

	out << std::endl;
	return out;
}


int _tmain(int argc, _TCHAR* argv[])
{
	Matrix a(7, 5, 4.8, -2.7);
	std::cout << "Matrix a:\n";
	std::cout << a;

	getch();
	return 0;
}
