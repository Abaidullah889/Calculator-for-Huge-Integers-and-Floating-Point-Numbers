#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class HexaFloat
{

private:
	int base;
	int size;
	int* Vs;
	int p_ind;
	bool isneg;
public:
	HexaFloat();
	HexaFloat(int size);
	HexaFloat(const HexaFloat& S);
	HexaFloat(ifstream& rdr);
	void Setbase(int n);
	const HexaFloat& operator=(const HexaFloat& S);
	void Assign(const HexaFloat& S);
	void Load(ifstream& rdr);
	void GetFloat(string l);
	void Print();
	int operator[](int i) const;
	int& operator[](int i);
	const HexaFloat add(const HexaFloat& S)const;
	const HexaFloat sub(const HexaFloat& S)const;
	bool LessThanQuantityWise(const HexaFloat& S) const;
	bool GreaterThanQuantityWise(const HexaFloat& S) const;
	bool EqualQuantityWise(const HexaFloat& S) const;

	const HexaFloat operator!()const;
	const HexaFloat operator+(const HexaFloat& S)const;
	const HexaFloat& operator+=(const HexaFloat& S);
	const HexaFloat operator-(const HexaFloat& S)const;
	const HexaFloat& operator-=(const HexaFloat& S);

	bool  operator>(const HexaFloat& S)const;
	bool  operator>=(const HexaFloat& S)const;
	bool  operator<(const HexaFloat& S)const;
	bool  operator<=(const HexaFloat& S)const;
	bool  operator==(const HexaFloat& S)const;
	bool operator!=(const HexaFloat I)const;

	const HexaFloat operator*(const HexaFloat& S)const;
	const HexaFloat& operator*=(const HexaFloat& S);
	const HexaFloat operator/(const HexaFloat& S)const;
	const HexaFloat& operator/=(const HexaFloat& S);


	const HexaFloat operator++(int d);
	HexaFloat& operator++();
	const HexaFloat operator--(int d);
	HexaFloat& operator--();


	friend ostream& operator<<(ostream& cout, const HexaFloat& H);
	ostream& operator<< (ostream& cout);
	friend ifstream& operator>>(ifstream& rdr, HexaFloat& H);
	ifstream& operator>>(ifstream& rdr);
	friend istream& operator>>(istream& in, HexaFloat& H);


	static HexaFloat One(int n);
	static HexaFloat MOne(int n);
	static HexaFloat Zero(int n);
	int BeforeDecimal()const;
	void AddZero(int n);
	void TrimFromLast();
	void MultiplyFloat(int s);
	void Trim();
};

