#include <iostream>
#include <fstream>


template <typename T> class Matrix;
template <typename T>
std::ostream& operator << (std::ostream& os, const Matrix<T>& obj)
{
	for (int i = 0; i < obj.ROW; i++)
	{
		for (int j = 0; j < obj.COL; j++)
			os << obj.matrix[i][j] << " ";
		std::cout << std::endl;
	}
	os << std::endl;
	return os;
}



template <typename T>
std::istream& operator >> (std::istream& is, Matrix<T>& obj)
{
	std::cout << "Enter the number of rows: ";
	is >> obj.ROW;
	std::cout << "Enter the number of columns: ";
	is >> obj.COL;

	obj.matrix = new T * [obj.ROW];
	for (int i = 0; i < obj.ROW; i++)
		obj.matrix[i] = new T[obj.COL];

	for (int i = 0; i < obj.ROW; i++)
		for (int j = 0; j < obj.COL; j++)
			is >> obj.matrix[i][j];

	return is;
}

template <typename T> 
class Matrix
{
public:
	
	Matrix()
	{
		this->ROW = 0;
		this->COL = 0;
		this->matrix = nullptr;
	}

	Matrix(int ROW, int COL)
	{
		this->ROW = ROW;
		this->COL = COL;
		this->matrix = new T*[ROW];
		for (int i = 0; i < ROW; i++)
		{
			std::cout << "Enter the " << i+1 << " line: ";
			this->matrix[i] = new T[COL];
			for (int j = 0; j < COL; j++)
				std::cin >> this->matrix[i][j];
			std::cout << std::endl;
		}
	}

	Matrix(const Matrix& other)
	{
		this->matrix = new T* [other.ROW];
		for (int i = 0; i < other.COL; i++)
		{
			this->matrix[i] = new T[other.COL];
			for (int j = 0; j < other.COL; j++)
				this->matrix[i][j] = other.matrix[i][j];
		}
		this->ROW = other.ROW;
		this->COL = other.COL;
	}

	~Matrix()
	{
		for (int i = 0; i < this->ROW; i++)
			delete[] this->matrix[i];
		delete[] this->matrix;
	}

	Matrix& operator =(const Matrix& other)
	{
		if (this->matrix != nullptr)
		{
			for (int i = 0; i < this->ROW; i++)
				delete[] this->matrix[i];
			delete[] this->matrix;
		}

		this->matrix = new T* [other.ROW];
		for (int i = 0; i < other.ROW; i++)
		{
			this->matrix[i] = new T[other.COL];
			for (int j = 0; j < other.COL; j++)
				this->matrix[i][j] = other.matrix[i][j];
		}
		this->ROW = other.ROW;
		this->COL = other.COL;

		return *this;
	}

	Matrix operator +(const Matrix& other)
	{
		if (this->ROW != other.ROW && this->COL != other.COL)
			throw std::string("Operator + error! Not equal size of matrixes.");
		Matrix temp;
		temp.matrix = new T* [other.ROW];
		for (int i = 0; i < other.ROW; i++)
		{
			temp.matrix[i] = new T[other.COL];
			for (int j = 0; j < other.COL; j++)
				temp.matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
		}
		temp.ROW = other.ROW;
		temp.COL = other.COL;

		return temp;
	}

	Matrix& operator +=(const Matrix& other)
	{
		if (this->ROW != other.ROW && this->COL != other.COL)
			throw std::string("Operator += error! Not equal size of matrixes.");
		Matrix temp = this->operator+(other);
		this->operator=(temp);

		return *this;
	}

	int det()
	{
		int temp = 0;
		if (this->COL != this->ROW)
			return -1;
		else if (this->COL == 3)
			for (int i = 0; i < this->ROW; i++)
			{
				temp += this->matrix[i][0] * (this->matrix[(i + 1) % 3][1] * this->matrix[(i + 2) % 3][2] -
					this->matrix[(i + 1) % 3][2] * this->matrix[(i + 2) % 3][1]);
			}
		else if (this->COL == 2)
			temp = this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] * this->matrix[1][0];
		else
			return this->matrix[0][0];
		return temp;
	}

	Matrix operator *(int val)
	{
		Matrix temp;
		temp.matrix = new T* [this->ROW];
		for (int i = 0; i < this->ROW; i++)
		{
			temp.matrix[i] = new T[this->COL];
			for (int j = 0; j < this->COL; j++)
				temp.matrix[i][j] = this->matrix[i][j]*val;
		}
		return temp;
	}

	Matrix& operator *=(int val)
	{
		Matrix temp = this->operator*(val);
		this->operator=(temp);
		return *this;

	}

	Matrix operator *(const Matrix& other)
	{
		if (this->COL != other.ROW)
			throw std::string("Operator * error! Not equal value of columns and rows.");
		Matrix temp;
		temp.ROW = this->ROW;
		temp.COL = other.COL;
		temp.matrix = new int* [this->ROW];
		for (int i = 0; i < this->ROW; i++)
		{
			temp.matrix[i] = new int[other.COL];
			for (int j = 0; j < other.COL; j++)
				temp.matrix[i][j] = 0;
		}
		for (int i = 0; i < this->ROW ; i++)
			for (int j = 0; j < other.COL ; j++)
				for (int k = 0; k < other.ROW; k++)
					temp.matrix[i][j] += this->matrix[i][k] * other.matrix[k][j];

		return temp;
	}

	Matrix& operator *=(const Matrix& other)
	{
		if (this->COL != other.ROW)
			throw std::string("Operator *= error! Not equal value of columns and rows.");
		Matrix temp = this->operator*(other);
		this->operator=(temp);

		return *this;
	}

	Matrix& operator ++()
	{
		for (int i = 0; i < this->ROW; i++)
			for (int j = 0; j < this->COL; j++)
				this->matrix[i][j]++;
		return *this;
	}

	Matrix& operator ++(int value)
	{
		Matrix temp(*this);
		for (int i = 0; i < this->ROW; i++)
			for (int j = 0; j < this->COL; j++)
				this->matrix[i][j]++;
		return temp;
	}

	int* operator [](const int index)
	{
		return this->matrix[index];
	}

	

private:
	int ROW;
	int COL;
	T** matrix;

	template <typename T1>friend std::ostream& operator <<(std::ostream&, const Matrix<T1>&);
	template <typename T1>friend std::istream& operator >>(std::istream& , Matrix<T1>& );
};




int main()
{
	try {

		/*Matrix<int> a(2,2);
		Matrix<int> b(2,1);*/
		Matrix<char> c;
		std::cin >> c;
		std::cout << std::endl << c;
	}
	catch (std::string msg) {
		std::cout << msg;
	}
	catch (...) {
		std::cout << "unknown error";
	}
	return 0;

}
