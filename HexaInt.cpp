#include "Bscs22133HexaInt.h"
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

HexaInt::HexaInt()
{
	this->base = 0;
	this->size = 0;
	this->Vs = nullptr;
	this->isNeg = false;
}
HexaInt::HexaInt(int s)
{
	this->base = 0;
	this->size = s;
	this->Vs = new int[s];
	this->isNeg = false;
}
HexaInt::HexaInt(const HexaInt& S)
{
	this->Assign(S);
}
HexaInt::HexaInt(ifstream& rdr)
{
	this->Load(rdr);
}
void HexaInt::Load(ifstream& rdr)
{
	while (rdr.peek() == '\n' || rdr.peek() == ' ' || rdr.peek() == '	')
	{
		rdr.ignore();
	}
	char s;
	s = rdr.peek();
	if (s == '-')
	{
		this->isNeg = true;
		rdr.ignore();
	}
	else
	{
		this->isNeg = false;
	}
	string l;
	getline(rdr, l);
	this->size = l.size();
	this->Vs = new int[this->size] {0};
	for (int i = 0; i < this->size; i++)
	{
		int n = l[i];
		if (n >= 48 && n <= 57)
		{
			this->Vs[this->size - i - 1] = n - '0';
		}
		else
		{
			this->Vs[this->size - i - 1] = n - 55;
		}
	}
}
void HexaInt::Print()
{
	cout << ((this->isNeg) ? '-' : '+');
	for (int i = 0; i < this->size; i++)
	{
		if (this->Vs[this->size - i - 1] >= 0 && this->Vs[this->size - i - 1] <=9)
		{
			char c = this->Vs[this->size-i-1]+48;
			cout << c;

		}
		else
		{
			char c = this->Vs[this->size - i - 1] + 55;
			cout << c;
		}
	}
}
void HexaInt::Setbase(int n)
{
	this->base = n;
}
void HexaInt::Assign(const HexaInt& S)
{
	if (S.size != 0)
	{
		this->size = S.size;
		int* p = new int[this->size] {0};
		for (int i = 0; i < this->size; i++)
		{
			p[i] = S.Vs[i];
		}
		this->isNeg = S.isNeg;
		//delete[]this->Vs;
		this->base = S.base;
		this->Vs = p;
		p = nullptr;
	}
}

///////////////////////////////////////////////////////////////////////////////Operator/////////////////////////////////////////////////////////////////

const HexaInt& HexaInt::operator=(const HexaInt& S)
{

	this->Assign(S);
	return *this;
}
const HexaInt HexaInt::operator+(const HexaInt& S)const
{
	if (this->isNeg != S.isNeg)
	{
		if (this->size == S.size)
		{
			int count = 0;
			for (int i = 0; i < this->size; i++)
			{

				if (this->Vs[i] != S.Vs[i])
				{
					break;
				}
				count++;
				if (count == this->size)
				{
					return Zero(this->base);
					//throw invalid_argument("Operation is not possible....");
					
				}
			}
		}
	}

	if (this->isNeg == S.isNeg)
	{
		if (this->GreaterThanQuantityWise(S))
		{
			HexaInt R = this->add(S);
			R.isNeg = this->isNeg;
			return R;
		}
		else
		{
			HexaInt R = S.add(*this);
			R.isNeg = S.isNeg;
			return R;
		}
	}
	else
	{
		if (this->GreaterThanQuantityWise(S))
		{
			HexaInt R = this->sub(S);
			R.isNeg = this->isNeg;
			return R;
		}
		else
		{
			HexaInt R = S.sub(*this);
			R.isNeg = S.isNeg;
			return R;
		}
	}
}
const HexaInt& HexaInt::operator+=(const HexaInt& S)
{
	if (this->isNeg != S.isNeg)
	{
		if (this->size == S.size)
		{
			int count = 0;
			for (int i = 0; i < this->size; i++)
			{

				if (this->Vs[i] != S.Vs[i])
				{
					break;
				}
				count++;
				if (count == this->size)
				{
					throw invalid_argument("Operation is not possible....");
				}
			}
		}
	}

	if (this->isNeg == S.isNeg)
	{
		if (this->GreaterThanQuantityWise(S))
		{
			HexaInt R = this->add(S);
			R.isNeg = this->isNeg;
			*this = R;
			return *this;
		}
		else
		{
			HexaInt R = S.add(*this);
			R.isNeg = S.isNeg;
			*this = R;
			return *this;
		}
	}
	else
	{
		if (this->GreaterThanQuantityWise(S))
		{
			HexaInt R = this->sub(S);
			R.isNeg = this->isNeg;
			*this = R;
			return *this;
		}
		else
		{
			HexaInt R = S.sub(*this);
			R.isNeg = S.isNeg;
			*this = R;
			return *this;
		}
	}
}
const HexaInt HexaInt::operator!()const
{
	HexaInt R = (*this);
	R.isNeg = !(this->isNeg);
	return R;
}
const HexaInt HexaInt::operator-(const HexaInt& S)const
{
	return (*this) + (!S);
}
const HexaInt& HexaInt::operator-=(const HexaInt& S)
{
	HexaInt I = (*this) += (!S);
	*this = I;
	return *this;
}

