#include <iostream>
#include <string>


class Big_int
{
public:
	Big_int()
	{
		this->mas_num = nullptr;
		this->is_negative = false;
		this->size = 0;
	}

	Big_int(std::string str)
	{
		if (str[0] == '-')
		{
			this->is_negative = true;
			str = str.substr(1);
		}
		else
			this->is_negative = false;

		this->size = (str.length() % 18 == 0 ? (str.length() / 18) : (str.length() / 18) + 1);
		this->mas_num = new long long[this->size];
		for (int i = this->size - 1; i >= 0; i--)
		{
			if (i == this->size - 1)
			{
				this->mas_num[i] = stoll(str.substr(0, (str.length() % 18)==0 ? 18 : (str.length() % 18)));
				str = str.substr((str.length() % 18)==0 ? 18 : (str.length() % 18));
			}
			else
			{
				this->mas_num[i] = stoll(str.substr(0, 18));
				str = str.substr(18);
			}
		}
	}

	~Big_int()
	{
		delete[] this->mas_num;
	}

	Big_int(const Big_int& other)
	{
		this->mas_num = new long long[other.size];
		this->is_negative = other.is_negative;
		this->size = other.size;

		for (int i = this->size - 1; i >= 0; i--)
			this->mas_num[i] = other.mas_num[i];
	}

	Big_int& operator =(const Big_int& other)
	{
		if (this->mas_num != nullptr)
			delete[] this->mas_num;

		this->mas_num = new long long[other.size];
		this->is_negative = other.is_negative;
		this->size = other.size;

		for (int i = this->size - 1; i >= 0; i--)
			this->mas_num[i] = other.mas_num[i];
		return *this;
	}

