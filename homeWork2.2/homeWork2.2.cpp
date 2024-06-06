#include <iostream>
#include <stdlib.h>


class Matrix
{
public:
	Matrix(int row, int col)
	{
		this->data = new int* [row];
		for (int i = 0; i < row; i++)
			this->data[i] = new int[col];
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				srand((col+i+j)%100);
				this->data[i][j]=rand()%100;
			}
		}
		this->row = row;
		this->col = col;
	}

	Matrix(const Matrix& other)
	{
		this->data = new int* [other.row];
		for (int i = 0; i < other.row; i++)
			this->data[i] = new int[other.col];

		for (int i = 0; i < other.row; i++)
			for (int j = 0; j < other.col; j++)
				this->data[i][j] = other.data[i][j];

		this->row = other.row;
		this->col = other.col;
	}

	Matrix& operator = (const Matrix& other)
	{
		if (this->data != nullptr)
		{
			for (int i = 0; i < row; i++)
				delete[] this->data[i];
			delete[] this->data;
		}

		this->row = other.row;
		this->col = other.col;

		this->data = new int* [other.row];
		for (int i = 0; i < other.row; i++)
			this->data[i] = new int[other.col];

		for (int i = 0; i < other.row; i++)
			for (int j = 0; j < other.col; j++)
				this->data[i][j] = other.data[i][j];

		return *this;
	}

	void print()
	{
		for (int i = 0; i < this->row; i++)
		{
			for (int j = 0; j < this->col; j++)
				std::cout << this->data[i][j]<<" ";
			std::cout << std::endl;
		}
	}

	~Matrix()
	{
		for (int i = 0; i < row; i++)
			delete[] this->data[i];
		delete[] this->data;
	}

private:
	int** data;
	int row;
	int col;
};
	


int main()
{
	Matrix a(3, 3);
	Matrix b(4, 4);
	

	a.print();
	std::cout << std::endl;
	b.print();
	std::cout << std::endl;


	b = a;

	a.print();
	std::cout << std::endl;
	b.print();

	return 0;
}