bool  HexaInt::operator>(const HexaInt& S)const
{
	if (this->isNeg != S.isNeg)
	{
		return this->isNeg == false;
	}
	else if (this->isNeg == true)
	{
		return this->LessThanQuantityWise(S);
	}
	else
	{
		return this->GreaterThanQuantityWise(S);
	}
}
bool  HexaInt::operator>=(const HexaInt& S)const
{
	if ((*this > S) || (*this == S))
	{
		return true;
	}
	return false;
}
bool  HexaInt::operator<(const HexaInt& S)const
{
	return S > (*this);
}
bool  HexaInt::operator<=(const HexaInt& S)const
{
	if ((*this < S) || (*this == S))
	{
		return true;
	}
	return false;
}
bool  HexaInt::operator==(const HexaInt& S)const
{
	return (!(*this < S) && !(*this > S));
}
bool HexaInt::operator!=(const HexaInt I)const
{
	if (*this == I)
	{
		return false;
	}
	return true;
}

ostream& operator<<(ostream& cout, const HexaInt& H)
{
	cout << ((H.isNeg) ? '-' : '+');
	for (int i = 0; i < H.size; i++)
	{
		if (H.Vs[H.size - i - 1] >= 0 && H.Vs[H.size - i - 1] <= 9)
		{
			char c = H.Vs[H.size - i - 1] + 48;
			cout << c;

		}
		else
		{
			char c = H.Vs[H.size - i - 1] + 55;
			cout << c;
		}
	}
	return cout;
}


const HexaInt HexaInt::operator++(int d)
{
	HexaInt R = (*this);
	(*this) = (*this) + One(this->base);
	return R;
}
HexaInt& HexaInt::operator++()
{
	HexaInt P = One(this->base);
	(*this) = (*this) + P;
	return (*this);
}
const HexaInt HexaInt::operator--(int d)
{
	HexaInt R = (*this);
	(*this) = (*this) - One(this->base);
	return R;
}
HexaInt& HexaInt::operator--()
{
	HexaInt P = One(this->base);
	(*this) = (*this) + P;
	return (*this);
}

const HexaInt HexaInt::operator*(const HexaInt& S)const
{
	HexaInt R;
	HexaInt I;
	HexaInt A = *this;
	A.isNeg = false;
	HexaInt B = S;
	B.isNeg = false;
	HexaInt C;
	while (B != Zero(this->base))
	{
		R = A;
		C = One(this->base);
		while (C + C <= B)
		{
			R += R;
			C += C;
		}
		I += R;
		B = B - C;
	}

	if ((*this).isNeg != S.isNeg)
	{
		I.isNeg = true;
	}
	if ((*this).isNeg == S.isNeg)
	{
		I.isNeg = false;
	}
	return I;
}
const HexaInt& HexaInt::operator*=(const HexaInt& S)
{
	HexaInt R;
	HexaInt I;
	HexaInt A = *this;
	A.isNeg = false;
	HexaInt B = S;
	B.isNeg = false;
	HexaInt C;
	while (B != Zero(this->base))
	{
		R = A;
		C = One(this->base);
		while (C + C <= B)
		{
			R += R;
			C += C;
		}
		I += R;
		B = B - C;
	}

	if ((*this).isNeg != S.isNeg)
	{
		I.isNeg = true;
	}
	if ((*this).isNeg == S.isNeg)
	{
		I.isNeg = false;
	}
	*this = I;
	return *this;
}

const HexaInt HexaInt::operator/(const HexaInt& S)const
{
	HexaInt A;
	HexaInt B;
	A = *this;
	B = S;
	A.isNeg = false;
	B.isNeg = false;

	if (A >= B)
	{
		B.isNeg = false;
		A.isNeg = false;
		HexaInt R;
		HexaInt l;
		HexaInt I;
		HexaInt C = One(this->base);

		while (A != Zero(this->base))
		{
			R = B;
			C = One(this->base);
			while (R + R <= A)
			{
				R += R;
				C += C;
			}
			I += C;
			A = A - R;
			if (A < B)
			{
				l = A;
				break;
			}
		}
		if ((*this).isNeg != S.isNeg)
		{
			I.isNeg = true;
		}
		if ((*this).isNeg == S.isNeg)
		{
			I.isNeg = false;
		}
		return I;
	}
	else if (A < B)
	{
		HexaInt I = Zero(this->base);
		return I;
	}
}
const HexaInt& HexaInt::operator/=(const HexaInt& S)
{
	HexaInt A;
	HexaInt B;
	A = *this;
	B = S;
	A.isNeg = false;
	B.isNeg = false;

	if (A >= B)
	{
		B.isNeg = false;
		A.isNeg = false;
		HexaInt R;
		HexaInt l;
		HexaInt I;
		HexaInt C = One(this->base);

		while (A != Zero(this->base))
		{
			R = B;
			C = One(this->base);
			while (R + R <= A)
			{
				R += R;
				C += C;
			}
			I += C;
			A = A - R;
			if (A < B)
			{
				l = A;
				break;
			}
		}
		if ((*this).isNeg != S.isNeg)
		{
			I.isNeg = true;
		}
		if ((*this).isNeg == S.isNeg)
		{
			I.isNeg = false;
		}
		*this = I;
		return *this;
	}
	else if (A < B)
	{
		HexaInt I = Zero(this->base);
		*this = I;
		return *this;
	}
}

