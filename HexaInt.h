#pragma once
#include<iostream>
#include<fstream>
using namespace std;

class HexaInt
{
private:
	int base;
	int* Vs;
	bool isNeg;
	int size;

public:

	void Load(ifstream& rdr);
	void Print();
	HexaInt();
	HexaInt(int s);
	HexaInt(const HexaInt& S);
	HexaInt(ifstream& rdr);
	void Setbase(int n);
	void Assign(const HexaInt& S);
	void Trim();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	const HexaInt add(const HexaInt& S)const;
	const HexaInt sub(const HexaInt& S)const;
	bool LessThanQuantityWise(const HexaInt& S) const;
	bool GreaterThanQuantityWise(const HexaInt& S) const;
	bool EqualQuantityWise(const HexaInt& S) const;


	const HexaInt operator+(const HexaInt& S)const;
	const HexaInt& operator+=(const HexaInt& S);
	const HexaInt operator!()const;
	const HexaInt operator-(const HexaInt& S)const;
	const HexaInt& operator-=(const HexaInt& S);

	bool  operator>(const HexaInt& S)const;
	bool  operator>=(const HexaInt& S)const;
	bool  operator<(const HexaInt& S)const;
	bool  operator<=(const HexaInt& S)const;
	bool  operator==(const HexaInt& S)const;
	bool operator!=(const HexaInt I)const;
	friend ostream& operator<<(ostream& cout, const HexaInt& H);

	const HexaInt operator++(int d);
	HexaInt& operator++();
	const HexaInt operator--(int d);
	HexaInt& operator--();

	const HexaInt operator*(const HexaInt& S)const;
	const HexaInt& operator*=(const HexaInt& S);
	const HexaInt operator/(const HexaInt& S)const;
	const HexaInt& operator/=(const HexaInt& S);
	const HexaInt operator%(const HexaInt& S)const;
	const HexaInt& operator%=(const HexaInt& S);

	int operator[](int i) const;
	int& operator[](int i);

	const HexaInt& operator=(const HexaInt& S);


	static HexaInt One(int n);
	static HexaInt Zero(int n);

	~HexaInt();

};

