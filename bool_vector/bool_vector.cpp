#include <iostream>

template <typename T>
class Vector;

template<>
class Vector<bool>
{
public:
	Vector()
	{
		this->bool_mas = nullptr;
		this->size_ = 0;
		this->capacity = 0;
	}

	void push_back(bool val)
	{
		if (this->size_ == this->capacity)
		{
			size_t nCapacity = this->capacity == 0 ? 1 : this->capacity * 2;
			this->resize(nCapacity);
		}

		size_t byteId = this->size_ / 8;
		size_t bitId = this->size_ % 8;

		if (val)
			this->bool_mas[byteId] |= (1 << bitId);
		else
			this->bool_mas[byteId] &= ~(1 << bitId);

		this->size_++;

	}

	bool& operator [](size_t index)
	{
		if (index > this->size_)
			throw - 1;
		size_t bytId = index / 8;
		size_t bitId = index % 8;
		bool val = (this->bool_mas[bytId] >> bitId) % 2;
		return val;
	}

	size_t size()
	{
		return this->size_;
	}

	void insert(size_t index, bool val)
	{
		if (index > this->size_)
			throw - 1;

		if (this->size_+1 == this->capacity)
		{
			size_t nCapacity = this->capacity == 0 ? 1 : this->capacity * 2;
			this->resize(nCapacity);
		}

		if (index == this->size_)
		{
			this->push_back(val);
			return;
		}

		size_t bytId = index / 8;
		size_t bitId = index % 8;

		if (val)
		{
			for (size_t i = this->size_ / 8; i > bytId; i--)
				this->bool_mas[i] = (this->bool_mas[i] << 1) ^ (this->bool_mas[i - 1] >> 7);
			this->bool_mas[bytId] = ((this->bool_mas[bytId] / (1 << bitId)) << (bitId + 1)) | ((this->bool_mas[bytId] % (1 << bitId)) | (1 << bitId));
		}

		else
		{
			for (size_t i = this->size_ / 8; i > bytId; i--)
				this->bool_mas[i] = (this->bool_mas[i] << 1) ^ (this->bool_mas[i - 1] >> 7);
			this->bool_mas[bytId]= ((this->bool_mas[bytId] / (1 << bitId)) << (bitId + 1)) | (this->bool_mas[bytId] % (1 << bitId));
		}

		this->size_++;
	}

	void erase(size_t index)
	{
		if (index >= this->size_)
			throw - 1;

		size_t bytId = index / 8;
		size_t bitId = index % 8;

		this->bool_mas[bytId] = ((this->bool_mas[bytId] >> bitId + 1) << bitId) | (this->bool_mas[bytId] % (1 << bitId));
		for (size_t i = bytId; i < this->size_ / 8; i++) 
		{
			this->bool_mas[i + 1] % 2 == 0 ? this->bool_mas[i] : this->bool_mas[i] |= (1 << 7);
			this->bool_mas[i + 1] >>= 1;
		}

		this->size_--;
	}

private:
	uint8_t* bool_mas;
	size_t size_;
	size_t capacity;

	void resize(size_t nCapacity)
	{
		uint8_t* new_mas = new uint8_t[(nCapacity + 7) / 8];
		if (this->bool_mas != nullptr)
		{
			for (size_t i = 0; i < (this->capacity + 7) / 8; i++)
				new_mas[i] = this->bool_mas[i];
			delete[] this->bool_mas;
		}

		this->bool_mas = new_mas;
		this->capacity = nCapacity;
	}
};


int main()
{
	Vector<bool> a;
	a.push_back(true);
	a.push_back(false);
	a.push_back(true);
	a.push_back(true);
	a.push_back(true);
	a.push_back(false);
	a.push_back(true);
	a.push_back(false);
	a.push_back(true);
	a.push_back(false);
	a.push_back(true);
	a.push_back(true);

	a.insert(7,false);
	
	for (size_t i = 0; i < a.size(); i++)
		std::cout << a[i];

	return 0;
}