	Big_int operator +(const Big_int& other)
	{
		Big_int temp;
		if (this->is_negative && other.is_negative || !this->is_negative && !other.is_negative)
		{
			if (this->size >= other.size)
			{
				if (this->size == other.size && ((this->mas_num[this->size - 1] + other.mas_num[other.size - 1]) >= MAX))
				{
					temp.mas_num = new long long[this->size + 1];
					temp.is_negative = this->is_negative;
					temp.size = this->size + 1;
					temp.mas_num[temp.size - 1] = 0;
				}
				else
				{
					temp.mas_num = new long long[this->size];
					temp.is_negative = this->is_negative;
					temp.size = this->size;
				}
				for (int i = 0; i < this->size; i++)
					temp.mas_num[i] = this->mas_num[i];

				for (int i = 0; i < other.size; i++)
				{
					if (temp.mas_num[i] + other.mas_num[i] >= MAX)
					{
						temp.mas_num[i] = (temp.mas_num[i] + other.mas_num[i]) % MAX;
						temp.mas_num[i + 1]++;
					}
					else
						temp.mas_num[i] = temp.mas_num[i] + other.mas_num[i];
				}
			}

			else
			{
				temp.mas_num = new long long[other.size];
				temp.is_negative = other.is_negative;
				temp.size = other.size;
				for (int i = 0; i < other.size; i++)
					temp.mas_num[i] = other.mas_num[i];

				for (int i = 0; i < this->size; i++)
				{
					if (temp.mas_num[i] + this->mas_num[i] >= MAX)
					{
						temp.mas_num[i] = (temp.mas_num[i] + this->mas_num[i]) % MAX;
						temp.mas_num[i + 1] = temp.mas_num[i + 1] + 1;
					}
					else
						temp.mas_num[i] = temp.mas_num[i] + this->mas_num[i];
				}
			}

		}

		else if (this->is_negative != other.is_negative)
		{
			if (this->size > other.size)
			{
				temp.mas_num = new long long[this->size];
				temp.is_negative = this->is_negative;
				temp.size = this->size;
				for (int i = 0; i < this->size; i++)
					temp.mas_num[i] = this->mas_num[i];

				for (int i = 0; i < other.size; i++)
				{
					if (temp.mas_num[i] < other.mas_num[i])
					{
						temp.mas_num[i] = temp.mas_num[i] + MAX - other.mas_num[i];
						temp.mas_num[i + 1] = temp.mas_num[i + 1] - 1;
					}
					else
						temp.mas_num[i] = temp.mas_num[i] - other.mas_num[i];
				}
			}

			else if (this->size < other.size)
			{
				temp.mas_num = new long long[other.size];
				temp.is_negative = other.is_negative;
				temp.size = other.size;
				for (int i = 0; i < other.size; i++)
					temp.mas_num[i] = other.mas_num[i];

				for (int i = 0; i < this->size; i++)
				{
					if (temp.mas_num[i] < this->mas_num[i])
					{
						temp.mas_num[i] = temp.mas_num[i] + MAX - this->mas_num[i];
						temp.mas_num[i + 1] = temp.mas_num[i + 1] - 1;
					}
					else
						temp.mas_num[i] = temp.mas_num[i] - this->mas_num[i];
				}
			}

			else
			{
				if (this->mas_num[this->size - 1] > other.mas_num[other.size - 1])
				{
					temp.mas_num = new long long[this->size];
					temp.is_negative = this->is_negative;
					temp.size = this->size;

					for (int i = 0; i < this->size; i++)
						temp.mas_num[i] = this->mas_num[i];

					for (int i = 0; i < other.size; i++)
					{
						if (temp.mas_num[i] < other.mas_num[i])
						{
							temp.mas_num[i] = temp.mas_num[i] + MAX - other.mas_num[i];
							temp.mas_num[i + 1] = temp.mas_num[i + 1] - 1;
						}
						else
							temp.mas_num[i] = temp.mas_num[i] - other.mas_num[i];
					}
				}

				else if (this->mas_num[this->size - 1] < other.mas_num[other.size - 1])
				{
					temp.mas_num = new long long[other.size];
					temp.is_negative = other.is_negative;
					temp.size = other.size;
					for (int i = 0; i < other.size; i++)
						temp.mas_num[i] = other.mas_num[i];

					for (int i = 0; i < this->size; i++)
					{
						if (temp.mas_num[i] < this->mas_num[i])
						{
							temp.mas_num[i] = temp.mas_num[i] + MAX - this->mas_num[i];
							temp.mas_num[i + 1] = temp.mas_num[i + 1] - 1;
						}
						else
							temp.mas_num[i] = temp.mas_num[i] - this->mas_num[i];
					}
				}

				else
				{
					for (int j = this->size - 1; j >= 0; j--)
					{
						if (this->mas_num[j] > other.mas_num[j])
						{
							temp.mas_num = new long long[this->size];
							temp.is_negative = this->is_negative;
							temp.size = this->size;

							for (int i = 0; i < this->size; i++)
								temp.mas_num[i] = this->mas_num[i];

							for (int i = 0; i < other.size; i++)
							{
								if (temp.mas_num[i] < other.mas_num[i])
								{
									temp.mas_num[i] = temp.mas_num[i] + MAX - other.mas_num[i];
									temp.mas_num[i + 1] = temp.mas_num[i + 1] - 1;
								}
								else
									temp.mas_num[i] = temp.mas_num[i] - other.mas_num[i];
							}

							break;
						}

						else if (this->mas_num[j] < other.mas_num[j])
						{
							temp.mas_num = new long long[other.size];
							temp.is_negative = other.is_negative;
							temp.size = other.size;

							for (int i = 0; i < other.size; i++)
								temp.mas_num[i] = other.mas_num[i];

							for (int i = 0; i < this->size; i++)
							{
								if (temp.mas_num[i] < this->mas_num[i])
								{
									temp.mas_num[i] = temp.mas_num[i] + MAX - this->mas_num[i];
									temp.mas_num[i + 1] = temp.mas_num[i + 1] - 1;
								}
								else
									temp.mas_num[i] = temp.mas_num[i] - this->mas_num[i];
							}

							break;
						}

						else if (j == 0 && this->mas_num[0] == other.mas_num[0])
						{
							temp.mas_num = new long long[1];
							temp.is_negative = false;
							temp.size = 1;
							temp.mas_num[0] = 0;
						}
					}
				}
			}


			while (temp.mas_num[temp.size - 1] == 0 && temp.size != 1)
				temp.size--;
		}

		return temp;
	}

