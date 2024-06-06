#include <iostream>
#include <fstream>
#include <memory>
#include <filesystem>

// N < 256 и a_i < 256, для всех i=1..N
// .txt - массив данных в формате N и a_i, где i=1..N (ASCII)
// .bin - массив данных в формате N и a_i, где i=1..N (bin)
namespace fileS = std::filesystem;

class DataReader
{
protected:
	std::ifstream m_in;
	std::string m_filename;
	uint8_t* m_data;
	uint8_t m_n;

public:
	DataReader(const std::string& filename) :
		m_filename(filename), m_n(0), m_data(nullptr){}

	virtual ~DataReader() {}
	virtual bool Open() = 0;
	virtual void Read() = 0;

	void Close()
	{
		m_in.close();
	}

	virtual void GetData(uint8_t* buf, uint8_t& n) = 0;
};

class TxtReader : public DataReader
{
public:
	TxtReader(const std::string& filename) : DataReader(filename) {}
	virtual ~TxtReader()
	{
		if (m_data != nullptr)
			delete[] m_data;
	}

	bool Open() override
	{
		m_in.open(m_filename);
		if (!m_in.is_open())
			return false;
		return true;
	}

	void Read() override
	{
		int tmp;
		m_in >> tmp;
		m_n = tmp;
		m_data = new uint8_t[m_n];
		for (int i = 0; i < m_n; i++)
		{
			int tmp;
			m_in >> tmp;
			m_data[i] = tmp;
		}
	}

	void GetData(uint8_t* buf, uint8_t& n) override {}
};

class BinReader : public DataReader
{
public:

	BinReader(const std::string& filename) : DataReader(filename) {}
	virtual ~BinReader()
	{
		if (m_data != nullptr)
			delete[] m_data;
	}

	bool Open() override
	{
		m_in.open(m_filename, std::ios::binary);
		if (!m_in.is_open())
			return false;
		return true;
	}

	void Read() override
	{
		m_in.read(reinterpret_cast<char*>(& m_n), 1);
		m_data = new uint8_t[m_n];
		m_in.read(reinterpret_cast<char*>(m_data), m_n);
	}

	void GetData(uint8_t* buf, uint8_t& n) override {} 
};

class BinFReader : public DataReader
{
public:
	BinFReader(const std::string& filename) : DataReader(filename) {}
	virtual ~BinFReader() 
	{
		if (m_data != nullptr)
			delete[] m_data;
	}

	bool Open() override 
	{
		m_in.open(m_filename, std::ios::binary);
		if (!m_in.is_open())
			return false;
		return true;
	}

	void Read() override 
	{
		uint8_t numFloats;
		m_in.read(reinterpret_cast<char*>(&numFloats), sizeof(uint8_t));
		m_n = numFloats;
		delete[] m_data;
		m_data = new uint8_t[m_n * sizeof(float)];
		m_in.read(reinterpret_cast<char*>(m_data), m_n * sizeof(float));
	}

	void GetData(uint8_t* buf, uint8_t& n) override
	{
		std::cout << "Number:" << " " << int(m_n) << std::endl;
		for (size_t i = 0; i < m_n * 4; i += 4) {
			std::cout << *(float*)(m_data + i) << std::endl;
		}
	}
};


std::unique_ptr<DataReader> Factory(const std::string& filename)
{
	std::string extension = filename.substr(filename.find_last_of('.') + 1);

	if (extension == "txt")
		return std::make_unique <TxtReader>(filename);
	else if (extension == "bin")
		return std::make_unique <BinReader>(filename);
	else if (extension == "binf")
		return std::make_unique<BinFReader>(filename); 
	return nullptr;
}

void create_bin_file() 
{
	std::ofstream out("laba_7_bin.bin", std::ios::binary);
	uint8_t buf[7];
	buf[0] = 6;
	for (int i = 1; i < 7; i++)
	{
		buf[i] = i + 100;
	}
	out.write(reinterpret_cast<char*>(buf), sizeof(buf));

	if (out.is_open())
	{
		std::cout << "File created successfully" << std::endl;
		std::cout << "File path: " << fileS::absolute("laba_7_bin.bin") << std::endl;
	}
	else 
		std::cerr << "Failed to create file" << std::endl;
}

void create_binf_file() 
{
	std::ofstream out("laba_7_binF.binf", std::ios::binary);
	float buf[4] = { 7.1f, 1.98f, 2.58f, 1.474f };
	uint8_t size = 4;
	out.write(reinterpret_cast<char*>(&size), sizeof(uint8_t));
	out.write(reinterpret_cast<char*>(buf), sizeof(buf));
	if (out.is_open()) 
	{
		std::cout << "File created successfully" << std::endl;
		std::cout << "File path: " << fileS::absolute("laba_7_binF.binf") << std::endl;
	}
	else 
		std::cerr << "Failed to create file" << std::endl;
}

int main()
{
	
	create_binf_file();

	uint8_t n = 0;
	uint8_t buf[100];
	std::unique_ptr<DataReader> Reader = Factory("laba_7_binF.binf");
	if (!Reader)
		return -1;
	if (!Reader->Open())
		return -10;
	Reader->Read();
	Reader->GetData(buf, n);
	Reader->Close();

	return 0;
}