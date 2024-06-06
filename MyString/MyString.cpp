#include <iostream>

class String
{
public:
	String()
	{
		this->str = nullptr;
		this->length = 0;
	}
	String(const char* str)
	{
		this->length = strlen(str);
		this->str = new char[length + 1];

		for (int i = 0; i < length; i++)
			this->str[i] = str[i];

		this->str[length] = '\0';
	}

	~String()
	{
		delete[] this->str;
	}

	int Length()
	{
		return this->length;
	}

	String(const String& other)
	{
		this->str = new char[other.length + 1];
		this->length = other.length;

		for (int i = 0; i < other.length; i++)
			this->str[i] = other.str[i];

		this->str[other.length] = '\0';
	}

	String& operator =(const String& other)
	{
		if (this->str != nullptr)
			delete[] this->str;

		this->str = new char[other.length + 1];
		this->length = other.length;

		for (int i = 0; i < other.length; i++)
			this->str[i] = other.str[i];

		this->str[other.length] = '\0';
		return *this;
	}

	String operator +(const String& other)
	{
		String newstr;
		newstr.str = new char[this->length + other.length + 1];

		{
			int i = 0;
			for (; i < this->length; i++)
				newstr.str[i] = this->str[i];

			for (int j = 0; j < other.length; j++)
			{
				newstr.str[i] = other.str[j];
				i++;
			}
		}

		newstr.str[this->length + other.length] = '\0';
		newstr.length = this->length + other.length;

		return newstr;
	}

	String& operator +=(const String& other)
	{
		String newstr=this->operator+(other);
		
		newstr.str[this->length + other.length] = '\0';
		newstr.length = this->length + other.length;
		
		
		if (this->str != nullptr)
			delete[] this->str;

		this->str = new char[newstr.length + 1];

		for (int i = 0; i < newstr.length; i++)
			this->str[i] = newstr.str[i];

		this->str[newstr.length] = '\0';
		this->length = newstr.length;

		return *this;
	}

	bool operator ==(const String& other)
	{
		if (this->length != other.length)
			return false;

		int cnt = 0;

		for (int i = 0; i < this->length; i++)
		{
			if (this->str[i] == other.str[i])
				cnt++;
			if (cnt == this->length)
				return true;
		}
		return false;
	}

	bool operator !=(const String& other)
	{
		return !(this->operator==(other));
	}

	bool operator >(const String& other)
	{
		for (int i = 0; i < (this->length < other.length ? this->length : other.length); i++)
			if (this->str[i] > other.str[i])
				return true;

		if (this->length > other.length)
			return true;

		return false;
	}

	bool operator <(const String& other)
	{
		for (int i = 0; i < (this->length < other.length ? this->length : other.length); i++)
			if (this->str[i] < other.str[i])
				return true;

		if (this->length < other.length)
			return true;

		return false;
	}

	char& operator[](int index)
	{
		return this->str[index];
	}

	friend std::ostream& operator <<(std::ostream& os, const String& obj);
	friend std::istream& operator >>(std::istream& is, String& obj);

	int find(const char mas[])
	{
		for (int i = 0; i < this->length; i++)
		{
			int cnt = 0;
			if (this->str[i] == mas[0])
				for (int j = 0; j < strlen(mas); j++)
				{
					if (this->str[i + j] == mas[j])
						cnt++;
				}
			if (cnt == strlen(mas))
				return i;
		}
		return -1;//если не найдена подстрока
	}
	
	const char* c_str()
	{
		return this->str;
	}

	const char& at(unsigned index)const
	{
		if (this->length<=index)
			throw std::out_of_range("Invalid index");
		return this->str[index];
	}

	char& at(unsigned index)
	{
		if (this->length <= index)
			throw std::out_of_range("Invalid index");
		return this->str[index];
	}

private:
	char *str;
	int length;
};

std::ostream& operator <<(std::ostream& os, const String& obj)
{
	return os << obj.str;
}

std::istream& operator >>(std::istream& is, String& obj)
{
	char mas[255];
	is >> mas;
	obj.str = new char[strlen(mas)+1];
	for (int i = 0; i < strlen(mas); i++)
		obj.str[i] = mas[i];
	obj.length = strlen(mas);
	obj.str[strlen(mas)] = '\0';
	return is;
}



int main()
{
	String a("asnend");
	String b("sfsfa");
	a += b;
	std::cout << a;
	return 0;
}