	Big_int& operator +=(const Big_int& other)
	{
		Big_int temp;

		if (this->is_negative == other.is_negative)
		{
			if (this->size == other.size && (this->mas_num[this->size - 1] + other.mas_num[other.size - 1]) >= MAX)
			{
				temp.mas_num = new long long[this->size + 1];
				temp.is_negative = this->is_negative;
				temp.size = this->size + 1;

				for (int i = 0; i < this->size; i++)
					temp.mas_num[i] = this->mas_num[i];

				for (int i = 0; i < other.size; i++)
				{
					if (temp.mas_num[i] + other.mas_num[i] >= MAX)
					{
						temp.mas_num[i] = (temp.mas_num[i] + other.mas_num[i]) % MAX;
						temp.mas_num[i + 1]++;
					}
					else
						temp.mas_num[i] = temp.mas_num[i] + other.mas_num[i];
				}
			}
			else if (this->size >= other.size)
			{
				temp.mas_num = new long long[this->size];
				temp.is_negative = this->is_negative;
				temp.size = this->size;

				for (int i = 0; i < this->size; i++)
					temp.mas_num[i] = this->mas_num[i];

				for (int i = 0; i < other.size; i++)
				{
					if (temp.mas_num[i] + other.mas_num[i] >= MAX)
					{
						temp.mas_num[i] = (temp.mas_num[i] + other.mas_num[i]) % MAX;
						temp.mas_num[i + 1]++;
					}
					else
						temp.mas_num[i] = temp.mas_num[i] + other.mas_num[i];
				}
			}
			else
			{
				temp.mas_num = new long long[other.size];
				temp.is_negative = other.is_negative;
				temp.size = other.size;

				for (int i = 0; i < other.size; i++)
					temp.mas_num[i] = other.mas_num[i];

				for (int i = 0; i < this->size; i++)
				{
					if (temp.mas_num[i] + this->mas_num[i] >= MAX)
					{
						temp.mas_num[i] = (temp.mas_num[i] + this->mas_num[i]) % MAX;
						temp.mas_num[i + 1]++;
					}
					else
						temp.mas_num[i] = temp.mas_num[i] + this->mas_num[i];
				}
			}
		}

		else if (this->is_negative != other.is_negative)
		{
			if (this->size > other.size)
			{
				temp.mas_num = new long long[this->size];
				temp.is_negative = this->is_negative;
				temp.size = this->size;

				for (int i = 0; i < this->size; i++)
					temp.mas_num[i] = this->mas_num[i];

				for (int i = 0; i < other.size; i++)
				{
					if (temp.mas_num[i] < other.mas_num[i])
					{
						temp.mas_num[i] = temp.mas_num[i] + MAX - other.mas_num[i];
						temp.mas_num[i + 1]--;
					}
					else
						temp.mas_num[i] = temp.mas_num[i] - other.mas_num[i];
				}
			}
			else if (this->size < other.size)
			{
				temp.mas_num = new long long[other.size];
				temp.is_negative = other.is_negative;
				temp.size = other.size;

				for (int i = 0; i < other.size; i++)
					temp.mas_num[i] = other.mas_num[i];

				for (int i = 0; i < this->size; i++)
				{
					if (temp.mas_num[i] < this->mas_num[i])
					{
						temp.mas_num[i] = temp.mas_num[i] + MAX - this->mas_num[i];
						temp.mas_num[i + 1]--;
					}
					else
						temp.mas_num[i] = temp.mas_num[i] - this->mas_num[i];
				}
			}
			else
			{
				for (int j = this->size - 1; j >= 0; j--)
				{
					if (this->mas_num[j] > other.mas_num[j])
					{
						temp.mas_num = new long long[this->size];
						temp.is_negative = this->is_negative;
						temp.size = this->size;

						for (int i = 0; i < this->size; i++)
							temp.mas_num[i] = this->mas_num[i];

						for (int i = 0; i < other.size; i++)
						{
							if (temp.mas_num[i] < other.mas_num[i])
							{
								temp.mas_num[i] = temp.mas_num[i] + MAX - other.mas_num[i];
								temp.mas_num[i + 1]--;
							}
							else
								temp.mas_num[i] = temp.mas_num[i] - other.mas_num[i];
						}
						break;
					}
					else if (this->mas_num[j] < other.mas_num[j])
					{
						temp.mas_num = new long long[other.size];
						temp.is_negative = other.is_negative;
						temp.size = other.size;

						for (int i = 0; i < other.size; i++)
							temp.mas_num[i] = other.mas_num[i];

						for (int i = 0; i < this->size; i++)
						{
							if (temp.mas_num[i] < this->mas_num[i])
							{
								temp.mas_num[i] = temp.mas_num[i] + MAX - this->mas_num[i];
								temp.mas_num[i + 1]--;
							}
							else
								temp.mas_num[i] = temp.mas_num[i] - this->mas_num[i];
						}
						break;
					}
					else if (j == 0 && this->mas_num[0] == other.mas_num[0])
					{
						temp.mas_num = new long long[1];
						temp.is_negative = false;
						temp.size = 1;
						temp.mas_num[0] = 0;
					}
				}
			}
			while (temp.mas_num[temp.size - 1] == 0 && temp.size != 1)
				temp.size--;
		}

		delete[] this->mas_num;

		this->mas_num = new long long[temp.size];
		this->size = temp.size;
		this->is_negative = temp.is_negative;

		for (int i = 0; i < temp.size; i++)
			this->mas_num[i] = temp.mas_num[i];

		return *this;
	}

