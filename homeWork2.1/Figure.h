#pragma once
#include <iostream>
#include <Windows.h>

class Figure
{
public:
	Figure(int side_a, int side_b, int height);
	~Figure();
	int Square();
	int Perimeter();
	void Get_Parameters();

private:
	int side_a;
	int side_b;
	int height;
};

