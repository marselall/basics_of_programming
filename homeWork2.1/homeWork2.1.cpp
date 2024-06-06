#include "Figure.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);


	Figure a(10, 12, 11);
	a.Get_Parameters();
	std::cout << a.Perimeter() << std::endl << a.Square();
	return 0;
}