	Big_int operator *(int val)
	{
		Big_int temp;

		if (val == 0)
		{
			temp.mas_num = new long long[1];
			temp.is_negative = false;
			temp.size = 1;
			temp.mas_num[0] = 0;
		}

		else if(val<=9)
		{
			temp.mas_num = new long long[this->size + 1];
			temp.is_negative = (val < 0 ? !this->is_negative : this->is_negative);
			temp.size = this->size + 1;

			for (int i = 0; i < temp.size; i++)
				temp.mas_num[i] = 0;

			for (int i = 0; i < this->size; i++)
			{
				if (this->mas_num[i] * val >= MAX)
				{
					temp.mas_num[i] = temp.mas_num[i] + (this->mas_num[i] * val) % MAX;
					temp.mas_num[i + 1]= temp.mas_num[i+1] + (this->mas_num[i] * val) / MAX;
				}
				else
					temp.mas_num[i] = temp.mas_num[i] + this->mas_num[i] * val;
			}

		}

		else
		{
			temp.mas_num = new long long[this->size + 1];
			temp.is_negative = (val < 0 ? !this->is_negative : this->is_negative);
			temp.size = this->size + 1;

			for (int i = 0; i < temp.size; i++)
				temp.mas_num[i] = 0;

			int iter = 1;
			while (val!= 0)
			{
				for (int i = 0; i < this->size; i++)
				{

					if (this->mas_num[i] * (val % 10) >= MAX && iter == 1)
					{
						temp.mas_num[i] = temp.mas_num[i] + (this->mas_num[i] * (val%10)) % MAX;
						temp.mas_num[i + 1] = temp.mas_num[i + 1] + (this->mas_num[i] * (val%10)) / MAX;
					}

					else if(this->mas_num[i] * (val % 10) <= MAX && iter == 1)
						temp.mas_num[i] = temp.mas_num[i] + this->mas_num[i] * (val%10);

					else if (this->mas_num[i] * (val % 10) >=MAX)
					{
						temp.mas_num[i] = temp.mas_num[i] + ((this->mas_num[i] * (val % 10)) % (MAX / iter) * iter);
						if (temp.mas_num[i] >= MAX)
						{
							temp.mas_num[i] = temp.mas_num[i] % MAX;
							temp.mas_num[i + 1]++;
						}
						temp.mas_num[i + 1] = temp.mas_num[i + 1] + ((this->mas_num[i] * (val % 10)) / (MAX / iter));
					}
					else
					{
						temp.mas_num[i] = temp.mas_num[i] + ((this->mas_num[i] * (val % 10)) * iter);
					}
				}

				iter*=10;
				val /= 10;
			}
		}

		while (temp.mas_num[temp.size - 1] == 0 && temp.size != 1)
			temp.size--;

		return temp;
	}

