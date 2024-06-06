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
		std::cout << "Высота в параллелограмме не может быть больше обеих сторон параллелограмма одновременно." << std::endl;
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
	std::cout << "Сторона а = " << this->side_a << std::endl;
	std::cout << "Сторона b = " << this->side_b << std::endl;
	std::cout << "Высота = " << this->height << std::endl;
}	






