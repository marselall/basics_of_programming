#include "Figure.h"

Figure::Figure(int side_a, int side_b, int height)
{
	if ((height <= side_a) || (height <= side_b))
	{
		this->side_a = side_a;
		this->side_b = side_b;
		this->height = height;
	}
	else
	{
		std::cout << "������ � ��������������� �� ����� ���� ������ ����� ������ ��������������� ������������." << std::endl;
		this->side_a = side_a;
		this->side_b = side_b;
		this->height = 0;
	}
}

Figure::~Figure() {};

int Figure::Square()
{
	if (this->side_a < this->side_b && this->side_a >= this->height)
		return this->side_a * this->height;
	else if (this->side_a < this->side_b && this->side_a < this->height)
		return this->side_b * this->height;
}

int Figure::Perimeter()
{
	return (this->side_a + this->side_b) * 2;
}

void Figure::Get_Parameters()
{
	std::cout << "������� � = " << this->side_a << std::endl;
	std::cout << "������� b = " << this->side_b << std::endl;
	std::cout << "������ = " << this->height << std::endl;
}	