	Big_int operator *(const Big_int other)
	{
		Big_int temp;
		(this->is_negative || other.is_negative) ? temp.is_negative = true : temp.is_negative = false;
		temp.mas_num = new long long[this->size + other.size + 1];
		temp.size = this->size + other.size + 1;
		for (int i = 0; i < temp.size; i++)
			temp.mas_num[i] = 0;

		for (int i = 0; i < this->size; i++)
		{
			long long num = this->mas_num[i];
			long long cnt = 1;
			while (num != 0)
			{
				for (int j = 0; j < other.size; j++)
				{
					temp.mas_num[i + j] += (other.mas_num[j] * (num % 10)) % (MAX / cnt) * cnt;
					temp.mas_num[i + j + 1] += (other.mas_num[j] * (num % 10)) / (MAX / cnt);
					if (temp.mas_num[i + j] > MAX)
					{
						temp.mas_num[i + j + 1] += temp.mas_num[i + j] / MAX;
						temp.mas_num[i + j] = temp.mas_num[i + j] % MAX;
					}
				}
				cnt *= 10;
				num /= 10;
			}
		}

		int i = temp.size-1;
		while (temp.mas_num[i] == 0 && temp.size!=1)
		{
			temp.size -= 1;
			i--;
		}

		return temp;
	}

	Big_int& operator *=(const Big_int& other)
	{
		Big_int temp;
		(this->is_negative || other.is_negative) ? temp.is_negative = true : temp.is_negative = false;
		temp.mas_num = new long long[this->size + other.size + 1];
		temp.size = this->size + other.size + 1;
		for (int i = 0; i < temp.size; i++)
			temp.mas_num[i] = 0;

		for (int i = 0; i < this->size; i++)
		{
			long long num = this->mas_num[i];
			long long cnt = 1;
			while (num != 0)
			{
				for (int j = 0; j < other.size; j++)
				{
					temp.mas_num[i + j] += (other.mas_num[j] * (num % 10)) % (MAX / cnt) * cnt;
					temp.mas_num[i + j + 1] += (other.mas_num[j] * (num % 10)) / (MAX / cnt);
					if (temp.mas_num[i + j] > MAX)
					{
						temp.mas_num[i + j + 1] += temp.mas_num[i + j] / MAX;
						temp.mas_num[i + j] = temp.mas_num[i + j] % MAX;
					}
				}
				cnt *= 10;
				num /= 10;
			}
		}

		int i = temp.size - 1;
		while (temp.mas_num[i] == 0)
		{
			temp.size -= 1;
			i--;
		}

		delete[] this->mas_num;

		this->mas_num = new long long[temp.size];
		this->size = temp.size;
		this->is_negative = temp.is_negative;

		for (int i = 0; i < temp.size; i++)
			this->mas_num[i] = temp.mas_num[i]; 

		return *this;
	}

