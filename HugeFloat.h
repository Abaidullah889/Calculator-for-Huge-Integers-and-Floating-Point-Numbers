#pragma once
#include<fstream>
using namespace std;
class HugeFloat
{
private:
	int size;
	int* Vs;
	int p_ind;
	bool isneg;
	void Trim();
	void TrimFromLast();
	void MultiplyFloat(int s);
	void AddZero(int n);
	int BeforeDecimal()const;
	const HugeFloat add(const HugeFloat& S)const;
	const HugeFloat sub(const HugeFloat& S)const;
	bool LessThanQuantityWise(const HugeFloat& S) const;
	bool GreaterThanQuantityWise(const HugeFloat& S) const;
	bool EqualQuantityWise(const HugeFloat& S) const;


public:
	HugeFloat();
	HugeFloat(int size);
	HugeFloat(const HugeFloat& S);
	HugeFloat(ifstream& rdr);
	void Assign(const HugeFloat& S);
	void GetFloat(string l);
	void Pirnt();
	void Load(ifstream& rdr);
	const HugeFloat& operator=(const HugeFloat& S);
	int operator[](int i) const;
	int& operator[](int i);


	static HugeFloat One();
	static HugeFloat MOne();
	static HugeFloat Zero();

	
	//////////////////////////////////////////////////////////////////////////////////////// OPERATOR //////////////////////////////////////////////////////////////////////////

	const HugeFloat operator+(const HugeFloat& S)const;
	const HugeFloat& operator+=(const HugeFloat& S);
	const HugeFloat operator!()const;
	const HugeFloat operator-(const HugeFloat& S)const;
	const HugeFloat& operator-=(const HugeFloat& S);
	bool  operator>(const HugeFloat& S)const;
	bool  operator>=(const HugeFloat& S)const;
	bool  operator<(const HugeFloat& S)const;
	bool  operator<=(const HugeFloat& S)const;
	bool  operator==(const HugeFloat& S)const;
	bool operator!=(const HugeFloat I)const;


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	friend ostream& operator<<(ostream& cout, const HugeFloat& H);
	ostream& operator<< (ostream& cout);
	friend ifstream& operator>>(ifstream& rdr, HugeFloat& H);
	ifstream& operator>>(ifstream& rdr);
	friend istream& operator>>(istream& in,HugeFloat& H);

	const HugeFloat operator++(int d);
	HugeFloat& operator++();
	const HugeFloat operator--(int d);
	HugeFloat& operator--();
	const HugeFloat operator*(const HugeFloat& S)const;
	const HugeFloat& operator*=(const HugeFloat& S);
	const HugeFloat operator/(const HugeFloat& S)const;
	const HugeFloat& operator/=(const HugeFloat& S);


	~HugeFloat();
};