const HexaInt HexaInt::operator%(const HexaInt& S)const
{
	HexaInt A = *this;
	HexaInt B = S;
	A.isNeg = false;
	B.isNeg = false;
	if (A >= B)
	{
		HexaInt R;
		HexaInt l;
		HexaInt I;
		HexaInt C = One(this->base);

		while (A != Zero(this->base))
		{
			R = B;
			C = One(this->base);
			while (R + R <= A)
			{
				R += R;
				C += C;
			}
			I += C;
			A = A - R;
			if (A < B)
			{
				l = A;
				break;
			}
		}
		return l;
	}
	if (A < B)
	{
		HexaInt I = A;
		return I;
	}
}
const HexaInt& HexaInt::operator%=(const HexaInt& S)
{
	HexaInt A = *this;
	HexaInt B = S;
	A.isNeg = false;
	B.isNeg = false;
	if (A >= B)
	{
		HexaInt R;
		HexaInt l;
		HexaInt I;
		HexaInt C = One(this->base);

		while (A != Zero(this->base))
		{
			R = B;
			C = One(this->base);
			while (R + R <= A)
			{
				R += R;
				C += C;
			}
			I += C;
			A = A - R;
			if (A < B)
			{
				l = A;
				break;
			}
		}
		*this = l;
		return *this;
	}
	if (A < B)
	{
		HexaInt I = A;
		*this = I;
		return *this;
	}
}


int HexaInt::operator[](int i) const
{
	if (i >= this->size)
	{
		return 0;
	}
	else
	{
		return this->Vs[i];
	}
}
int& HexaInt::operator[](int i)
{
	if (i >= this->size)
	{
		int t = 0;
		return t;
	}
	else
	{
		return this->Vs[i];
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const HexaInt HexaInt::add(const HexaInt& S)const
{
	HexaInt P(this->size + 1);
	int carry = 0;
	int ans = 0;
	for (int i = 0; i < P.size; i++)
	{
		ans = ((*this)[i] + S[i] + carry) % this->base;
		carry = ((*this)[i] + S[i] + carry) / this->base;

		P[i] = ans;
	}
	P.base = this->base;
	P.Trim();
	return P;
}
const HexaInt HexaInt::sub(const HexaInt& S)const
{
	HexaInt P(this->size);
	int ans = 0;
	int carry = 0;
	for (int i = 0; i < P.size; i++)
	{
		ans = ((*this)[i] - S[i] - carry) % this->base;
		carry = ((ans < 0) ? 1 : 0);
		ans = ((ans < 0) ? ans + this->base : ans);
		P[i] = ans;
	}
	P.Trim();
	P.base = this->base;
	return P;
}

bool HexaInt::LessThanQuantityWise(const HexaInt& S) const
{
	if (this->size > S.size)
	{
		return false;
	}
	else if (this->size < S.size)
	{
		return true;
	}
	for (int i = this->size - 1; i >= 0; i--)
	{
		if (this->Vs[i] > S.Vs[i])
		{
			return false;
		}
		if (this->Vs[i] < S.Vs[i])
		{
			return true;
		}
	}
	return false;
}
bool HexaInt::GreaterThanQuantityWise(const HexaInt& S) const
{
	return S.LessThanQuantityWise(*this);
}
bool HexaInt::EqualQuantityWise(const HexaInt& S) const
{
	return (!(*this).LessThanQuantityWise(S) && !(*this).GreaterThanQuantityWise(S));
}



HexaInt HexaInt::One(int n)
{
	HexaInt R(1);
	R.Vs[0] = 1;
	R.base = n;
	return R;
}
HexaInt HexaInt::Zero(int n)
{
	HexaInt R(1);
	R.Vs[0] = 0;
	R.base = n;
	return R;
}


void HexaInt::Trim()
{
	int zcount = 0;
	for (int i = this->size - 1; i >= 0; i--)
	{
		if (this->Vs[i] == 0)
		{
			zcount++;
		}
		if (this->Vs[i] != 0)
		{
			break;
		}
	}

	HexaInt P(this->size - zcount);
	for (int i = this->size - 1 - zcount, j = 0; i >= 0; i--, j++)
	{
		P.Vs[P.size - 1 - j] = this->Vs[i];
	}
	delete[]this->Vs;
	this->size = P.size;
	this->Vs = P.Vs;
	P.Vs = nullptr;
}


HexaInt::~HexaInt()
{
	delete[]this->Vs;
}