	bool operator <(const Big_int& other)
	{
		if (this->size < other.size)
			return true;

		else if (this->size == other.size)
			for (int i = this->size - 1; i >= 0; i--)
				return (this->mas_num[i] < other.mas_num[i] ? true : false);
		else
			return false;
	}

	bool operator >(const Big_int& other)
	{
		if (this->size > other.size)
			return true;
		else if (this->size == other.size)
			for (int i = this->size - 1; i >= 0; i--)
				return (this->mas_num[i] > other.mas_num[i] ? true : false);
		else
			return false;
	}

	bool operator ==(const Big_int& other)
	{
		if (this->size != other.size)
			return false;
		else
		{
			int cnt = 0;
			for (int i = this->size - 1; i >= 0; i--)
				this->mas_num[i] == other.mas_num[i] ? cnt++ : cnt += 0;
			return (cnt == this->size ? true : false);
		}
	}

	bool operator !=(const Big_int& other)
	{
		if (this->size != other.size)
			return true;
		else
		{
			int cnt = 0;
			for (int i = this->size - 1; i >= 0; i--)
				this->mas_num[i] == other.mas_num[i] ? cnt++ : cnt += 0;
			return (cnt == this->size ? false : true);
		}
	}

	friend std::ostream& operator <<(std::ostream& os, const Big_int& obj);
	friend std::istream& operator >>(std::istream& is, Big_int& obj);

	void print()
	{
		if (this->is_negative)
			std::cout << '-';
		for (int i = this->size - 1; i >= 0; i--)
		{
			if (this->mas_num[i] == 0 && this->size != 1)
			{
				std::cout << ZERO;
				continue;
			}
			if (std::to_string(this->mas_num[i]).length() < 18 && i!=this->size-1)
			{
				std::cout << ZERO.substr(0, ZERO.length() - std::to_string(this->mas_num[i]).length()) << std::to_string(this->mas_num[i]);
				continue;
			}

			std::cout << std::to_string(this->mas_num[i]);
		}
	}

private:
	long long* mas_num;
	bool is_negative;
	int size;
	const long long MAX = 1000000000000000000;
	std::string ZERO = "000000000000000000";
};



std::ostream& operator<<(std::ostream& os, const Big_int& obj)
{
	if (obj.is_negative)
		os << '-';
	for (int i = obj.size - 1; i >= 0; i--)
	{
		if (obj.mas_num[i] == 0 && obj.size != 1)
		{
			os << obj.ZERO;
			continue;
		}
		if (std::to_string(obj.mas_num[i]).length() < 18 && i != obj.size - 1)
		{
			os << obj.ZERO.substr(0, obj.ZERO.length() - std::to_string(obj.mas_num[i]).length());
			os << std::to_string(obj.mas_num[i]);
			continue;
		}

		os << std::to_string(obj.mas_num[i]);
	}
	os << std::endl;
	return os;
}

std::istream& operator>>(std::istream& is, Big_int& obj)
{
	std::string number;
	is >> number;
	if (number[0] == '-')
	{
		obj.is_negative = true;
		number = number.substr(1);
	}
	else
		obj.is_negative = false;

	obj.size = (number.length() % 18 == 0 ? (number.length() / 18) : (number.length() / 18) + 1);
	obj.mas_num = new long long[obj.size];
	for (int i = obj.size - 1; i >= 0; i--)
	{
		if (i == obj.size - 1)
		{
			obj.mas_num[i] = stoll(number.substr(0, (number.length() % 18) == 0 ? 18 : (number.length() % 18)));
			number = number.substr((number.length() % 18) == 0 ? 18 : (number.length() % 18));
		}
		else
		{
			obj.mas_num[i] = stoll(number.substr(0, 18));
			number = number.substr(18);
		}
	}
	return is;
}

int main()
{
	Big_int a("99999999999999999999999999");
	Big_int b("99999999999999999999");
	Big_int c;
	
	Big_int v("1");
	Big_int w("0");
	//std::cin >> c
	std::cout << v*w;
}


